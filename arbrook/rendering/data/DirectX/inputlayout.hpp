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

namespace rythe::rendering
{
	template<typename APIType>
	struct Ishader;

	namespace internal
	{
		struct shader;
	}
}

namespace rythe::rendering::internal
{
	struct inputlayout
	{
		friend struct rendering::Ishader<shader>;
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
		void bind(window& hwnd, rendering::shader_handle shader)
		{
			m_hwnd = hwnd;
			m_vsBlob = shader->getImpl().VS;

			std::vector<ID3D11Buffer*> buffers;
			int i = 0;
			stride.resize(m_vertexBuffers.size());
			offset.resize(m_vertexBuffers.size());
			for (auto& handle : m_vertexBuffers)
			{
				stride[i] = handle->m_impl.m_elementSize;
				offset[i] = (i <= 0 ? 0 : offset[i - 1] + stride[i]);
				i++;
				buffers.push_back(handle.buffer->m_impl);
			}

			m_hwnd.devcon->IASetVertexBuffers(0, m_vertexBuffers.size(), buffers.data(), stride.data(), offset.data());

			if (m_indexBuffer.buffer != nullptr)
				m_hwnd.devcon->IASetIndexBuffer(m_indexBuffer.buffer->m_impl, static_cast<DXGI_FORMAT>(FormatType::R32U), 0);
			else
				log::warn("No index buffer was bound, thats ok if this was intended behaviour");

			if (m_layout != nullptr)
				m_hwnd.devcon->IASetInputLayout(m_layout);
		}

		void addBuffer(buffer_handle handle)
		{
			switch (static_cast<internal::TargetType>(handle.getTargetType()))
			{
			case TargetType::VERTEX_BUFFER:
				m_vertexBuffers.push_back(handle);
				break;
			case TargetType::INDEX_BUFFER:
				m_indexBuffer = handle;
				break;
			default:
				log::error("That type is not supported");
				break;
			}
		}

		void setAttributePtr(const std::string& attribName, unsigned int index, FormatType components, unsigned int stride, unsigned int offset, InputClass inputClass)
		{
			m_vertexAttribs.emplace_back(vertexattribute{ std::move(attribName), index, components, stride, offset, inputClass });
		}

		void submitAttributes()
		{
			for (auto& attrib : m_vertexAttribs)
			{
				elementDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ attrib.name.c_str(), 0, static_cast<DXGI_FORMAT>(attrib.format), 0, D3D11_APPEND_ALIGNED_ELEMENT, static_cast<D3D11_INPUT_CLASSIFICATION>(attrib.inputClass),0 });
			}

			m_hwnd.dev->CreateInputLayout(elementDesc.data(), elementDesc.size(), m_vsBlob->GetBufferPointer(), m_vsBlob->GetBufferSize(), &m_layout);
			m_hwnd.devcon->IASetInputLayout(m_layout);
		}
	};
}
