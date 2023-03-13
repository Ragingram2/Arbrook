#pragma once
#include <memory>

#include <rythe/primitives>

#include "rendering/data/DirectX/buffer.hpp"

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

		void bufferVertexData(float data[], int size, unsigned int usage)
		{

		}

		void bufferIndexData(unsigned int data[], int size, unsigned int usage)
		{

		}

		void setAttributePtr(int index, int components, unsigned int type, bool normalize, int stride, const void* pointer = 0)
		{

		}
	};
}