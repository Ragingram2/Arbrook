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
}

namespace rythe::rendering::internal
{
	struct buffer
	{
		friend struct rendering::buffer_handle;
	public:
		unsigned int id = 0;
		unsigned int elementSize = 0;
		ID3D11Buffer* internalBuffer;
	private:
		D3D11_BUFFER_DESC m_bufferDesc;
		TargetType m_target;
		UsageType m_usage;
	public:
		operator ID3D11Buffer* () const { return internalBuffer; }
		void initialize(TargetType target, UsageType usage)
		{
			m_target = target;
			m_usage = usage;

			ZeroMemory(&m_bufferDesc, sizeof(m_bufferDesc));

			m_bufferDesc.Usage = static_cast<D3D11_USAGE>(m_usage);
			m_bufferDesc.BindFlags = static_cast<D3D11_BIND_FLAG>(m_target);
			m_bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		void bind(window& hwnd)
		{
			switch (m_target)
			{
			case TargetType::ARRAY_BUFFER:
				hwnd.m_devcon->IASetVertexBuffers(0, 1, &internalBuffer, &elementSize, 0);
				break;
			case TargetType::ELEMENT_ARRAY_BUFFER:
				hwnd.m_devcon->IASetIndexBuffer(internalBuffer, static_cast<DXGI_FORMAT>(FormatType::R32U), 0);
				break;
			default:
				log::error("That type is not supported");
				break;
			}
		}

		template<typename elementType, typename dataType>
		void bufferData(window& hwnd, elementType data[], int size)
		{
			elementSize = sizeof(elementType);
			m_bufferDesc.ByteWidth = sizeof(dataType) * size;

			hwnd.m_dev->CreateBuffer(&m_bufferDesc, NULL, &internalBuffer);

			D3D11_MAPPED_SUBRESOURCE resource;
			HRESULT hResult = hwnd.m_devcon->Map(internalBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &resource);
			memcpy(resource.pData, data, size);
			// This will be S_OK
			if (hResult != S_OK)
			{
				log::debug("Buffer failed to be filled");
				return;
			}

			hwnd.m_devcon->Unmap(internalBuffer, NULL);
		}
	};
}