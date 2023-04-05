#pragma once

#define RenderingAPI_OpenGL 0
#define RenderingAPI_DX11 1

#define RenderingAPI RenderingAPI_DX11


#if RenderingAPI == RenderingAPI_OpenGL
#define TextureParams_HPP_PATH "rendering/data/OpenGL/textureparameters.hpp"//do this more
#define RenderInterface_HPP_PATH "rendering/data/OpenGL/renderinterface.hpp"
#define VertexArray_HPP_PATH "rendering/data/OpenGL/vertexarray.hpp"
#define Buffer_HPP_PATH "rendering/data/OpenGL/buffer.hpp"
#define Shader_HPP_PATH "rendering/data/OpenGL/shader.hpp"
#define Window_HPP_PATH "rendering/data/OpenGL/window.hpp"
#define EnumTypes_HPP_PATH "rendering/data/OpenGL/enumtypes.hpp"
#define ShaderLanguage "GLSL"
#endif

#if RenderingAPI == RenderingAPI_DX11
#define TextureParams_HPP_PATH "rendering/data/DirectX/textureparameters.hpp"//do this more
#define RenderInterface_HPP_PATH "rendering/data/DirectX/renderinterface.hpp"
#define VertexArray_HPP_PATH "rendering/data/DirectX/vertexarray.hpp"
#define Buffer_HPP_PATH "rendering/data/DirectX/buffer.hpp"
#define Shader_HPP_PATH "rendering/data/DirectX/shader.hpp"
#define Window_HPP_PATH "rendering/data/DirectX/window.hpp"
#define EnumTypes_HPP_PATH "rendering/data/DirectX/enumtypes.hpp"
#define ShaderLanguage "HLSL"


#define HR(x) \
{\
	HRESULT hr = x;\
	if(FAILED(hr))\
	{ \
		__debugbreak();\
	} \
}

#endif
