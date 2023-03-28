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
	template<typename APIType>
	struct Ibuffer
	{
	private:
		APIType m_impl;
	public:
		const APIType* operator->() const { return m_impl; }
		APIType* operator->() { return &m_impl; }

		void initialize(TargetType target, UsageType usage) { m_impl.initialize(static_cast<internal::TargetType>(target), static_cast<internal::UsageType>(usage)); }
		void bind() { m_impl.bind(); }
		template<typename dataType>
		void bufferData(dataType data[], int size) { m_impl.bufferData(data, size); }
		void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0) { m_impl.setAttributePtr(index, components, static_cast<internal::DataType>(type), normalize, stride, pointer); }
	};
}