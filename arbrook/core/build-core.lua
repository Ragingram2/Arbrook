createProject("engine","core","StaticLib")
includedirs {
    "src/",
    "include/",
    "include/*/",
    "include/*/src/",
    "include/*/include/",
    "../../include/",
    "../../include/*/",
    "../../include/*/src/",
    "../../include/*/include/",
    "../../include/*/third_party/",
    "../../include/*/third_party/*/",
    "../../include/*/third_party/*/src/",
    "../../include/*/third_party/*/include/"
}   
 
files { 
    "src/core/**.h",
    "src/core/**.hpp",
    "src/core/**.inl",
    "src/core/**.c",
    "src/core/**.cpp" 
}


