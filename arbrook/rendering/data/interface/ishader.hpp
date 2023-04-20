#pragma once
#include <string>

#include "core/math/math.hpp"
#include "rendering/data/interface/enumtypes.hpp"
#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	class ShaderCache;
	template<typename APIType>
	class IRenderInterface;
	namespace internal
	{
		struct inputlayout;
		class RenderInterface;
	}
}

namespace rythe::rendering
{
	template<typename APIType>
	struct Ishader
	{
		friend class ShaderCache;
		friend class IRenderInterface<internal::RenderInterface>;
		friend struct internal::inputlayout;
		friend struct shader_handle;
	private:
		APIType m_impl;
	public:
		void bind() { m_impl.bind(); }
		void addBuffer(ShaderType type, buffer_handle handle) { m_impl.addBuffer(static_cast<internal::ShaderType>(type), handle); }
		template<typename elementType>
		void setData(const std::string& bufferName, elementType data[]) { m_impl.setData(bufferName, data); }
		//void setUniform(const std::string& name, math::vec4 value) { m_impl.setUniform(name, value); }
		//void setUniform(const std::string& name, math::vec3 value) { m_impl.setUniform(name, value); }
		//void setUniform(const std::string& name, math::vec2 value) { m_impl.setUniform(name, value); }
		//void setUniform(const std::string& name, float value) { m_impl.setUniform(name, value); }

		//void setUniform(const std::string& name, math::ivec4 value) { m_impl.setUniform(name, value); }
		//void setUniform(const std::string& name, math::ivec3 value) { m_impl.setUniform(name, value); }
		//void setUniform(const std::string& name, math::ivec2 value) { m_impl.setUniform(name, value); }
		//void setUniform(const std::string& name, int value) { m_impl.setUniform(name, value); }

		std::string getName() { return m_impl.name; }
		unsigned int getId() { return m_impl.programId; }
	private:
		APIType& getImpl() { return m_impl; }
	};
}