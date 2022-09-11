require("common")
require("core")
require("file-system")

local test_path = source_path.."test/"
local test_include_path = test_path.."include/"

function addTest()
   local test_src_path = test_path.."src/"

   project "test"
      kind "ConsoleApp"

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
end