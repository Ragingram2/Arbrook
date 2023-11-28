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
		std::unordered_map<std::string, buffer_handle> m_constBuffers;
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

			for (auto [name, handle] : m_constBuffers)
			{
				handle->bind();
				glBindBufferBase(GL_UNIFORM_BUFFER, handle->m_impl.bindId, handle->getId());
			}
		}

		template<typename elementType>
		void setData(const std::string& bufferName, elementType data[])
		{
			if (m_constBuffers.count(bufferName) != 0)
			{
				m_constBuffers[bufferName]->bufferData<elementType>(data);
			}
		}

		void addBuffer(buffer_handle handle)
		{
			if (static_cast<internal::TargetType>(handle->getTargetType()) != TargetType::CONSTANT_BUFFER)
			{
				log::error("Buffer is not a constant buffer, this is not supported");
				return;
			}
			log::debug("Adding a Constant Buffer to shader {}", name);
			if (!m_constBuffers.count(handle->getName()))
			{
				m_constBuffers.emplace(handle->getName(), handle);
				log::debug("Binding Uniform Buffer {}", handle->getName());
				auto idx = glGetUniformBlockIndex(programId, handle->getName().c_str());
				glUniformBlockBinding(programId, idx, handle->m_impl.bindId);
				return;
			}
			//log::debug("Binding Uniform Buffer");
			//auto idx = glGetUniformBlockIndex(programId, handle->getName().c_str());
			//glUniformBlockBinding(programId, idx, handle->m_impl.bindId);
		}

		void release()
		{
			glDeleteProgram(programId);
			clearBuffers();
		}

		void clearBuffers()
		{
			m_constBuffers.clear();
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