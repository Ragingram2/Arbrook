#pragma once
#include <rsl/primitives>
#include <rsl/utilities>

#include "core/logging/logging.hpp"

#include "rendering/interface/definitions.hpp"
#include "rendering/cache/shadercache.hpp"
#include "rendering/cache/texturecache.hpp"
#include "rendering/cache/buffercache.hpp"
#include "rendering/pipeline/pipelinebase.hpp"
#include "rendering/components/mesh_renderer.hpp"

namespace rythe::rendering
{
	struct graphics_stage_base
	{
	private:
		bool m_initialized = false;
	public:
		static PipelineBase* pipeline;
		RenderInterface* RI;

	protected:
		virtual void setup() RYTHE_PURE;
		virtual void shutdown_impl() RYTHE_PURE;
	public:
		virtual ~graphics_stage_base() = default;
		virtual void render() RYTHE_PURE;
		virtual rsl::priority_type priority() RYTHE_IMPURE_RETURN(0);

		bool isInitialized() { return m_initialized; }
		void init()
		{
			m_initialized = true;
			setup();
		}
	};

	template<typename Self>
	struct graphics_stage : public graphics_stage_base, protected core::System<mesh_renderer>
	{
		void shutdown_impl() override
		{
		}
	};

	template<typename T>
	concept StageType = std::derived_from<T, graphics_stage<T>>;

	struct clear_stage : public graphics_stage<clear_stage>
	{
		virtual void setup() override
		{
			RI->setSwapInterval(0);
			RI->setViewport(1, 0, 0, Width, Height, 0, 1);
			RI->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);
		}

		virtual void render() override
		{
			RI->clear(ClearBit::COLOR);
		}

		virtual rsl::priority_type priority() override
		{
			return 1;
		}
	};

	struct render_stage : public graphics_stage<render_stage>
	{
		virtual void setup() override
		{
			tex_vtx verticies[] =
			{	//positions						
				{ { -1.f, 1.0f, 0.0f  },	{ 0, 1 } },//0
				{ {-1.f,-1.0f, 0.0f  },	{ 0, 0 } },//1
				{ {  1.0f,-1.0f, 0.0f },		{ 1, 0 } },//2
				{ { -1.0f, 1.0f, 0.0f },		{ 0, 1 } },//0
				{ {  1.0f,-1.0f, 0.0f },		{ 1, 0 } },//2
				{ {  1.0f, 1.0f, 0.0f },		{ 1, 1 } }//3
			};

			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				auto& shader = renderer.shader = ShaderCache::createShader(*RI,"default","resources/shaders/texture.shader");
				auto& texture = renderer.texture = TextureCache::createTexture2D(*RI,"Rythe","resources/textures/Rythe.png");
				auto& vBuffer = renderer.vertexBuffer = BufferCache::createBuffer<tex_vtx>(*RI, "Vertex Buffer", TargetType::VERTEX_BUFFER, UsageType::STATICDRAW, verticies, sizeof(verticies) / sizeof(tex_vtx));
				auto& layout = renderer.layout;
				
				shader->bind();
				texture->bind();
				layout.initialize(RI->getHwnd(), 1, shader);
				layout.setAttributePtr("POSITION", 0, FormatType::RGB32F, 0, sizeof(tex_vtx), 0);
				layout.setAttributePtr("TEXCOORD", 1, FormatType::RG32F, 0, sizeof(tex_vtx), sizeof(math::vec3));
				vBuffer->bind();
				layout.bind();
			}
			RI->checkError();
		}

		virtual void render() override
		{
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				renderer.bind();
				RI->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
			}
			RI->checkError();
		}

		virtual rsl::priority_type priority() override
		{
			return 2;
		}
	};
}