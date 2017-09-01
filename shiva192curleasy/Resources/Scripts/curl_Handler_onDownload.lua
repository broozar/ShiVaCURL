--------------------------------------------------------------------------------
--  Handler.......... : onDownload
--  Author........... : 
--  Description...... : 
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function curl.onDownload ( sID, kType, sContent )
--------------------------------------------------------------------------------
	
    -- error handling, capture/forward as needed
    
    if kType == scurl.kErrorFilePartial then
        log.warning ( "sCURL Lua: '", sID, "' File transferwas incomplete: ", sContent )

    elseif kType == scurl.kErrorFileRetrieval then
        log.warning ( "sCURL Lua: '", sID, "' File could not be retrieved: ", sContent )
        
    elseif kType == scurl.kErrorFileSize then
        log.warning ( "sCURL Lua: '", sID, "' File size error: ", sContent )

    elseif kType == scurl.kErrorSSL then
        log.warning ( "sCURL Lua: '", sID, "' File failed the SSL handshake: ", sContent )    

    elseif kType == scurl.kErrorFileWrite then
        log.warning ( "sCURL Lua: '", sID, "' File could not be written: ", sContent )    
        
    elseif kType == scurl.kErrorFile then
        log.warning ( "sCURL Lua: '", sID, "' File error: ", sContent )    
    
    -- real work  
    
    elseif kType == scurl.kFile then
        log.message ( "sCURL Lua: '", sID, "' File: ", sContent )
    
    end
	
--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
