print("including physics")
includedirs {
    basicIncludes,
    "../../include/",
    "../../include/*/",
    "../../include/*/src/",
    "../../include/*/include/",
    "../../include/*/third_party/",
    "../../include/*/third_party/*/",
    "../../include/*/third_party/*/src/",
    "../../include/*/third_party/*/include/"
}  
dependson { "physics" }
filter "configurations:Debug*"
    links {"physics-d"}

filter "configurations:Release*"
    links {"physics"}

filter {}