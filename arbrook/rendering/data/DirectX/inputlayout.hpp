#pragma once
#include <memory>

#include <rythe/primitives>

#include "core/logging/logging.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/vertex.hpp"
#include "rendering/data/vertexattribute.hpp"
#include "rendering/data/config.hpp"
#include Buffer_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct inputlayout
	{
	public:
		unsigned int id = 0;
	private:
		window m_hwnd;
		std::vector<D3D11_INPUT_ELEMENT_DESC> elementDesc;
		std::vector<buffer_handle> m_vertexBuffers;
		buffer_handle m_indexBuffer;
		std::vector<unsigned int> stride;
		std::vector<unsigned int> offset;
		std::vector<vertexattribute> m_vertexAttribs;
		ID3D11InputLayout* m_layout = nullptr;
		ID3D10Blob* m_vsBlob = nullptr;
	public:

		//pass a shader to be bound with
		void bind(window& hwnd, shader_handle shader)
		{
			m_hwnd = hwnd;
			m_vsBlob = shader->VS;

			std::vector<ID3D11Buffer*> buffers;
			int i = 0;
			stride.resize(m_vertexBuffers.size());
			offset.resize(m_vertexBuffers.size());
			for (auto& handle : m_vertexBuffers)
			{
				stride[i] = handle->elementSize;
				offset[i] = (i <= 0 ? 0 : offset[i - 1] + stride[i]);
				i++;
				buffers.push_back(handle.buffer->operator ID3D11Buffer * ());
			}

			m_hwnd.m_devcon->IASetVertexBuffers(0, m_vertexBuffers.size(), buffers.data(), stride.data(), offset.data());

			if (m_indexBuffer.buffer != nullptr)
				m_hwnd.m_devcon->IASetIndexBuffer(m_indexBuffer.buffer->internalBuffer, static_cast<DXGI_FORMAT>(FormatType::R32U), 0);
			else
				log::warn("No index buffer was bound, thats ok if this was intended behaviour");

			if (m_layout != nullptr)
				m_hwnd.m_devcon->IASetInputLayout(m_layout);
		}

		void unbind()
		{
			//Unbinding is done automatically
		}

		void addBuffer(buffer_handle handle)
		{
			switch (handle.getTargetType())
			{
			case TargetType::ARRAY_BUFFER:
				m_vertexBuffers.push_back(handle);
				break;
			case TargetType::ELEMENT_ARRAY_BUFFER:
				m_indexBuffer = handle;
				break;
			default:
				log::error("That type is not supported");
				break;
			}
		}

		//use custom vertex attrib, and std::move the string
		void setAttributePtr(const std::string& attribName, unsigned int index, FormatType components, unsigned int stride, unsigned int offset)
		{
			m_vertexAttribs.emplace_back(vertexattribute{ std::move(attribName), index, components, stride, offset });
		}

		void submitAttributes()
		{
			for (auto& attrib : m_vertexAttribs)
			{
				elementDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ attrib.name.c_str(), attrib.index, static_cast<DXGI_FORMAT>(attrib.format), 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 });
			}

			m_hwnd.m_dev->CreateInputLayout(elementDesc.data(), elementDesc.size(), m_vsBlob->GetBufferPointer(), m_vsBlob->GetBufferSize(), &m_layout);
			m_hwnd.m_devcon->IASetInputLayout(m_layout);
		}
	};
}