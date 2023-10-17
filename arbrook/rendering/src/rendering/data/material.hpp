#pragma once
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/texturehandle.hpp"

namespace rythe::rendering
{
	struct material
	{
		texture_handle m_texture;
		shader_handle m_shader;

		material() = default;
		material(const material& mat) : m_texture(mat.m_texture), m_shader(mat.m_shader) {}

		void bind()
		{
			if (m_shader != nullptr)
				m_shader->bind();
			else
				log::warn("[Material] Shader handle is null, cannot bind");
			if (m_texture != nullptr)
				m_texture->bind();
			else
				log::warn("[Material] Texture handle is null, cannot bind");
		}
	};

}