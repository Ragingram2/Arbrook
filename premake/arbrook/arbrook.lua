include("_preload.lua")

premake.solution = {
    Configuration = {
        RELEASE = 1,
        DEVELOPMENT = 2,
        DEBUG = 3
    },
    loadedProjects = {},
    buildSettings = {
        platform = "x86_64",
        toolset = "clang",
        cppVersion = "C++20"
    },
    defines =
    {
        "TRACY_ENABLE",
        "_SILENCE_STDEXT_ARR_ITERS_DEPRECATION_WARNING",
    }
}

local solution = premake.solution

local projects = dofile("projects.lua")

function solution.configName(config)
    local configNames = { 
        [solution.Configuration.RELEASE] = "Release",
        [solution.Configuration.DEVELOPMENT] = "Development",
        [solution.Configuration.DEBUG] = "Debug"        
    }

    return configNames[config]
end

function solution.targetSuffix(config)
    local configSuffix = { 
        [solution.Configuration.RELEASE] = "",
        [solution.Configuration.DEVELOPMENT] = "-dev",
        [solution.Configuration.DEBUG] = "-debug"        
    }

    return configSuffix[config]
end

function solution.configure()
    filter { "configurations:Debug" }
        targetsuffix(solution.targetSuffix(solution.Configuration.DEBUG))
    filter { "configurations:Development" }
        targetsuffix(solution.targetSuffix(solution.Configuration.DEVELOPMENT))

    projects.scan("./")
end

return solution
