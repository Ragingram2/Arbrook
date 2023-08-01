
-- group "applications"
-- project "sandbox"
--     location "src/sandbox"
--     kind "ConsoleApp"
createProject("applications","sandbox","ConsoleApp")
includedirs {"sandbox/include/","sandbox/src"}   
files { "src/%{prj.name}/**.h", "src/%{prj.name}/**.hpp" ,"src/%{prj.name}/**.inl","src/%{prj.name}/**.c", "src/%{prj.name}/**.cpp" }
dofile  "arbrook/core/include-core.lua"
dofile  "arbrook/rendering/include-rendering.lua"
--group ""