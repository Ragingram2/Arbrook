#pragma once
#include "rendering/data/interface/itexture.hpp"
#include "rendering/data/config.hpp"
#include Texture_HPP_PATH

namespace rythe::rendering
{
	struct texture_handle
	{
		Itexture<internal::texture>* m_texture;
		texture_handle() = default;
		texture_handle(Itexture<internal::texture>* tex) : m_texture(tex) {}

		Itexture<internal::texture>* operator->() { return m_texture; }
		operator Itexture<internal::texture>& () const { return *m_texture; }
		operator unsigned int() const { return m_texture->getId(); }
	};
}