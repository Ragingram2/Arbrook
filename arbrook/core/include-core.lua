--This is only used to include the neccesary stuff for this module
print("including core")
includedirs {
    "$(SolutionDir)include/",
    "$(SolutionDir)arbrook/core/src/",
    "$(SolutionDir)include/rythe-standard-library/src/",
    "$(SolutionDir)include/rythe-standard-library/third_party/spdlog/include/"
}
dependson { "core", "rsl"}
filter "configurations:Debug*"
    links {"core-d"}

filter "configurations:Release*"
    links {"core"}

    filter {}