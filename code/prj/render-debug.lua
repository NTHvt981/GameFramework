require("common")
require("core")
require("graphic-system")

local render_debug_prj_name = "render-debug"
local render_debug_path = source_path..render_debug_prj_name.."/"
local render_debug_include_path = render_debug_path.."include/"

function addRenderDebug()
   local render_debug_src_path = render_debug_path.."src/"

   project(render_debug_prj_name)
      kind("StaticLib")

      files { 
         render_debug_path.."**.h", 
         render_debug_path.."**.cpp" 
      }

      includedirs { 
         render_debug_include_path,
         render_debug_src_path
      }

      includeCore()
      includeGraphicSystem()
end

function includeRenderDebug()
   includedirs { 
      render_debug_include_path
   }

   links {
      render_debug_prj_name
   }
end