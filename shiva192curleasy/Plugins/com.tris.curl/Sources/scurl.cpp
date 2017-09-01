//-----------------------------------------------------------------------------
#include "PrecompiledHeader.h"
#include "scurl.h"
//-----------------------------------------------------------------------------
#include <vector>
#include <thread>
#include <mutex>
#include <cstdio>

/* // redefine if needed
#define CURL_MAX_WRITE_SIZE 524288
*/

extern "C" {
	#include "curl.h"
}



// lazy globals
const char * _sAI = "curl"; // target AI
const char * _sES = "onResponse"; // string event handler
const char * _sEF = "onDownload"; // file event handler

const char * _useragent = "libcurl-agent/1.0";

bool _init = false;

typedef struct {
	const std::string sID;
	S3DX::AIVariable MessageTypeConstant;
	std::string sMessage;
} curlMessage;

std::vector<curlMessage> _vCurlMessages;
std::mutex mu_vCurlResults;

std::vector<curlMessage> _vCurlFiles;
std::mutex mu_vCurlFiles;



#ifdef S3DX_DLL
	scurlAPI scurl ;
#endif


//-----------------------------------------------------------------------------
//  Stuff
//-----------------------------------------------------------------------------

size_t CurlWrite_CallbackFunc_StdString(void *contents, size_t size, size_t nmemb, std::string *s) {

	// based on https://stackoverflow.com/questions/2329571/c-libcurl-get-output-into-a-string

	size_t newLength = size*nmemb;

	{
		// SO code... seems long
		//	size_t oldLength = s->size();
		//	try {
		//		s->resize(oldLength + newLength);
		//	} catch (std::bad_alloc &e) {
		//#   pragma TODO( handle memory problem )
		//		return 0;
		//	}
		//
		//	std::copy((char*)contents, (char*)contents + newLength, s->begin() + oldLength);
		//
		//	return newLength;
	}

	// seems simpler:
	s->append((char*)contents, newLength);

	return newLength;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, void *stream) {
	size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
	return written;
}

inline void _ccustom(CURL * curl, const std::string & url, std::string & s) {
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // set URL
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirection
	curl_easy_setopt(curl, CURLOPT_USERAGENT, _useragent);
	curl_easy_setopt(curl, CURLOPT_FAILONERROR, true); // 404 detection
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, CurlWrite_CallbackFunc_StdString); // callback for stdString
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s); // pass s to callback function
}

inline void _ccustomF(CURL * curl, const std::string & url, FILE * pagefile) {
	curl_easy_setopt(curl, CURLOPT_URL, url.c_str()); // set URL
	curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // follow redirection
	curl_easy_setopt(curl, CURLOPT_USERAGENT, _useragent);
	curl_easy_setopt(curl, CURLOPT_FAILONERROR, true); // 404 detection
	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, pagefile);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
}

//-----------------------------------------------------------------------------
//  Threads
//-----------------------------------------------------------------------------

void thrEasyGetHTTP(const std::string && sID, const std::string && url) {

	auto url2 = "http://" + url; // new URL
	std::string s; // output string

	CURL * curl = curl_easy_init();
	if (curl) {
		_ccustom(curl, url2, s);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https

		auto res = curl_easy_perform(curl); // perform blocking operation
		if (res == CURLE_OK) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kWebsite, std::move(s) });
		}
		else if (res == CURLE_HTTP_RETURNED_ERROR){
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kError404, curl_easy_strerror(res) });
		}
		else {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kErrorWebsite, curl_easy_strerror(res) });
		}

		curl_easy_cleanup(curl);
	}
}

//-----------------------------------------------------------------------------

void thrEasyPostHTTP(const std::string && sID, const std::string && url, const std::string && postdata) {

	auto url2 = "http://" + url; // new URL
	std::string s; // output string

	CURL * curl = curl_easy_init();
	if (curl) {
		_ccustom(curl, url2, s);
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https

		// curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata.c_str());

		auto res = curl_easy_perform(curl); // perform blocking operation
		if (res == CURLE_OK) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kWebsite, std::move(s) });
		}
		else if (res == CURLE_HTTP_RETURNED_ERROR) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kError404, curl_easy_strerror(res) });
		}
		else if (res == CURLE_HTTP_POST_ERROR) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kErrorPost, curl_easy_strerror(res) });
		}
		else {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kErrorWebsite, curl_easy_strerror(res) });
		}

		curl_easy_cleanup(curl);
	}
}

//-----------------------------------------------------------------------------

void thrEasyGetHTTPS(const std::string && sID, const std::string && url, const bool && peerVeri, const bool && hostVeri) {

	auto url2 = "https://" + url; // new URL
	std::string s; // output string

	CURL * curl = curl_easy_init();
	if (curl) {
		_ccustom(curl, url2, s);
		
		/*
		* If you want to connect to a site who isn't using a certificate that is
		* signed by one of the certs in the CA bundle you have, you can skip the
		* verification of the server's certificate. This makes the connection
		* A LOT LESS SECURE.
		*
		* If you have a CA cert for the server stored someplace else than in the
		* default bundle, then the CURLOPT_CAPATH option might come handy for
		* you.
		*/

		if (peerVeri) curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
		else curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

		/*
		* If the site you're connecting to uses a different host name that what
		* they have mentioned in their server certificate's commonName (or
		* subjectAltName) fields, libcurl will refuse to connect. You can skip
		* this check, but this will make the connection less secure.
		*/

		if (hostVeri) curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
		else curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		auto res = curl_easy_perform(curl); // perform blocking operation
		if (res == CURLE_OK) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kWebsite, std::move(s) });
		}
		else if (res == CURLE_HTTP_RETURNED_ERROR) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kError404, curl_easy_strerror(res) });
		}
		else if (res == CURLE_SSL_CONNECT_ERROR) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kErrorSSL, curl_easy_strerror(res) });
		}
		else {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kErrorWebsite, curl_easy_strerror(res) });
		}

		/* always cleanup */
		curl_easy_cleanup(curl);
	}
}

//-----------------------------------------------------------------------------

void thrEasyPostHTTPS(const std::string && sID, const std::string && url, const bool && peerVeri, const bool && hostVeri, const std::string && postdata) {

	auto url2 = "https://" + url; // new URL
	std::string s; // output string

	CURL * curl = curl_easy_init();
	if (curl) {
		_ccustom(curl, url2, s);
		/*
		* If you want to connect to a site who isn't using a certificate that is
		* signed by one of the certs in the CA bundle you have, you can skip the
		* verification of the server's certificate. This makes the connection
		* A LOT LESS SECURE.
		*
		* If you have a CA cert for the server stored someplace else than in the
		* default bundle, then the CURLOPT_CAPATH option might come handy for
		* you.
		*/

		if (peerVeri) curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
		else curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

		/*
		* If the site you're connecting to uses a different host name that what
		* they have mentioned in their server certificate's commonName (or
		* subjectAltName) fields, libcurl will refuse to connect. You can skip
		* this check, but this will make the connection less secure.
		*/

		if (hostVeri) curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
		else curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postdata.c_str());

		auto res = curl_easy_perform(curl); // perform blocking operation
		if (res == CURLE_OK) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kWebsite, std::move(s) });
		}
		else if (res == CURLE_HTTP_RETURNED_ERROR) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kError404, curl_easy_strerror(res) });
		}
		else if (res == CURLE_SSL_CONNECT_ERROR) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kErrorSSL, curl_easy_strerror(res) });
		}
		else if (res == CURLE_HTTP_POST_ERROR) {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kErrorPost, curl_easy_strerror(res) });
		}
		else {
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			_vCurlMessages.push_back({ std::move(sID), scurl.kErrorWebsite, curl_easy_strerror(res) });
		}

		curl_easy_cleanup(curl);
	}
}

//-----------------------------------------------------------------------------

void thrDownloadHTTP(const std::string && sID, const std::string && url, const std::string && sTargetFile) {

	auto url2 = "http://" + url; // new URL

	CURL * curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L); //only for https
		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L); //only for https

		FILE *pagefile = fopen(sTargetFile.c_str(), "wb"); // output file
		_ccustomF(curl, url2, pagefile);

		if (pagefile) {
			auto res = curl_easy_perform(curl); // perform blocking operation

			if (res == CURLE_OK) {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kFile, "File transfer completed successfully." });
			}
			else if (res == CURLE_PARTIAL_FILE) {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFilePartial, curl_easy_strerror(res) });
			}
			else if (res == CURLE_WRITE_ERROR) {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFileWrite, curl_easy_strerror(res) });
			}
			else if (res == CURLE_FILESIZE_EXCEEDED) {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFileSize, curl_easy_strerror(res) });
			}
			else {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFile, curl_easy_strerror(res) });
			}

			fclose(pagefile);
		}
		else {
			std::lock_guard<std::mutex> _(mu_vCurlFiles);
			_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFileWrite, "Pagefile WB fopen failed." });
		}
		
		curl_easy_cleanup(curl);
	}
}

//-----------------------------------------------------------------------------

void thrDownloadHTTPS(const std::string && sID, const std::string && url, const bool && peerVeri, const bool && hostVeri, const std::string && sTargetFile) {

	auto url2 = "https://" + url; // new URL

	CURL * curl = curl_easy_init();
	if (curl) {

		/*
		* If you want to connect to a site who isn't using a certificate that is
		* signed by one of the certs in the CA bundle you have, you can skip the
		* verification of the server's certificate. This makes the connection
		* A LOT LESS SECURE.
		*
		* If you have a CA cert for the server stored someplace else than in the
		* default bundle, then the CURLOPT_CAPATH option might come handy for
		* you.
		*/

		if (peerVeri) curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
		else curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

		/*
		* If the site you're connecting to uses a different host name that what
		* they have mentioned in their server certificate's commonName (or
		* subjectAltName) fields, libcurl will refuse to connect. You can skip
		* this check, but this will make the connection less secure.
		*/

		if (hostVeri) curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 1L);
		else curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

		FILE *pagefile = fopen(sTargetFile.c_str(), "wb"); // output file
		_ccustomF(curl, url2, pagefile);

		if (pagefile) {
			auto res = curl_easy_perform(curl); // perform blocking operation

			if (res == CURLE_OK) {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kFile, "File transfer completed successfully." });
			}
			else if (res == CURLE_PARTIAL_FILE) {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFilePartial, curl_easy_strerror(res) });
			}
			else if (res == CURLE_WRITE_ERROR) {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFileWrite, curl_easy_strerror(res) });
			}
			else if (res == CURLE_FILESIZE_EXCEEDED) {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFileSize, curl_easy_strerror(res) });
			}
			else if (res == CURLE_SSL_CONNECT_ERROR) {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kErrorSSL, curl_easy_strerror(res) });
			}
			else {
				std::lock_guard<std::mutex> _(mu_vCurlFiles);
				_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFile, curl_easy_strerror(res) });
			}

			fclose(pagefile);
		}
		else {
			std::lock_guard<std::mutex> _(mu_vCurlFiles);
			_vCurlFiles.push_back({ std::move(sID), scurl.kErrorFileWrite, "Pagefile WB fopen failed." });
		}

		curl_easy_cleanup(curl);
	}
}

//-----------------------------------------------------------------------------
//  Callbacks
//-----------------------------------------------------------------------------

int Callback_scurl_messageLoop ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.messageLoop" ) ;

	if (!_init) {
		; // do nothing
	} else {
		{
			std::lock_guard<std::mutex> _(mu_vCurlResults);
			if (!_vCurlMessages.empty()) {

				for (auto & i : _vCurlMessages)
					S3DX::user.sendEvent(S3DX::application.getCurrentUser(), _sAI, _sES, i.sID.c_str(), i.MessageTypeConstant, i.sMessage.c_str());

				_vCurlMessages.clear();
			}
		}
		{
			std::lock_guard<std::mutex> _(mu_vCurlFiles);
			if (!_vCurlFiles.empty()) {

				for (auto & i : _vCurlFiles)
					S3DX::user.sendEvent(S3DX::application.getCurrentUser(), _sAI, _sEF, i.sID.c_str(), i.MessageTypeConstant, i.sMessage.c_str());

				_vCurlFiles.clear();
			}
		}
	}

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_scurl_globalShutdown ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.globalShutdown" ) ;

	curl_global_cleanup();

    S3DX_API_PROFILING_STOP( ) ;
    return 0;
}

//-----------------------------------------------------------------------------

int Callback_scurl_init ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.init" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sAIModel      = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sEventStrings = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sEventFiles   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	auto sAI = sAIModel.GetStringValue();
	auto sES = sEventStrings.GetStringValue();
	auto sEF = sEventFiles.GetStringValue();


	if ((sAI == nullptr) || (sAI[0] == '\0'))
		; // stay with default
	else
		_sAI = sAI;

	if ((sES == nullptr) || (sES[0] == '\0'))
		; // stay with default
	else
		_sES = sES;

	if ((sEF == nullptr) || (sEF[0] == '\0'))
		; // stay with default
	else
		_sEF = sEF;

	auto res = curl_global_init(CURL_GLOBAL_DEFAULT);
	if (CURLcode::CURLE_OK == res) {
		_vCurlMessages.reserve(12);
		_init = true;
		bOK.SetBooleanValue(true);
	}
	else {
		bOK.SetBooleanValue(false);
		S3DX::user.sendEvent(S3DX::application.getCurrentUser(), _sAI, _sES, scurl.kErrorInit, curl_easy_strerror(res));
	}


    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_scurl_easyGetHTTP ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.easyGetHTTP" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	if (!_init) {
		bOK.SetBooleanValue(false);
	}
	else {
		std::thread thr(thrEasyGetHTTP, sID.GetStringValue(), sURL.GetStringValue());
		thr.detach();
		bOK.SetBooleanValue(true);
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_scurl_easyPostHTTP ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.easyPostHTTP" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL  = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sData = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	if (!_init) {
		bOK.SetBooleanValue(false);
	}
	else {
		std::thread thr(thrEasyPostHTTP, sID.GetStringValue(), sURL.GetStringValue(), sData.GetStringValue());
		thr.detach();
		bOK.SetBooleanValue(true);
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_scurl_easyGetHTTPS ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.easyGetHTTPS" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID                       = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL                      = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipPeerVerification     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipHostnameVerification = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	if (!_init) {
		bOK.SetBooleanValue(false);
	}
	else {
		std::thread thr(thrEasyGetHTTPS, sID.GetStringValue(), sURL.GetStringValue(), bSkipPeerVerification.GetBooleanValue(), bSkipHostnameVerification.GetBooleanValue());
		thr.detach();
		bOK.SetBooleanValue(true);
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_scurl_easyPostHTTPS ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.easyPostHTTPS" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID                       = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL                      = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipPeerVerification     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipHostnameVerification = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	S3DX::AIVariable sPostdata				   = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
	
    // Output Parameters 
    S3DX::AIVariable bOK ;


	if (!_init) {
		bOK.SetBooleanValue(false);
	}
	else {
		std::thread thr(thrEasyPostHTTPS, sID.GetStringValue(), sURL.GetStringValue(), bSkipPeerVerification.GetBooleanValue(), bSkipHostnameVerification.GetBooleanValue(), sPostdata.GetStringValue());
		thr.detach();
		bOK.SetBooleanValue(true);
	}


    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_scurl_easyDownloadHTTP ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.easyDownloadHTTP" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID         = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL        = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sTargetFile = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	if (!_init) {
		bOK.SetBooleanValue(false);
	}
	else {
		std::thread thr(thrDownloadHTTP, sID.GetStringValue(), sURL.GetStringValue(), sTargetFile.GetStringValue());
		thr.detach();
		bOK.SetBooleanValue(true);
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_scurl_easyDownloadHTTPS ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.easyDownloadHTTPS" ) ;

    // Input Parameters 
    int iInputCount = 0 ;
    S3DX::AIVariable sID                       = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL                      = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sTargetFile               = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipPeerVerification     = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipHostnameVerification = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

    // Output Parameters 
    S3DX::AIVariable bOK ;

	if (!_init) {
		bOK.SetBooleanValue(false);
	}
	else {
		std::thread thr(thrDownloadHTTPS, sID.GetStringValue(), sURL.GetStringValue(), bSkipPeerVerification.GetBooleanValue(), bSkipHostnameVerification.GetBooleanValue(), sTargetFile.GetStringValue());
		thr.detach();
		bOK.SetBooleanValue(true);
	}

    // Return output Parameters 
    int iReturnCount = 0 ;
    _pOut[iReturnCount++] = bOK ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------
//  Constructor / Destructor
//-----------------------------------------------------------------------------

scurlPackage::scurlPackage ( )
{
#ifdef S3DX_DLL
    scurl.kErrorPost          = 7 ; 
    scurl.kErrorFile          = 5 ; 
    scurl.kErrorSSL           = 6 ; 
    scurl.kErrorFilePartial   = 0 ; 
    scurl.kErrorFileRetrieval = 1 ; 
    scurl.kErrorFileWrite     = 2 ; 
    scurl.kErrorFileSize      = 3 ; 
    scurl.kFile               = 4 ; 
    scurl.pfn_scurl_messageLoop       = Callback_scurl_messageLoop       ;
    scurl.kErrorWebsite = 3 ; 
    scurl.pfn_scurl_globalShutdown    = Callback_scurl_globalShutdown    ;
    scurl.kErrorInit = 0 ; 
    scurl.kError404  = 1 ; 
    scurl.kWebsite   = 2 ; 
    scurl.pfn_scurl_init              = Callback_scurl_init              ;
    scurl.pfn_scurl_easyGetHTTP       = Callback_scurl_easyGetHTTP       ;
    scurl.pfn_scurl_easyPostHTTP      = Callback_scurl_easyPostHTTP      ;
    scurl.pfn_scurl_easyGetHTTPS      = Callback_scurl_easyGetHTTPS      ;
    scurl.pfn_scurl_easyPostHTTPS     = Callback_scurl_easyPostHTTPS     ;
    scurl.pfn_scurl_easyDownloadHTTP  = Callback_scurl_easyDownloadHTTP  ;
    scurl.pfn_scurl_easyDownloadHTTPS = Callback_scurl_easyDownloadHTTPS ;
	
#endif
}

//-----------------------------------------------------------------------------

scurlPackage::~scurlPackage ( )
{

}

//-----------------------------------------------------------------------------
//  Functions table
//-----------------------------------------------------------------------------

static S3DX::AIFunction aMyFunctions [ ] =
{
    { "messageLoop"      , Callback_scurl_messageLoop      , ""   , ""                                                                        , "for onEnterFrame(), clears message vector and dispatches events"                                                          , 0 }, 
    { "globalShutdown"   , Callback_scurl_globalShutdown   , ""   , ""                                                                        , "always call onApplicationWillQuit"                                                                                        , 0 }, 
    { "init"             , Callback_scurl_init             , "bOK", "sAIModel, sEventStrings, sEventFiles"                                    , "init plugin with target AIModel and Events"                                                                               , 0 }, 
    { "easyGetHTTP"      , Callback_scurl_easyGetHTTP      , "bOK", "sID, sURL"                                                               , "simple HTTP GET request, result string over Event handler"                                                                , 0 }, 
    { "easyPostHTTP"     , Callback_scurl_easyPostHTTP     , "bOK", "sID, sURL, sData"                                                        , "simple HTTP POST request, result string over Event handler"                                                               , 0 }, 
    { "easyGetHTTPS"     , Callback_scurl_easyGetHTTPS     , "bOK", "sID, sURL, bSkipPeerVerification, bSkipHostnameVerification"             , "simple HTTPS GET request, result string over Event handler. Skipping verification makes the connection much less secure!" , 0 }, 
    { "easyPostHTTPS"    , Callback_scurl_easyPostHTTPS    , "bOK", "sID, sURL, bSkipPeerVerification, bSkipHostnameVerification, sPostdata"  , "simple HTTPS POST request, result string over Event handler. Skipping verification makes the connection much less secure!", 0 }, 
    { "easyDownloadHTTP" , Callback_scurl_easyDownloadHTTP , "bOK", "sID, sURL, sTargetFile"                                                  , "download file over HTTP, result string over Event handler"                                                                , 0 }, 
    { "easyDownloadHTTPS", Callback_scurl_easyDownloadHTTPS, "bOK", "sID, sURL, sTargetFile, bSkipPeerVerification, bSkipHostnameVerification", "download file over HTTPs, result string over Event handler. Skipping verification makes the connection much less secure!" , 0 }    
    //{ NULL, NULL, NULL, NULL, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Constants table
//-----------------------------------------------------------------------------

static S3DX::AIConstant aMyConstants [ ] =
{
    { "kErrorPost"         , 7, "HTTP POST error"                              , 0 }, 
    { "kErrorFile"         , 5, "general file download error"                  , 0 }, 
    { "kErrorSSL"          , 6, "SSL handshake error"                          , 0 }, 
    { "kErrorFilePartial"  , 0, "file transfer longer or shorter than expected", 0 }, 
    { "kErrorFileRetrieval", 1, "file retrieval / zero byte error"             , 0 }, 
    { "kErrorFileWrite"    , 2, "file write error"                             , 0 }, 
    { "kErrorFileSize"     , 3, "filesize exceeded"                            , 0 }, 
    { "kFile"              , 4, "file download OK"                             , 0 }, 
    { "kErrorWebsite", 3, "error in the web thread"      , 0 }, 
    { "kErrorInit", 0, "error during init()"          , 0 }, 
    { "kError404" , 1, "page not found"               , 0 }, 
    { "kWebsite"  , 2, "regular response from website", 0 }	
    //{ NULL, 0, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Accessors
//-----------------------------------------------------------------------------

const char *scurlPackage::GetName ( ) const
{
    return "scurl" ;
}

//-----------------------------------------------------------------------------

S3DX::uint32 scurlPackage::GetFunctionCount ( ) const
{
	if ( aMyFunctions[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyFunctions ) / sizeof( S3DX::AIFunction ) ;
	}
}

//-----------------------------------------------------------------------------

S3DX::uint32 scurlPackage::GetConstantCount ( ) const
{
	if ( aMyConstants[0].pName == NULL )
	{
		return 0 ;
	}
	else
	{
		return sizeof( aMyConstants ) / sizeof( S3DX::AIConstant ) ;
	}
}

//-----------------------------------------------------------------------------

const S3DX::AIFunction *scurlPackage::GetFunctionAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyFunctions[ _iIndex ] ;
}

//-----------------------------------------------------------------------------

const S3DX::AIConstant *scurlPackage::GetConstantAt ( S3DX::uint32 _iIndex ) const
{
    return &aMyConstants[ _iIndex ] ;
}
