require("common")
require("core")
require("file-system")
require("graphic-system")
require("graphic-directx9")
require("input-system")
require("input-directx")
require("logic")

require("DirectXSDK")

local app_prj_name = "app"
local app_path = source_path..app_prj_name.."/"
local app_include_path = app_path.."include/"

function addApp()
   local app_src_path = app_path.."src/"

   project(app_prj_name)
      kind("WindowedApp")

      files { 
         app_path.."**.h", 
         app_path.."**.cpp" 
      }

      includedirs { 
         app_include_path,
         app_src_path
      }
      
      includeCore()
      includeGraphicDirectx9()
      includeInputDirectx()
      includeDirectXSDK()
      includeLogic()
end