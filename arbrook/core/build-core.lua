createProject("engine","core","StaticLib")
includedirs {
    "$(SolutionDir)include/",
    "$(SolutionDir)include/rsl/src/",
    "$(SolutionDir)arbrook/core/include/",
    "$(SolutionDir)arbrook/core/src/"
}   
 
files { 
    "src/core/**.h",
    "src/core/**.hpp",
    "src/core/**.inl",
    "src/core/**.c",
    "src/core/**.cpp" 
}


