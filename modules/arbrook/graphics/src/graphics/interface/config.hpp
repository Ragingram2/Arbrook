#pragma once
#include <imgui/backends/imgui_impl_glfw.h>


#ifdef _DEBUG
#define CHECKERROR(hr,text,func) if(FAILED(hr))  { log::error(text); func;}
#else
#define CHECKERROR(hr,text,func) hr;
#endif

#define SAFE_RELEASE(p) if(p) { p->Release() (p) = NULL} 

#if RenderingAPI == RenderingAPI_OGL
#include <imgui/backends/imgui_impl_opengl3.h>
#define Texture_HPP_PATH "../interface/OpenGL/texture.hpp"
#define TextureParams_HPP_PATH "../interface/OpenGL/textureparameters.hpp"
#define RenderInterface_HPP_PATH "../interface/OpenGL/renderinterface.hpp"
#define InputLayout_HPP_PATH "../interface/OpenGL/inputlayout.hpp"
#define Buffer_HPP_PATH "../interface/OpenGL/buffer.hpp"
#define Shader_HPP_PATH "../interface/OpenGL/shader.hpp"
#define Window_HPP_PATH "../interface/OpenGL/window.hpp"
#define EnumTypes_HPP_PATH "../interface/OpenGL/enumtypes.hpp"
#define ShaderCompiler_HPP_PATH "../interface/OpenGL/shadercompiler.hpp"
#define Framebuffer_HPP_PATH "../interface/OpenGL/framebuffer.hpp"
#endif

#if RenderingAPI == RenderingAPI_DX11
#include <imgui/backends/imgui_impl_dx11.h>
#define Texture_HPP_PATH "../interface/DirectX/texture.hpp"
#define TextureParams_HPP_PATH "../interface/DirectX/textureparameters.hpp"
#define RenderInterface_HPP_PATH "../interface/DirectX/renderinterface.hpp"
#define InputLayout_HPP_PATH "../interface/DirectX/inputlayout.hpp"
#define Buffer_HPP_PATH "../interface/DirectX/buffer.hpp"
#define Shader_HPP_PATH "../interface/DirectX/shader.hpp"
#define Window_HPP_PATH "../interface/DirectX/window.hpp"
#define EnumTypes_HPP_PATH "../interface/DirectX/enumtypes.hpp"
#define ShaderCompiler_HPP_PATH "../interface/DirectX/shadercompiler.hpp"
#define Framebuffer_HPP_PATH "../interface/DirectX/framebuffer.hpp"
#endif

#if RenderingAPI == RenderingAPI_VK
#include <imgui/backends/imgui_impl_vulkan.h>
#define Texture_HPP_PATH "../interface/Vulkan/texture.hpp"
#define TextureParams_HPP_PATH "../interface/Vulkan/textureparameters.hpp"
#define RenderInterface_HPP_PATH "../interface/Vulkan/renderinterface.hpp"
#define InputLayout_HPP_PATH "../interface/Vulkan/inputlayout.hpp"
#define Buffer_HPP_PATH "../interface/Vulkan/buffer.hpp"
#define Shader_HPP_PATH "../interface/Vulkan/shader.hpp"
#define Window_HPP_PATH "../interface/Vulkan/window.hpp"
#define EnumTypes_HPP_PATH "../interface/Vulkan/enumtypes.hpp"
#define ShaderCompiler_HPP_PATH "../interface/Vulkan/shadercompiler.hpp"
#define Framebuffer_HPP_PATH "../interface/Vulkan/framebuffer.hpp"
#endif




