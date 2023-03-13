#pragma once
#include <vector>
#include <concepts>

#include <rythe/primitives>

#include "core/core.hpp"
#include "rendering/data/bufferconcepts.hpp"

namespace rythe::rendering
{
	template<typename APIType, typename T, typename dataType>
		requires validType<T>
	struct Ibuffer
	{
	private:
		APIType m_impl;
	public:
		void initialize() { m_impl.initialize(); }
		void bind() { m_impl.bind(); }
		void unbind() { m_impl.unbind(); }

		void bufferData(dataType data[], int size, unsigned int usage) { m_impl.bufferData(data, size, usage); }
		void setAttributePtr(int index, int components, unsigned int type, bool normalize, int stride, const void* pointer = 0) { m_impl.setAttributePtr(index, components, type, normalize, stride, pointer); }
	};

}