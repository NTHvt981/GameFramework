require("common")
require("DirectXSDK")
require("core")
require("input-system")
require("graphic-system")
require("audio-system")

local direct_wrapper_prj_name = "direct-wrapper"
local direct_wrapper_path = source_path..direct_wrapper_prj_name.."/"
local direct_wrapper_include_path = direct_wrapper_path.."include/"

function addDirectWrapper()
   local direct_wrapper_src_path = direct_wrapper_path.."src/"

   project(direct_wrapper_prj_name)
      kind("StaticLib")

      files { 
         direct_wrapper_path.."**.h", 
         direct_wrapper_path.."**.cpp" 
      }

      includedirs { 
         direct_wrapper_include_path,
         direct_wrapper_src_path
      }

      includeCore()
      includeInputSystem()
      includeAudioSystem()
      includeGraphicSystem()
      includeDirectXSDK()
end

function includeDirectWrapper()
   includedirs { 
      direct_wrapper_include_path
   }

   links {
      direct_wrapper_prj_name
   }

   includeCore()
   includeInputSystem()
   includeAudioSystem()
   includeGraphicSystem()
   includeDirectXSDK()
end