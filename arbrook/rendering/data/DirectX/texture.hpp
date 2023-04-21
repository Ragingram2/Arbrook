#pragma once
#include <string>

#include "rendering/data/DirectX/dx11includes.hpp"
#include "rendering/data/textureparameters.hpp"
#include "rendering/data/config.hpp"
#include Window_HPP_PATH

#include <stb/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION

namespace rythe::rendering::internal
{
	struct texture
	{
	private:
		ID3D11Texture2D* m_texture;
		ID3D11ShaderResourceView* m_shaderResource = nullptr;
		ID3D11SamplerState* m_texSamplerState = nullptr;
		D3D11_SAMPLER_DESC m_sampDesc;
		D3D11_TEXTURE2D_DESC m_texDesc;
		TargetType m_texType;
		UsageType m_usage;
		window m_hwnd;
	public:
		unsigned int id;
		std::string name;
		unsigned char* data;
		texture_parameters params;
		texture() = default;
		texture(unsigned int id, std::string name) : id(id), name(name) { }
		texture(texture* other)
		{
			name = other->name;
			id = other->id;
			data = other->data;
			params = other->params;
		}

		void initialize(window& hwnd, TargetType texType, UsageType usage, texture_parameters params, bool generateMipMaps = false)
		{
			m_hwnd = hwnd;
			m_texType = texType;
			m_usage = usage;
			this->params = params;
		}

		void bind()
		{
			m_hwnd.m_devcon->PSSetShaderResources(0, 1, &m_shaderResource);
			m_hwnd.m_devcon->PSSetSamplers(0, 1, &m_texSamplerState);
		}

		void loadData(const std::string& filepath, bool flipVertical = true)
		{
			ZeroMemory(&m_sampDesc, sizeof(m_sampDesc));
			m_sampDesc.Filter = static_cast<D3D11_FILTER>(params.filterMode);// D3D11_FILTER_MIN_MAG_MIP_LINEAR;
			m_sampDesc.AddressU = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(params.wrapModeS);//D3D11_TEXTURE_ADDRESS_WRAP;
			m_sampDesc.AddressV = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(params.wrapModeT);//D3D11_TEXTURE_ADDRESS_WRAP;
			m_sampDesc.AddressW = static_cast<D3D11_TEXTURE_ADDRESS_MODE>(params.wrapModeT);//D3D11_TEXTURE_ADDRESS_WRAP;
			//m_sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
			m_sampDesc.MinLOD = 0;
			m_sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

			HRESULT hr = m_hwnd.m_dev->CreateSamplerState(&m_sampDesc, &m_texSamplerState);
			if (FAILED(hr))
			{
				log::error("Texture sampler failed creation");
			}

			log::debug("loading Data");
			stbi_set_flip_vertically_on_load(flipVertical);
			data = stbi_load(filepath.c_str(), &params.resolution.x, &params.resolution.y, &params.channels, 0);
			if (!data)
			{
				log::error("Image failed to load");
			}

			ZeroMemory(&m_texDesc, sizeof(m_texDesc));
			m_texDesc.Width = params.resolution.x;
			m_texDesc.Height = params.resolution.y;
			m_texDesc.MipLevels = params.mipLevels;
			m_texDesc.ArraySize = 1;
			m_texDesc.Format = static_cast<DXGI_FORMAT>(params.format);
			m_texDesc.SampleDesc.Count = 1;
			m_texDesc.SampleDesc.Quality = 0;
			m_texDesc.Usage = static_cast<D3D11_USAGE>(m_usage);
			m_texDesc.BindFlags = static_cast<unsigned int>(m_texType);

			D3D11_SUBRESOURCE_DATA subData;
			subData.pSysMem = data;
			subData.SysMemPitch = m_texDesc.Width * 4;

			hr = m_hwnd.m_dev->CreateTexture2D(&m_texDesc, &subData, &m_texture);
			if (FAILED(hr))
			{
				log::error("Texture creation failed");
				m_hwnd.checkError();
			}

			hr = m_hwnd.m_dev->CreateShaderResourceView(m_texture, nullptr, &m_shaderResource);
			if (FAILED(hr))
			{
				log::error("Failed to create the ShaderResourceView");
				m_hwnd.checkError();
			}
		}
	};
}
