#pragma once
#include <string>

#include <GL/glew.h>

#include <rsl/logging>

#include "rendering/data/textureparameters.hpp"

#include <stb/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION

namespace rythe::rendering::internal
{
	struct texture
	{
	private:
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
			this->params = params;

			glGenTextures(1, &id);
			bind();
			glTexParameteri(static_cast<GLenum>(m_texType), GL_TEXTURE_WRAP_S, static_cast<GLint>(params.wrapModeS));
			glTexParameteri(static_cast<GLenum>(m_texType), GL_TEXTURE_WRAP_T, static_cast<GLint>(params.wrapModeT));
			glTexParameteri(static_cast<GLenum>(m_texType), GL_TEXTURE_MIN_FILTER, static_cast<GLint>(params.filterMode));
			glTexParameteri(static_cast<GLenum>(m_texType), GL_TEXTURE_MAG_FILTER, static_cast<GLint>(params.filterMode));

			if (generateMipMaps)
			{
				glGenerateMipmap(static_cast<GLenum>(m_texType));
			}
		}

		void bind()
		{
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

			//make some enums for the data formats
			switch (params.channels)
			{
			case 4:
				glTexImage2D(static_cast<GLenum>(m_texType), 0, GL_RGBA, params.resolution.x, params.resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
				break;
			case 3:
				glTexImage2D(static_cast<GLenum>(m_texType), 0, GL_RGB, params.resolution.x, params.resolution.y, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
				break;
			}
		}
	};
}