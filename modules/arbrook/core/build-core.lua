createProject("engine","core","StaticLib")
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

files { 
    "src/core/**.h",
    "src/core/**.hpp",
    "src/core/**.inl",
    "src/core/**.c",
    "src/core/**.cpp"
}


