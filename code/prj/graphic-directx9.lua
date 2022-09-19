require("common")
require("DirectXSDK")
require("core")
require("graphic-system")

local graphic_directx9_prj_name = "graphic-directx9"
local graphic_directx9_path = source_path..graphic_directx9_prj_name.."/"
local graphic_directx9_include_path = graphic_directx9_path.."include/"

function addGraphicDirectx9()
   local graphic_directx9_src_path = graphic_directx9_path.."src/"

   project(graphic_directx9_prj_name)
      kind("StaticLib")

      files { 
         graphic_directx9_path.."**.h", 
         graphic_directx9_path.."**.cpp" 
      }

      includedirs { 
         graphic_directx9_include_path,
         graphic_directx9_src_path
      }

      includeCore()
      includeGraphicSystem()
      includeDirectXSDK()
end

function includeGraphicDirectx9()
   includedirs { 
      graphic_directx9_include_path
   }

   links {
      graphic_directx9_prj_name
   }

   includeCore()
   includeGraphicSystem()
   includeDirectXSDK()
end