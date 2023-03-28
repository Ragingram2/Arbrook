#pragma once
#include <memory>

#include <rythe/primitives>

#include "rendering/data/vertex.hpp"
#include "rendering/data/config.hpp"
#include Buffer_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct vertexarray
	{
		unsigned int m_id;
		buffer m_indexBuffer;
		buffer m_vertexBuffer;

		window m_hwnd;

		void initialize(int num = 1)
		{
			m_vertexBuffer.initialize(TargetType::ARRAY_BUFFER, UsageType::StaticDraw);
			m_indexBuffer.initialize(TargetType::ELEMENT_ARRAY_BUFFER, UsageType::StaticDraw);
		}

		void bind(window& hwnd)
		{
			m_hwnd = hwnd;
			unsigned int stride = 4 * sizeof(float);
			unsigned int offset = 0;
			m_hwnd.m_devcon->IASetVertexBuffers(0, 1, &m_vertexBuffer.m_internalBuffer, &stride, &offset);
			m_hwnd.m_devcon->IASetIndexBuffer(m_indexBuffer.m_internalBuffer, DXGI_FORMAT_R32_UINT, offset);
		}

		void unbind()
		{

		}

		void bufferVertexData(vertex data[], int size)
		{
			m_vertexBuffer.bufferData(m_hwnd, data, size);

		}

		void bufferIndexData(unsigned int data[], int size)
		{
			m_indexBuffer.bufferData(m_hwnd, data, size);

		}

		void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0)
		{

		}
	};
}