--------------------------------------------------------------------------------
--  Handler.......... : onLaunchThreads
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function curl_test.onLaunchThreads (  )
--------------------------------------------------------------------------------
	
	scurl.easyGetHTTP ( "googleCOM", "google.com" ) -- normal website
    scurl.easyGetHTTP ( "generalError", "gogogoggoggle.com" ) -- host cannot be resolved, general error
    scurl.easyGetHTTP ( "404test", "google.com/derps" ) -- 404 page not found
    scurl.easyPostHTTP ( "POSTtest", "httpbin.org/post", "name=derpy&value=hooves" ) -- POST
    scurl.easyGetHTTPS ( "twitterSSL", "twitter.com/", false, false ) -- HTTPS with full verification
    scurl.easyDownloadHTTP ( "fileDL", "www.shiva-engine.com/presskits/logos.zip", application.getPackDirectory ( ) .. "/logosFromShiVaWebsite.zip" ) -- download ZIP
    
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
