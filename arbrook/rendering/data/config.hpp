#pragma once

#define RenderingAPI_OpenGL 0
#define RenderingAPI_DX11 1

#define RenderingAPI RenderingAPI_DX11


#if RenderingAPI == RenderingAPI_OpenGL
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
