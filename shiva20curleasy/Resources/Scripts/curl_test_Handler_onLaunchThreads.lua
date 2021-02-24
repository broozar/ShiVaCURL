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
    scurl.easyGetHTTP ( "h1", "httpbin.org/get?name=djey&value=toto" ) -- variables in URL for $_GET
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

    -- MAC only: please refer to 'man curl' for all options
    --scurl.raw ( "rawHTTP", "-s --user-agent 'shivabrowser' -L -f --show-error --data 'name=derpy&value=hooves' httpbin.org/post" )

--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
