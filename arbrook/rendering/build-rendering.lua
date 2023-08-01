
-- group "engine"
-- project "rendering"
--     location "src/rendering"
--     kind "StaticLib"
createProject("engine","rendering","StaticLib")
targetdir "Arbrook/build/%{cfg.buildcfg}"
libdirs { "Arbrook/lib/", "Arbrook/build/%{cfg.buildcfg}/" }
includedirs {"rendering/include/","C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"}    
defines { "ARBROOK_INTERNAL", "PROJECT_NAME=graphics","RenderingAPI_OGL=0","RenderingAPI_DX11=1"}
files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp" ,"src/%{prj.name}/**.inl","src/%{prj.name}/**.c", "src/%{prj.name}/**.cpp" }


--group ""