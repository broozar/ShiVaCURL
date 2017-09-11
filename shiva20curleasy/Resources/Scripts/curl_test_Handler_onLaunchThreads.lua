--------------------------------------------------------------------------------
--  Handler.......... : onLaunchThreads
--  Author........... :
--  Description...... :
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function curl_test.onLaunchThreads (  )
--------------------------------------------------------------------------------

    -- GET
    scurl.easyGetHTTP ( "googleCOM", "google.com" ) -- normal website
    scurl.easyGetHTTP ( "generalError", "gogogoggoggle.com" ) -- host cannot be resolved, general error
    scurl.easyGetHTTP ( "404test", "google.com/derps" ) -- 404 page not found

    -- HTTPS
    scurl.easyGetHTTPS ( "twitterSSL", "twitter.com/", false, false ) -- HTTPS with full verification

    -- POST
    scurl.easyPostHTTP ( "POSTtest", "httpbin.org/post", "name=derpy&value=hooves" ) -- POST
    scurl.easyPostHTTP ( "badPOSTtest", "bogus-address-123.org/post", "name=derpy&value=hooves" ) -- POST error

    -- FILES
    scurl.easyDownloadHTTP ( "fileDL", "www.shiva-engine.com/presskits/logos.zip", application.getPackDirectory ( ) .. "/logosFromShiVaWebsite.zip" ) -- download ZIP OK
    scurl.easyDownloadHTTP ( "fileDL404", "www.shiva-engine.com/presskits/nothere.zip", application.getPackDirectory ( ) .. "/BAD1.zip" ) -- file does not exist
    scurl.easyDownloadHTTP ( "fileDLHost", "www.shi-eng.ccoomm/llooggooss.zip", application.getPackDirectory ( ) .. "/BAD2.zip" ) -- host cannot be resolved

--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------