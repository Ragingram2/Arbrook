#pragma once
#include <memory>

#include <rythe/primitives>

#include "rendering/data/config.hpp"
#include Buffer_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct vertexarray
	{
		unsigned int m_id;
		//buffer<index, unsigned int> m_indexBuffer;
		//buffer<vertex, float> m_vertexBuffer;

		void initialize(int num = 1)
		{

		}

		void bind()
		{

		}

		void unbind()
		{
	
		}

		void bufferVertexData(float data[], int size, UsageType usage)
		{

		}

		void bufferIndexData(unsigned int data[], int size, UsageType usage)
		{

		}

		void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0)
		{

		}
	};
}