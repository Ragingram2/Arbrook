#pragma once
#include "rendering/data/texture.hpp"

namespace rythe::rendering
{
	struct texture_handle
	{
		texture* m_texture;
		texture_handle() = default;
		texture_handle(texture* tex) : m_texture(tex) {}

		texture* operator->() { return m_texture; }
		operator texture& () const { return *m_texture; }
		operator unsigned int() const { return m_texture->m_id; }
	};
}