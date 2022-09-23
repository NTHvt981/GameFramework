require("common")
require("core")
require("file-system")
require("graphic-system")

local database_prj_name = "database"
local database_path = source_path..database_prj_name.."/"
local database_include_path = database_path.."include/"

function addDatabase()
   local database_src_path = database_path.."src/"

   project(database_prj_name)
      kind("StaticLib")

      files { 
         database_path.."**.h", 
         database_path.."**.cpp" 
      }

      includedirs { 
         database_include_path,
         database_src_path
      }

      includeCore()
      includeFileSystem()
      includeGraphicSystem()
end

function includeDatabase()
    includedirs { 
        database_include_path
     }

     links {
        database_prj_name
     }
end