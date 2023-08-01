
-- group "engine"
-- project "core"
--     location "src/core"
--     kind "StaticLib"
createProject("engine","core","StaticLib")
includedirs {"core/include/"}    
defines { "ARBROOK_INTERNAL", "PROJECT_NAME=core" }
files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp" ,"src/%{prj.name}/**.inl","src/%{prj.name}/**.c", "src/%{prj.name}/**.cpp" }
--group ""