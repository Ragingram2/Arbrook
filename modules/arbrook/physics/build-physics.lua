createProject("engine","physics","StaticLib")
includedirs {
    basicIncludes
}  

files { 
    "src/physics/**.h",
    "src/physics/**.hpp",
    "src/physics/**.inl",
    "src/physics/**.c",
    "src/physics/**.cpp"
}
dofile "arbrook/core/include-core.lua"
