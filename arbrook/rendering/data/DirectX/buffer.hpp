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
	private:
		ID3D11Buffer* m_internalBuffer;
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

		template<typename dataType>
		void bufferData(dataType data[], int size)
		{
			bd.ByteWidth = sizeof(dataType) * size;

			window::dev->CreateBuffer(&bd, NULL, &m_internalBuffer);

			D3D11_MAPPED_SUBRESOURCE ms;
			window::devcon->Map(m_internalBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);
			memcpy(ms.pData, data, size);
			window::devcon->Unmap(m_internalBuffer, NULL);
		}

		void setAttributePtr(int index, int components, DataType type, bool normalize, int stride, const void* pointer = 0)
		{

		}
	};
}