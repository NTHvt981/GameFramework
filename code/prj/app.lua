require("common")
require("core")
require("file-system")
require("graphic-system")
require("render-debug")
require("render-directx9")
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
      includeFileSystem()
      includeGraphicSystem()
      includeRenderDirectx9()
      includeRenderDebug()
      includeLogic()

      includeDirectXSDK()
end