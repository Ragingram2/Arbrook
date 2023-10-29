--This is only used to include the neccesary stuff for this module
print("including rendering")
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
    "../../include/*/third_party/*/include/",
    "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
}  
dependson { "rendering" }
filter "configurations:Debug*"
    links {"rendering-d","glfw3_mt","bgfx-d","bimg-d","bx-d","glew32s","opengl32","libpng16"}

filter "configurations:Release*"
    links {"rendering","glfw3_mt","bgfx","bimg","bx","glew32s","opengl32","libpng16"}

filter {}

