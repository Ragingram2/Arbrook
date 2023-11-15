createProject("applications","sandbox","ConsoleApp")
targetdir "$(SolutionDir)bin\\build\\"

includedirs {
    "src/",
    "include/",
    "include/*/",
    "include/*/src/",
    "include/*/include/",
    "include/bx/include/compat/msvc/"
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

