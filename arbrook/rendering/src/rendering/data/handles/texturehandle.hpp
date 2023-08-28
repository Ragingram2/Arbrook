#pragma once
#include "rendering/interface/itexture.hpp"
#include "rendering/interface/config.hpp"
#include Texture_HPP_PATH

namespace rythe::rendering
{
	//struct texture_handle
	//{
	//	Itexture<internal::texture>* m_texture;
	//	texture_handle() = default;
	//	texture_handle(std::nullptr_t null_ptr) : m_texture(null_ptr) {}
	//	texture_handle(Itexture<internal::texture>* tex) : m_texture(tex) {}
	//	texture_handle(texture_handle& tex) : m_texture(tex.m_texture) {}

	//	Itexture<internal::texture>* operator->() { return m_texture; }
	//	operator Itexture<internal::texture>& () const { return *m_texture; }
	//	operator unsigned int() const { return m_texture->getId(); }
	//};
}