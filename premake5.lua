
function scandir(directory,recursive, extensions)
    directory = directory or ''
    recursive = recursive or false
    -- if string.sub(directory, -1) ~= '/' then directory = directory .. '/' end

    local currentDirectory = directory
    local fileList = {}
    local command = "dir " .. directory .. " /b"
    if recursive then command = command .. '/s' end

    for fileName in io.popen(command):lines() do
        if string.find(fileName,"include") then
            goto continue
        end
        if string.sub(fileName, -1) == '/' then
            -- Directory, don't do anything
        elseif string.sub(fileName, -1) == ':' then
            currentDirectory = string.sub(fileName, 1, -2) .. 'wat'
            -- if currentDirectory ~= directory then
                currentDirectory = currentDirectory .. '/'
            -- end
        elseif string.len(fileName) == 0 then
            -- Blank line
            currentDirectory = directory
        -- elseif string.find(fileName,"%.lua$") then
            -- File is a .lua file
        else
            if type(extensions) == 'table' then
                for _, extension in ipairs(extensions) do
                    if string.find(fileName,"%." .. extension .. "$") then
                        table.insert(fileList, currentDirectory .. fileName)
                    end
                end
            else
                table.insert(fileList, currentDirectory .. fileName)
            end
        end
        ::continue::
    end
    return fileList
end


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
            defines {"DEBUG"}
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

cleanExts = {"vcxproj","vcxproj.filters","vcxproj.user"}

workspace "arbrook"
    configurations {"DebugOGL","DebugDX11","ReleaseOGL","ReleaseDX11" }
    platforms {"Win64"}

include(formatEngineModulePath("core"))
include(formatEngineModulePath("rendering"))
include(formatApplicationPath("sandbox"))
include "include/rsl/build-rsl.lua"


newaction
{
    trigger = "clean",
    description = "clean the project files",
    execute = function ()
        for key, value in ipairs(scandir("",true,cleanExts)) do
            os.remove(value)
        end
    end
}