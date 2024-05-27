require("common")
require("core")
require("audio-system")

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
      includeAudioSystem()
end

function includeLogic()
   includedirs { 
      logic_include_path
   }

   links {
      logic_prj_name
   }
end