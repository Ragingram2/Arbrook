#pragma once
#include <D3D11.h>
#include <D3DX11.h>
#include <D3DX10.h>

#include "rendering/data/config.hpp"
#include Window_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering::internal
{
	struct buffer
	{
		unsigned int m_id = 0;
		ID3D11Buffer* m_internalBuffer;
	private:
		D3D11_BUFFER_DESC bd;
		TargetType m_target;
		UsageType m_usage;
		int m_numBuffers = 1;

	public:

		void initialize(TargetType target, UsageType usage)
		{
			m_target = target;
			m_usage = usage;

			ZeroMemory(&bd, sizeof(bd));

			bd.Usage = static_cast<D3D11_USAGE>(m_usage);
			bd.BindFlags = static_cast<D3D11_BIND_FLAG>(m_target);
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		}

		void bind()
		{

		}

		template<typename elementType, typename dataType>
		void bufferData(window& hwnd, elementType data[], int size)
		{
			bd.ByteWidth = sizeof(dataType) * size;

			D3D11_SUBRESOURCE_DATA initData;
			ZeroMemory(&initData, sizeof(initData));
			initData.pSysMem = data;

			hwnd.m_dev->CreateBuffer(&bd, &initData, &m_internalBuffer);

			D3D11_MAPPED_SUBRESOURCE resource;
			HRESULT hResult = hwnd.m_devcon->Map(m_internalBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &resource);

			// This will be S_OK
			if (hResult != S_OK)
			{
				log::debug("Buffer failed to be filled");
				return;
			}
			resource.pData = data;

			hwnd.m_devcon->Unmap(m_internalBuffer, NULL);
		}
	};
}