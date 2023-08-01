print("including rendering")
includedirs { "src/","include/"}
dependson { "rendering"}
filter "kind:not StaticLib"
    links { "core", "GL", "GLFW","imgui","bgfx","bimg","bx","stb" }
