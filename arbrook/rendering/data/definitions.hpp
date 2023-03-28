#pragma once
#include "rendering/data/interface/irenderinterface.hpp"
#include "rendering/data/interface/ivertexarray.hpp"
#include "rendering/data/interface/ishader.hpp"
#include "rendering/data/interface/ibuffer.hpp"
#include "rendering/data/interface/window.hpp"
#include "rendering/data/config.hpp"
#include RenderInterface_HPP_PATH
#include EnumTypes_HPP_PATH
#include VertexArray_HPP_PATH
#include Buffer_HPP_PATH
#include Shader_HPP_PATH
#include Window_HPP_PATH

namespace rythe::rendering
{
	typedef IRenderInterface<internal::RenderInterface> RenderInterface;
	typedef Ivertexarray<internal::vertexarray> vertexarray;
	typedef Ibuffer<internal::buffer> buffer;
	typedef Ishader<internal::shader> shader;

	static RenderInterface api;
}
