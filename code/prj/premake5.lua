local root_path = "../../"
local release_path = root_path.."release/"
local libs_path = root_path.."libs/"
local temp_path = root_path.."temp/"
local code_path = root_path.."code/"
local prj_path = code_path.."prj/"
local prj_2019_path = prj_path.."vs2019/"
local source_path = code_path.."source/"
local Core = "Core"

function addSln()
   solution "Game"
      location (prj_2019_path)
      language "C++"
      cppdialect "C++20"
      startproject "app"
      configurations { "Debug", "Profile", "Release" }
      platforms { "Win64" }
      architecture "x86_64"
      system "Windows"

      targetdir (release_path.."%{cfg.buildcfg}")
   
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

local core_path = source_path.."core/"
local core_include_path = core_path.."include/"
function addCore()
   local core_src_path = core_path.."src/"

   project "core"
      kind "StaticLib"

      files { 
         core_path.."**.h", 
         core_path.."**.cpp" 
      }

      includedirs { 
         core_include_path,
         core_src_path
      }
end

local file_system_path = source_path.."file-system/"
local file_system_include_path = file_system_path.."include/"
function addFileSystem()
   local file_system_src_path = file_system_path.."src/"

   project "file-system"
      kind "StaticLib"

      files { 
         file_system_path.."**.h", 
         file_system_path.."**.cpp" 
      }

      includedirs { 
         core_include_path,

         file_system_include_path,
         file_system_src_path
      }

      links {
         "core"
      }
end

local file_system_path = source_path.."file-system/"
local file_system_include_path = file_system_path.."include/"
function addFileSystem()
   local file_system_src_path = file_system_path.."src/"

   project "file-system"
      kind "StaticLib"

      files { 
         file_system_path.."**.h", 
         file_system_path.."**.cpp" 
      }

      includedirs { 
         core_include_path,

         file_system_include_path,
         file_system_src_path
      }

      links {
         "core"
      }
end

local app_path = source_path.."app/"
local app_include_path = app_path.."include/"
local lib_directx_path = libs_path.."DirectXSDK/"
function addApp()
   project "app"
      kind "WindowedApp"

      files { 
         app_path.."**.h", 
         app_path.."**.cpp" 
      }

      includedirs { 
         core_include_path,
         file_system_include_path,

         app_include_path
      }

      externalincludedirs { 
         lib_directx_path.."Include"
      }

      libdirs { 
         lib_directx_path.."Lib/x64/" 
      }

      links {
         "core",
         "file-system",

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
end

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
         core_include_path,
         file_system_include_path,

         test_include_path,
         test_src_path
      }

      links {
         "core",
         "file-system",
      }
end

-- add solution and projects

addSln()
addCore()
addFileSystem()
addApp()
addTest()
