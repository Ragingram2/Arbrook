createProject("engine","input","StaticLib")
includedirs { basicIncludes }
 
files { 
    "src/input/**.h",
    "src/input/**.hpp",
    "src/input/**.inl",
    "src/input/**.c",
    "src/input/**.cpp" 
}

dofile "arbrook/core/include-core.lua"