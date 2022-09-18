require("common")
require("core")
require("file-system")

local xml_prj_name = "xml"
local xml_path = source_path..xml_prj_name.."/"
local xml_include_path = xml_path.."include/"
function addXml()
   local xml_src_path = xml_path.."src/"

   project(xml_prj_name)
      kind "StaticLib"

      files { 
         xml_path.."**.h", 
         xml_path.."**.cpp" 
      }

      includedirs { 
         xml_include_path,
         xml_src_path
      }

      includeCore()
      includeFileSystem()
end

function includeXml()
    includedirs { 
        xml_include_path
    }

    links {
        xml_prj_name
    }
end