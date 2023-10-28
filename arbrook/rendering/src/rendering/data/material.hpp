#pragma once
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/texturehandle.hpp"

namespace rythe::rendering
{
	struct material
	{
		texture_handle texture;
		shader_handle shader;

		material() = default;
		material(const material& mat) : texture(mat.texture), shader(mat.shader) {}

		void bind()
		{
			if (shader != nullptr)
				shader->bind();
			else
				log::warn("[Material] Shader handle is null, cannot bind");
			if (texture != nullptr)
				texture->bind();
		}
	};

}