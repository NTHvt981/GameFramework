require("common")
require("core")

local audio_system_prj_name = "audio-system"
local audio_system_path = source_path..audio_system_prj_name.."/"
local audio_system_include_path = audio_system_path.."include/"
function addAudioSystem()
   local audio_system_src_path = audio_system_path.."src/"

   project(audio_system_prj_name)
      kind "StaticLib"

      files { 
         audio_system_path.."**.h", 
         audio_system_path.."**.cpp" 
      }

      includedirs { 
         audio_system_include_path,
         audio_system_src_path
      }

      includeCore()
end

function includeAudioSystem()
    includedirs { 
        audio_system_include_path
    }

    links {
        audio_system_prj_name
    }
end