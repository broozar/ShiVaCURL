--------------------------------------------------------------------------------
--  Handler.......... : onResponse
--  Author........... :
--  Description...... :
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function curl.onResponse ( sID, kType, sContent )
--------------------------------------------------------------------------------

    -- error handling, capture/forward as needed

    if kType == scurl.kErrorInit then
        log.warning ( "sCURL Lua: '", sID, "' hit an init error!" )

    elseif kType == scurl.kError404 then
        log.warning ( "sCURL Lua: '", sID, "' received a 404! " )

    elseif kType == scurl.kErrorPost then
        log.warning ( "sCURL Lua: '", sID, "' hit a POST error: ", sContent )

    elseif kType == scurl.kErrorSSL then
        log.warning ( "sCURL Lua: '", sID, "' failed the SSL handshake: ", sContent )

    elseif kType == scurl.kErrorWebsite then
        log.warning ( "sCURL Lua: '", sID, "' hit a web error: ", sContent )

    -- real work

    elseif kType == scurl.kWebsite then
        log.message ( "sCURL Lua: '", sID, "' said: ", sContent ) -- this will truncate the output, do not be alarmed...
        log.message ( "", sID, " length: ", string.getLength ( sContent ) ) -- check the length instead, it's all there

    end

--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
