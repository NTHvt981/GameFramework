require("common")
require("core")
require("file-system")
require("DirectXSDK")

local app_path = source_path.."app/"
local app_include_path = app_path.."include/"

function addApp()
   project "app"
      kind "WindowedApp"

      files { 
         app_path.."**.h", 
         app_path.."**.cpp" 
      }

      includedirs { 
         app_include_path
      }

      links {
         "Winmm",
         "ole32",
         "avrt",
         "legacy_stdio_definitions"
      }

      includeCore()
      includeFileSystem()
      includeDirectXSDK()
end