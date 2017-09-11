--------------------------------------------------------------------------------
--  Handler.......... : onInit
--  Author........... :
--  Description...... :
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
function curl.onInit (  )
--------------------------------------------------------------------------------

    if not scurl.init ( "curl", "onResponse", "onDownload" ) then
        log.warning ( "sCURL Lua: INIT failed. cURL will not be available." )
        return
    end

    application.setOption ( application.kOptionNativeStringPoolSize, 2048 )

--------------------------------------------------------------------------------
end
--------------------------------------------------------------------------------
