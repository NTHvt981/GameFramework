require("common")
require("core")
require("graphic-system")

local graphic_debug_prj_name = "graphic-debug"
local graphic_debug_path = source_path..graphic_debug_prj_name.."/"
local graphic_debug_include_path = graphic_debug_path.."include/"

function addGraphicDebug()
   local graphic_debug_src_path = graphic_debug_path.."src/"

   project(graphic_debug_prj_name)
      kind("StaticLib")

      files { 
         graphic_debug_path.."**.h", 
         graphic_debug_path.."**.cpp" 
      }

      includedirs { 
         graphic_debug_include_path,
         graphic_debug_src_path
      }

      includeCore()
      includeGraphicSystem()
end

function includeGraphicDebug()
   includedirs { 
      graphic_debug_include_path
   }

   links {
      graphic_debug_prj_name
   }
   
   includeCore()
   includeGraphicSystem()
end