#pragma once
#include <vector>
#include <concepts>

#include <rythe/primitives>

#include "core/core.hpp"
#include "rendering/data/interface/enumtypes.hpp"
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
		struct shader;
		class RenderInterface;
	}
}

namespace rythe::rendering
{
	template<typename APIType>
	struct Ibuffer
	{
		friend class BufferCache;
		friend class IRenderInterface<internal::RenderInterface>;
		friend struct internal::inputlayout;
		friend struct internal::shader;
		friend struct buffer_handle;
	private:
		APIType m_impl;
	public:
		void initialize(TargetType target, UsageType usage) { m_impl.initialize(static_cast<internal::TargetType>(target), static_cast<internal::UsageType>(usage)); }
		void bind() { m_impl.bind(); }
		template<typename elementType, typename dataType = elementType>
		void bufferData(elementType data[], int size) { m_impl.bufferData<elementType,dataType>(data, size); }

		std::string getName() { return m_impl.name; }
		unsigned int getId() { return m_impl.id; }
		TargetType getTargetType() { return static_cast<TargetType>(m_impl.m_target); }
	private:
		APIType& getImpl() { return m_impl; }
	};
}