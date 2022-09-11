require("common")
require("core")

local file_system_prj_name = "file-system"
local file_system_path = source_path.."file-system/"
local file_system_include_path = file_system_path.."include/"
local file_system_src_path = file_system_path.."src/"

function addFileSystem()
   project(file_system_prj_name)
      kind "StaticLib"

      files { 
         file_system_path.."**.h", 
         file_system_path.."**.cpp" 
      }

      includedirs { 
         file_system_include_path,
         file_system_src_path
      }

      pchheader "stdafx.h"
      pchsource(file_system_src_path.."stdafx.cpp")

      includeCore()
end

function includeFileSystem()
    includedirs { 
        file_system_include_path
    }

    links {
        file_system_prj_name
    }
end