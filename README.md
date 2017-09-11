# ShiVaCURL
cURL integration for ShiVa

This plugin allows you to make regular HTTP/S GET and POST requests as well as download files to local storage. All calls are fully multithreaded using C++11 std::thread.

## What is cURL?
cURL is a command line tool and library for transferring data with URLs. curl is free and open source software and exists thanks to thousands of contributors. The curl project follows well established open source best practises.

Visit https://curl.haxx.se/ for more information.

# Installation and Usage
1. copy the Plugin folder to your project
2. copy the "curl" AIModel to your project (via STE)
3. configure target AIModel and event handlers in curl.onInit()
4. capture events using your own event handlers

Have a look at the curl_test project for a working example configuration.

# API
API is packed under scurl.\* and has the following member functions:

    { "messageLoop"      , Callback_scurl_messageLoop      , ""   , ""                                                                        , "for onEnterFrame(), clears message vector and dispatches events"                                                          , 0 }, 
    { "globalShutdown"   , Callback_scurl_globalShutdown   , ""   , ""                                                                        , "always call onApplicationWillQuit"                                                                                        , 0 }, 
    { "init"             , Callback_scurl_init             , "bOK", "sAIModel, sEventStrings, sEventFiles"                                    , "init plugin with target AIModel and Events"                                                                               , 0 }, 
    { "easyGetHTTP"      , Callback_scurl_easyGetHTTP      , "bOK", "sID, sURL"                                                               , "simple HTTP GET request, result string over Event handler"                                                                , 0 }, 
    { "easyPostHTTP"     , Callback_scurl_easyPostHTTP     , "bOK", "sID, sURL, sData"                                                        , "simple HTTP POST request, result string over Event handler"                                                               , 0 }, 
    { "easyGetHTTPS"     , Callback_scurl_easyGetHTTPS     , "bOK", "sID, sURL, bSkipPeerVerification, bSkipHostnameVerification"             , "simple HTTPS GET request, result string over Event handler. Skipping verification makes the connection much less secure!" , 0 }, 
    { "easyPostHTTPS"    , Callback_scurl_easyPostHTTPS    , "bOK", "sID, sURL, bSkipPeerVerification, bSkipHostnameVerification, sPostdata"  , "simple HTTPS POST request, result string over Event handler. Skipping verification makes the connection much less secure!", 0 }, 
    { "easyDownloadHTTP" , Callback_scurl_easyDownloadHTTP , "bOK", "sID, sURL, sTargetFile"                                                  , "download file over HTTP, result string over Event handler"                                                                , 0 }, 
    { "easyDownloadHTTPS", Callback_scurl_easyDownloadHTTPS, "bOK", "sID, sURL, sTargetFile, bSkipPeerVerification, bSkipHostnameVerification", "download file over HTTPs, result string over Event handler. Skipping verification makes the connection much less secure!" , 0 }

## API examples
Once initialized, you can make a cURL call from any AI:

    scurl.easyGetHTTP ( "googleCOM", "google.com" ) -- normal website
    scurl.easyGetHTTP ( "generalError", "gogogoggoggle.com" ) -- host cannot be resolved, general error
    scurl.easyGetHTTP ( "404test", "google.com/derps" ) -- 404 page not found
    scurl.easyPostHTTP ( "POSTtest", "httpbin.org/post", "name=derpy&value=hooves" ) -- POST
    scurl.easyGetHTTPS ( "twitterSSL", "twitter.com/", false, false ) -- HTTPS with full verification
    scurl.easyDownloadHTTP ( "fileDL", "www.shiva-engine.com/presskits/logos.zip", application.getPackDirectory ( ) .. "/logosFromShiVaWebsite.zip" ) -- download ZIP
    
## Events
Results will be printed into one of two event handlers, Files or Messages. You can define the names of these handlers in scurl.init(). The event handlers have the following signature:

    curl.onResponse ( sID, kType, sContent ) -- for messages
    curl.onDownload ( sID, kType, sContent ) -- for files
    
## Error handling
The API provides several constants for error handling:

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
    
Error handling on Mac is different for HTTP(S) document requests (forwards the entire error line from the command line tool) and very limited for file downloads. Do not rely on any error codes except for kWebsite/kFile for GOOD and kErrorWebsite/kErrorFile for BAD requests.
