require("common")

local lib_directx_path = libs_path.."DirectXSDK/"

function includeDirectXSDK()
    externalincludedirs { 
        lib_directx_path.."include"
     }

     libdirs { 
        lib_directx_path.."libs/x64/" 
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
        "X3DAudio"
     }
end