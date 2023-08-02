createProject("applications","sandbox","ConsoleApp")
targetdir "$(SolutionDir)bin\\build\\"
includedirs {
    "$(SolutionDir)application/sandbox/include/",
    "$(SolutionDir)application/sandbox/src/"
}   

files { 
    "../../arbrook/Arbrook.cpp",
    "src/sandbox/**.h",
    "src/sandbox/**.hpp",
    "src/sandbox/**.inl",
    "src/sandbox/**.c",
    "src/sandbox/**.cpp" 
}

dofile "arbrook/core/include-core.lua"
dofile "arbrook/rendering/include-rendering.lua"

