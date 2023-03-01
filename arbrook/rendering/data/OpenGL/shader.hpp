#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_map>

#include <GL/glew.h>
 
#include "core/logging/logging.hpp"
#include "core/math/math.hpp"

namespace rythe::rendering::internal
{
	namespace log = core::log;
	namespace math = core::math;

	
	struct shader
	{
	public:
		unsigned int m_programId;
		std::unordered_map<std::string, unsigned int> m_uniforms;

		shader() = default;

		operator unsigned int() const { return m_programId; }

		//void initialize();
		void bind();
		//void deleteShader();
		
		//shader& loadShader(const std::string& filepath);

		template<typename uniformType>
		void setUniform(const std::string& name, uniformType value);

	private:
		bool registerUniform(const std::string& name);
		//unsigned int compileShader(unsigned int type, const std::string& source);
	};
}