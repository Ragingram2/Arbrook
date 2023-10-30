#pragma once
#include <string>

#include "core/math/math.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/bufferhandle.hpp"
#include "rendering/interface/OpenGL/oglincludes.hpp"
#include "rendering/interface/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct shader
	{
	public:
		unsigned int programId;
		std::string name;

	private:
		std::unordered_map<std::string, buffer_handle> m_vsConstBuffers;
		std::unordered_map<std::string, buffer_handle> m_psConstBuffers;
	public:
		shader() = default;
		shader(shader* other)
		{
			programId = other->programId;
			name = other->name;
		}
		operator unsigned int() const { return programId; }

		void initialize(const std::string& name, const shader_source& source)
		{
			this->name = name;
			programId = glCreateProgram();

			unsigned int vs = compileShader(ShaderType::VERTEX, source.vertexSource);
			unsigned int fs = compileShader(ShaderType::FRAGMENT, source.fragSource);

			glAttachShader(programId, vs);
			glAttachShader(programId, fs);
			glLinkProgram(programId);
			glValidateProgram(programId);

			glDeleteShader(vs);
			glDeleteShader(fs);
		}

		void bind()
		{
			glUseProgram(programId);
		}

		template<typename elementType>
		void setData(const std::string& bufferName, elementType data[])
		{
			if (m_vsConstBuffers.count(bufferName) != 0)
			{
				m_vsConstBuffers[bufferName]->bufferData<elementType>(data);
			}

			if (m_psConstBuffers.count(bufferName) != 0)
			{
				m_psConstBuffers[bufferName]->bufferData<elementType>(data);
			}
		}

		void addBuffer(ShaderType type, buffer_handle handle)
		{
			if (static_cast<internal::TargetType>(handle->getTargetType()) != TargetType::CONSTANT_BUFFER)
			{
				log::error("Buffer is not a constant buffer, this is not supported");
				return;
			}

			switch (type)
			{
			case ShaderType::VERTEX:
				if (!m_vsConstBuffers.count(handle->getName()))
					m_vsConstBuffers.emplace(handle->getName(), handle);
				return;
				break;
			case ShaderType::FRAGMENT:
				if (!m_psConstBuffers.count(handle->getName()))
					m_psConstBuffers.emplace(handle->getName(), handle);
				return;
				break;
			default:
				log::error("Adding a constant buffer to shader type {} is not supported", RYTHE_STRINGIFY(TargetType::CONSTANT_BUFFER));
				break;
			}

			glUniformBlockBinding(programId, glGetUniformBlockIndex(programId, handle->getName().c_str()), handle->m_impl.bindId);
		}

		void release()
		{
			glDeleteProgram(programId);
			clearBuffers();
		}

		void clearBuffers()
		{
			m_vsConstBuffers.clear();
			m_psConstBuffers.clear();
		}
	private:
		unsigned int compileShader(ShaderType type, const std::string& source)
		{
			unsigned int id = glCreateShader(static_cast<GLenum>(type));
			const char* src = source.c_str();
			glShaderSource(id, 1, &src, nullptr);
			glCompileShader(id);

			int result;
			glGetShaderiv(id, GL_COMPILE_STATUS, &result);

			int length;
			glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
			char* message = (char*)__builtin_alloca(length * sizeof(char));
			glGetShaderInfoLog(id, length, &length, message);

			if (result == GL_FALSE)
			{
				log::error(message);
				glDeleteShader(id);
				return 0;
			}

			return id;
		}
	};

}