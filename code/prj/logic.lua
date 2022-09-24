require("common")
require("core")
require("file-system")
require("database")
require("graphic-system")
require("physic-system")
require("input-system")

local logic_prj_name = "logic"
local logic_path = source_path.."logic/"
local logic_include_path = logic_path.."include/"

function addLogic()
   local logic_src_path = logic_path.."src/"

   project(logic_prj_name)
      kind("StaticLib")

      files { 
         logic_path.."**.h", 
         logic_path.."**.cpp" 
      }

      includedirs { 
         logic_include_path,
         logic_src_path
      }

      includeCore()
      includeFileSystem()
      includeGraphicSystem()
      includePhysicSystem()
      includeInputSystem()
      includeDatabase()
end

function includeLogic()
   includedirs { 
      logic_include_path
   }

   links {
      logic_prj_name
   }
end