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

-- projects = {}

-- newaction
-- {
--     trigger = "test",
--     description = "Test action",
--     execute = function()
--         projects = scandir(".arbrook-project")
--     end
-- }


function formatEngineModulePath(moduleName)
    return string.format("arbrook/%s/build-%s.lua", moduleName,moduleName,moduleName)
end

function formatApplicationPath(moduleName)
    return string.format("application/%s/build-%s.lua", moduleName, moduleName)
end

function scandir(fileName)
    local i, t, popen = 0, {}, io.popen
    local pfile = popen('dir "'..fileName..'" /s /b')
    for filename in pfile:lines() do
        i = i + 1
        t[i] = filename
    end
    pfile:close()
    return t
end

function removeSubstring(str, substr)
    -- Find the starting index of the substring in the string.
    local startIndex, endIndex = string.find(str, substr)
 
    -- If the substring is found, remove it from the string.
    if startIndex and endIndex then
        local prefix = string.sub(str, 1, startIndex - 1)
        local suffix = string.sub(str, endIndex + 1)
        return prefix .. suffix
    end
 
    -- If the substring is not found, return the original string.
    return str
end

function getProjectDir()
    return removeSubstring(""..os.getcwd(),".arbrook-project")
end

function new_createProject(projectData)
    print("Building " .. projectData.name)
    group ("" .. projectData.group)
    project ("" .. projectData.name)
        kind ("".. projectData.type)
        location (projectData.location)
        architecture "x64"
        toolset (projectData.toolset)
        language (projectData.lang)
        cppdialect (projectData.dialect)
        buildoptions {projectData.buildOptions}
        targetdir (projectData.targetDir)
        libdirs {SolutionDir.."bin\\lib\\"}--this should be based on dependencies
        objdir (SolutionDir.."bin\\obj")--this too
        defines {projectData.defines}
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
        buildoptions {
            "-Wno-nonportable-include-path",
            "-Wno-reorder-init-list",
            "-Wno-reorder-ctor",
            "-Wno-c99-designator",
            "-Wno-microsoft-exception-spec"
        }
        targetdir "$(SolutionDir)bin\\lib"
        libdirs {"$(SolutionDir)bin\\lib\\"}
        objdir "$(SolutionDir)bin\\obj"
        defines {"ARBROOK_INTERNAL", "PROJECT_NAME="..projectName, "TRACY_ENABLE"}
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

SolutionDir = "D:\\Repos\\Arbrook\\"

DefaultDefines = 
{
    "TRACY_ENABLE"
}
DefaultBuildOptions =
{
    "-Wno-nonportable-include-path",
    "-Wno-reorder-init-list",
    "-Wno-reorder-ctor",
    "-Wno-c99-designator",
    "-Wno-microsoft-exception-spec"
}
basicIncludes = {
"src/",
"include/",
"include/*/",
"include/*/src/",
"include/*/include/",
"include/*/lib/include/",
"include/*/public/",
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
include(formatEngineModulePath("graphics"))
include(formatEngineModulePath("physics"))

-- projects = scandir(".arbrook-project")

-- for i, path in pairs(projects) do
--     local project = dofile(path.."\\project.lua")
--     new_createProject(project)
-- end

include(formatApplicationPath("sandbox"))
include "include/rythe-standard-library/build-rythe-standard-library.lua"


