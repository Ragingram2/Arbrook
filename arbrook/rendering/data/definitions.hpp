#pragma once
#include "rendering/data/interface/irenderinterface.hpp"
#include "rendering/data/interface/iinputlayout.hpp"
#include "rendering/data/interface/ishader.hpp"
#include "rendering/data/interface/ibuffer.hpp"
#include "rendering/data/interface/window.hpp"
#include "rendering/data/config.hpp"
#include RenderInterface_HPP_PATH
#include EnumTypes_HPP_PATH
#include InputLayout_HPP_PATH 
#include Buffer_HPP_PATH
#include Shader_HPP_PATH
#include Window_HPP_PATH

namespace rythe::rendering
{
	typedef IRenderInterface<internal::RenderInterface> RenderInterface;
	typedef Iinputlayout<internal::inputlayout> inputlayout;
	typedef Ibuffer<internal::buffer> buffer;
	typedef Ishader<internal::shader> shader;
}
