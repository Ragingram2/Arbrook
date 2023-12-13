#pragma once
#include <string>


#include <rsl/logging>

#include "rendering/data/textureparameters.hpp"
#include "rendering/interface/OpenGL/oglincludes.hpp"

#include <stb/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION

namespace rythe::rendering::internal
{
	namespace log = rsl::log;
	struct texture
	{
	private:
		GLenum m_nativeType;
		TargetType m_texType;
	public:
		unsigned int id;
		std::string name;
		unsigned char* data;
		texture_parameters params;
		texture() = default;
		texture(unsigned int id, std::string name) : id(id), name(name) { }
		texture(texture* other)
		{
			name = other->name;
			id = other->id;
			data = other->data;
			params = other->params;
		}

		void initialize(TargetType texType, texture_parameters params, bool generateMipMaps = false)
		{
			m_texType = texType;
			m_nativeType = static_cast<GLenum>(m_texType);
			this->params = params;
			this->params.generateMipMaps = generateMipMaps;

			glGenTextures(1, &id);
			bind();
			glTexParameteri(m_nativeType, GL_TEXTURE_WRAP_R, static_cast<GLint>(params.wrapModeR));
			glTexParameteri(m_nativeType, GL_TEXTURE_WRAP_S, static_cast<GLint>(params.wrapModeS));
			glTexParameteri(m_nativeType, GL_TEXTURE_WRAP_T, static_cast<GLint>(params.wrapModeT));
			glTexParameteri(m_nativeType, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(params.filterMode));
			glTexParameteri(m_nativeType, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(params.filterMode));

		}

		void bind(TextureSlot textureSlot = TextureSlot::TEXTURE0)
		{
			glActiveTexture(static_cast<GLenum>(textureSlot));
			glBindTexture(static_cast<GLenum>(m_texType), id);
		}

		void loadData(const std::string& filepath, bool flipVertical = true)
		{
			stbi_set_flip_vertically_on_load(flipVertical);
			data = stbi_load(filepath.c_str(), &params.resolution.x, &params.resolution.y, &params.channels, 0);
			if (!data)
			{
				rsl::log::error("Image failed to load");
			}

			if (params.immutable)
			{
				auto mipCount = params.generateMipMaps ? params.mipLevels : 1;
				glTexParameteri(m_nativeType, GL_TEXTURE_MAX_LEVEL, mipCount);
				glTexStorage2D(m_nativeType, static_cast<GLint>(mipCount), static_cast<GLint>(params.format), params.resolution.x, params.resolution.y);

				switch (params.channels)
				{
				case 4:
					glTexSubImage2D(m_nativeType, 0, 0, 0, params.resolution.x, params.resolution.y, GL_RGBA, GL_UNSIGNED_INT_24_8, data);
					break;
				case 3:
					glTexSubImage2D(m_nativeType, 0, 0, 0, params.resolution.x, params.resolution.y, GL_RGB, GL_UNSIGNED_INT_24_8, data);
					break;
				case 1:
					glTexSubImage2D(m_nativeType, 0, 0, 0, params.resolution.x, params.resolution.y, GL_RED, GL_UNSIGNED_INT_24_8, data);
				}
			
			}
			else
			{
				switch (params.channels)
				{
				case 4:
					glTexImage2D(m_nativeType, 0, GL_RGBA, params.resolution.x, params.resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
					break;
				case 3:
					glTexImage2D(m_nativeType, 0, GL_RGB, params.resolution.x, params.resolution.y, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
					break;
				case 1:
					glTexImage2D(m_nativeType, 0, GL_RED, params.resolution.x, params.resolution.y, 0, GL_RED, GL_UNSIGNED_BYTE, data);
				}
			}

			if (params.generateMipMaps)
			{
				glGenerateMipmap(m_nativeType);
			}
		}
	};
}