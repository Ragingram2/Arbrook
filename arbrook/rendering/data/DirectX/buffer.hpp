#pragma once
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include "core/logging/logging.hpp"

#include "rendering/data/config.hpp"
#include Window_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	struct buffer_handle;
	template<typename APIType>
	struct Ibuffer;

	namespace internal
	{
		struct inputlayout;
	}
}

namespace rythe::rendering::internal
{
	struct buffer
	{
		friend struct rendering::buffer_handle;
		friend struct Ibuffer<internal::buffer>;
		friend struct internal::inputlayout;
	public:
		unsigned int id = 0;
		std::string name;
	private:
		unsigned int m_size;
		unsigned int m_elementSize = 0;

		ID3D11Buffer* m_internalBuffer;
		D3D11_BUFFER_DESC m_bufferDesc;

		TargetType m_target;
		UsageType m_usage;
		window m_hwnd;

	public:
		operator ID3D11Buffer* () const { return m_internalBuffer; }
		template<typename elementType>
		void initialize(window& hwnd, TargetType target, UsageType usage, int size)
		{
			m_hwnd = hwnd;
			m_target = target;
			m_usage = usage;
			m_size = size;
			m_elementSize = sizeof(elementType);

			createBuffer();
		}

		void bind()
		{
			switch (m_target)
			{
			case TargetType::VERTEX_BUFFER:
				m_hwnd.m_devcon->IASetVertexBuffers(0, 1, &m_internalBuffer, &m_elementSize, 0);
				break;
			case TargetType::INDEX_BUFFER:
				m_hwnd.m_devcon->IASetIndexBuffer(m_internalBuffer, static_cast<DXGI_FORMAT>(FormatType::R32U), 0);
				break;
			case TargetType::CONSTANT_BUFFER:
				m_hwnd.m_devcon->VSSetConstantBuffers(0, 1, &m_internalBuffer);
				break;
			default:
				log::error("That type is not supported");
				break;
			}
		}

		template<typename elementType>
		void bufferData(elementType data[], int size = 0)
		{
			if (size < 1)
			{
				size = m_size;
			}
			else if (size > m_size)
			{
				m_size = size;
				m_elementSize = sizeof(elementType);
				createBuffer();
			}

			D3D11_MAPPED_SUBRESOURCE resource;
			HRESULT hr = m_hwnd.m_devcon->Map(m_internalBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &resource);
			m_hwnd.checkError();
			memcpy(resource.pData, data, m_size * sizeof(elementType));
			if (FAILED(hr))
			{
				log::error("Buffer failed to be filled");
				return;
			}

			m_hwnd.m_devcon->Unmap(m_internalBuffer, NULL);
		}

	private:
		void createBuffer()
		{
			ZeroMemory(&m_bufferDesc, sizeof(m_bufferDesc));

			m_bufferDesc.Usage = static_cast<D3D11_USAGE>(m_usage);
			m_bufferDesc.BindFlags = static_cast<D3D11_BIND_FLAG>(m_target);
			m_bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			m_bufferDesc.MiscFlags = 0;
			m_bufferDesc.StructureByteStride = 0;

			if (m_target == TargetType::CONSTANT_BUFFER)
				m_bufferDesc.ByteWidth = static_cast<unsigned int>(m_elementSize + (16 - (m_elementSize % 16)));
			else
				m_bufferDesc.ByteWidth = m_elementSize;

			m_bufferDesc.ByteWidth *= m_size;

			HRESULT hr = m_hwnd.m_dev->CreateBuffer(&m_bufferDesc, NULL, &m_internalBuffer);
			m_hwnd.checkError();
			if (FAILED(hr))
			{
				log::error("Buffer failed to be created");
				return;
			}
		}
	};
}