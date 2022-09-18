require("common")
require("DirectXSDK")
require("core")
require("graphic-system")

local render_directx9_prj_name = "render-directx9"
local render_directx9_path = source_path..render_directx9_prj_name.."/"
local render_directx9_include_path = render_directx9_path.."include/"

function addRenderDirectx9()
   local render_directx9_src_path = render_directx9_path.."src/"

   project(render_directx9_prj_name)
      kind("StaticLib")

      files { 
         render_directx9_path.."**.h", 
         render_directx9_path.."**.cpp" 
      }

      includedirs { 
         render_directx9_include_path,
         render_directx9_src_path
      }

      includeCore()
      includeGraphicSystem()
      includeDirectXSDK()
end

function includeRenderDirectx9()
   includedirs { 
      render_directx9_include_path
   }

   links {
      render_directx9_prj_name
   }
end