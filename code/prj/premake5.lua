require("common")
require("core")
require("file-system")
require("graphic-system")
require("app")
require("test")

local core_prj_name = "core"
local core_path = source_path.."core/"
local core_include_path = core_path.."include/"

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

-- add solution and projects

addSln()
addCore()
addFileSystem()
addGraphicSystem()
addApp()
addTest()
