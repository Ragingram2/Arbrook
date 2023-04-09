#pragma once
#include <memory>

#include <rythe/primitives>

#include "core/logging/logging.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/vertex.hpp"
#include "rendering/data/vertexattribute.hpp"
#include "rendering/data/config.hpp"
#include Buffer_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct vertexarray
	{

	private:
		std::vector<vertexattribute> m_vertexAttribs;
		ID3D11InputLayout* pLayout = nullptr;
		ID3D10Blob* m_vsBlob = nullptr;
		window m_hwnd;

	public:
		unsigned int m_id = 0;
		buffer m_indexBuffer;
		buffer m_vertexBuffer;

	public:
		//pass a shader to be bound with
		void initialize(int num = 1)
		{
			m_vertexBuffer.initialize(TargetType::ARRAY_BUFFER, UsageType::StaticDraw);
			m_indexBuffer.initialize(TargetType::ELEMENT_ARRAY_BUFFER, UsageType::StaticDraw);
			m_id = 1;
			log::debug("VAO INIT");
		}

		void bind(window& hwnd)
		{
			if (m_id == 0)
				initialize();

			m_hwnd = hwnd;
			m_vsBlob = rendering::activeShader->VS;

			unsigned int stride[1] = { sizeof(vertex) };
			unsigned int offset = 0;

			m_hwnd.m_devcon->IASetVertexBuffers(0, 1, &m_vertexBuffer.m_internalBuffer, stride, &offset);

			//Not required here, it is possible not to need indecies
			m_hwnd.m_devcon->IASetIndexBuffer(m_indexBuffer.m_internalBuffer, static_cast<DXGI_FORMAT>(FormatType::R32U), offset);
			m_hwnd.m_devcon->IASetInputLayout(pLayout);
		}

		void unbind()
		{
			//m_hwnd.m_devcon->IASetVertexBuffers(0, 1, NULL, 0, 0);
			//m_hwnd.m_devcon->IASetIndexBuffer(NULL, static_cast<DXGI_FORMAT>(FormatType::R32U), 0);
			//m_hwnd.m_devcon->IASetInputLayout(NULL);
		}

		void submitAttributes()
		{
			std::vector<D3D11_INPUT_ELEMENT_DESC> elementDesc;
			for (auto attrib : m_vertexAttribs)
			{
				elementDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ attrib.name, attrib.index, static_cast<DXGI_FORMAT>(attrib.format), 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
			}

			m_hwnd.m_dev->CreateInputLayout(elementDesc.data(), elementDesc.size(), m_vsBlob->GetBufferPointer(), m_vsBlob->GetBufferSize(), &pLayout);
			m_hwnd.m_devcon->IASetInputLayout(pLayout);
		}

		void bufferVertexData(vertex data[], int size)
		{
			m_vertexBuffer.bufferData<vertex, float>(m_hwnd, data, size);
		}

		void bufferIndexData(unsigned int data[], int size)
		{
			m_indexBuffer.bufferData<unsigned int, unsigned int>(m_hwnd, data, size);
		}
		//use custom vertex attrib, and std::move the string
		void setAttributePtr(const char* attribName, unsigned int index, FormatType components, unsigned int stride, unsigned int offset)
		{
			m_vertexAttribs.emplace_back(vertexattribute{ attribName, index, components, stride, offset });
		}
	};
}