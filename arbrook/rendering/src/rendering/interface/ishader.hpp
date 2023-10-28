#pragma once
#include <string>

#include "rendering/interface/enumtypes.hpp"
#include "rendering/interface/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	struct buffer_handle;
	class ShaderCache;

	template<typename APIType>
	struct Ishader
	{
		friend class ShaderCache;
		//friend class IRenderInterface<internal::RenderInterface>;
		//friend struct internal::inputlayout;
		//friend struct shader_handle;
	private:
		APIType m_impl;
	public:
		void bind() { m_impl.bind(); }
		void addBuffer(ShaderType type, buffer_handle handle) { m_impl.addBuffer(static_cast<internal::ShaderType>(type), handle); }
		template<typename elementType>
		void setData(const std::string& bufferName, elementType data[]) { m_impl.setData(bufferName, data); }
		void release() { m_impl.release(); }
		void clearBuffers() { m_impl.clearBuffers(); }

		std::string getName() { return m_impl.name; }
		unsigned int getId() { return m_impl.programId; }
	private:
		APIType& getImpl() { return m_impl; }
	};
}