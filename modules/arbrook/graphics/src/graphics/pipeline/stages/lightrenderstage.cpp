#include "lightrenderstage.hpp"

namespace rythe::rendering
{
	void light_render_stage::setup(core::transform camTransf, camera& cam)
	{
		(void)camTransf;
		(void)cam;
		pointLightBuffer = BufferCache::createConstantBuffer<point_light_buffer>("PointLightBuffer", SV_PT_LIGHTS, UsageType::STATICDRAW);
		directionalLightBuffer = BufferCache::createConstantBuffer<dir_light_buffer>("DirectionalLightBuffer", SV_DIR_LIGHTS, UsageType::STATICDRAW);

		lightProjection = math::orthographic(-500.0f, 500.0f, -500.0f, 500.0f, -10.0f, 100.0f);
		shadowProjection = math::perspective(90.0f, Shadow_Width / Shadow_Height, 1.0f, far_plane);
	}

	void light_render_stage::render(core::transform camTransf, camera& cam)
	{
		(void)camTransf;
		(void)cam;
		ZoneScopedN("[Renderer] [Light Stage] Render");
		int lightCount = 0;
		for (auto& ent : m_filter)
		{
			auto& transf = ent.getComponent<core::transform>();
			auto& lightComp = ent.getComponent<light>();
			if (!ent->enabled || !lightComp.enabled.get())
			{
				if (lightComp.type() == LightType::DIRECTIONAL)
					dirLightData.dir_data[0].intensity = 0.0f;
				else
				{
					if (lightComp.index() > -1)
						pointLightData.point_data[lightComp.index()].intensity = 0.0f;
				}

				lightComp.index() = -1;
				continue;
			}
			auto lightView = math::lookAt(transf.forward(), math::vec3::zero, transf.up());

			switch (lightComp.type())
			{
			case LightType::DIRECTIONAL:
				lightComp.asDirectionalLight().lightProjection() = lightProjection;
				lightComp.asDirectionalLight().lightView() = lightView;
				lightComp.asDirectionalLight().direction = transf.forward();
				dirLightData.dir_data[0] = lightComp.asDirectionalLight();
				break;
			case LightType::POINT:
				if (m_lastIdx >= MAX_POINT_LIGHT_COUNT) return;
				lightCount++;
				lightComp.asPointLight().shadowProjection = shadowProjection;
				buildShadowCube(lightComp.asPointLight().shadowTransforms.get().data(), transf.position);
				lightComp.asPointLight().position = transf.position;
				lightComp.asPointLight().farPlane = far_plane;
				if (lightComp.index() < 0)
				{
					lightComp.index() = m_lastIdx++;
				}
				if (lightComp.index() < MAX_POINT_LIGHT_COUNT)
					pointLightData.point_data[lightComp.index()] = lightComp.asPointLight();
				break;
			case LightType::SPOT:
				//lightComp.data.position = transf.position;
				break;
			}
		}

		lightInfo.count = lightCount;
		m_lastIdx = lightInfo.count;

		if (pointLightBuffer)
			pointLightBuffer->bufferData(&pointLightData, 1u);

		if (directionalLightBuffer)
			directionalLightBuffer->bufferData(&dirLightData, 1u);
	}

	rsl::priority_type light_render_stage::priority() const { return LIGHT_PRIORITY; }

	void light_render_stage::buildShadowCube(math::mat4* transfArray, math::vec3 lightPos)
	{
		transfArray[0] = math::lookAt(lightPos, lightPos + math::vec3::left, math::vec3::up);
		transfArray[1] = math::lookAt(lightPos, lightPos + math::vec3::right, math::vec3::up);
#if RenderingAPI == RenderingAPI_OGL
		transfArray[2] = math::lookAt(lightPos, lightPos + math::vec3::down, math::vec3::backward);
		transfArray[3] = math::lookAt(lightPos, lightPos + math::vec3::up, math::vec3::forward);
#else
		transfArray[2] = math::lookAt(lightPos, lightPos + math::vec3::up, math::vec3::forward);
		transfArray[3] = math::lookAt(lightPos, lightPos + math::vec3::down, math::vec3::backward);
#endif
		transfArray[4] = math::lookAt(lightPos, lightPos + math::vec3::backward, math::vec3::up);
		transfArray[5] = math::lookAt(lightPos, lightPos + math::vec3::forward, math::vec3::up);
	}
}