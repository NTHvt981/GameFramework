require("common")
require("core")
require("input-system")

local input_debug_prj_name = "input-debug"
local input_debug_path = source_path..input_debug_prj_name.."/"
local input_debug_include_path = input_debug_path.."include/"

function addInputDebug()
   local input_debug_src_path = input_debug_path.."src/"

   project(input_debug_prj_name)
      kind("StaticLib")

      files { 
         input_debug_path.."**.h", 
         input_debug_path.."**.cpp" 
      }

      includedirs { 
         input_debug_include_path,
         input_debug_src_path
      }

      includeCore()
      includeInputSystem()
end

function includeInputDebug()
   includedirs { 
      input_debug_include_path
   }

   links {
      input_debug_prj_name
   }
   
   includeCore()
   includeInputSystem()
end