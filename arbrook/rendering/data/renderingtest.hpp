#pragma once
#include <chrono>
#include <ctime>
#include <GLFW/glfw3.h>

#include <rythe/delegate>

#include "core/ecs/ecs.hpp"
#include "rendering/data/definitions.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/shadercache.hpp"
#include "rendering/data/texturecache.hpp"
#include "rendering/data/buffercache.hpp"
#include "rendering/components/spriterenderer.hpp"
#include "rendering/data/vertex.hpp"


namespace rythe::rendering
{

	struct rendering_test
	{
		virtual ~rendering_test() = default;
		virtual void setup(RenderInterface* api) = 0;
		virtual void update(RenderInterface* api) = 0;
		virtual void destroy(RenderInterface* api) = 0;
	};

#pragma region My API
	//make seperate rendering test structs 
	struct API_DrawArraysTest : public rendering_test
	{
		inputlayout layout;
		buffer_handle buffer;
		shader_handle shader;
		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing API_TestDrawArrays");
			glfwSetWindowTitle(api->getWindow(), "API_TestDrawArrays");
			math::vec3 verticies[6] =
			{	//positions						
				{  -0.1f, 0.1f, 0.0f  },//0
				{ 	-0.1f,-0.1f, 0.0f  },//1
				{  0.1f,-0.1f, 0.0f  },//2
				{  -0.1f, 0.1f, 0.0f  },//0
				{  0.1f,-0.1f, 0.0f },//2
				{  0.1f, 0.1f, 0.0f }//3
			};
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/test.shader");
			buffer = BufferCache::createBuffer<math::vec3>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(math::vec3));
			shader->bind();
			layout.addBuffer(buffer);
			layout.bind(api->getHwnd(), shader);
			layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec3), 0);
			layout.submitAttributes();
		}

		virtual void update(RenderInterface* api) override
		{
			shader->bind();
			layout.bind(api->getHwnd(), shader);
			api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			ShaderCache::deleteShader("test");
			layout.release();
		}
	};

	struct API_DrawArraysInstancedTest : public rendering_test
	{
		inputlayout layout;
		buffer_handle buffer;
		shader_handle shader;
		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing API_DrawArraysInstancedTest");
			glfwSetWindowTitle(api->getWindow(), "API_DrawArraysInstancedTest");
			math::vec3 verticies[6] =
			{	//positions						
				{  -0.1f, 0.1f, 0.0f  },//0
				{ 	-0.1f,-0.1f, 0.0f  },//1
				{  0.1f,-0.1f, 0.0f  },//2
				{  -0.1f, 0.1f, 0.0f  },//0
				{  0.1f,-0.1f, 0.0f },//2
				{  0.1f, 0.1f, 0.0f }//3
			};
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/instance_test.shader");
			buffer = BufferCache::createBuffer<math::vec3>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(math::vec3));
			shader->bind();
			layout.addBuffer(buffer);
			layout.bind(api->getHwnd(), shader);
			layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec3), 0);
			layout.submitAttributes();
		}

		virtual void update(RenderInterface* api) override
		{
			shader->bind();
			layout.bind(api->getHwnd(), shader);
			api->drawArraysInstanced(PrimitiveType::TRIANGLESLIST, 6, 2, 0, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			ShaderCache::deleteShader("test");
			layout.release();
		}
	};

	struct API_DrawIndexedTest : public rendering_test
	{
		inputlayout layout;
		buffer_handle vBuffer;
		buffer_handle idxBuffer;
		shader_handle shader;
		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing API_DrawIndexedTest");
			glfwSetWindowTitle(api->getWindow(), "API_DrawIndexedTest");
			math::vec3 verticies[4] =
			{	//positions						
				{  -0.1f, 0.1f, 0.0f  },//0
				{ 	-0.1f,-0.1f, 0.0f  },//1
				{  0.1f,-0.1f, 0.0f  },//2
				{  0.1f, 0.1f, 0.0f  },//3
			};
			unsigned int indicies[6] =
			{
				0,1,2,
				0,2,3
			};
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/test.shader");
			vBuffer = BufferCache::createBuffer<math::vec3>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(math::vec3));
			idxBuffer = BufferCache::createBuffer<unsigned int>(*api, "Index Buffer", TargetType::INDEX_BUFFER, UsageType::STATICDRAW, indicies, sizeof(indicies) / sizeof(unsigned int));
			shader->bind();
			layout.addBuffer(vBuffer);
			layout.addBuffer(idxBuffer);
			layout.bind(api->getHwnd(), shader);
			layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec3), 0);
			layout.submitAttributes();
		}

		virtual void update(RenderInterface* api) override
		{
			shader->bind();
			layout.bind(api->getHwnd(), shader);
			api->drawIndexed(PrimitiveType::TRIANGLESLIST, 6, 0, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			BufferCache::deleteBuffer("Index Buffer");
			ShaderCache::deleteShader("test");
			layout.release();
		}
	};

	struct API_DrawIndexedInstancedTest : public rendering_test
	{
		inputlayout layout;
		buffer_handle vBuffer;
		buffer_handle idxBuffer;
		shader_handle shader;
		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing API_DrawIndexedInstancedTest");
			glfwSetWindowTitle(api->getWindow(), "API_DrawIndexedInstancedTest");
			math::vec3 verticies[4] =
			{	//positions						
				{  -0.1f, 0.1f, 0.0f  },//0
				{ 	-0.1f,-0.1f, 0.0f  },//1
				{  0.1f,-0.1f, 0.0f  },//2
				{  0.1f, 0.1f, 0.0f  },//3
			};
			unsigned int indicies[6] =
			{
				0,1,2,
				0,2,3
			};
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/instance_test.shader");
			vBuffer = BufferCache::createBuffer<math::vec3>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(math::vec3));
			idxBuffer = BufferCache::createBuffer<unsigned int>(*api, "Index Buffer", TargetType::INDEX_BUFFER, UsageType::STATICDRAW, indicies, sizeof(indicies) / sizeof(unsigned int));
			shader->bind();
			layout.addBuffer(vBuffer);
			layout.addBuffer(idxBuffer);
			layout.bind(api->getHwnd(), shader);
			layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec3), 0);
			layout.submitAttributes();
		}

		virtual void update(RenderInterface* api) override
		{
			shader->bind();
			layout.bind(api->getHwnd(), shader);
			api->drawIndexedInstanced(PrimitiveType::TRIANGLESLIST, 6, 2, 0, 0, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			BufferCache::deleteBuffer("Index Buffer");
			ShaderCache::deleteShader("test");
			layout.release();
		}
	};
#pragma endregion

#pragma region BGFX
	struct BGFX_DrawArraysTest : public rendering_test
	{
		virtual void setup(RenderInterface* api) override
		{
		}

		virtual void update(RenderInterface* api) override
		{
		}

		virtual void destroy(RenderInterface* api) override
		{
		}
	};
#pragma endregion

#pragma region Native API

#if RenderingAPI == RenderingAPI_OGL
	struct Native_DrawArraysTest : public rendering_test
	{
		unsigned int bufferId;
		unsigned int vaoId;
		unsigned int shaderId;
		shader_handle shader;
		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing NativeOGL_DrawArraysTest");
			glfwSetWindowTitle(api->getWindow(), "NativeOGL_DrawArraysTest");
			math::vec3 verticies[6] =
			{	//positions						
				{  -0.1f, 0.1f, 0.0f  },//0
				{ 	-0.1f,-0.1f, 0.0f  },//1
				{  0.1f,-0.1f, 0.0f  },//2
				{  -0.1f, 0.1f, 0.0f  },//0
				{  0.1f,-0.1f, 0.0f },//2
				{  0.1f, 0.1f, 0.0f }//3
			};
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/test.shader");
			shaderId = shader;
			glGenBuffers(1, &bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glBufferData(GL_ARRAY_BUFFER, 6 * (sizeof(math::vec3)), verticies, static_cast<GLenum>(UsageType::STATICDRAW));
			glUseProgram(shaderId);
			glGenVertexArrays(1, &vaoId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec3), reinterpret_cast<void*>(0));
			glVertexAttribDivisor(0, 0);
		}

		virtual void update(RenderInterface* api) override
		{
			glUseProgram(shaderId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}

		virtual void destroy(RenderInterface* api) override
		{
			ShaderCache::deleteShader("test");
		}
	};

	struct Native_DrawArraysInstancedTest : public rendering_test
	{
		unsigned int bufferId;
		unsigned int vaoId;
		unsigned int shaderId;
		shader_handle shader;
		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing NativeOGL_DrawArraysInstancedTest");
			glfwSetWindowTitle(api->getWindow(), "NativeOGL_DrawArraysInstancedTest");
			math::vec3 vertices[6] =
			{   // positions
				{ -0.1f, 0.1f, 0.0f },  // 0
				{ -0.1f,-0.1f, 0.0f },  // 1
				{  0.1f,-0.1f, 0.0f },  // 2
				{ -0.1f, 0.1f, 0.0f },  // 0
				{  0.1f,-0.1f, 0.0f },  // 2
				{  0.1f, 0.1f, 0.0f }   // 3
			};
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/instance_test.shader");
			shaderId = shader;
			glGenBuffers(1, &bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glBufferData(GL_ARRAY_BUFFER, 6 * (sizeof(math::vec3)), vertices, static_cast<GLenum>(UsageType::STATICDRAW));
			glUseProgram(shaderId);
			glGenVertexArrays(1, &vaoId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec3), reinterpret_cast<void*>(0));
		}

		virtual void update(RenderInterface* api) override
		{
			glUseProgram(shaderId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glDrawArraysInstanced(GL_TRIANGLES, 0, 6, 2); // Draw 2 instances
		}

		virtual void destroy(RenderInterface* api) override
		{
			ShaderCache::deleteShader("test");
		}
	};

	struct Native_DrawIndexedTest : public rendering_test
	{
		unsigned int vboId;
		unsigned int vaoId;
		unsigned int eboId;
		unsigned int shaderId;
		shader_handle shader;
		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing NativeOGL_DrawIndexedTest");
			glfwSetWindowTitle(api->getWindow(), "NativeOGL_DrawIndexedTest");
			math::vec3 vertices[4] =
			{   // positions
				{ -0.1f, -0.1f, 0.0f }, // 0
				{  0.1f, -0.1f, 0.0f }, // 1
				{  0.1f,  0.1f, 0.0f }, // 2
				{ -0.1f,  0.1f, 0.0f }  // 3
			};
			unsigned int indices[6] =
			{
				0, 1, 2,
				2, 3, 0
			};
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/test.shader");
			shaderId = shader;
			glGenBuffers(1, &vboId);
			glBindBuffer(GL_ARRAY_BUFFER, vboId);
			glBufferData(GL_ARRAY_BUFFER, 4 * (sizeof(math::vec3)), vertices, static_cast<GLenum>(UsageType::STATICDRAW));
			glGenBuffers(1, &eboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, static_cast<GLenum>(UsageType::STATICDRAW));
			glUseProgram(shaderId);
			glGenVertexArrays(1, &vaoId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, vboId);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec3), reinterpret_cast<void*>(0));
		}

		virtual void update(RenderInterface* api) override
		{
			glUseProgram(shaderId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
		}

		virtual void destroy(RenderInterface* api) override
		{
			ShaderCache::deleteShader("test");
		}
	};

	struct Native_DrawIndexedInstancedTest : public rendering_test
	{
		unsigned int vboId;
		unsigned int vaoId;
		unsigned int eboId;
		unsigned int shaderId;
		shader_handle shader;
		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing NativeOGL_DrawIndexedInstancedTest");
			glfwSetWindowTitle(api->getWindow(), "NativeOGL_DrawIndexedInstancedTest");
			math::vec3 vertices[4] =
			{   // positions
				{ -0.1f, -0.1f, 0.0f }, // 0
				{  0.1f, -0.1f, 0.0f }, // 1
				{  0.1f,  0.1f, 0.0f }, // 2
				{ -0.1f,  0.1f, 0.0f }  // 3
			};
			unsigned int indices[6] =
			{
				0, 1, 2,
				2, 3, 0
			};
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/instance_test.shader");
			shaderId = shader;
			glGenBuffers(1, &vboId);
			glBindBuffer(GL_ARRAY_BUFFER, vboId);
			glBufferData(GL_ARRAY_BUFFER, 4 * (sizeof(math::vec3)), vertices, static_cast<GLenum>(UsageType::STATICDRAW));
			glGenBuffers(1, &eboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(unsigned int), indices, static_cast<GLenum>(UsageType::STATICDRAW));
			glUseProgram(shaderId);
			glGenVertexArrays(1, &vaoId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, vboId);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec3), reinterpret_cast<void*>(0));
		}

		virtual void update(RenderInterface* api) override
		{
			glUseProgram(shaderId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
			glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, 2);
		}

		virtual void destroy(RenderInterface* api) override
		{
			ShaderCache::deleteShader("test");
		}
	};

#elif RenderingAPI == RenderingAPI_DX11

	inline void InitializeShadersAndLayout(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11InputLayout* inputLayout, ID3D10Blob* vtxBlob, ID3D10Blob* pixBlob, ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, rythe::rendering::shader_source source)
	{
		HRESULT hr = D3DCompile(source.vertexSource.c_str(), source.vertexSource.length(), nullptr, nullptr, nullptr, "VShader", "vs_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &vtxBlob, nullptr);
		if (FAILED(hr))
		{
			log::error("Vertex Shader Compilation failed");
		}
		hr = D3DCompile(source.fragSource.c_str(), source.fragSource.length(), nullptr, nullptr, nullptr, "PShader", "ps_4_0", D3DCOMPILE_ENABLE_STRICTNESS, 0, &pixBlob, nullptr);
		if (FAILED(hr))
		{
			log::error("Fragment Shader Compilation failed");
		}

		// Vertex shader
		device->CreateVertexShader(vtxBlob->GetBufferPointer(), vtxBlob->GetBufferSize(), 0, &vertexShader);
		device->CreatePixelShader(pixBlob->GetBufferPointer(), pixBlob->GetBufferSize(), 0, &pixelShader);

		// Set the shaders
		deviceContext->VSSetShader(vertexShader, 0, 0);
		deviceContext->PSSetShader(pixelShader, 0, 0);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		device->CreateInputLayout(layout, sizeof(layout) / sizeof(layout[0]), vtxBlob->GetBufferPointer(),
			vtxBlob->GetBufferSize(), &inputLayout);

		// Set the input layout
		deviceContext->IASetInputLayout(inputLayout);
	}

	struct Native_DrawArraysTest : public rendering_test
	{
		ID3D11Buffer* vertexBuffer;
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D10Blob* vertexBlob;
		ID3D10Blob* pixelBlob;
		ID3D11DeviceContext* deviceContext;
		ID3D11Device* device;

		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing NativeDX11_DrawArraysTest");
			api->setWindowTitle("NativeDx11_DrawArraysTest");

			device = api->getHwnd().dev;
			deviceContext = api->getHwnd().devcon;

			// Define the vertex data
			math::vec3 vertices[6] =
			{   // positions
				{ -0.1f, 0.1f, 0.0f },  // 0
				{ -0.1f,-0.1f, 0.0f },  // 1
				{  0.1f,-0.1f, 0.0f },  // 2
				{ -0.1f, 0.1f, 0.0f },  // 0
				{  0.1f,-0.1f, 0.0f },  // 2
				{  0.1f, 0.1f, 0.0f }   // 3
			};

			// Create the vertex buffer
			D3D11_BUFFER_DESC bd = {};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(math::vec3) * 6;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = vertices;
			device->CreateBuffer(&bd, &initData, &vertexBuffer);

			// Set the vertex buffer
			UINT stride = sizeof(math::vec3);
			UINT offset = 0;
			deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

			//Load shader source
			auto source = ShaderCache::loadShader("resources/shaders/test.shader");

			// Create and set the shaders and Set the input layout
			InitializeShadersAndLayout(device, deviceContext, inputLayout, vertexBlob, pixelBlob, vertexShader, pixelShader, source);

			// Set primitive topology
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		virtual void update(RenderInterface* api) override
		{
			// Draw the vertex buffer
			deviceContext->Draw(6, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			if (vertexBuffer) vertexBuffer->Release();
			if (inputLayout) inputLayout->Release();
			if (vertexShader) vertexShader->Release();
			if (pixelShader) pixelShader->Release();
		}
	};

	struct Native_DrawArraysInstancedTest : public rendering_test
	{
		ID3D11Buffer* vertexBuffer;
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D10Blob* vertexBlob;
		ID3D10Blob* pixelBlob;
		ID3D11DeviceContext* deviceContext;
		ID3D11Device* device;

		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing NativeDX11_DrawArraysInstancedTest");
			api->setWindowTitle("NativeDX11_DrawArraysInstancedTest");

			device = api->getHwnd().dev;
			deviceContext = api->getHwnd().devcon;

			// Define the vertex data
			math::vec3 vertices[6] =
			{   // positions
				{ -0.1f, 0.1f, 0.0f },  // 0
				{ -0.1f,-0.1f, 0.0f },  // 1
				{  0.1f,-0.1f, 0.0f },  // 2
				{ -0.1f, 0.1f, 0.0f },  // 0
				{  0.1f,-0.1f, 0.0f },  // 2
				{  0.1f, 0.1f, 0.0f }   // 3
			};

			// Create the vertex buffer
			D3D11_BUFFER_DESC bd = {};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(math::vec3) * 6;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = vertices;
			device->CreateBuffer(&bd, &initData, &vertexBuffer);

			// Set the vertex buffer
			UINT stride = sizeof(math::vec3);
			UINT offset = 0;
			deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

			//Load shader source
			auto source = ShaderCache::loadShader("resources/shaders/instance_test.shader");

			// Create and set the shaders and Set the input layout
			InitializeShadersAndLayout(device, deviceContext, inputLayout, vertexBlob, pixelBlob, vertexShader, pixelShader, source);

			// Set primitive topology
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		virtual void update(RenderInterface* api) override
		{
			// Draw the vertex buffer instanced
			deviceContext->DrawInstanced(6, 2, 0, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			if (vertexBuffer) vertexBuffer->Release();
			if (inputLayout) inputLayout->Release();
			if (vertexShader) vertexShader->Release();
			if (pixelShader) pixelShader->Release();
		}
	};

	struct Native_DrawIndexedTest : public rendering_test
	{
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D10Blob* vertexBlob;
		ID3D10Blob* pixelBlob;
		ID3D11DeviceContext* deviceContext;
		ID3D11Device* device;

		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing NativeDX11_DrawIndexedTest");
			api->setWindowTitle("NativeDX11_DrawIndexedTest");
			device = api->getHwnd().dev;
			deviceContext = api->getHwnd().devcon;

			// Define the vertex data
			math::vec3 vertices[4] =
			{   // positions
				{ -0.1f, -0.1f, 0.0f }, // 0
				{  0.1f, -0.1f, 0.0f }, // 1
				{  0.1f,  0.1f, 0.0f }, // 2
				{ -0.1f,  0.1f, 0.0f }  // 3
			};

			// Define the index data
			UINT indices[] =
			{
				0, 1, 2,
				2, 3, 0
			};

			// Create the vertex buffer
			D3D11_BUFFER_DESC bd = {};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(math::vec3) * 4;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = vertices;
			device->CreateBuffer(&bd, &initData, &vertexBuffer);

			// Create the index buffer
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(UINT) * 6;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			initData.pSysMem = indices;
			device->CreateBuffer(&bd, &initData, &indexBuffer);

			// Set the vertex buffer
			UINT stride = sizeof(math::vec3);
			UINT offset = 0;
			deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

			// Set the index buffer
			deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

			//Load shader source
			auto source = ShaderCache::loadShader("resources/shaders/test.shader");

			// Create and set the shaders and Set the input layout
			InitializeShadersAndLayout(device, deviceContext, inputLayout, vertexBlob, pixelBlob, vertexShader, pixelShader, source);

			// Set primitive topology
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		virtual void update(RenderInterface* api) override
		{
			// Draw the indexed vertex buffer
			deviceContext->DrawIndexed(6, 0, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			if (vertexBuffer) vertexBuffer->Release();
			if (indexBuffer) indexBuffer->Release();
			if (inputLayout) inputLayout->Release();
			if (vertexShader) vertexShader->Release();
			if (pixelShader) pixelShader->Release();
		}
	};

	struct Native_DrawIndexedInstancedTest : public rendering_test
	{
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D10Blob* vertexBlob;
		ID3D10Blob* pixelBlob;
		ID3D11DeviceContext* deviceContext;
		ID3D11Device* device;

		virtual void setup(RenderInterface* api) override
		{
			log::debug("Initializing NativeDX11_DrawIndexedInstancedTest");
			api->setWindowTitle("NativeDX11_DrawIndexedInstancedTest");
			device = api->getHwnd().dev;
			deviceContext = api->getHwnd().devcon;

			// Define the vertex data
			math::vec3 vertices[4] =
			{   // positions
				{ -0.1f, -0.1f, 0.0f }, // 0
				{  0.1f, -0.1f, 0.0f }, // 1
				{  0.1f,  0.1f, 0.0f }, // 2
				{ -0.1f,  0.1f, 0.0f }  // 3
			};

			// Define the index data
			UINT indices[] =
			{
				0, 1, 2,
				2, 3, 0
			};

			// Create the vertex buffer
			D3D11_BUFFER_DESC bd = {};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(math::vec3) * 4;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = vertices;
			device->CreateBuffer(&bd, &initData, &vertexBuffer);

			// Create the index buffer
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(UINT) * 6;
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			initData.pSysMem = indices;
			device->CreateBuffer(&bd, &initData, &indexBuffer);

			// Set the vertex buffer
			UINT stride = sizeof(math::vec3);
			UINT offset = 0;
			deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

			// Set the index buffer
			deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

			//Load shader source
			auto source = ShaderCache::loadShader("resources/shaders/instance_test.shader");

			// Create and set the shaders and Set the input layout
			InitializeShadersAndLayout(device, deviceContext, inputLayout, vertexBlob, pixelBlob, vertexShader, pixelShader, source);

			// Set primitive topology
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		virtual void update(RenderInterface* api) override
		{
			// Draw the indexed vertex buffer instanced
			deviceContext->DrawIndexedInstanced(6, 2, 0, 0, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			if (vertexBuffer) vertexBuffer->Release();
			if (indexBuffer) indexBuffer->Release();
			if (inputLayout) inputLayout->Release();
			if (vertexShader) vertexShader->Release();
			if (pixelShader) pixelShader->Release();
		}
	};
#endif
#pragma endregion
}