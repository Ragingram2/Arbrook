function formatEngineModulePath(moduleName)
    return string.format("arbrook/%s/build-%s.lua", moduleName,moduleName,moduleName)
end

function formatApplicationPath(moduleName)
    return string.format("application/%s/build-%s.lua", moduleName, moduleName)
end

function createProject(groupName,projectName,kindName)
    print("Building " .. projectName)
    group ("" .. groupName)
    project ("" .. projectName)
        kind (""..kindName)
        location ("src/"..projectName)
        architecture "x64"
        toolset "clang"
        language "C++"
        cppdialect "C++20"
        targetdir "$(SolutionDir)bin\\lib"
        libdirs {"$(SolutionDir)bin\\lib\\"}
        objdir "$(SolutionDir)bin\\obj"
        defines {"ARBROOK_INTERNAL", "PROJECT_NAME="..projectName}
        filter "configurations:Debug*"
            defines {"DEBUG","BX_CONFIG_DEBUG"}
            symbols "On"
            targetsuffix "-d"
        filter "configurations:Release*"
            defines {"NDEBUG"}
            optimize "On"
        filter "configurations:*OGL"
            defines {"RenderingAPI_OGL=0","RenderingAPI=0"}
        
        filter "configurations:*DX11"
            defines {"RenderingAPI_DX11=1","RenderingAPI=1"}  

        filter {}
    group ""
end

basicIncludes = {
"src/",
"include/",
"include/*/",
"include/*/src/",
"include/*/include/",
"include/*/lib/include/",
"include/*/third_party/",
"include/*/third_party/*/",
"include/*/third_party/*/src/",
"include/*/third_party/*/include/",
"include/*/third_party/*/lib/include/"
}

workspace "arbrook"
    configurations {"DebugOGL","DebugDX11","ReleaseOGL","ReleaseDX11" }
    platforms {"Win64"}

include(formatEngineModulePath("core"))
include(formatEngineModulePath("input"))
include(formatEngineModulePath("rendering"))
include(formatEngineModulePath("physics"))
include(formatApplicationPath("sandbox"))
include "include/rythe-standard-library/build-rythe-standard-library.lua"


newaction
{
    trigger = "clean",
    description = "clean the project files",
    execute = function ()
        local ok, err = os.remove{"**.vcxproj","**.vcxproj.filters"}
        if not ok then
            error(err)
        end
    end
}