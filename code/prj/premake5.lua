local root_path = "../../"
local release_path = root_path.."release/"
local libs_path = root_path.."libs/"
local lib_directx_path = libs_path.."DirectXSDK/"
local temp_path = root_path.."temp/"
local code_path = root_path.."code/"
local prj_path = code_path.."prj/"
local prj_2019_path = prj_path.."vs2019/"
local source_path = code_path.."source/"
local app_path = source_path.."app/"
local app_include_path = app_path.."include/"

function addSln()
   solution "Game"
      location (prj_2019_path)
      cppdialect "C++20"
      startproject "app"
      configurations { "Debug", "Profile", "Release" }
      platforms { "Win64" }
      architecture "x86_64"
      system "Windows"
   
      filter {"configurations:Debug*"}
         defines { "DEBUG" }
         symbols "Full"
         optimize "Debug"
         targetsuffix "_d"
         
      filter {"configurations:Profile*"}
         symbols "On"
         optimize "On"
         targetsuffix "_p"

      filter {"configurations:Release*"}
         defines { "NDEBUG" }
         symbols "Off"
         optimize "Full"
         targetsuffix "_r"
end

function addApp()
   project "app"
      kind "WindowedApp"
      language "C++"

      files { 
         app_path.."**.h", 
         app_path.."**.cpp" 
      }

      includedirs { 
         app_include_path
      }

      externalincludedirs { 
         lib_directx_path.."Include"
      }

      libdirs { 
         lib_directx_path.."Lib/x64/" 
      }

      links {
         "d3d9",
         "d3dx9",
         "dxerr",
         "dxguid",
         "dinput8",
         "d3dcompiler",
         "dxgi",
         "dsound",
         "dwrite",
         "Winmm",
         "ole32",
         "avrt",
         "legacy_stdio_definitions",
         "X3DAudio"
      }

      targetdir (release_path.."%{cfg.buildcfg}")
end

-- add solution and projects

addSln()
addApp()
