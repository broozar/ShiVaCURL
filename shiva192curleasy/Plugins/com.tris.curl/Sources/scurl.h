//-----------------------------------------------------------------------------
#ifndef __scurl_h__
#define __scurl_h__
//-----------------------------------------------------------------------------
#include "S3DXAIPackage.h"
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Package declaration
//-----------------------------------------------------------------------------
class scurlPackage : public S3DX::AIPackage
{
public :

    //-------------------------------------------------------------------------
    //  Constructor / Destructor
	//-------------------------------------------------------------------------

	scurlPackage         ( ) ;
                               ~scurlPackage         ( ) ;

	//-------------------------------------------------------------------------
    //  Accessors
	//-------------------------------------------------------------------------

    const   char               *GetName             ( ) const ;
            S3DX::uint32        GetFunctionCount    ( ) const ;
            S3DX::uint32        GetConstantCount    ( ) const ;
    const   S3DX::AIFunction   *GetFunctionAt       ( S3DX::uint32 _iIndex ) const ;
    const   S3DX::AIConstant   *GetConstantAt       ( S3DX::uint32 _iIndex ) const ;

} ;

//-----------------------------------------------------------------------------
// Package API declaration
//-----------------------------------------------------------------------------
class scurlAPI
{
public :

    //-------------------------------------------------------------------------
    //  API Constructor
	//-------------------------------------------------------------------------
                                scurlAPI       ( ) 
                                {
                                    pfn_scurl_messageLoop       = NULL ;
                                    pfn_scurl_globalShutdown    = NULL ;
                                    pfn_scurl_init              = NULL ;
                                    pfn_scurl_easyGetHTTP       = NULL ;
                                    pfn_scurl_easyPostHTTP      = NULL ;
                                    pfn_scurl_easyGetHTTPS      = NULL ;
                                    pfn_scurl_easyPostHTTPS     = NULL ;
                                    pfn_scurl_easyDownloadHTTP  = NULL ;
                                    pfn_scurl_easyDownloadHTTPS = NULL ;

                                }

	//-------------------------------------------------------------------------
	//  API Callbacks 
	//-------------------------------------------------------------------------

    S3DX::AICallback        pfn_scurl_messageLoop ;
    S3DX::AICallback        pfn_scurl_globalShutdown ;
    S3DX::AICallback        pfn_scurl_init ;
    S3DX::AICallback        pfn_scurl_easyGetHTTP ;
    S3DX::AICallback        pfn_scurl_easyPostHTTP ;
    S3DX::AICallback        pfn_scurl_easyGetHTTPS ;
    S3DX::AICallback        pfn_scurl_easyPostHTTPS ;
    S3DX::AICallback        pfn_scurl_easyDownloadHTTP ;
    S3DX::AICallback        pfn_scurl_easyDownloadHTTPS ;

	//-------------------------------------------------------------------------
	//  API Functions 
	//-------------------------------------------------------------------------

    inline void                 messageLoop       (  ) { if ( pfn_scurl_messageLoop ) pfn_scurl_messageLoop ( 0, NULL, NULL );  }
    inline void                 globalShutdown    (  ) { if ( pfn_scurl_globalShutdown ) pfn_scurl_globalShutdown ( 0, NULL, NULL );  }
    inline S3DX::AIVariable     init              ( const S3DX::AIVariable& sAIModel, const S3DX::AIVariable& sEventStrings, const S3DX::AIVariable& sEventFiles ) { S3DX_DECLARE_VIN_03( sAIModel, sEventStrings, sEventFiles ) ; S3DX::AIVariable vOut ; if ( pfn_scurl_init ) pfn_scurl_init ( 3, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     easyGetHTTP       ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sURL ) { S3DX_DECLARE_VIN_02( sID, sURL ) ; S3DX::AIVariable vOut ; if ( pfn_scurl_easyGetHTTP ) pfn_scurl_easyGetHTTP ( 2, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     easyPostHTTP      ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sURL, const S3DX::AIVariable& sData ) { S3DX_DECLARE_VIN_03( sID, sURL, sData ) ; S3DX::AIVariable vOut ; if ( pfn_scurl_easyPostHTTP ) pfn_scurl_easyPostHTTP ( 3, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     easyGetHTTPS      ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sURL, const S3DX::AIVariable& bSkipPeerVerification, const S3DX::AIVariable& bSkipHostnameVerification ) { S3DX_DECLARE_VIN_04( sID, sURL, bSkipPeerVerification, bSkipHostnameVerification ) ; S3DX::AIVariable vOut ; if ( pfn_scurl_easyGetHTTPS ) pfn_scurl_easyGetHTTPS ( 4, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     easyPostHTTPS     ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sURL, const S3DX::AIVariable& bSkipPeerVerification, const S3DX::AIVariable& bSkipHostnameVerification, const S3DX::AIVariable& sPostdata ) { S3DX_DECLARE_VIN_05( sID, sURL, bSkipPeerVerification, bSkipHostnameVerification, sPostdata ) ; S3DX::AIVariable vOut ; if ( pfn_scurl_easyPostHTTPS ) pfn_scurl_easyPostHTTPS ( 5, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     easyDownloadHTTP  ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sURL, const S3DX::AIVariable& sTargetFile ) { S3DX_DECLARE_VIN_03( sID, sURL, sTargetFile ) ; S3DX::AIVariable vOut ; if ( pfn_scurl_easyDownloadHTTP ) pfn_scurl_easyDownloadHTTP ( 3, vIn, &vOut ); return vOut ; }
    inline S3DX::AIVariable     easyDownloadHTTPS ( const S3DX::AIVariable& sID, const S3DX::AIVariable& sURL, const S3DX::AIVariable& sTargetFile, const S3DX::AIVariable& bSkipPeerVerification, const S3DX::AIVariable& bSkipHostnameVerification ) { S3DX_DECLARE_VIN_05( sID, sURL, sTargetFile, bSkipPeerVerification, bSkipHostnameVerification ) ; S3DX::AIVariable vOut ; if ( pfn_scurl_easyDownloadHTTPS ) pfn_scurl_easyDownloadHTTPS ( 5, vIn, &vOut ); return vOut ; }

 	//-------------------------------------------------------------------------
	//  API Constants 
	//-------------------------------------------------------------------------

    S3DX::AIVariable kErrorPost ; 
    S3DX::AIVariable kErrorFile ; 
    S3DX::AIVariable kErrorSSL ; 
    S3DX::AIVariable kErrorFilePartial ; 
    S3DX::AIVariable kErrorFileRetrieval ; 
    S3DX::AIVariable kErrorFileWrite ; 
    S3DX::AIVariable kErrorFileSize ; 
    S3DX::AIVariable kFile ; 
    S3DX::AIVariable kErrorWebsite ; 
    S3DX::AIVariable kErrorInit ; 
    S3DX::AIVariable kError404 ; 
    S3DX::AIVariable kWebsite ; 

} ;

extern scurlAPI scurl;

//-----------------------------------------------------------------------------
#endif
//-----------------------------------------------------------------------------
