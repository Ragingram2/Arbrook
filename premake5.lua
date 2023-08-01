
-- newaction
-- {
--     trigger = "clean",
--     description = "clean the project files",
--     execute = function ()
--         cleanextensions { ".vcxproj", ".vcxproj.filters",".vcxproj.user" }
--     end
-- }


function formatEngineModulePath(moduleName)
    return string.format("arbrook/%s/build-%s.lua", moduleName,moduleName,moduleName)
end

function formatApplicationPath(moduleName)
    return string.format("application/%s/build-%s.lua", moduleName, moduleName)
end

function createProject(groupName,projectName, kindName)
    print("Building " .. projectName)
    group ("" .. groupName)
    project ("" .. projectName)
        location ("src/" .. projectName)
        kind (""..kindName)
        architecture "x64"
        toolset "clang"
        language "C++"
        cppdialect "C++20"
    group ""
end

workspace "arbrook"
    configurations {"DebugOGL","DebugDX11","ReleaseOGL","ReleaseDX11" }
    platforms {"Win64"}

include(formatEngineModulePath("core"))
include(formatEngineModulePath("rendering"))
include(formatApplicationPath("sandbox"))
include "include/rsl/build-rsl.lua"


    



