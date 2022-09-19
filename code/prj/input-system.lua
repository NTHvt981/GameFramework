require("common")
require("core")

local input_system_prj_name = "input-system"
local input_system_path = source_path.."input-system/"
local input_system_include_path = input_system_path.."include/"
function addInputSystem()
   local input_system_src_path = input_system_path.."src/"

   project(input_system_prj_name)
      kind "StaticLib"

      files { 
         input_system_path.."**.h", 
         input_system_path.."**.cpp" 
      }

      includedirs { 
         input_system_include_path,
         input_system_src_path
      }

      includeCore()
end

function includeInputSystem()
    includedirs { 
        input_system_include_path
    }

    links {
        input_system_prj_name
    }
end