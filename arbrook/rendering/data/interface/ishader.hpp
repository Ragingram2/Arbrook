#pragma once
#include <string>
#include <GL/glew.h>

#include "core/math/math.hpp"

namespace rythe::rendering
{
	template<typename APIType>
	struct Ishader
	{
	private:
		APIType m_impl;
	public:
		const APIType* operator->() const { return m_impl; }
		APIType* operator->() { return m_impl; }

		void setUniform(const std::string& name, math::vec4 value) { m_impl.setUniform(name, value); }
		void setUniform(const std::string& name, math::vec3 value) { m_impl.setUniform(name, value); }
		void setUniform(const std::string& name, math::vec2 value) { m_impl.setUniform(name, value); }
		void setUniform(const std::string& name, float value) { m_impl.setUniform(name, value); }

		void setUniform(const std::string& name, math::ivec4 value) { m_impl.setUniform(name, value); }
		void setUniform(const std::string& name, math::ivec3 value) { m_impl.setUniform(name, value); }
		void setUniform(const std::string& name, math::ivec2 value) { m_impl.setUniform(name, value); }
		void setUniform(const std::string& name, int value) { m_impl.setUniform(name, value); }

		unsigned int getId() { m_impl.m_programId; }
	};
}