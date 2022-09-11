require("common")
require("core")
require("file-system")

local graphic_system_prj_name = "graphic-system"
local graphic_system_path = source_path.."graphic-system/"
local graphic_system_include_path = graphic_system_path.."include/"
function addGraphicSystem()
   local graphic_system_src_path = graphic_system_path.."src/"

   project(graphic_system_prj_name)
      kind "StaticLib"

      files { 
         graphic_system_path.."**.h", 
         graphic_system_path.."**.cpp" 
      }

      includedirs { 
         graphic_system_include_path,
         graphic_system_src_path
      }

      includeCore()
      includeFileSystem()
end

function includeGraphicSystem()
    includedirs { 
        graphic_system_include_path
    }

    links {
        graphic_system_prj_name
    }
end