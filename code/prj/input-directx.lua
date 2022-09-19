require("common")
require("DirectXSDK")
require("core")
require("input-system")

local input_directx9_prj_name = "input-directx"
local input_directx9_path = source_path..input_directx9_prj_name.."/"
local input_directx9_include_path = input_directx9_path.."include/"

function addInputDirectx()
   local input_directx9_src_path = input_directx9_path.."src/"

   project(input_directx9_prj_name)
      kind("StaticLib")

      files { 
         input_directx9_path.."**.h", 
         input_directx9_path.."**.cpp" 
      }

      includedirs { 
         input_directx9_include_path,
         input_directx9_src_path
      }

      includeCore()
      includeInputSystem()
      includeDirectXSDK()
end

function includeInputDirectx()
   includedirs { 
      input_directx9_include_path
   }

   links {
      input_directx9_prj_name
   }

   includeCore()
   includeInputSystem()
   includeDirectXSDK()
end