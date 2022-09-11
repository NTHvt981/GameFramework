require("common")
require("core")
require("file-system")

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

      includeCore()
      includeFileSystem()
end