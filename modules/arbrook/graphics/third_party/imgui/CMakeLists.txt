cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

# Folder structure
set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY ON)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# Project
if(APPLE)
	project(imgui LANGUAGES OBJCXX)
else()
	project(imgui LANGUAGES CXX)
endif()

add_library(imgui STATIC
	imconfig.h
	imgui.h
	imgui_internal.h
	imstb_rectpack.h
	imstb_textedit.h
	imstb_truetype.h
	
	imgui.cpp
	imgui_demo.cpp
	imgui_draw.cpp
	imgui_tables.cpp
	imgui_widgets.cpp

	backends/imgui_impl_glfw.h
	backends/imgui_impl_opengl3.h
	backends/imgui_impl_glfw.cpp
	backends/imgui_impl_opengl3.cpp

	addons/ImGuizmo/ImGuizmo.h
	addons/ImGuizmo/ImCurveEdit.h
	addons/ImGuizmo/ImGradient.h
	addons/ImGuizmo/ImSequencer.h
	addons/ImGuizmo/ImZoomSlider.h
	addons/ImGuizmo/GraphEditor.h

	addons/ImGuizmo/ImGuizmo.cpp
	addons/ImGuizmo/ImCurveEdit.cpp
	addons/ImGuizmo/ImGradient.cpp
	addons/ImGuizmo/ImSequencer.cpp
	addons/ImGuizmo/GraphEditor.cpp

	addons/FileBrowser/ImGuiFileBrowser.h
	addons/FileBrowser/ImGuiFileBrowser.cpp
	addons/FileBrowser/Dirent/dirent.h

	addons/ImNodes/imnodes.h
	addons/ImNodes/imnodes_internal.h
	addons/ImNodes/imnodes.cpp
)

target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(imgui PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/addons/FileBrowser)