#pragma once
#include <memory>

#include <rythe/primitives>

#include "core/logging/logging.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/vertex.hpp"
#include "rendering/data/config.hpp"
#include Buffer_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct vertexarray
	{
	public:
		unsigned int m_id;
		buffer m_indexBuffer;
		buffer m_vertexBuffer;

	private:
		std::vector<D3D11_INPUT_ELEMENT_DESC> m_elementDesc;
		ID3D11InputLayout* pLayout;
		ID3D10Blob* m_vsBlob;

		window m_hwnd;
	public:
		void initialize(int num = 1)
		{
			m_vertexBuffer.initialize(TargetType::ARRAY_BUFFER, UsageType::StaticDraw);
			m_indexBuffer.initialize(TargetType::ELEMENT_ARRAY_BUFFER, UsageType::StaticDraw);
			m_id = 1;
		}

		void bind(window& hwnd)
		{
			m_hwnd = hwnd;

			if (m_id == 0)
				initialize();

			m_vsBlob = rendering::activeShader->VS;

			unsigned int stride[1] = { sizeof(vertex) };
			unsigned int offset = 0;

			m_hwnd.m_devcon->IASetVertexBuffers(0, 1, &m_vertexBuffer.m_internalBuffer, stride, &offset);
			m_hwnd.m_devcon->IASetIndexBuffer(m_indexBuffer.m_internalBuffer, static_cast<DXGI_FORMAT>(FormatType::R32U), offset);
			m_hwnd.m_devcon->IASetInputLayout(pLayout);
		}

		void unbind()
		{

		}

		void submitAttributes()
		{
			m_hwnd.m_dev->CreateInputLayout(m_elementDesc.data(), m_elementDesc.size(), m_vsBlob->GetBufferPointer(), m_vsBlob->GetBufferSize(), &pLayout);
		}

		void bufferVertexData(vertex data[], int size)
		{
			m_vertexBuffer.bufferData<vertex, float>(m_hwnd, data, size);
		}

		void bufferIndexData(unsigned int data[], int size)
		{
			m_indexBuffer.bufferData<unsigned int, unsigned int>(m_hwnd, data, size);
		}

		void setAttributePtr(LPCSTR attribName, unsigned int index, FormatType components, int stride, unsigned int offset)
		{
			m_elementDesc.emplace_back<D3D11_INPUT_ELEMENT_DESC>({ attribName, index, static_cast<DXGI_FORMAT>(components), 0, offset, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		}
	};
}