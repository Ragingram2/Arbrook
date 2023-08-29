#pragma once
#include <string>

#include "rendering/interface/enumtypes.hpp"
#include "rendering/data/handles.hpp"
#include "rendering/data/bufferhandle.hpp"
#include "rendering/interface/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	class ShaderCache;
	template<typename APIType>
	class IRenderInterface;
	namespace internal
	{
		struct inputlayout;
		struct shader;
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
		//friend struct data_handle<Ishader<internal::shader>>;
		friend struct shader_handle;
	private:
		APIType m_impl;
	public:
		void bind() { m_impl.bind(); }
		void addBuffer(ShaderType type, buffer_handle handle) { m_impl.addBuffer(static_cast<internal::ShaderType>(type), handle); }
		template<typename elementType>
		void setData(const std::string& bufferName, elementType data[]) { m_impl.setData(bufferName, data); }

		std::string getName() { return m_impl.name; }
		unsigned int getId() { return m_impl.programId; }
	private:
		APIType& getImpl() { return m_impl; }
	};
}