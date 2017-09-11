//-----------------------------------------------------------------------------
#include "PrecompiledHeader.h"
#include "scurl.h"
//-----------------------------------------------------------------------------
#include <vector>
#include <thread>
#include <mutex>
#include <cstdio>
#include <string>

/* // redefine if needed
#define CURL_MAX_WRITE_SIZE 524288
*/

// Windows includes
#ifdef _WINDOWS
    extern "C" {
        #include "curl.h"
    }
#endif // _WINDOWS




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

#ifdef _WINDOWS

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

#endif // _WINDOWS



#ifdef __MAC__

inline const int HTTPstatusCode (const std::string & URL) {
    auto check = "curl -s -o /dev/null -I -L -w \"%{http_code}\" " + URL;
    
    FILE* lsofFile_p (popen(check.c_str(), "r"));
    if (!lsofFile_p) return 0;
    char buffer[4];
    char *line_p = fgets(buffer, sizeof(buffer), lsofFile_p);
    pclose(lsofFile_p);
    
    return atoi(line_p);
}

inline void statusCodeText (const std::string & URL, std::string & returnStr) {

    auto check = "curl -s -f -o /dev/null -I -L --show-error " + URL + " 2>&1";
    char buffer[256];
    
    FILE * stream = popen(check.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, sizeof(buffer), stream) != nullptr) returnStr.append(buffer);
        pclose(stream);
    }
    else {
        returnStr.append("Stream error!");
    }
}

inline void performCURL(const std::string & request, std::string & returnStr) {
    
    char buffer[2048];
    
    FILE * stream = popen(request.c_str(), "r");
    if (stream) {
        while (!feof(stream))
            if (fgets(buffer, sizeof(buffer), stream) != nullptr) returnStr.append(buffer);
        pclose(stream);
    }
    else {
        returnStr.append("Stream error!");
    }
}

inline bool doesFileExist (const std::string & URL) {
    auto check = "if curl -o /dev/null -s --fail -I -L " + URL + "; then echo YES ; else echo NO ; fi";
    
    FILE * lsofFile_p (popen(check.c_str(), "r"));
    if (!lsofFile_p) return false;
    char buffer[4]; // YES plus null terminator
    char * line_p = fgets(buffer, sizeof(buffer), lsofFile_p);
    pclose(lsofFile_p);
    
    std::string result(line_p);
    if (result == "YES") return true;
    else return false;
}

#endif // __MAC__

//-----------------------------------------------------------------------------
//  Threads WINDOWS
//-----------------------------------------------------------------------------

#ifdef _WINDOWS

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
		else if (res == CURLE_HTTP_RETURNED_ERROR) {
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
	
#endif // _WINDOWS
	
//-----------------------------------------------------------------------------
//  Threads MAC
//-----------------------------------------------------------------------------

#ifdef __MAC__

void thrEasyGetHTTP(const std::string && sID, const std::string && url) {
    
    std::string url2 ("http://" + url); // new URL
    auto res = HTTPstatusCode(url2);
    
    if (res == 200) {
        // all OK
        std::string url3 ("curl --user-agent \""); // new URL
        url3 +=  _useragent;
        url3 += "\" -L ";
        url3 += url2;
        
        std::string s;
        performCURL(url3, s);
        std::lock_guard<std::mutex> _(mu_vCurlResults);
//        _vCurlMessages.push_back({ std::move(sID), scurl.kWebsite, std::move(s) });
        _vCurlMessages.push_back({ std::move(sID), 2, std::move(s) });
    }
    else if (res == 404) {
        std::lock_guard<std::mutex> _(mu_vCurlResults);
//        _vCurlMessages.push_back({ std::move(sID), scurl.kError404, "404 Error" });
        _vCurlMessages.push_back({ std::move(sID), 1, "404 Error" });
    }
    else {
        // general error
        std::string err = "";
        statusCodeText(url2, err);
        std::lock_guard<std::mutex> _(mu_vCurlResults);
//        _vCurlMessages.push_back({ std::move(sID), scurl.kErrorWebsite, err.c_str() });
        _vCurlMessages.push_back({ std::move(sID), 3, std::move(err) });
    }
}

//-----------------------------------------------------------------------------

void thrEasyPostHTTP(const std::string && sID, const std::string && url, const std::string && pdata) {

    std::string url2 ("http://" + url); // new URL
    
    std::string url3 ("curl --user-agent \""); // new URL
    url3 +=  _useragent;
    url3 += "\" ";
    url3 += "--data \"" + pdata + "\" ";
    url3 += "-f --show-error -L http://" + url;
        
    std::string s;
    performCURL(url3, s);
    
    // I can't seem to find a good error check on POST requests for the CLI version on CURL,
    // so this will have to do...
    
    if (!s.empty()) {
        std::lock_guard<std::mutex> _(mu_vCurlResults);
        //        _vCurlMessages.push_back({ std::move(sID), scurl.kWebsite, std::move(s) });
        _vCurlMessages.push_back({ std::move(sID), 2, std::move(s) });
    }
    else {
        std::lock_guard<std::mutex> _(mu_vCurlResults);
        //        _vCurlMessages.push_back({ std::move(sID), scurl.kErrorWebsite, err.c_str() });
        _vCurlMessages.push_back({ std::move(sID), 3, "Empty return string!" });
    }
}

//-----------------------------------------------------------------------------

void thrEasyGetHTTPS(const std::string && sID, const std::string && url, const bool && peerVeri, const bool && hostVeri) {
    
    std::string url2 ("https://" + url); // new URL
    auto res = HTTPstatusCode(url2);
    
    if (res == 200) {
        // all OK
        
        std::string url3 ("curl --user-agent \""); // new URL
        url3 +=  _useragent;
        url3 += "\" ";
        url3 += "-L https://" + url;
        
        // MISSING:
        // CURLOPT_SSL_VERIFYPEER
        // CURLOPT_SSL_VERIFYHOST
        
        std::string s;
        performCURL(url3, s);
        std::lock_guard<std::mutex> _(mu_vCurlResults);
//        _vCurlMessages.push_back({ std::move(sID), scurl.kWebsite, std::move(s) });
        _vCurlMessages.push_back({ std::move(sID), 2, std::move(s) });
    }
    else if (res == 404) {
        std::lock_guard<std::mutex> _(mu_vCurlResults);
//        _vCurlMessages.push_back({ std::move(sID), scurl.kError404, "404 Error" });
        _vCurlMessages.push_back({ std::move(sID), 1, "404 Error" });
    }
    // MISSING: SSL_CONNECT_ERROR
    else {
        // general error
        std::string err;
        statusCodeText(url2, err);
        std::lock_guard<std::mutex> _(mu_vCurlResults);
        //        _vCurlMessages.push_back({ std::move(sID), scurl.kErrorWebsite, err.c_str() });
        _vCurlMessages.push_back({ std::move(sID), 3, std::move(err) });
    }
}

//-----------------------------------------------------------------------------

void thrEasyPostHTTPS(const std::string && sID, const std::string && url, const bool && peerVeri, const bool && hostVeri, const std::string && postdata) {

    std::string url2 ("https://" + url); // new URL
    auto res = HTTPstatusCode(url2);
    
    if (res == 200) {
        // all OK
        
        std::string url3 ("curl --user-agent \""); // new URL
        url3 +=  _useragent;
        url3 += "\" ";
        url3 += "--data \"" + postdata + "\" ";
        url3 += "-L https://" + url;
        
        // MISSING:
        // CURLOPT_SSL_VERIFYPEER
        // CURLOPT_SSL_VERIFYHOST
        
        std::string s;
        performCURL(url3, s);
        std::lock_guard<std::mutex> _(mu_vCurlResults);
//        _vCurlMessages.push_back({ std::move(sID), scurl.kWebsite, std::move(s) });
        _vCurlMessages.push_back({ std::move(sID), 2, std::move(s) });
    }
    else if (res == 404) {
        std::lock_guard<std::mutex> _(mu_vCurlResults);
//        _vCurlMessages.push_back({ std::move(sID), scurl.kError404, "404 Error" });
        _vCurlMessages.push_back({ std::move(sID), 1, "404 Error" });
    }
    // MISSING: SSL_CONNECT_ERROR
    else {
        // general error
        std::string err;
        statusCodeText(url2, err);
        std::lock_guard<std::mutex> _(mu_vCurlResults);
        //        _vCurlMessages.push_back({ std::move(sID), scurl.kErrorWebsite, err.c_str() });
        _vCurlMessages.push_back({ std::move(sID), 3, std::move(err) });
    }
}

//-----------------------------------------------------------------------------

void thrDownloadHTTP(const std::string && sID, const std::string && url, const std::string && sTargetFile) {

	auto url2 = "http://" + url; // new URL
    
    std::string url3 ("curl ");
    url3 += "-s --fail -o \"" + sTargetFile + "\" ";
    url3 += url2;
    
    if (doesFileExist(url2)) {
        std::string s;
        performCURL(url3, s);
        std::lock_guard<std::mutex> _(mu_vCurlFiles);
//      _vCurlFiles.push_back({ std::move(sID), scurl.kFile, "File transfer completed successfully." });
        _vCurlFiles.push_back({ std::move(sID), 4, std::move(s) });
    }
    // TODO: other file errors
    else {
        std::lock_guard<std::mutex> _(mu_vCurlFiles);
        // _vCurlFiles.push_back({ std::move(sID), scurl.kErrorFile, curl_easy_strerror(res) });
        _vCurlFiles.push_back({ std::move(sID), 5, "General file download error!" });
    }
}

//-----------------------------------------------------------------------------

void thrDownloadHTTPS(const std::string && sID, const std::string && url, const bool && peerVeri, const bool && hostVeri, const std::string && sTargetFile) {

	auto url2 = "https://" + url; // new URL
    
    std::string url3 ("curl ");
    url3 += "-s --fail -o \"" + sTargetFile + "\" ";
    url3 += url2;
    // TODO: SSL
    // CURLOPT_SSL_VERIFYPEER
    // CURLOPT_SSL_VERIFYHOST
    
    if (doesFileExist(url2)) {
        std::string s;
        performCURL(url3, s);
        std::lock_guard<std::mutex> _(mu_vCurlFiles);
        //      _vCurlFiles.push_back({ std::move(sID), scurl.kFile, "File transfer completed successfully." });
        _vCurlFiles.push_back({ std::move(sID), 4, std::move(s) });
    }
    // TODO: other file errors
    else {
        std::lock_guard<std::mutex> _(mu_vCurlFiles);
        // _vCurlFiles.push_back({ std::move(sID), scurl.kErrorFile, curl_easy_strerror(res) });
        _vCurlFiles.push_back({ std::move(sID), 5, "General file download error!" });
    }
}

#endif // __MAC__

//-----------------------------------------------------------------------------
//  Callbacks ALL OSes
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------

int Callback_scurl_messageLoop ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.messageLoop" ) ;

    // Input Parameters
    int iInputCount = 0 ;

    // Output Parameters 

	if (!_init) {
		; // do nothing
	}
	else {
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

    // Return output Parameters 
    int iReturnCount = 0 ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_scurl_globalShutdown ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.globalShutdown" ) ;

    // Input Parameters
    int iInputCount = 0 ;

    // Output Parameters 

#ifdef _WINDOWS
	curl_global_cleanup();
#endif // _WINDOWS

	// no shutdown needed for mac

    // Return output Parameters 
    int iReturnCount = 0 ;

    S3DX_API_PROFILING_STOP( ) ;
    return iReturnCount;
}

//-----------------------------------------------------------------------------

int Callback_scurl_init ( int _iInCount, const S3DX::AIVariable *_pIn, S3DX::AIVariable *_pOut )
{
    S3DX_API_PROFILING_START( "scurl.init" ) ;

    // Input Parameters
    int iInputCount = 0 ;
    S3DX::AIVariable sAIModel = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sEventStrings = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sEventFiles = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

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

#ifdef _WINDOWS
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
#endif // _WINDOWS

#ifdef __MAC__
	// no curl init needed
    _vCurlMessages.reserve(12);
    _init = true;
    bOK.SetBooleanValue(true);
#endif // __MAC__


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
    S3DX::AIVariable sID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
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
    S3DX::AIVariable sID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
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
    S3DX::AIVariable sID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipPeerVerification = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
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
    S3DX::AIVariable sID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipPeerVerification = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipHostnameVerification = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sPostdata = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;

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
    S3DX::AIVariable sID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
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
    S3DX::AIVariable sID = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sURL = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable sTargetFile = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
    S3DX::AIVariable bSkipPeerVerification = ( iInputCount < _iInCount ) ? _pIn[iInputCount++] : S3DX::AIVariable ( ) ;
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
	
    scurl.pfn_scurl_messageLoop = Callback_scurl_messageLoop ;
    scurl.pfn_scurl_globalShutdown = Callback_scurl_globalShutdown ;
    scurl.pfn_scurl_init = Callback_scurl_init ;
    scurl.pfn_scurl_easyGetHTTP = Callback_scurl_easyGetHTTP ;
    scurl.pfn_scurl_easyPostHTTP = Callback_scurl_easyPostHTTP ;
    scurl.pfn_scurl_easyGetHTTPS = Callback_scurl_easyGetHTTPS ;
    scurl.pfn_scurl_easyPostHTTPS = Callback_scurl_easyPostHTTPS ;
    scurl.pfn_scurl_easyDownloadHTTP = Callback_scurl_easyDownloadHTTP ;
    scurl.pfn_scurl_easyDownloadHTTPS = Callback_scurl_easyDownloadHTTPS ;
    scurl.kErrorPost = 7 ;
    scurl.kErrorFile = 5 ;
    scurl.kErrorSSL = 6 ;
    scurl.kErrorFilePartial = 0 ;
    scurl.kErrorFileRetrieval = 1 ;
    scurl.kErrorFileWrite = 2 ;
    scurl.kErrorFileSize = 3 ;
    scurl.kFile = 4 ;
    scurl.kErrorWebsite = 3 ;
    scurl.kErrorInit = 0 ;
    scurl.kError404 = 1 ;
    scurl.kWebsite = 2 ;

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
    { "messageLoop", Callback_scurl_messageLoop, "", "", "cURL thread message dispatcher", 0 },
    { "globalShutdown", Callback_scurl_globalShutdown, "", "", "memory sanitizer", 0 },
    { "init", Callback_scurl_init, "bOK", "sAIModel, sEventStrings, sEventFiles", "init plugin and define handler names for string / file events", 0 },
    { "easyGetHTTP", Callback_scurl_easyGetHTTP, "bOK", "sID, sURL", "GET request, result in string event handler", 0 },
    { "easyPostHTTP", Callback_scurl_easyPostHTTP, "bOK", "sID, sURL, sData", "POST request, result in string event handler", 0 },
    { "easyGetHTTPS", Callback_scurl_easyGetHTTPS, "bOK", "sID, sURL, bSkipPeerVerification, bSkipHostnameVerification", "GET request over SSL, result in string event handler", 0 },
    { "easyPostHTTPS", Callback_scurl_easyPostHTTPS, "bOK", "sID, sURL, bSkipPeerVerification, bSkipHostnameVerification, sPostdata", "POST request over SSL, result in string event handler", 0 },
    { "easyDownloadHTTP", Callback_scurl_easyDownloadHTTP, "bOK", "sID, sURL, sTargetFile", "file download request, result in file event handler", 0 },
    { "easyDownloadHTTPS", Callback_scurl_easyDownloadHTTPS, "bOK", "sID, sURL, sTargetFile, bSkipPeerVerification, bSkipHostnameVerification", "file download request over SSL, result in file event handler", 0 }
    //{ NULL, NULL, NULL, NULL, NULL, 0}
} ;

//-----------------------------------------------------------------------------
//  Constants table
//-----------------------------------------------------------------------------

static S3DX::AIConstant aMyConstants [ ] =
{
	{ "kErrorPost", 7, "POST error", 0 },
    { "kErrorFile", 5, "general file download error", 0 },
    { "kErrorSSL", 6, "SSL handshake error", 0 },
    { "kErrorFilePartial", 0, "file download shorter than expected", 0 },
    { "kErrorFileRetrieval", 1, "zero byte error", 0 },
    { "kErrorFileWrite", 2, "file write error", 0 },
    { "kErrorFileSize", 3, "file too big", 0 },
    { "kFile", 4, "file download OK", 0 },
    { "kErrorWebsite", 3, "error in web thread", 0 },
    { "kErrorInit", 0, "error during init()", 0 },
    { "kError404", 1, "page not found", 0 },
    { "kWebsite", 2, "website response OK", 0 }
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
