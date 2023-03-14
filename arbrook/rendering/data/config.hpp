#pragma once

#define RenderingAPI_OpenGL 0
#define RenderingAPI_DX11 1

#define RenderingAPI RenderingAPI_OpenGL


#if RenderingAPI == RenderingAPI_OpenGL
#define TextureParams_HPP_PATH "rendering/data/OpenGL/textureparameters.hpp"//do this more
#include "rendering/data/OpenGL/renderinterface.hpp"
#include "rendering/data/OpenGL/vertexarray.hpp"
#include "rendering/data/OpenGL/buffer.hpp"
#include "rendering/data/OpenGL/shader.hpp"
#endif

#if RenderingAPI == RenderingAPI_DX11
#include "rendering/data/DirectX/renderinterface.hpp"
#include "rendering/data/DirectX/vertexarray.hpp"
#include "rendering/data/DirectX/buffer.hpp"
#include "rendering/data/DirectX/shader.hpp"
#endif
