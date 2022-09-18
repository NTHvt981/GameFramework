require("common")
require("core")

local physic_system_prj_name = "physic-system"
local physic_system_path = source_path.."physic-system/"
local physic_system_include_path = physic_system_path.."include/"
function addPhysicSystem()
   local physic_system_src_path = physic_system_path.."src/"

   project(physic_system_prj_name)
      kind "StaticLib"

      files { 
         physic_system_path.."**.h", 
         physic_system_path.."**.cpp" 
      }

      includedirs { 
         physic_system_include_path,
         physic_system_src_path
      }

      includeCore()
end

function includePhysicSystem()
    includedirs { 
        physic_system_include_path
    }

    links {
        physic_system_prj_name
    }
end