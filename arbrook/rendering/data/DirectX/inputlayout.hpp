#pragma once
#include <memory>

#include <rythe/primitives>

#include "core/logging/logging.hpp"

#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/vertexattribute.hpp"
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH
#include Window_HPP_PATH

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
		std::vector<vertexattribute> m_vertexAttribs;
		ID3D11InputLayout* m_layout = nullptr;
		ID3D10Blob* m_vsBlob = nullptr;
	public:
		void initialize(window& hwnd, unsigned int numBuffers, shader_handle shader)
		{
			m_hwnd = hwnd;
			m_vsBlob = shader->getImpl().VS;
		}

		void bind()
		{
			if (m_vertexAttribs.size() > 0)
			{
				for (auto& attrib : m_vertexAttribs)
				{
					elementDesc.emplace_back(D3D11_INPUT_ELEMENT_DESC{ attrib.name.c_str(), attrib.index, static_cast<DXGI_FORMAT>(attrib.format), attrib.inputSlot, D3D11_APPEND_ALIGNED_ELEMENT, static_cast<D3D11_INPUT_CLASSIFICATION>(attrib.inputClass),attrib.step });
				}
				CHECKERROR(m_hwnd.dev->CreateInputLayout(elementDesc.data(), elementDesc.size(), m_vsBlob->GetBufferPointer(), m_vsBlob->GetBufferSize(), &m_layout),"Failed creating input layout",m_hwnd.checkError());

				clearAttributes();
			}

			m_hwnd.devcon->IASetInputLayout(m_layout);
		}

		void setAttributePtr(const std::string& attribName, unsigned int index, FormatType components, unsigned int inputSlot, unsigned int stride, unsigned int offset, InputClass inputClass, unsigned int instancedStep)
		{
			m_vertexAttribs.emplace_back(vertexattribute{ std::move(attribName), index, components, inputSlot, stride, offset, inputClass, instancedStep });
		}

		void clearAttributes()
		{
			m_vertexAttribs.clear();
			elementDesc.clear();
		}

		void release()
		{
			if (!m_layout)
			{
				return;
			}
			m_layout->Release();
			m_layout = nullptr;
			clearAttributes();
		}
	};
}
