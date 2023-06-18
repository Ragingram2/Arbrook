#pragma once

#if RenderingAPI == RenderingAPI_OGL
#define Texture_HPP_PATH "rendering/data/OpenGL/texture.hpp"
#define TextureParams_HPP_PATH "rendering/data/OpenGL/textureparameters.hpp"
#define RenderInterface_HPP_PATH "rendering/data/OpenGL/renderinterface.hpp"
#define InputLayout_HPP_PATH "rendering/data/OpenGL/inputlayout.hpp"
#define Buffer_HPP_PATH "rendering/data/OpenGL/buffer.hpp"
#define Shader_HPP_PATH "rendering/data/OpenGL/shader.hpp"
#define Window_HPP_PATH "rendering/data/OpenGL/window.hpp"
#define EnumTypes_HPP_PATH "rendering/data/OpenGL/enumtypes.hpp"
#define ShaderLanguage "GLSL"
#endif

#if RenderingAPI == RenderingAPI_DX11
#define Texture_HPP_PATH "rendering/data/DirectX/texture.hpp"
#define TextureParams_HPP_PATH "rendering/data/DirectX/textureparameters.hpp"
#define RenderInterface_HPP_PATH "rendering/data/DirectX/renderinterface.hpp"
#define InputLayout_HPP_PATH "rendering/data/DirectX/inputlayout.hpp"
#define Buffer_HPP_PATH "rendering/data/DirectX/buffer.hpp"
#define Shader_HPP_PATH "rendering/data/DirectX/shader.hpp"
#define Window_HPP_PATH "rendering/data/DirectX/window.hpp"
#define EnumTypes_HPP_PATH "rendering/data/DirectX/enumtypes.hpp"
#define ShaderLanguage "HLSL"

#ifdef _DEBUG
#define CHECKERROR(hr,text,func) if(FAILED(hr))  { log::error(text); func;__debugbreak();}
#else
#define CHECKERROR(hr,text,func)
#endif
#endif




