createProject("engine","core","StaticLib")
includedirs {
    "$(SolutionDir)include/",
    "$(SolutionDir)include/rythe-standard-library/src/",
    "$(SolutionDir)include/rythe-standard-library/third_party/spdlog/include/",
    "$(SolutionDir)arbrook/core/include/",
    "$(SolutionDir)arbrook/core/src/",
    "include/rythe-standard-library/src/",
    "include/rythe-standard-library/third_party/*/include/",
    "include/rythe-standard-library/third_party/*/src/"
}   
 
files { 
    "src/core/**.h",
    "src/core/**.hpp",
    "src/core/**.inl",
    "src/core/**.c",
    "src/core/**.cpp" 
}


