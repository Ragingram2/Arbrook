#pragma once
#include "rendering/interface/irenderinterface.hpp"
#include "rendering/interface/iinputlayout.hpp"
#include "rendering/interface/ishader.hpp"
#include "rendering/interface/ibuffer.hpp"
#include "rendering/interface/itexture.hpp"
#include "rendering/interface/window.hpp"
#include "rendering/interface/config.hpp"
#include RenderInterface_HPP_PATH
#include EnumTypes_HPP_PATH
#include InputLayout_HPP_PATH 
#include Buffer_HPP_PATH
#include Shader_HPP_PATH
#include Texture_HPP_PATH
#include Window_HPP_PATH

namespace rythe::rendering
{
	typedef IRenderInterface<internal::RenderInterface> RenderInterface;
	typedef Iinputlayout<internal::inputlayout> inputlayout;
	typedef Ibuffer<internal::buffer> buffer;
	typedef Ishader<internal::shader> shader;
	typedef Itexture<internal::texture> texture;
}

#define Screen_Width 1280.f
#define Screen_Height 720.f
