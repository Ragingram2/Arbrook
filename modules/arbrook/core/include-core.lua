--This is only used to include the neccesary stuff for this module
print("including core")
includedirs {
    basicIncludes,
    "../../include/",
    "../../include/*/",
    "../../include/*/src/",
    "../../include/*/include/",
    "../../include/*/third_party/",
    "../../include/*/third_party/*/",
    "../../include/*/third_party/*/src/",
    "../../include/*/third_party/*/include/",
    "../../include/*/public/"
}

dependson { "core", "rsl"}
filter "configurations:Debug*"
    links {"core-d", "assimp-d","zlibstatic-d","TracyProfiler-d"}

filter "configurations:Release*"
    links {"core","assimp","zlibstatic","TracyProfiler"}

    filter {}