require("common")

local core_prj_name = "core"
local core_path = source_path.."core/"
local core_include_path = core_path.."include/"

function addCore()
   local core_src_path = core_path.."src/"

   project(core_prj_name)
      kind("StaticLib")

      files { 
         core_path.."**.h", 
         core_path.."**.cpp" 
      }

      includedirs { 
         core_include_path,
         core_src_path
      }
end

function includeCore()
    includedirs { 
        core_include_path
     }

     links {
        core_prj_name
     }
end