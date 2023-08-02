--This is only used to include the neccesary stuff for this module
print("including core")
includedirs {
    "$(SolutionDir)include/",
    "$(SolutionDir)arbrook/core/src/",
    "$(SolutionDir)include/rsl/src/"
}
dependson { "core" }
filter "configurations:Debug*"
    links {"core-d"}

filter "configurations:Release*"
    links {"core"}

    filter {}