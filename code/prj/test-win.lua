require("common")
require("core")
require("file-system")
require("graphic-system")

local test_prj_name = "test-win"
local test_path = source_path..test_prj_name.."/"
local test_include_path = test_path.."include/"

function addTestWin()
   local test_src_path = test_path.."src/"

   project(test_prj_name)
      kind "WindowedApp"

      files { 
         test_path.."**.h", 
         test_path.."**.cpp" 
      }

      includedirs { 
         test_include_path,
         test_src_path
      }

      includeCore()
      includeFileSystem()
      includeGraphicSystem()
end