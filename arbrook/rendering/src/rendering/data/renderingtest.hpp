#pragma once
#include <chrono>
#include <ctime>

#include <GLFW/glfw3native.h>
#include <GLFW/glfw3.h>

#include <bgfx/bgfx.h>
#include <bgfx/platform.h>
#include <bx/math.h>
#include <bx/allocator.h>
#include <bx/file.h>

#include <rsl/delegate>

#include "core/ecs/ecs.hpp"
#include "core/components/components.hpp"

#include "rendering/interface/definitions.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/cache/shadercache.hpp"
#include "rendering/cache/texturecache.hpp"
#include "rendering/cache/buffercache.hpp"
#include "rendering/components/spriterenderer.hpp"
#include "rendering/components/mesh_renderer.hpp"
#include "rendering/data/vertex.hpp"
#include "rendering/components/components.hpp"



namespace rythe::rendering
{
	enum APIType
	{
		None,
		Arbrook,
		BGFX,
		Native
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

	struct uniformData
	{
		math::mat4 mvp;
	};

	struct vtx
	{
		math::vec4 position;
		math::vec2 uv;
	};

	struct tex_vtx
	{
		math::vec4 position;
		math::vec2 uv;
	};

	struct rendering_test
	{
		APIType type;
		std::string name;
		virtual ~rendering_test() = default;
		virtual void setup(RenderInterface* api) = 0;
		virtual void update(RenderInterface* api) = 0;
		virtual void destroy(RenderInterface* api) = 0;
	};

	struct dummy_test : public rendering_test
	{
		inputlayout layout;
		buffer_handle vBuffer;
		shader_handle shader;
		texture_handle texture;

		virtual void setup(RenderInterface* api) override
		{
			type = None;
			name = "";
			log::debug("Initializing", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), "Initializing");
			tex_vtx verticies[] =
			{	//positions						
				{ { -1.f, 1.0f, 0.0f  },	{ 0, 1 } },//0
				{ {-1.f,-1.0f, 0.0f  },	{ 0, 0 } },//1
				{ {  1.0f,-1.0f, 0.0f },		{ 1, 0 } },//2
				{ { -1.0f, 1.0f, 0.0f },		{ 0, 1 } },//0
				{ {  1.0f,-1.0f, 0.0f },		{ 1, 0 } },//2
				{ {  1.0f, 1.0f, 0.0f },		{ 1, 1 } }//3
			};
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/texture.shader");
			texture = TextureCache::createTexture2D(*api, "test", "resources/textures/Rythe.png");
			vBuffer = BufferCache::createBuffer<tex_vtx>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(tex_vtx));
			shader->bind();
			texture->bind();
			layout.initialize(api->getHwnd(), 1, shader);
			layout.setAttributePtr(vBuffer,"POSITION", 0, FormatType::RGB32F, 0, sizeof(tex_vtx), 0);
			layout.setAttributePtr(vBuffer,"TEXCOORD", 1, FormatType::RG32F, 0, sizeof(tex_vtx), sizeof(math::vec3));
			layout.submitAttributes();
			layout.bind();
		}

		virtual void update(RenderInterface* api) override
		{
			api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			ShaderCache::deleteShader("test");
			layout.release();
		}
	};

	inline camera cam;
	inline core::transform transf;
	inline math::mat4 projection = cam.projection = math::perspective(math::radians(45.f), Screen_Width / Screen_Height, .1f, 100.0f);
	inline math::mat4 view = cam.view = math::lookAt((math::vec3)transf.position, transf.position + transf.forward(), transf.up());
	inline math::mat4 projView = projection * view;
	inline float count = 64.f;
	inline float instanceCount = 65536.f / 2.f;
	//inline float instanceCount = 16.f;
	inline float min = -2.f;
	inline float max = 2.f;

	inline float step = (max - min) / math::floor(math::sqrt(count));
	inline float instanceStep = (max - min) / math::floor(math::sqrt(instanceCount));

	static vtx vertices[36] =
	{
		//Back
		{ { -0.1f,  0.1f, -0.1f,1.0f	},	{	1.0f, 1.0f	} },//0
		{ {  0.1f, -0.1f, -0.1f,1.0f	},	{	0.0f, 0.0f	} },//2
		{ { -0.1f, -0.1f, -0.1f,1.0f	 },	{	1.0f, 0.0f	} },//1

		{ { -0.1f,  0.1f, -0.1f,1.0f		},	{	1.0f, 1.0f	} },//0
		{ {  0.1f,  0.1f, -0.1f,1.0f		},	{	0.0f, 1.0f	} },//3
		{ {  0.1f, -0.1f, -0.1f,1.0f		},	{	0.0f, 0.0f	} },//2

		//Front
		{ { -0.1f,  0.1f, 0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ { -0.1f, -0.1f, 0.1f,1.0f	},	{	0.0f, 0.0f	} },//1
		{ {  0.1f, -0.1f, 0.1f,1.0f		},	{	1.0f, 0.0f	} },//2

		{ { -0.1f,  0.1f, 0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {  0.1f, -0.1f, 0.1f,1.0f		},	{	1.0f, 0.0f	} },//2
		{ {  0.1f,  0.1f, 0.1f,1.0f		},	{	1.0f, 1.0f	} },//3

		//Left
		{ {	0.1f, 0.1f, -0.1f,1.0f		},	{	1.0f, 1.0f	} },//0
		{ {	0.1f, -0.1f, 0.1f,1.0f		},	{	0.0f, 0.0f	} },//2
		{ {	0.1f, -0.1f,-0.1f,1.0f		},	{	1.0f, 0.0f	} },//1

		{ {	0.1f, 0.1f, -0.1f	,1.0f		},	{	1.0f, 1.0f	} },//0
		{ {	0.1f, 0.1f,  0.1f	,1.0f		},	{	0.0f, 1.0f	} },//3
		{ {0.1f, -0.1f, 0.1f,1.0f		},	{	0.0f, 0.0f } },//2

		//Right
		{ {	-0.1f,0.1f, -0.1f	,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {	-0.1f, -0.1f,-0.1f,1.0f	},	{	0.0f, 0.0f	} },//1
		{ {	-0.1f, -0.1f, 0.1f,1.0f		},	{	1.0f, 0.0f	} },//2

		{ {	-0.1f, 0.1f, -0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {-0.1f, -0.1f, 0.1f,1.0f		},	{	1.0f, 0.0f } },//2
		{ {	-0.1f, 0.1f,  0.1f,1.0f		},	{	1.0f, 1.0f	} },//3

		//Bottom
		{ { -0.1f, -0.1f,  0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ { -0.1f, -0.1f, -0.1f,1.0f		},	{	0.0f, 0.0f	} },//1
		{ {  0.1f, -0.1f, -0.1f,1.0f		},	{	1.0f, 0.0f	} },//2

		{ { -0.1f, -0.1f,  0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {  0.1f, -0.1f, -0.1f,1.0f		},	{	1.0f, 0.0f	} },//2
		{ {  0.1f, -0.1f,  0.1f,1.0f		},	{	1.0f, 1.0f	} },//3

		//Top
		{ { -0.1f, 0.1f,  0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {  0.1f, 0.1f, -0.1f,1.0f		},	{	1.0f, 0.0f	} },//2
		{ { -0.1f, 0.1f, -0.1f,1.0f		},	{	0.0f, 0.0f	} },//1

		{ { -0.1f, 0.1f,  0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {  0.1f, 0.1f	,  0.1f,1.0f		},	{	1.0f, 1.0f	} },//3
		{ {  0.1f, 0.1f, -0.1f,1.0f		},	{	1.0f, 0.0f	} }//2
	};

	static math::vec3 normals[36] =
	{
		{ 0.0f, 0.0f, -1.0f},
		{ 0.0f, 0.0f, -1.0f},
		{ 0.0f, 0.0f, -1.0f},
		{ 0.0f, 0.0f, -1.0f},
		{ 0.0f, 0.0f, -1.0f},
		{ 0.0f, 0.0f, -1.0f},

		{ 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 1.0f},
		{ 0.0f, 0.0f, 1.0f},

		{ -1.0f,  0.0f,  0.0f},
		{ -1.0f,  0.0f,  0.0f},
		{ -1.0f,  0.0f,  0.0f},
		{ -1.0f,  0.0f,  0.0f},
		{ -1.0f,  0.0f,  0.0f},
		{ -1.0f,  0.0f,  0.0f},

		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},
		{ 1.0f,  0.0f,  0.0f},

		{0.0f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},
		{0.0f, -1.0f, 0.0f},

		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
		{0.0f, 1.0f, 0.0f},
	};

	static vtx instance_vertices[36] =
	{
		//Back
		{ { -0.1f,  0.1f, -0.1f,1.0f		},	{	1.0f, 1.0f	} },//0
		{ {  0.1f, -0.1f, -0.1,1.0f		},	{	0.0f, 0.0f	} },//2
		{ { -0.1f, -0.1f, -0.1,1.0f	 },	{	1.0f, 0.0f	} },//1

		{ { -0.1f,  0.1f, -0.1,1.0f		},	{	1.0f, 1.0f	} },//0
		{ {  0.1f,  0.1f, -0.1,1.0f		},	{	0.0f, 1.0f	} },//3
		{ {  0.1f, -0.1f, -0.1,1.0f		},	{	0.0f, 0.0f	} },//2

		//Front					,1.0f	
		{ { -0.1f,  0.1f, 0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ { -0.1f, -0.1f, 0.1f,1.0f		},	{	0.0f, 0.0f	} },//1
		{ {  0.1f, -0.1f, 0.1f,1.0f		},	{	1.0f, 0.0f	} },//2

		{ { -0.1f,  0.1f, 0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {  0.1f, -0.1f, 0.1f,1.0f		},	{	1.0f, 0.0f	} },//2
		{ {  0.1f,  0.1f, 0.1f,1.0f	},	{	1.0f, 1.0f	} },//3

		//Left					 ,1.0f	
		{ {	0.1f, 0.1f, -0.1f	,1.0f	},	{	1.0f, 1.0f	} },//0
		{ {	0.1f, -0.1f, 0.1f	,1.0f	},	{	0.0f, 0.0f	} },//2
		{ {	0.1f, -0.1f,-0.1f	,1.0f	},	{	1.0f, 0.0f	} },//1

		{ {	0.1f, 0.1f, -0.1f	,1.0f	},	{	1.0f, 1.0f	} },//0
		{ {	0.1f, 0.1f,  0.1f	,1.0f	},	{	0.0f, 1.0f	} },//3
		{ {0.1f, -0.1f, 0.1f	,1.0f	},	{	0.0f, 0.0f } },//2

		//Right					
		{ {	-0.1f,0.1f, -0.1f	,1.0f	},	{	0.0f, 1.0f	} },//0
		{ {	-0.1f, -0.1f,-0.1f,1.0f		},	{	0.0f, 0.0f	} },//1
		{ {	-0.1f, -0.1f, 0.1f,1.0f	  },	{	1.0f, 0.0f	} },//2

		{ {	-0.1f, 0.1f, -0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {-0.1f, -0.1f, 0.1f,1.0f	},	{	1.0f, 0.0f } },//2
		{ {	-0.1f, 0.1f,  0.1f,1.0f	},	{	1.0f, 1.0f	} },//3

		//Bottom				
		{ { -0.1f, -0.1f,  0.1,1.0f		},	{	0.0f, 1.0f	} },//0
		{ { -0.1f, -0.1f, -0.1,1.0f		},	{	0.0f, 0.0f	} },//1
		{ {  0.1f, -0.1f, -0.1,1.0f		},	{	1.0f, 0.0f	} },//2

		{ { -0.1f, -0.1f,  0.1,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {  0.1f, -0.1f, -0.1,1.0f		},	{	1.0f, 0.0f	} },//2
		{ {  0.1f, -0.1f,  0.1,1.0f		},	{	1.0f, 1.0f	} },//3

		//Top					 
		{ { -0.1f, 0.1f,  0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {  0.1f, 0.1f, -0.1f,1.0f		},	{	1.0f, 0.0f	} },//2
		{ { -0.1f, 0.1f, -0.1f,1.0f		},	{	0.0f, 0.0f	} },//1

		{ { -0.1f, 0.1f,  0.1f,1.0f		},	{	0.0f, 1.0f	} },//0
		{ {  0.1f, 0.1f	,  0.1f,1.0f		},	{	1.0f, 1.0f	} },//3
		{ {  0.1f, 0.1f, -0.1f,1.0f		},	{	1.0f, 0.0f	} }//2
	};

	static vtx indVertices[8] =
	{
		{{ -.1f, -.1f,  0.1f,1.0f	},		{0,0}	}, //0
		{{	 .1f, -.1f,  0.1f,1.0f	},		{1,0}	}, //1
		{{	-.1f,  .1f,  0.1f,1.0f	},		{0,1}	}, //2
		{{	 .1f,  .1f,  0.1f,1.0f	},		{1,1}	}, //3
		{{	-.1f, -.1f, -0.1f,1.0f	},	{0,0}	}, //4
		{{	 .1f, -.1f, -0.1f,1.0f	},		{1,0}	},//5
		{{	-.1f,  .1f, -0.1f,1.0f	},		{0,1}	}, //6
		{{	 .1f,  .1f, -0.1f,1.0f	},		{1,1}	}  //7
	};

	static vtx instance_indVertices[8] =
	{
		{{ -.1f, -.1f,  0.1f,1.0f	},		{0,0}	}, //0
		{{	 .1f, -.1f,  0.1f,1.0f	},		{1,0}	}, //1
		{{	-.1f,  .1f,  0.1f,1.0f	},		{0,1}	}, //2
		{{	 .1f,  .1f,  0.1f,1.0f	},		{1,1}	}, //3
		{{	-.1f, -.1f, -0.1f,1.0f	},	{0,0}	}, //4
		{{	 .1f, -.1f, -0.1f,1.0f	},		{1,0}	}, //5
		{{	-.1f,  .1f, -0.1f,1.0f	},		{0,1}	}, //6
		{{	 .1f,  .1f, -0.1f,1.0f	},		{1,1}	}  //7
	};

	static unsigned int indicies[36] =
	{
		//Top
		2, 6, 7,
		2, 3, 7,

		//Bottom
		0, 4, 5,
		0, 1, 5,

		//Left
		0, 2, 6,
		0, 4, 6,

		//Right
		1, 3, 7,
		1, 5, 7,

		//Front
		0, 2, 3,
		0, 1, 3,

		//Back
		4, 6, 7,
		4, 5, 7
	};

#pragma region My API
	struct API_DrawArraysTest : public rendering_test
	{
		inputlayout layout;
		buffer_handle vBuffer;
		buffer_handle nBuffer;
		buffer_handle cBuffer;
		texture_handle texture;
		shader_handle shader;
		uniformData data;

		float i = 0;

		virtual void setup(RenderInterface* api) override
		{
			for (auto& vert : vertices)
			{
				vert.position *= (step * 2.f);
				vert.position.w = 1;
			}

			for (auto& vert : instance_vertices)
			{
				vert.position *= (instanceStep * 4.f);
				vert.position.w = 1;
			}

			for (auto& vert : indVertices)
			{
				vert.position *= (step * 2.f);
				vert.position.w = 1;
			}

			for (auto& vert : instance_indVertices)
			{
				vert.position *= (instanceStep * 4.f);
				vert.position.w = 1;
			}

			type = Arbrook;
			name = "DrawArrays";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/cube.shader");
			texture = TextureCache::getTexture2D("test");
			vBuffer = BufferCache::createBuffer<vtx>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, vertices, sizeof(vertices) / sizeof(vtx));
			cBuffer = BufferCache::createBuffer<uniformData>(*api, "ConstantBuffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW);
			shader->addBuffer(ShaderType::VERTEX, cBuffer);
			shader->bind();
			texture->bind();
			layout.initialize(api->getHwnd(), 1, shader);
			layout.setAttributePtr(vBuffer,"POSITION", 0, FormatType::RGBA32F, 0, sizeof(vtx), 0);
			layout.submitAttributes();
			//layout.setAttributePtr("TEXCOORD", 1, FormatType::RG32F, 0, sizeof(vtx), sizeof(math::vec4));
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			for (float x = min; x < max; x += step)
			{
				for (float y = min; y < max; y += step)
				{
					math::vec3 pos = { x + (step / 2.f), y + (step / 2.f), 0.0f };
					auto model = math::translate(math::mat4(1.0f), pos);
					data.mvp = projView * math::rotate(model, math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					shader->setData("ConstantBuffer", &data);
					api->drawArrays(PrimitiveType::TRIANGLESLIST, 0, sizeof(vertices) / sizeof(vtx));
				}
			}
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			BufferCache::deleteBuffer("ConstantBuffer");
			ShaderCache::deleteShader("test");
			layout.release();
		}
	};

	struct API_DrawArraysInstancedTest : public rendering_test
	{
		std::vector<math::mat4> models;

		inputlayout layout;
		buffer_handle buffer;
		buffer_handle matrixBuffer;
		buffer_handle constantBuffer;
		shader_handle shader;
		texture_handle texture;
		uniformData data;

		float i = 0;
		int index = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Arbrook;
			name = "DrawArraysInstanced";

			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/instance_cube.shader");
			buffer = BufferCache::createBuffer<vtx>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, instance_vertices, sizeof(instance_vertices) / sizeof(vtx));
			matrixBuffer = BufferCache::createBuffer<math::mat4>(*api, "Matrix Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW);
			constantBuffer = BufferCache::createBuffer<uniformData>(*api, "ConstantBuffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW);
			texture = TextureCache::getTexture2D("test");
			shader->addBuffer(ShaderType::VERTEX, constantBuffer);
			shader->bind();
			texture->bind();

			layout.initialize(api->getHwnd(), 2, shader);
			layout.setAttributePtr(buffer,"POSITION", 0, FormatType::RGBA32F, 0, sizeof(vtx), 0);
			//layout.setAttributePtr("TEXCOORD", 1, FormatType::RG32F, 0, sizeof(vtx), sizeof(math::vec4));
			layout.setAttributePtr(matrixBuffer,"MODEL", 0, FormatType::RGBA32F, 1, sizeof(math::mat4), 0.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.setAttributePtr(matrixBuffer,"MODEL", 1, FormatType::RGBA32F, 1, sizeof(math::mat4), 1.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.setAttributePtr(matrixBuffer,"MODEL", 2, FormatType::RGBA32F, 1, sizeof(math::mat4), 2.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.setAttributePtr(matrixBuffer,"MODEL", 3, FormatType::RGBA32F, 1, sizeof(math::mat4), 3.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.submitAttributes();

			data.mvp = projView;
			shader->setData("ConstantBuffer", &data);
			models.resize(instanceCount);
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			index = 0;
			for (float x = min; x < max; x += instanceStep)
			{
				for (float y = min; y < max; y += instanceStep)
				{
					math::vec3 pos = { x + (instanceStep / 2.f), y + (instanceStep / 2.f), 0.0f };
					models[index] = math::translate(math::mat4(1.0f), pos);
					models[index] = math::rotate(models[index], math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					index++;

					if (index >= instanceCount)
						break;
				}
				if (index >= instanceCount)
					break;
			}

			texture->bind();
			matrixBuffer->bufferData(models.data(), models.size());
			api->drawArraysInstanced(PrimitiveType::TRIANGLESLIST, 36, instanceCount, 0, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			BufferCache::deleteBuffer("Matrix Buffer");
			BufferCache::deleteBuffer("ConstantBuffer");
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
		texture_handle texture;
		shader_handle shader;
		uniformData data;

		float i = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Arbrook;
			name = "DrawIndexed";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/cube.shader");
			texture = TextureCache::getTexture2D("test");
			vBuffer = BufferCache::createBuffer<vtx>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, indVertices, sizeof(indVertices) / sizeof(vtx));
			idxBuffer = BufferCache::createBuffer<unsigned int>(*api, "Index Buffer", TargetType::INDEX_BUFFER, UsageType::STATICDRAW, indicies, sizeof(indicies) / sizeof(unsigned int));
			cBuffer = BufferCache::createBuffer<uniformData>(*api, "ConstantBuffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW);
			shader->addBuffer(ShaderType::VERTEX, cBuffer);
			shader->bind();
			
			idxBuffer->bind();
			layout.initialize(api->getHwnd(), 1, shader);
			layout.setAttributePtr(vBuffer,"POSITION", 0, FormatType::RGB32F, 0, sizeof(vtx), 0);
			//layout.setAttributePtr("TEXCOORD", 1, FormatType::RG32F, 0, sizeof(vtx), sizeof(math::vec3));
			layout.submitAttributes();
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			for (float x = min; x < max; x += step)
			{
				for (float y = min; y < max; y += step)
				{
					math::vec3 pos = { x + (step / 2.f), y + (step / 2.f), 0.0f };
					auto model = math::translate(math::mat4(1.0f), pos);
					data.mvp = projView * math::rotate(model, math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					shader->setData("ConstantBuffer", &data);
					vBuffer->bind();
					idxBuffer->bind();
					api->drawIndexed(PrimitiveType::TRIANGLESLIST, sizeof(indicies) / sizeof(unsigned int), 0, 0);
				}
			}
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			BufferCache::deleteBuffer("Index Buffer");
			BufferCache::deleteBuffer("ConstantBuffer");
			ShaderCache::deleteShader("test");
			layout.release();
		}
	};

	struct API_DrawIndexedInstancedTest : public rendering_test
	{

		std::vector<math::mat4> models;

		inputlayout layout;
		buffer_handle vBuffer;
		buffer_handle idxBuffer;
		buffer_handle constantBuffer;
		buffer_handle matrixBuffer;
		texture_handle texture;
		shader_handle shader;
		uniformData data;

		float i = 0;
		int index = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Arbrook;
			name = "DrawIndexedInstanced";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());

			shader = ShaderCache::createShader(*api, "test", "resources/shaders/instance_cube.shader");
			texture = TextureCache::getTexture2D("test");
			vBuffer = BufferCache::createBuffer<vtx>(*api, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, instance_indVertices, sizeof(instance_indVertices) / sizeof(vtx));
			idxBuffer = BufferCache::createBuffer<unsigned int>(*api, "Index Buffer", TargetType::INDEX_BUFFER, UsageType::STATICDRAW, indicies, sizeof(indicies) / sizeof(unsigned int));
			constantBuffer = BufferCache::createBuffer<uniformData>(*api, "ConstantBuffer", TargetType::CONSTANT_BUFFER, UsageType::STATICDRAW);
			matrixBuffer = BufferCache::createBuffer<math::mat4>(*api, "Matrix Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW);
			shader->addBuffer(ShaderType::VERTEX, constantBuffer);
			shader->bind();
			idxBuffer->bind();

			layout.initialize(api->getHwnd(), 2, shader);
			layout.setAttributePtr(vBuffer,"POSITION", 0, FormatType::RGB32F, 0, sizeof(vtx), 0);
			//layout.setAttributePtr("TEXCOORD", 1, FormatType::RG32F, 0, sizeof(vtx), sizeof(math::vec3));
			layout.setAttributePtr(matrixBuffer,"MODEL", 0, FormatType::RGBA32F, 1, sizeof(math::mat4), 0.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.setAttributePtr(matrixBuffer,"MODEL", 1, FormatType::RGBA32F, 1, sizeof(math::mat4), 1.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.setAttributePtr(matrixBuffer,"MODEL", 2, FormatType::RGBA32F, 1, sizeof(math::mat4), 2.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.setAttributePtr(matrixBuffer,"MODEL", 3, FormatType::RGBA32F, 1, sizeof(math::mat4), 3.f * sizeof(math::vec4), InputClass::PER_INSTANCE, 1);
			layout.submitAttributes();

			data.mvp = projView;
			shader->setData("ConstantBuffer", &data);
			models.resize(instanceCount);
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			index = 0;
			for (float x = min; x < max; x += instanceStep)
			{
				for (float y = min; y < max; y += instanceStep)
				{
					math::vec3 pos = { x + (instanceStep / 2.f), y + (instanceStep / 2.f), 0.0f };
					models[index] = math::translate(math::mat4(1.0f), pos);
					models[index] = math::rotate(models[index], math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					index++;
					if (index >= instanceCount)
						break;
				}
				if (index >= instanceCount)
					break;
			}
			matrixBuffer->bufferData(models.data(), models.size());
			vBuffer->bind();
			idxBuffer->bind();
			api->drawIndexedInstanced(PrimitiveType::TRIANGLESLIST, sizeof(indicies) / sizeof(unsigned int), instanceCount, 0, 0, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			BufferCache::deleteBuffer("Vertex Buffer");
			BufferCache::deleteBuffer("Index Buffer");
			BufferCache::deleteBuffer("Matrix Buffer");
			BufferCache::deleteBuffer("ConstantBuffer");
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
		size_t fileSize = 0;
		file.open(fsPath, std::ifstream::in | std::ifstream::binary);
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

		file.open(vsPath, std::ifstream::in | std::ifstream::binary);
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

		return bgfx::createProgram(vhandle, fhandle, false);
	}

	struct BgfxCallback : public bgfx::CallbackI
	{
		virtual ~BgfxCallback()
		{
		}

		virtual void fatal(const char* _filePath, uint16_t _line, bgfx::Fatal::Enum _code, const char* _str) override
		{
			//BX_UNUSED(_filePath, _line);

			// Something unexpected happened, inform user and bail out.
			log::error("Fatal error {}:{} [{}]: {}", _filePath, _line, _code, _str);

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
		bgfx::IndexBufferHandle indexBuffer;
		bgfx::ProgramHandle shader;
		bgfx::VertexLayout inputLayout;
		BgfxCallback callback;
		uint64_t state = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_FRONT_CCW
			| BGFX_STATE_MSAA
			| 0;

		uniformData data;
		float i = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = BGFX;
			name = "DrawArrays";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());
			bgfx::Init init;
			init.platformData.nwh = glfwGetWin32Window(api->getWindow());
			init.platformData.ndt = nullptr;
#if RenderingAPI == RenderingAPI_OGL
			init.type = bgfx::RendererType::OpenGL;
#elif RenderingAPI == RenderingAPI_DX11
			init.type = bgfx::RendererType::Direct3D11;
			init.platformData.context = api->getHwnd().dev;
			init.platformData.backBuffer = api->getHwnd().backbuffer;
			init.platformData.backBufferDS = api->getHwnd().depthStencilView;
#endif

			init.resolution.width = api->getHwnd().m_resolution.x;
			init.resolution.height = api->getHwnd().m_resolution.y;
#ifdef _DEBUG
			//init.callback = &callback;
#endif
			bgfx::init(init);
			bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x6495EDff, 1.0f, 0);
			bgfx::setViewRect(0, 0, 0, Screen_Width, Screen_Height);

			inputLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float).end();

			vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(vertices, sizeof(vertices)), inputLayout);

#if RenderingAPI == RenderingAPI_OGL
			shader = loadShader("test", "resources/shaders/ogl/testFS.shader", "resources/shaders/ogl/testVS.shader");
#elif RenderingAPI == RenderingAPI_DX11
			shader = loadShader("test", "resources/shaders/dx11/testFS.shader", "resources/shaders/dx11/testVS.shader");
#endif

			if (shader.idx == bgfx::kInvalidHandle)
				log::error("Shader failed to compile");


			bgfx::setViewTransform(0, math::lookAt(cam.pos, cam.pos + cam.front, cam.up).data, math::perspective(math::radians(45.f), Screen_Width / Screen_Height, .1f, 100.0f).data);
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			bgfx::touch(0);

			for (float x = min; x < max; x += step)
			{
				for (float y = min; y < max; y += step)
				{
					math::vec3 pos = { x + (step / 2.f), y + (step / 2.f), 0.0f };
					auto model = math::translate(math::mat4(1.0f), pos);
					model = math::rotate(model, math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					bgfx::setTransform(model.data);

					bgfx::setVertexBuffer(0, vertexBuffer);
					bgfx::setState(state);
					bgfx::submit(0, shader);
				}
			}
			bgfx::frame();
			bgfx::frame();
		}

		virtual void destroy(RenderInterface* api) override
		{
			bgfx::shutdown();
			api->initialize(api->getHwnd().m_resolution, "Arbook", api->getWindow());
		}
	};

	struct BGFX_DrawArraysInstancedTest : public rendering_test
	{
		std::vector<math::mat4> models;

		bgfx::PlatformData platformData;
		bgfx::VertexBufferHandle vertexBuffer;
		bgfx::IndexBufferHandle indexBuffer;
		bgfx::ProgramHandle shader;
		bgfx::VertexLayout inputLayout;
		BgfxCallback callback;
		uint64_t state = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_FRONT_CCW
			| BGFX_STATE_MSAA
			| 0;

		uniformData data;
		float i = 0;
		int index = 0;


		virtual void setup(RenderInterface* api) override
		{
			type = BGFX;
			name = "DrawArraysInstanced";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());

			bgfx::Init init;
			init.platformData.nwh = glfwGetWin32Window(api->getWindow());
			init.platformData.ndt = nullptr;
#if RenderingAPI == RenderingAPI_OGL
			init.type = bgfx::RendererType::OpenGL;
#elif RenderingAPI == RenderingAPI_DX11
			init.type = bgfx::RendererType::Direct3D11;
			init.platformData.context = api->getHwnd().dev;
			init.platformData.backBuffer = api->getHwnd().backbuffer;
			init.platformData.backBufferDS = api->getHwnd().depthStencilView;
#endif
			init.resolution.width = api->getHwnd().m_resolution.x;
			init.resolution.height = api->getHwnd().m_resolution.y;
#ifdef _DEBUG
			//init.callback = &callback;
#endif
			bgfx::init(init);

			bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x6495EDff, 1.0f, 0);
			bgfx::setViewRect(0, 0, 0, Screen_Width, Screen_Height);

			inputLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float).end();

			vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(instance_vertices, sizeof(instance_vertices)), inputLayout);

#if RenderingAPI == RenderingAPI_OGL
			shader = loadShader("test", "resources/shaders/ogl/instance_testFS.shader", "resources/shaders/ogl/instance_testVS.shader");
#elif RenderingAPI == RenderingAPI_DX11
			shader = loadShader("test", "resources/shaders/dx11/instance_testFS.shader", "resources/shaders/dx11/instance_testVS.shader");
#endif

			if (shader.idx == bgfx::kInvalidHandle)
				log::error("Shader failed to compile");

			bgfx::setViewTransform(0, math::lookAt(cam.pos, cam.pos + cam.front, cam.up).data, math::perspective(math::radians(45.f), Screen_Width / Screen_Height, .1f, 100.0f).data);
		}

		virtual void update(RenderInterface* api) override
		{
			index = 0;
			i += .1f;
			bgfx::touch(0);

			uint32_t drawnCubes = bgfx::getAvailInstanceDataBuffer(instanceCount, sizeof(math::mat4));
			bgfx::InstanceDataBuffer instanceBuffer;
			bgfx::allocInstanceDataBuffer(&instanceBuffer, drawnCubes, sizeof(math::mat4));

			uint8_t* data = instanceBuffer.data;
			math::mat4* mtx = (math::mat4*)data;
			for (float x = min; x < max; x += instanceStep)
			{
				for (float y = min; y < max; y += instanceStep)
				{
					math::vec3 pos = { x + (instanceStep / 2.f), y + (instanceStep / 2.f), 0.0f };
					mtx[index] = math::translate(math::mat4(1.0f), pos);
					mtx[index] = math::rotate(mtx[index], math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					index++;
					if (index >= instanceCount)
						break;
				}
				if (index >= instanceCount)
					break;
			}

			bgfx::setVertexBuffer(0, vertexBuffer);
			bgfx::setInstanceDataBuffer(&instanceBuffer);
			bgfx::setState(state);
			bgfx::submit(0, shader);

			bgfx::frame();
			bgfx::frame();
		}

		virtual void destroy(RenderInterface* api) override
		{
			bgfx::shutdown();
			api->initialize(api->getHwnd().m_resolution, "Arbook", api->getWindow());
		}
	};

	struct BGFX_DrawIndexedTest : public rendering_test
	{
		bgfx::PlatformData platformData;
		bgfx::VertexBufferHandle vertexBuffer;
		bgfx::IndexBufferHandle indexBuffer;
		bgfx::ProgramHandle shader;
		bgfx::VertexLayout inputLayout;
		BgfxCallback callback;
		uint64_t state = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_FRONT_CCW
			| BGFX_STATE_MSAA
			| 0;

		uniformData data;
		float i = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = BGFX;
			name = "DrawIndexed";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());
			bgfx::Init init;
			init.platformData.nwh = glfwGetWin32Window(api->getWindow());
			init.platformData.ndt = nullptr;
#if RenderingAPI == RenderingAPI_OGL
			init.type = bgfx::RendererType::OpenGL;
#elif RenderingAPI == RenderingAPI_DX11
			init.type = bgfx::RendererType::Direct3D11;
			init.platformData.context = api->getHwnd().dev;
			init.platformData.backBuffer = api->getHwnd().backbuffer;
			init.platformData.backBufferDS = api->getHwnd().depthStencilView;
#endif

			init.resolution.width = api->getHwnd().m_resolution.x;
			init.resolution.height = api->getHwnd().m_resolution.y;
#ifdef _DEBUG
			init.callback = &callback;
#endif
			bgfx::init(init);

			bgfx::setDebug(BGFX_DEBUG_TEXT);

			bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x6495EDff, 1.0f, 0);
			bgfx::setViewMode(0, bgfx::ViewMode::Default);
			bgfx::setViewRect(0, 0, 0, Screen_Width, Screen_Height);

			inputLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float).end();

			vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(indVertices, sizeof(indVertices)), inputLayout);

			indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indicies, sizeof(indicies)));


#if RenderingAPI == RenderingAPI_OGL
			shader = loadShader("test", "resources/shaders/ogl/testFS.shader", "resources/shaders/ogl/testVS.shader");
#elif RenderingAPI == RenderingAPI_DX11
			shader = loadShader("test", "resources/shaders/dx11/testFS.shader", "resources/shaders/dx11/testVS.shader");
#endif

			if (shader.idx == bgfx::kInvalidHandle)
				log::error("Shader failed to compile");

			bgfx::setViewTransform(0, math::lookAt(cam.pos, cam.pos + cam.front, cam.up).data, math::perspective(math::radians(45.f), Screen_Width / Screen_Height, .1f, 100.0f).data);
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			bgfx::touch(0);

			for (float x = min; x < max; x += step)
			{
				for (float y = min; y < max; y += step)
				{
					math::vec3 pos = { x + (step / 2.f), y + (step / 2.f), 0.0f };
					auto model = math::translate(math::mat4(1.0f), pos);
					model = math::rotate(model, math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					bgfx::setTransform(model.data);

					bgfx::setVertexBuffer(0, vertexBuffer);
					bgfx::setIndexBuffer(indexBuffer);
					bgfx::setState(state);
					bgfx::submit(0, shader);
				}
			}

			bgfx::frame();
			bgfx::frame();
		}

		virtual void destroy(RenderInterface* api) override
		{
			bgfx::shutdown();
			api->initialize(api->getHwnd().m_resolution, "Arbook", api->getWindow());
		}
	};

	struct BGFX_DrawIndexedInstancedTest : public rendering_test
	{
		std::vector<math::mat4> models;

		bgfx::PlatformData platformData;
		bgfx::VertexBufferHandle vertexBuffer;
		bgfx::IndexBufferHandle indexBuffer;
		bgfx::ProgramHandle shader;
		bgfx::VertexLayout inputLayout;
		BgfxCallback callback;
		uint64_t state = 0
			| BGFX_STATE_WRITE_RGB
			| BGFX_STATE_WRITE_A
			| BGFX_STATE_WRITE_Z
			| BGFX_STATE_FRONT_CCW
			| BGFX_STATE_MSAA
			| 0;

		uniformData data;
		float i = 0;
		int index = 0;


		virtual void setup(RenderInterface* api) override
		{
			type = BGFX;
			name = "DrawIndexedInstanced";
			log::debug("Initializing {}_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}_Test{}", stringify(type), name).c_str());

			bgfx::Init init;
			init.platformData.nwh = glfwGetWin32Window(api->getWindow());
			init.platformData.ndt = nullptr;
#if RenderingAPI == RenderingAPI_OGL
			init.type = bgfx::RendererType::OpenGL;
#elif RenderingAPI == RenderingAPI_DX11
			init.type = bgfx::RendererType::Direct3D11;
			init.platformData.context = api->getHwnd().dev;
			init.platformData.backBuffer = api->getHwnd().backbuffer;
			init.platformData.backBufferDS = api->getHwnd().depthStencilView;
#endif

			init.resolution.width = api->getHwnd().m_resolution.x;
			init.resolution.height = api->getHwnd().m_resolution.y;
#ifdef _DEBUG
			init.callback = &callback;
#endif
			bgfx::init(init);

			bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH, 0x6495EDff, 1.0f, 0);
			bgfx::setViewMode(0, bgfx::ViewMode::Default);
			bgfx::setViewRect(0, 0, 0, Screen_Width, Screen_Height);

			inputLayout.begin().add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float).add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float).end();

			vertexBuffer = bgfx::createVertexBuffer(bgfx::makeRef(instance_indVertices, sizeof(instance_indVertices)), inputLayout);

			indexBuffer = bgfx::createIndexBuffer(bgfx::makeRef(indicies, sizeof(indicies)));


#if RenderingAPI == RenderingAPI_OGL
			shader = loadShader("test", "resources/shaders/ogl/instance_testFS.shader", "resources/shaders/ogl/instance_testVS.shader");
#elif RenderingAPI == RenderingAPI_DX11
			shader = loadShader("test", "resources/shaders/dx11/instance_testFS.shader", "resources/shaders/dx11/instance_testVS.shader");
#endif

			if (shader.idx == bgfx::kInvalidHandle)
				log::error("Shader failed to compile");

			bgfx::setViewTransform(0, math::lookAt(cam.pos, cam.pos + cam.front, cam.up).data, math::perspective(math::radians(45.f), Screen_Width / Screen_Height, .1f, 100.0f).data);
		}

		virtual void update(RenderInterface* api) override
		{
			index = 0;
			i += .1f;
			bgfx::touch(0);

			uint32_t drawnCubes = bgfx::getAvailInstanceDataBuffer(instanceCount, sizeof(math::mat4));
			bgfx::InstanceDataBuffer instanceBuffer;
			bgfx::allocInstanceDataBuffer(&instanceBuffer, drawnCubes, sizeof(math::mat4));

			uint8_t* data = instanceBuffer.data;
			math::mat4* mtx = (math::mat4*)data;
			for (float x = min; x < max; x += instanceStep)
			{
				for (float y = min; y < max; y += instanceStep)
				{
					math::vec3 pos = { x + (instanceStep / 2.f), y + (instanceStep / 2.f), 0.0f };
					mtx[index] = math::translate(math::mat4(1.0f), pos);
					mtx[index] = math::rotate(mtx[index], math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					index++;
					if (index >= instanceCount)
						break;
				}
				if (index >= instanceCount)
					break;
			}

			bgfx::setVertexBuffer(0, vertexBuffer);
			bgfx::setIndexBuffer(indexBuffer);
			bgfx::setInstanceDataBuffer(&instanceBuffer);
			bgfx::setState(state);
			bgfx::submit(0, shader);

			bgfx::frame();
			bgfx::frame();
		}

		virtual void destroy(RenderInterface* api) override
		{
			bgfx::shutdown();
			api->initialize(api->getHwnd().m_resolution, "Arbook", api->getWindow());
		}
	};
#pragma endregion

#pragma region Native API

#if RenderingAPI == RenderingAPI_OGL
	struct Native_DrawArraysTest : public rendering_test
	{
		unsigned int bufferId;
		unsigned int constantBufferId;
		unsigned int vaoId;
		unsigned int shaderId;
		shader_handle shader;
		uniformData data;

		float i = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Native;
			name = "DrawArrays";
			log::debug("Initializing {}OGL_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}OGL_Test{}", stringify(type), name).c_str());
			shader = ShaderCache::createShader(*api, "test", "resources/shaders/cube.shader");
			shaderId = shader;

			glGenBuffers(1, &constantBufferId);
			glBindBuffer(GL_UNIFORM_BUFFER, constantBufferId);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(uniformData), nullptr, GL_STATIC_DRAW);
			glBindBufferRange(GL_UNIFORM_BUFFER, 0, constantBufferId, 0, 1);
			glUseProgram(shaderId);
			glUniformBlockBinding(shaderId, glGetUniformBlockIndex(shaderId, "ConstantBuffer"), 0);

			glGenBuffers(1, &bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glUseProgram(shaderId);
			glGenVertexArrays(1, &vaoId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec4), reinterpret_cast<void*>(0));
			glVertexAttribDivisor(0, 0);

			//glEnableVertexAttribArray(1);
			//glVertexAttribPointer(1, 2, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec2), reinterpret_cast<void*>(0));
			//glVertexAttribDivisor(1, 0);

		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			for (float x = min; x < max; x += step)
			{
				for (float y = min; y < max; y += step)
				{
					math::vec3 pos = { x + (step / 2.f), y + (step / 2.f), 0.0f };
					auto model = math::translate(math::mat4(1.0f), pos);
					data.mvp = projView * math::rotate(model, math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					glBindBuffer(GL_UNIFORM_BUFFER, constantBufferId);
					glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(uniformData), &data);
					glDrawArrays(GL_TRIANGLES, 0, sizeof(vertices) / sizeof(vtx));
				}
			}
		}

		virtual void destroy(RenderInterface* api) override
		{
			ShaderCache::deleteShader("test");
		}
	};

	struct Native_DrawArraysInstancedTest : public rendering_test
	{
		std::vector<math::mat4> models;

		unsigned int bufferId;
		unsigned int matrixBufferId;
		unsigned int constantBufferId;
		unsigned int vaoId;
		unsigned int shaderId;
		shader_handle shader;
		uniformData data;

		float i = 0;
		int index = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Native;
			name = "DrawArraysInstanced";
			log::debug("Initializing {}OGL_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}OGL_Test{}", stringify(type), name).c_str());

			shader = ShaderCache::createShader(*api, "test", "resources/shaders/instance_cube.shader");
			shaderId = shader;

			glGenBuffers(1, &constantBufferId);
			glBindBuffer(GL_UNIFORM_BUFFER, constantBufferId);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(uniformData), nullptr, GL_STATIC_DRAW);
			glBindBufferRange(GL_UNIFORM_BUFFER, 0, constantBufferId, 0, 1);
			glUseProgram(shaderId);
			glUniformBlockBinding(shaderId, glGetUniformBlockIndex(shaderId, "ConstantBuffer"), 0);

			glGenBuffers(1, &bufferId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(instance_vertices), instance_vertices, static_cast<GLenum>(UsageType::STATICDRAW));

			glUseProgram(shaderId);
			glGenVertexArrays(1, &vaoId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, bufferId);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec3), reinterpret_cast<void*>(0));
			glVertexAttribDivisor(0, 0);

			//glEnableVertexAttribArray(1);
			//glVertexAttribPointer(1, 2, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec2), reinterpret_cast<void*>(0));
			//glVertexAttribDivisor(1, 0);

			glGenBuffers(1, &matrixBufferId);
			glBindBuffer(GL_ARRAY_BUFFER, matrixBufferId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(math::mat4), nullptr, static_cast<GLenum>(UsageType::STATICDRAW));
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);
			glEnableVertexAttribArray(5);

			glVertexAttribPointer(2, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(0 * sizeof(math::vec4)));
			glVertexAttribPointer(3, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(1 * sizeof(math::vec4)));
			glVertexAttribPointer(4, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(2 * sizeof(math::vec4)));
			glVertexAttribPointer(5, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(3 * sizeof(math::vec4)));

			glVertexAttribDivisor(2, 1);
			glVertexAttribDivisor(3, 1);
			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);

			data.mvp = projView;
			glBindBuffer(GL_UNIFORM_BUFFER, constantBufferId);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(uniformData), &data);
			models.resize(instanceCount);
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			index = 0;
			for (float x = min; x < max; x += instanceStep)
			{
				for (float y = min; y < max; y += instanceStep)
				{
					math::vec3 pos = { x + (instanceStep / 2.f), y + (instanceStep / 2.f), 0.0f };
					models[index] = math::translate(math::mat4(1.0f), pos);
					models[index] = math::rotate(models[index], math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					index++;
					if (index >= instanceCount)
						break;
				}
				if (index >= instanceCount)
					break;
			}
			glBindBuffer(GL_ARRAY_BUFFER, matrixBufferId);
			glBufferData(GL_ARRAY_BUFFER, models.size() * sizeof(math::mat4), models.data(), static_cast<GLenum>(UsageType::STATICDRAW));
			glDrawArraysInstanced(GL_TRIANGLES, 0, sizeof(instance_vertices) / sizeof(vtx), instanceCount);
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
		unsigned int matrixBufferId;
		unsigned int constantBufferId;
		unsigned int shaderId;
		shader_handle shader;
		uniformData data;
		camera cam;

		float i = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Native;
			name = "DrawIndexed";
			log::debug("Initializing {}OGL_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}OGL_Test{}", stringify(type), name).c_str());

			shader = ShaderCache::createShader(*api, "test", "resources/shaders/cube.shader");
			shaderId = shader;

			glGenBuffers(1, &constantBufferId);
			glBindBuffer(GL_UNIFORM_BUFFER, constantBufferId);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(uniformData), nullptr, GL_STATIC_DRAW);
			glBindBufferRange(GL_UNIFORM_BUFFER, 0, constantBufferId, 0, 1);
			glUseProgram(shaderId);
			glUniformBlockBinding(shaderId, glGetUniformBlockIndex(shaderId, "ConstantBuffer"), 0);

			glGenBuffers(1, &vboId);
			glBindBuffer(GL_ARRAY_BUFFER, vboId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(indVertices), indVertices, static_cast<GLenum>(UsageType::STATICDRAW));
			glGenBuffers(1, &eboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, static_cast<GLenum>(UsageType::STATICDRAW));
			glUseProgram(shaderId);
			glGenVertexArrays(1, &vaoId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, vboId);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec3), reinterpret_cast<void*>(0));
			glVertexAttribDivisor(0, 0);

			//glEnableVertexAttribArray(1);
			//glVertexAttribPointer(1, 2, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec2), reinterpret_cast<void*>(0));
			//glVertexAttribDivisor(1, 0);

			glGenBuffers(1, &matrixBufferId);
			glBindBuffer(GL_ARRAY_BUFFER, matrixBufferId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(math::mat4), nullptr, static_cast<GLenum>(UsageType::STATICDRAW));
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);
			glEnableVertexAttribArray(5);

			glVertexAttribPointer(2, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(0 * sizeof(math::vec4)));
			glVertexAttribPointer(3, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(1 * sizeof(math::vec4)));
			glVertexAttribPointer(4, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(2 * sizeof(math::vec4)));
			glVertexAttribPointer(5, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(3 * sizeof(math::vec4)));

			glVertexAttribDivisor(2, 1);
			glVertexAttribDivisor(3, 1);
			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			for (float x = min; x < max; x += step)
			{
				for (float y = min; y < max; y += step)
				{
					math::vec3 pos = { x + (step / 2.f), y + (step / 2.f), 0.0f };
					auto model = math::translate(math::mat4(1.0f), pos);
					data.mvp = projView * math::rotate(model, math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(uniformData), &data);
					glDrawElements(GL_TRIANGLES, sizeof(indicies) / sizeof(unsigned int), GL_UNSIGNED_INT, reinterpret_cast <void*>(0));
				}
			}

		}

		virtual void destroy(RenderInterface* api) override
		{
			ShaderCache::deleteShader("test");
		}
	};

	struct Native_DrawIndexedInstancedTest : public rendering_test
	{
		std::vector<math::mat4> models;

		unsigned int vboId;
		unsigned int vaoId;
		unsigned int eboId;
		unsigned int constantBufferId;
		unsigned int matrixBufferId;
		unsigned int shaderId;
		shader_handle shader;
		uniformData data;
		camera cam;

		float i = 0;
		int index = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Native;
			name = "DrawIndexedInstanced";
			log::debug("Initializing {}OGL_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}OGL_Test{}", stringify(type), name).c_str());

			shader = ShaderCache::createShader(*api, "test", "resources/shaders/instance_cube.shader");
			shaderId = shader;

			glGenBuffers(1, &constantBufferId);
			glBindBuffer(GL_UNIFORM_BUFFER, constantBufferId);
			glBufferData(GL_UNIFORM_BUFFER, sizeof(uniformData), nullptr, GL_STATIC_DRAW);
			glBindBufferRange(GL_UNIFORM_BUFFER, 0, constantBufferId, 0, 1);
			glUseProgram(shaderId);
			glUniformBlockBinding(shaderId, glGetUniformBlockIndex(shaderId, "ConstantBuffer"), 0);

			glGenBuffers(1, &vboId);
			glBindBuffer(GL_ARRAY_BUFFER, vboId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(instance_indVertices), instance_indVertices, static_cast<GLenum>(UsageType::STATICDRAW));
			glGenBuffers(1, &eboId);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, static_cast<GLenum>(UsageType::STATICDRAW));
			glUseProgram(shaderId);
			glGenVertexArrays(1, &vaoId);
			glBindVertexArray(vaoId);
			glBindBuffer(GL_ARRAY_BUFFER, vboId);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec3), reinterpret_cast<void*>(0));
			glVertexAttribDivisor(0, 0);

			//glEnableVertexAttribArray(1);
			//glVertexAttribPointer(1, 2, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::vec2), reinterpret_cast<void*>(0));
			//glVertexAttribDivisor(1, 0);

			glGenBuffers(1, &matrixBufferId);
			glBindBuffer(GL_ARRAY_BUFFER, matrixBufferId);
			glBufferData(GL_ARRAY_BUFFER, sizeof(math::mat4), nullptr, static_cast<GLenum>(UsageType::STATICDRAW));
			glEnableVertexAttribArray(2);
			glEnableVertexAttribArray(3);
			glEnableVertexAttribArray(4);
			glEnableVertexAttribArray(5);

			glVertexAttribPointer(2, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(0 * sizeof(math::vec4)));
			glVertexAttribPointer(3, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(1 * sizeof(math::vec4)));
			glVertexAttribPointer(4, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(2 * sizeof(math::vec4)));
			glVertexAttribPointer(5, 4, static_cast<GLenum>(DataType::FLOAT), false, sizeof(math::mat4), reinterpret_cast<void*>(3 * sizeof(math::vec4)));

			glVertexAttribDivisor(2, 1);
			glVertexAttribDivisor(3, 1);
			glVertexAttribDivisor(4, 1);
			glVertexAttribDivisor(5, 1);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);

			data.mvp = projView;

			glBindBuffer(GL_UNIFORM_BUFFER, constantBufferId);
			glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(uniformData), &data);
			models.resize(instanceCount);
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			index = 0;
			for (float x = min; x < max; x += instanceStep)
			{
				for (float y = min; y < max; y += instanceStep)
				{
					math::vec3 pos = { x + (instanceStep / 2.f), y + (instanceStep / 2.f), 0.0f };
					models[index] = math::translate(math::mat4(1.0f), pos);
					models[index] = math::rotate(models[index], math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					index++;
					if (index >= instanceCount)
						break;
				}
				if (index >= instanceCount)
					break;
			}
			glBindBuffer(GL_ARRAY_BUFFER, matrixBufferId);
			glBufferData(GL_ARRAY_BUFFER, models.size() * sizeof(math::mat4), models.data(), static_cast<GLenum>(UsageType::STATICDRAW));
			glDrawElementsInstanced(GL_TRIANGLES, sizeof(indicies) / sizeof(unsigned int), GL_UNSIGNED_INT, reinterpret_cast <void*>(0), instanceCount);

		}

		virtual void destroy(RenderInterface* api) override
		{
			ShaderCache::deleteShader("test");
		}
	};

#elif RenderingAPI == RenderingAPI_DX11

	inline void InitializeShadersAndLayout(ID3D11Device* device, ID3D11DeviceContext* deviceContext, ID3D11InputLayout* inputLayout, ID3D10Blob* vtxBlob, ID3D10Blob* pixBlob, ID3D11VertexShader* vertexShader, ID3D11PixelShader* pixelShader, rythe::rendering::shader_source source)
	{
		ID3DBlob* error;
		UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		flags |= D3DCOMPILE_DEBUG;
#endif
		HRESULT hr = D3DCompile(source.vertexSource.c_str(), source.vertexSource.length(), nullptr, nullptr, nullptr, "VShader", "vs_4_0", flags, 0, &vtxBlob, &error);
		if (FAILED(hr))
		{
			log::error("Vertex Shader Compilation failed");
			if (error)
			{
				log::error((char*)error->GetBufferPointer());
			}
		}
		hr = D3DCompile(source.fragSource.c_str(), source.fragSource.length(), nullptr, nullptr, nullptr, "PShader", "ps_4_0", flags, 0, &pixBlob, &error);
		if (FAILED(hr))
		{
			log::error("Fragment Shader Compilation failed");
			if (error)
			{
				log::error((char*)error->GetBufferPointer());
			}
		}

		// Vertex shader
		device->CreateVertexShader(vtxBlob->GetBufferPointer(), vtxBlob->GetBufferSize(), 0, &vertexShader);
		device->CreatePixelShader(pixBlob->GetBufferPointer(), pixBlob->GetBufferSize(), 0, &pixelShader);

		// Set the shaders
		deviceContext->VSSetShader(vertexShader, 0, 0);
		deviceContext->PSSetShader(pixelShader, 0, 0);

		D3D11_INPUT_ELEMENT_DESC layout[] =
		{
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }//,
			//{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
		};

		device->CreateInputLayout(layout, sizeof(layout) / sizeof(layout[0]), vtxBlob->GetBufferPointer(), vtxBlob->GetBufferSize(), &inputLayout);

		// Set the input layout
		deviceContext->IASetInputLayout(inputLayout);
	}

	struct Native_DrawArraysTest : public rendering_test
	{

		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* constantBuffer;
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;

		ID3D10Blob* vertexBlob;
		ID3D10Blob* pixelBlob;
		ID3D11DeviceContext* deviceContext;
		ID3D11Device* device;

		uniformData data;
		camera cam;

		float i = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Native;
			name = "DrawArrays";
			log::debug("Initializing {}DX11_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}DX11_Test{}", stringify(type), name).c_str());

			device = api->getHwnd().dev;
			deviceContext = api->getHwnd().devcon;

			// Create the vertex buffer
			D3D11_BUFFER_DESC bd = {};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(vertices);
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = vertices;
			device->CreateBuffer(&bd, &initData, &vertexBuffer);

			// Set the vertex buffer
			UINT stride = sizeof(vtx);
			UINT offset = 0;
			deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

			//Create Constant Buffer
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(uniformData);
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = 0;
			initData.pSysMem = &data;
			device->CreateBuffer(&bd, &initData, &constantBuffer);

			deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
			//Load shader source
			auto source = ShaderCache::loadShader("resources/shaders/cube.shader");

			// Create and set the shaders and Set the input layout
			InitializeShadersAndLayout(device, deviceContext, inputLayout, vertexBlob, pixelBlob, vertexShader, pixelShader, source);

			// Set primitive topology
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			for (float x = min; x < max; x += step)
			{
				for (float y = min; y < max; y += step)
				{
					math::vec3 pos = { x + (step / 2.f), y + (step / 2.f), 0.0f };
					auto model = math::translate(math::mat4(1.0f), pos);
					data.mvp = projView * math::rotate(model, math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));

					deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &data, 0, 0);
					deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
					deviceContext->Draw(sizeof(vertices) / sizeof(vtx), 0);
				}
			}
		}

		virtual void destroy(RenderInterface* api) override
		{
			if (vertexBuffer) vertexBuffer->Release();
			if (constantBuffer) constantBuffer->Release();
			if (inputLayout) inputLayout->Release();
			if (vertexShader) vertexShader->Release();
			if (pixelShader) pixelShader->Release();
		}
	};

	struct Native_DrawArraysInstancedTest : public rendering_test
	{
		std::vector<math::mat4> models;

		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* constantBuffer;
		ID3D11Buffer* matrixBuffer;
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;

		ID3D10Blob* vertexBlob;
		ID3D10Blob* pixelBlob;
		ID3D11DeviceContext* deviceContext;
		ID3D11Device* device;

		uniformData data;

		float i = 0;
		int index = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Native;
			name = "DrawArraysInstanced";
			log::debug("Initializing {}DX11_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}DX11_Test{}", stringify(type), name).c_str());

			device = api->getHwnd().dev;
			deviceContext = api->getHwnd().devcon;

			// Create the vertex buffer
			D3D11_BUFFER_DESC bd = {};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(instance_vertices);
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = instance_vertices;
			CHECKERROR(device->CreateBuffer(&bd, &initData, &vertexBuffer), "Failed Vertex Buffer Create", api->checkError());

			// Set the vertex buffer
			UINT stride = sizeof(vtx);
			UINT offset = 0;
			deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

			models.resize(instanceCount);
			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(math::mat4) * instanceCount;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			initData.pSysMem = models.data();
			CHECKERROR(device->CreateBuffer(&bd, &initData, &matrixBuffer), "Failed Matrix Buffer Create", api->checkError());

			// Set the vertex buffer
			stride = sizeof(math::mat4);
			offset = 0;
			deviceContext->IASetVertexBuffers(1, 1, &matrixBuffer, &stride, &offset);

			data.mvp = projView;
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(uniformData);
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = 0;
			initData.pSysMem = &data;
			CHECKERROR(device->CreateBuffer(&bd, &initData, &constantBuffer), "Failed Constant Buffer Create", api->checkError());

			deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

			//Load shader source
			auto source = ShaderCache::loadShader("resources/shaders/instance_cube.shader");

			UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
			flags |= D3DCOMPILE_DEBUG;
#endif
			ID3DBlob* error;
			HRESULT hr = D3DCompile(source.vertexSource.c_str(), source.vertexSource.length(), nullptr, nullptr, nullptr, "VShader", "vs_4_0", flags, 0, &vertexBlob, &error);
			if (FAILED(hr))
			{
				log::error("Vertex Shader Compilation failed");
				if (error)
				{
					log::error((char*)error->GetBufferPointer());
				}
				api->checkError();
			}
			hr = D3DCompile(source.fragSource.c_str(), source.fragSource.length(), nullptr, nullptr, nullptr, "PShader", "ps_4_0", flags, 0, &pixelBlob, &error);
			if (FAILED(hr))
			{
				log::error("Fragment Shader Compilation failed");
				if (error)
				{
					log::error((char*)error->GetBufferPointer());
				}
				api->checkError();
			}

			// Vertex shader
			device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), 0, &vertexShader);
			device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), 0, &pixelShader);

			// Set the shaders
			deviceContext->VSSetShader(vertexShader, 0, 0);
			deviceContext->PSSetShader(pixelShader, 0, 0);

			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				//{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

				{ "MODEL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
				{ "MODEL", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
				{ "MODEL", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
				{ "MODEL", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
			};

			device->CreateInputLayout(layout, 6, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &inputLayout);

			// Set the input layout
			deviceContext->IASetInputLayout(inputLayout);

			// Set primitive topology
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			index = 0;
			for (float x = min; x < max; x += instanceStep)
			{
				for (float y = min; y < max; y += instanceStep)
				{
					math::vec3 pos = { x + (instanceStep / 2.f), y + (instanceStep / 2.f), 0.0f };
					models[index] = math::translate(math::mat4(1.0f), pos);
					models[index] = math::rotate(models[index], math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					index++;
					if (index >= instanceCount)
						break;
				}
				if (index >= instanceCount)
					break;
			}

			D3D11_MAPPED_SUBRESOURCE resource;
			CHECKERROR(deviceContext->Map(matrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &resource), "Buffer Failed to be filled", api->checkError());
			memcpy(resource.pData, models.data(), models.size() * sizeof(math::mat4));
			deviceContext->Unmap(matrixBuffer, NULL);

			unsigned int stride = sizeof(math::mat4);
			unsigned int offset = 0;
			deviceContext->IASetVertexBuffers(1, 1, &matrixBuffer, &stride, &offset);
			deviceContext->DrawInstanced(sizeof(instance_vertices) / sizeof(vtx), instanceCount, 0, 0);
		}

		virtual void destroy(RenderInterface* api) override
		{
			if (vertexBuffer) vertexBuffer->Release();
			if (constantBuffer) constantBuffer->Release();
			if (matrixBuffer) matrixBuffer->Release();
			if (inputLayout) inputLayout->Release();
			if (vertexShader) vertexShader->Release();
			if (pixelShader) pixelShader->Release();
		}
	};

	struct Native_DrawIndexedTest : public rendering_test
	{
		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
		ID3D11Buffer* constantBuffer;
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D10Blob* vertexBlob;
		ID3D10Blob* pixelBlob;
		ID3D11DeviceContext* deviceContext;
		ID3D11Device* device;

		uniformData data;

		float i = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Native;
			name = "DrawIndexed";
			log::debug("Initializing {}DX11_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}DX11_Test{}", stringify(type), name).c_str());
			device = api->getHwnd().dev;
			deviceContext = api->getHwnd().devcon;

			// Create the vertex buffer
			D3D11_BUFFER_DESC bd = {};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(indVertices);
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = indVertices;
			device->CreateBuffer(&bd, &initData, &vertexBuffer);

			// Set the vertex buffer
			UINT stride = sizeof(vtx);
			UINT offset = 0;
			deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);


			// Create the index buffer
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(indicies);
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			initData.pSysMem = indicies;
			CHECKERROR(device->CreateBuffer(&bd, &initData, &indexBuffer), "Failed Index Buffer Create", api->checkError());

			// Set the index buffer
			deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);

			data.mvp = projView;
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(uniformData);
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = 0;
			initData.pSysMem = &data;
			CHECKERROR(device->CreateBuffer(&bd, &initData, &constantBuffer), "Failed Constant Buffer Create", api->checkError());

			deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

			//Load shader source
			auto source = ShaderCache::loadShader("resources/shaders/cube.shader");

			// Create and set the shaders and Set the input layout
			InitializeShadersAndLayout(device, deviceContext, inputLayout, vertexBlob, pixelBlob, vertexShader, pixelShader, source);

			// Set primitive topology
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			for (float x = min; x < max; x += step)
			{
				for (float y = min; y < max; y += step)
				{
					math::vec3 pos = { x + (step / 2.f), y + (step / 2.f), 0.0f };
					auto model = math::translate(math::mat4(1.0f), pos);
					data.mvp = projView * math::rotate(model, math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &data, 0, 0);
					deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
					deviceContext->DrawIndexed(sizeof(indicies) / sizeof(unsigned int), 0, 0);
				}
			}
		}

		virtual void destroy(RenderInterface* api) override
		{
			if (vertexBuffer) vertexBuffer->Release();
			if (indexBuffer) indexBuffer->Release();
			if (constantBuffer) constantBuffer->Release();
			if (inputLayout) inputLayout->Release();
			if (vertexShader) vertexShader->Release();
			if (pixelShader) pixelShader->Release();
		}
	};

	struct Native_DrawIndexedInstancedTest : public rendering_test
	{
		std::vector<math::mat4> models;

		ID3D11Buffer* vertexBuffer;
		ID3D11Buffer* indexBuffer;
		ID3D11Buffer* matrixBuffer;
		ID3D11Buffer* constantBuffer;
		ID3D11InputLayout* inputLayout;
		ID3D11VertexShader* vertexShader;
		ID3D11PixelShader* pixelShader;
		ID3D10Blob* vertexBlob;
		ID3D10Blob* pixelBlob;
		ID3D11DeviceContext* deviceContext;
		ID3D11Device* device;

		uniformData data;

		float i = 0;
		int index = 0;

		virtual void setup(RenderInterface* api) override
		{
			type = Native;
			name = "DrawIndexedInstanced";
			log::debug("Initializing {}DX11_Test{}", stringify(type), name);
			glfwSetWindowTitle(api->getWindow(), std::format("{}DX11_Test{}", stringify(type), name).c_str());
			device = api->getHwnd().dev;
			deviceContext = api->getHwnd().devcon;

			// Create the vertex buffer
			D3D11_BUFFER_DESC bd = {};
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(instance_indVertices);
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA initData = {};
			initData.pSysMem = instance_indVertices;
			CHECKERROR(device->CreateBuffer(&bd, &initData, &vertexBuffer), "Failed Vertex Buffer Create", api->checkError());

			// Set the vertex buffer
			UINT stride = sizeof(vtx);
			UINT offset = 0;
			deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);


			// Create the index buffer
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(indicies);
			bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
			bd.CPUAccessFlags = 0;
			initData.pSysMem = indicies;
			CHECKERROR(device->CreateBuffer(&bd, &initData, &indexBuffer), "Failed Index Buffer Create", api->checkError());

			// Set the index buffer
			deviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0);


			bd.Usage = D3D11_USAGE_DYNAMIC;
			bd.ByteWidth = sizeof(math::mat4) * instanceCount;
			bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
			CHECKERROR(device->CreateBuffer(&bd, NULL, &matrixBuffer), "Failed Matrix Buffer Create", api->checkError());

			// Set the vertex buffer
			stride = sizeof(math::mat4);
			offset = 0;
			deviceContext->IASetVertexBuffers(1, 1, &matrixBuffer, &stride, &offset);

			data.mvp = projView;
			bd.Usage = D3D11_USAGE_DEFAULT;
			bd.ByteWidth = sizeof(uniformData);
			bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			bd.CPUAccessFlags = 0;
			initData.pSysMem = &data;
			CHECKERROR(device->CreateBuffer(&bd, &initData, &constantBuffer), "Failed Constant Buffer Create", api->checkError());

			deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);

			//Load shader source
			auto source = ShaderCache::loadShader("resources/shaders/instance_cube.shader");


			UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
			flags |= D3DCOMPILE_DEBUG;
#endif
			ID3DBlob* error;
			HRESULT hr = D3DCompile(source.vertexSource.c_str(), source.vertexSource.length(), nullptr, nullptr, nullptr, "VShader", "vs_4_0", flags, 0, &vertexBlob, &error);
			if (FAILED(hr))
			{
				log::error("Vertex Shader Compilation failed");
				if (error)
				{
					log::error((char*)error->GetBufferPointer());
				}
				api->checkError();
			}
			hr = D3DCompile(source.fragSource.c_str(), source.fragSource.length(), nullptr, nullptr, nullptr, "PShader", "ps_4_0", flags, 0, &pixelBlob, &error);
			if (FAILED(hr))
			{
				log::error("Fragment Shader Compilation failed");
				if (error)
				{
					log::error((char*)error->GetBufferPointer());
				}
				api->checkError();
			}

			// Vertex shader
			device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), 0, &vertexShader);
			device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), 0, &pixelShader);

			// Set the shaders
			deviceContext->VSSetShader(vertexShader, 0, 0);
			deviceContext->PSSetShader(pixelShader, 0, 0);

			D3D11_INPUT_ELEMENT_DESC layout[] =
			{
				{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
				//{ "TEXCOORD", 1, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },

				{ "MODEL", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
				{ "MODEL", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
				{ "MODEL", 2, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 },
				{ "MODEL", 3, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_INSTANCE_DATA, 1 }
			};

			device->CreateInputLayout(layout, 6, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &inputLayout);

			// Set the input layout
			deviceContext->IASetInputLayout(inputLayout);

			// Set primitive topology
			deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			models.resize(instanceCount);
		}

		virtual void update(RenderInterface* api) override
		{
			i += .1f;
			index = 0;
			for (float x = min; x < max; x += instanceStep)
			{
				for (float y = min; y < max; y += instanceStep)
				{
					math::vec3 pos = { x + (instanceStep / 2.f), y + (instanceStep / 2.f), 0.0f };
					models[index] = math::translate(math::mat4(1.0f), pos);
					models[index] = math::rotate(models[index], math::radians(i), math::vec3(0.0f, 1.0f, 0.0f));
					index++;
					if (index >= instanceCount)
						break;
				}
				if (index >= instanceCount)
					break;
			}

			D3D11_MAPPED_SUBRESOURCE resource;
			CHECKERROR(deviceContext->Map(matrixBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &resource), "Buffer Failed to be filled", api->checkError());
			memcpy(resource.pData, models.data(), models.size() * sizeof(math::mat4));
			deviceContext->Unmap(matrixBuffer, NULL);

			unsigned int stride = sizeof(math::mat4);
			unsigned int offset = 0;
			deviceContext->IASetVertexBuffers(1, 1, &matrixBuffer, &stride, &offset);
			deviceContext->DrawIndexedInstanced(sizeof(indicies) / sizeof(unsigned int), instanceCount, 0, 0, 0);
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