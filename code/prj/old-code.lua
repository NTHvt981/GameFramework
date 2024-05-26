require("common")
require("core")
require("DirectXSDK")

local old_code_prj_name = "old-code"
local old_code_path = source_path..old_code_prj_name.."/"
local old_code_include_path = old_code_path.."include/"

function addOldCode()
   project(old_code_prj_name)
      kind "WindowedApp"

      files { 
         old_code_path.."**.h", 
         old_code_path.."**.cpp" 
      }

      includedirs { 
         old_code_include_path
      }

      links {
         "Winmm",
         "ole32",
         "avrt",
         "legacy_stdio_definitions"
      }

      includeCore()
      includeDirectXSDK()
end