#include "graphics/pipeline/stages/clearstage.hpp"

namespace ast = rythe::core::assets;
namespace rythe::rendering
{
	void clear_stage::setup(core::transform camTransf, camera& cam)
	{
		(void)camTransf;
		(void)cam;
		RI->makeCurrent();
		BufferCache::createConstantBuffer<camera_data>("CameraBuffer", SV_CAMERA, UsageType::STATICDRAW);
		BufferCache::createConstantBuffer<material_data>("MaterialBuffer", SV_MATERIALS, UsageType::STATICDRAW);
		RI->setSwapInterval(0);
		RI->setViewport(1, 0, 0, Screen_Width, Screen_Height);
		RI->setWindOrder(WindOrder::CCW);

		{
			pickingFBO = addFramebuffer("PickingBuffer");
			pickingFBO->initialize();
			pickingFBO->bind();
			auto colorHandle = TextureCache::createTexture("picking-color", TextureType::RENDER_TARGET, { 0, nullptr }, math::ivec2(Screen_Width, Screen_Height), texture_parameters
				{
					.minFilterMode = rendering::FilterMode::NEAREST,
					.magFilterMode = rendering::FilterMode::NEAREST,
					.format = rendering::FormatType::RGBA,
					.usage = rendering::UsageType::DEFAULT,
				});

			pickingFBO->attach(AttachmentSlot::COLOR0, colorHandle, true, true);
			pickingFBO->unbind();
		}

		{
			depthFBO = addFramebuffer("DepthBuffer");
			depthFBO->initialize();
			depthFBO->bind();


			//auto colorHandle = TextureCache::createTexture("shadowMap-color", TextureType::RENDER_TARGET, { 0, nullptr }, math::ivec2(Shadow_Width, Shadow_Height), texture_parameters
			//	{
			//		.usage = rendering::UsageType::DEFAULT,
			//		.minFilterMode = rendering::FilterMode::LINEAR,
			//		.magFilterMode = rendering::FilterMode::LINEAR
			//	});


			depthHandle = TextureCache::createTexture("shadowMap-depth", TextureType::DEPTH_STENCIL, { 0, nullptr }, math::ivec2(Shadow_Width, Shadow_Height), texture_parameters
				{
					.wrapModeS = rendering::WrapMode::CLAMP_TO_BORDER,
					.wrapModeT = rendering::WrapMode::CLAMP_TO_BORDER,
					.wrapModeR = rendering::WrapMode::CLAMP_TO_BORDER,
					.minFilterMode = rendering::FilterMode::NEAREST,
					.magFilterMode = rendering::FilterMode::NEAREST,
					.borderColor = math::vec4(1.0f),
					.format = rendering::FormatType::R24_G8,
					.usage = rendering::UsageType::DEPTH_COMPONENT
				});

			//adding a color attachment is only required cause dx11 throws a warning otherwise
			//depthFBO->attach(AttachmentSlot::COLOR0, colorHandle, true, true);
			depthFBO->attach(AttachmentSlot::DEPTH_STENCIL, depthHandle, false, false);
			depthFBO->unbind();
		}

		{
			depthCubeFBO = addFramebuffer("DepthCubeBuffer");
			depthCubeFBO->initialize();
			depthCubeFBO->bind();

			depthCubeMap = TextureCache::createCubemap("shadowCube-depth", { 0, nullptr }, math::ivec2(Shadow_Width, Shadow_Height), texture_parameters
				{
					.wrapModeS = rendering::WrapMode::CLAMP_TO_BORDER,
					.wrapModeT = rendering::WrapMode::CLAMP_TO_BORDER,
					.wrapModeR = rendering::WrapMode::CLAMP_TO_BORDER,
					.minFilterMode = rendering::FilterMode::NEAREST,
					.magFilterMode = rendering::FilterMode::NEAREST,
					.borderColor = math::vec4(1.0f),
					.format = rendering::FormatType::R24_G8,
					.usage = rendering::UsageType::DEPTH_COMPONENT,
				});

			depthCubeFBO->attach(AttachmentSlot::DEPTH_STENCIL, depthCubeMap, false, false);
			depthCubeFBO->unbind();
		}

		{
			mainFBO = addFramebuffer("MainBuffer");
			mainFBO->initialize();
			mainFBO->bind();

			texture_handle colorHandle = TextureCache::createTexture("main-color", TextureType::RENDER_TARGET, { 0, nullptr }, math::ivec2(Screen_Width, Screen_Height), texture_parameters
				{
					.minFilterMode = rendering::FilterMode::LINEAR,
					.magFilterMode = rendering::FilterMode::LINEAR,
					.usage = rendering::UsageType::DEFAULT
				});

			mainDepthHandle = TextureCache::createTexture("main-depth", TextureType::DEPTH_STENCIL, { 0, nullptr }, math::ivec2(Screen_Width, Screen_Height), texture_parameters
				{
					.wrapModeS = rendering::WrapMode::REPEAT,
					.wrapModeT = rendering::WrapMode::REPEAT,
					.minFilterMode = rendering::FilterMode::NEAREST,
					.magFilterMode = rendering::FilterMode::NEAREST,
					.format = rendering::FormatType::R24_G8,
					.usage = rendering::UsageType::DEPTH_COMPONENT
				});

			mainFBO->attach(AttachmentSlot::COLOR0, colorHandle, true, true);
			mainFBO->attach(AttachmentSlot::DEPTH_STENCIL, mainDepthHandle, true, true);
			mainFBO->unbind();
		}

		for (auto ent : m_filter)
		{
			mesh_renderer& renderer = ent.getComponent<mesh_renderer>();
			if (!ent.data->enabled || !renderer.enabled.get() || !renderer.model.meshHandle || !renderer.mainMaterial) continue;
			initializeModel(renderer);
		}
	}

	void clear_stage::render(core::transform camTransf, camera& cam)
	{
		(void)camTransf;
		(void)cam;
		ZoneScopedN("[Renderer] [Clear Stage] Render");
		mainFBO->bind();
		auto fboRes = mainFBO->getAttachment(AttachmentSlot::COLOR0)->getImpl().resolution;
		RI->setViewport(1, 0, 0, fboRes.x, fboRes.y);

		RI->depthTest(true);
		RI->depthWrite(true);
		RI->setDepthFunction(DepthFuncs::LESS);
		RI->updateDepthStencil();
		RI->cullFace(CullMode::BACK);

		RI->setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);
		RI->clear(true, DepthClearBit::DEPTH);

		for (auto ent : m_filter)
		{
			mesh_renderer& renderer = ent.getComponent<mesh_renderer>();
			if (!ent->enabled || !renderer.enabled.get()|| !renderer.model.meshHandle || !renderer.mainMaterial) continue;

			if (renderer.dirty.get())
				initializeModel(renderer);
		}
	}

	rsl::priority_type clear_stage::priority() const { return CLEAR_PRIORITY; }

	void clear_stage::initializeModel(mesh_renderer& renderer)
	{
		auto& model = renderer.model;
		auto meshHandle = renderer.model.meshHandle;

		if (renderer.mainMaterial)
		{
			renderer.mainMaterial.addTexture(TextureSlot::TEXTURE0, depthHandle);
			renderer.mainMaterial.addTexture(TextureSlot::TEXTURE1, depthCubeMap);

			for (auto [id, matId] : model.meshHandle->materialIds)
			{
				renderer.materials[id] = MaterialCache::getMaterial(matId);
				renderer.materials[id].addTexture(TextureSlot::TEXTURE0, depthHandle);
				renderer.materials[id].addTexture(TextureSlot::TEXTURE1, depthCubeMap);
			}
		}

		model.vertexBuffer = BufferCache::createVertexBuffer<math::vec4>(std::format("{}-Vertex Buffer", meshHandle->name), 0, UsageType::STATICDRAW, meshHandle->vertices);

		model.indexBuffer = BufferCache::createIndexBuffer(std::format("{}-Index Buffer", meshHandle->name), UsageType::STATICDRAW, meshHandle->indices);

		if (meshHandle->normals.size() > 0)
			model.normalBuffer = BufferCache::createVertexBuffer<math::vec3>(std::format("{}-Normal Buffer", meshHandle->name), 1, UsageType::STATICDRAW, meshHandle->normals);

		if (meshHandle->texCoords.size() > 0)
			model.uvBuffer = BufferCache::createVertexBuffer<math::vec2>(std::format("{}-UV Buffer", meshHandle->name), 2, UsageType::STATICDRAW, meshHandle->texCoords);

		if (meshHandle->tangents.size() > 0)
			model.tangentBuffer = BufferCache::createVertexBuffer<math::vec3>(std::format("{}-Tangent Buffer", meshHandle->name), 3, UsageType::STATICDRAW, meshHandle->tangents);

	}
}