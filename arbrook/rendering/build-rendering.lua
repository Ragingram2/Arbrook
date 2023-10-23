createProject("engine","rendering","StaticLib")
includedirs {
    "src/",
    "include/",
    "include/imgui/",
    "include/*/",
    "include/*/src/",
    "include/*/include/",
    "include/*/third_party/",
    "include/*/third_party/*/",
    "include/*/third_party/*/src/",
    "include/*/third_party/*/include/",
    "C:/Program Files (x86)/Microsoft DirectX SDK (June 2010)/Include"
}  
defines {"GLEW_STATIC"}
files { 
    "src/rendering/**.h",
    "src/rendering/**.hpp",
    "src/rendering/**.inl",
    "src/rendering/**.c",
    "src/rendering/**.cpp",
    "include/imgui/*.cpp",
    "include/imgui/backends/imgui_impl_glfw.cpp",
}
dofile "arbrook/core/include-core.lua"

filter "configurations:*OGL"
    files {
        "include/imgui/backends/imgui_impl_opengl3.cpp",
        "include/imgui/backends/imgui_impl_opengl3.h"
    }

filter "configurations:*DX11"
    files {
        "include/imgui/backends/imgui_impl_dx11.cpp",
        "include/imgui/backends/imgui_impl_dx11.h"
    }






