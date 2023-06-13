#pragma once
#include <chrono>
#include <ctime>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3native.h>
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <bx/allocator.h>
#include <bx/file.h>

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
	enum APIType
	{
		None,
		Arbrook,
		BGFX,
		Native
	};

	//template<size_t N>
	//struct lstring {
	//	constexpr lstring(const char(&str)[N]) {
	//		std::copy_n(str, N, value);
	//	}

	//	char value[N];
	//};

	//template<APIType t, lstring n>
	//struct test_properties
	//{
	//	APIType type = t;
	//	std::string name = n.value;
	//};

	struct rendering_test
	{
		APIType type;
		std::string name;
		virtual ~rendering_test() = default;
		virtual void setup(RenderInterface* api) = 0;
		virtual void update(RenderInterface* api) = 0;
		virtual void destroy(RenderInterface* api) = 0;
	};

	inline std::string stringify(APIType type)
	{
		switch (type)
		{
		case APIType::Arbrook:
			return "Arbrook";
			break;
		case APIType::BGFX:
			return  "BGFX";
			break;
		case APIType::Native:
			return  "Native";
			break;
		case APIType::None:
			return "None";
			break;
		}
		return "";
	}

	struct dummy_test : public rendering_test
	{
		inputlayout layout;
		buffer_handle vBuffer;
		buffer_handle cBuffer;
		shader_handle shader;

		virtual void setup(RenderInterface* api) override
		{
			type = None;
			name = "";
			log::debug("Initializing", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), "Initializing");
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
			vBuffer = BufferCache::createBuffer<math::vec3>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(math::vec3));
			//cBuffer = BufferCache::createBuffer<math::vec3>(*api, "Constant Buffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW);
			//shader->addBuffer(ShaderType::VERTEX, cBuffer);
			shader->bind();
			layout.addBuffer(vBuffer);
			layout.bind(api->getHwnd(), shader);
			layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec3), 0);
			layout.submitAttributes();
		}
		virtual void update(RenderInterface* api) override
		{
			api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
		}
		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			BufferCache::deleteBuffer("Constant Buffer");
			ShaderCache::deleteShader("test");
			layout.release();
		}
	};

#pragma region My API
	struct API_DrawArraysTest : public rendering_test
	{
		inputlayout layout;
		buffer_handle vBuffer;
		buffer_handle cBuffer;
		shader_handle shader;

		virtual void setup(RenderInterface* api) override
		{
			type = Arbrook;
			name = "DrawArrays";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());
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
			vBuffer = BufferCache::createBuffer<math::vec3>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(math::vec3));
			//cBuffer = BufferCache::createBuffer<math::vec3>(*api, "Constant Buffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW);
			//shader->addBuffer(ShaderType::VERTEX, cBuffer);
			shader->bind();
			layout.addBuffer(vBuffer);
			layout.bind(api->getHwnd(), shader);
			layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec3), 0);
			layout.submitAttributes();
		}

		virtual void update(RenderInterface* api) override
		{
			//for (float x = -1.0f; x < 1.0f; x += (2.f / 5.f))
			//{
			//	for (float y = -1.0f; y < 1.0f; y += (2.f / 5.f))
			//	{
			//		math::vec3 pos[] = { { x + .2f, y + .2f, 0.0f } };
			//		shader->setData("Constant Buffer", pos);
			api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
			//	}
			//}
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			//BufferCache::deleteBuffer("Constant Buffer");
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
			type = Arbrook;
			name = "DrawArraysInstanced";

			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());
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
			api->drawArraysInstanced(PrimitiveType::TRIANGLESLIST, 6, 25, 0, 0);
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
		buffer_handle cBuffer;
		buffer_handle idxBuffer;
		shader_handle shader;

		virtual void setup(RenderInterface* api) override
		{
			type = Arbrook;
			name = "DrawIndexed";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());
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
			//cBuffer = BufferCache::createBuffer<math::vec3>(*api, "Constant Buffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW);
			//shader->addBuffer(ShaderType::VERTEX, cBuffer);
			shader->bind();
			layout.addBuffer(vBuffer);
			layout.addBuffer(idxBuffer);
			layout.bind(api->getHwnd(), shader);
			layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(math::vec3), 0);
			layout.submitAttributes();
		}

		virtual void update(RenderInterface* api) override
		{
			//for (float x = -1.0f; x < 1.0f; x += (2.f / 5.f))
			//{
			//	for (float y = -1.0f; y < 1.0f; y += (2.f / 5.f))
			//	{
			//		math::vec3 pos[] = { { x + .2f, y + .2f, 0.0f } };
			//		shader->setData("Constant Buffer", pos);
			api->drawIndexed(PrimitiveType::TRIANGLESLIST, 6, 0, 0);
			//	}
			//}
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			BufferCache::deleteBuffer("Index Buffer");
			//BufferCache::deleteBuffer("Constant Buffer");
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
			type = Arbrook;
			name = "DrawIndexedInstanced";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());
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

	inline bgfx::ProgramHandle loadShader(std::string name, std::string fsPath, std::string vsPath)
	{
		char* data = new char[2048];
		std::ifstream file;
		size_t fileSize;
		file.open(fsPath);
		if (file.is_open()) {
			file.seekg(0, std::ios::end);
			fileSize = file.tellg();
			file.seekg(0, std::ios::beg);
			file.read(data, fileSize);
			file.close();
		}
		const bgfx::Memory* mem = bgfx::copy(data, fileSize + 1);
		mem->data[mem->size - 1] = '\0';
		bgfx::ShaderHandle fhandle = bgfx::createShader(mem);
		if (fhandle.idx == bgfx::kInvalidHandle)
			log::error("Fragment Shader failed compile");
		bgfx::setName(fhandle, "TestFragment");

		file.open(vsPath);
		if (file.is_open()) {
			file.seekg(0, std::ios::end);
			fileSize = file.tellg();
			file.seekg(0, std::ios::beg);
			file.read(data, fileSize);
			file.close();
		}

		mem = bgfx::copy(data, fileSize + 1);
		mem->data[mem->size - 1] = '\0';
		bgfx::ShaderHandle vhandle = bgfx::createShader(mem);
		if (vhandle.idx == bgfx::kInvalidHandle)
			log::error("Vertex Shader failed compile");
		bgfx::setName(vhandle, "TestVertex");

		return bgfx::createProgram(vhandle, fhandle, true);
	}

	static const 	math::vec3 verts[6] =
	{	//positions						
		{  -0.1f, 0.1f, 0.0f  },//0
		{ 	-0.1f,-0.1f, 0.0f  },//1
		{  0.1f,-0.1f, 0.0f  },//2
		{  -0.1f, 0.1f, 0.0f  },//0
		{  0.1f,-0.1f, 0.0f },//2
		{  0.1f, 0.1f, 0.0f }//3
	};

	struct BgfxCallback : public bgfx::CallbackI
	{
		virtual ~BgfxCallback()
		{
		}

		virtual void fatal(const char* _filePath, uint16_t _line, bgfx::Fatal::Enum _code, const char* _str) override
		{
			BX_UNUSED(_filePath, _line);

			// Something unexpected happened, inform user and bail out.
			log::error("Fatal error [{}]: {}", _code, _str);

			//abort();
		}

		virtual void traceVargs(const char* _filePath, uint16_t _line, const char* _format, va_list _argList) override
		{
			//log::debug("%s (%d): ", _filePath, _line);
			//log::debug(_format, _argList);
		}

		virtual void profilerBegin(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
		{
		}

		virtual void profilerBeginLiteral(const char* /*_name*/, uint32_t /*_abgr*/, const char* /*_filePath*/, uint16_t /*_line*/) override
		{
		}

		virtual void profilerEnd() override
		{
		}

		virtual uint32_t cacheReadSize(uint64_t _id) override
		{
			return 0;
		}

		virtual bool cacheRead(uint64_t _id, void* _data, uint32_t _size) override
		{
			return false;
		}

		virtual void cacheWrite(uint64_t _id, const void* _data, uint32_t _size) override
		{

		}

		virtual void screenShot(const char* _filePath, uint32_t _width, uint32_t _height, uint32_t _pitch, const void* _data, uint32_t /*_size*/, bool _yflip) override
		{

		}

		virtual void captureBegin(uint32_t _width, uint32_t _height, uint32_t /*_pitch*/, bgfx::TextureFormat::Enum /*_format*/, bool _yflip) override
		{

		}

		virtual void captureEnd() override
		{

		}

		virtual void captureFrame(const void* _data, uint32_t /*_size*/) override
		{
		}
	};

	struct BGFX_DrawArraysTest : public rendering_test
	{
		bgfx::PlatformData platformData;
		bgfx::VertexBufferHandle vertexBuffer;
		bgfx::ProgramHandle shader;
		bgfx::VertexLayout inputLayout;
		BgfxCallback callback;


		uint64_t state = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_FRONT_CCW
			| BGFX_STATE_MSAA;

		virtual void setup(RenderInterface* api) override
		{
			type = BGFX;
			name = "DrawArrays";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());

			bgfx::Init init;
			init.platformData.ndt = nullptr;
			init.platformData.nwh = glfwGetWin32Window(api->getWindow());
#if RenderingAPI == RenderingAPI_OGL
			init.type = bgfx::RendererType::OpenGL;
			init.platformData.context = glfwGetCurrentContext();
#elif RenderingAPI == RenderingAPI_DX11
			init.type = bgfx::RendererType::Direct3D11;
			init.platformData.context = api->getHwnd().dev;
			init.platformData.backBuffer = api->getHwnd().backbuffer;
			init.platformData.backBufferDS = api->getHwnd().depthStencilView;
#endif

			init.resolution.width = api->getHwnd().m_resolution.x;
			init.resolution.height = api->getHwnd().m_resolution.y;
			init.callback = &callback;
			bgfx::init(init);

			inputLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).end();

			vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(verts, sizeof(verts)), inputLayout);
			shader = loadShader("test", "resources/shaders/testFS.shader", "resources/shaders/testVS.shader");

			if (shader.idx == bgfx::kInvalidHandle)
				log::error("Shader failed to compile");

			bgfx::setViewRect(0, 0, 0, uint16_t(600), uint16_t(600));
		}

		virtual void update(RenderInterface* api) override
		{
			bgfx::setVertexBuffer(0, vertexBuffer);
			bgfx::setState(state);
			bgfx::submit(0, shader);
			bgfx::frame();
		}

		virtual void destroy(RenderInterface* api) override
		{
			if (shader.idx != bgfx::kInvalidHandle)
				bgfx::destroy(shader);

			bgfx::destroy(vertexBuffer);
			bgfx::shutdown();
			api->initialize(api->getHwnd().m_resolution, "", api->getWindow());
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
			type = Native;
			name = "DrawArrays";
			log::debug("Initializing {}OGL_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}OGL_Test{}", stringify(type), name).c_str());
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
			type = Native;
			name = "DrawArraysInstanced";
			log::debug("Initializing {}OGL_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}OGL_Test{}", stringify(type), name).c_str());
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
			type = Native;
			name = "DrawIndexed";
			log::debug("Initializing {}OGL_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}OGL_Test{}", stringify(type), name).c_str());

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
			type = Native;
			name = "DrawIndexedInstanced";
			log::debug("Initializing {}OGL_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}OGL_Test{}", stringify(type), name).c_str());
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
			type = Native;
			name = "DrawArrays";
			log::debug("Initializing {}DX11_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}DX11_Test{}", stringify(type), name).c_str());

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
			type = Native;
			name = "DrawArraysInstanced";
			log::debug("Initializing {}DX11_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}DX11_Test{}", stringify(type), name).c_str());

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
			type = Native;
			name = "DrawIndexed";
			log::debug("Initializing {}DX11_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}DX11_Test{}", stringify(type), name).c_str());
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
			type = Native;
			name = "DrawIndexedInstanced";
			log::debug("Initializing {}DX11_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}DX11_Test{}", stringify(type), name).c_str());
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