#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
 
#include "core/logging/logging.hpp"
#include "core/math/math.hpp"

namespace rythe::rendering
{
	namespace log = core::log;
	namespace math = core::math;
	struct shader
	{
	private:
		unsigned int m_programId = 0;
		std::string m_vertexSource;
		std::string m_fragSource;
		std::unordered_map<std::string, unsigned int> m_uniforms;

	public:
		shader() = default;
		shader(const std::string& filepath);

		operator unsigned int() const { return m_programId; }

		void initialize();
		void bind();
		void deleteShader();
		
		shader& loadShader(const std::string& filepath);

		template<typename uniformType>
		void setUniform(const std::string& name, uniformType value);

		bool logCall()
		{
			bool success = true;
			while (GLenum error = glGetError())
			{
				log::error(error);
				__debugbreak();
				success = false;
			}
			return success;
		}

	private:
		bool registerUniform(const std::string& name);
		unsigned int compileShader(unsigned int type, const std::string& source);
	};
}

#include "rendering/data/shader.inl"