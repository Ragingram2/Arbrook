createProject("engine","rendering","StaticLib")
includedirs {
    "$(SolutionDir)arbrook/rendering/include/",
    "$(SolutionDir)arbrook/rendering/include/imgui/",
    "$(SolutionDir)arbrook/rendering/src/",
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
    defines {"RenderingAPI_OGL=0","RenderingAPI=0"}
    files {
        "include/imgui/backends/imgui_impl_opengl3.cpp",
        "include/imgui/backends/imgui_impl_opengl3.h"
    }

filter "configurations:*DX11"
    defines {"RenderingAPI_DX11=1","RenderingAPI=1"}  
    files {
        "include/imgui/backends/imgui_impl_dx11.cpp",
        "include/imgui/backends/imgui_impl_dx11.h"
    }






