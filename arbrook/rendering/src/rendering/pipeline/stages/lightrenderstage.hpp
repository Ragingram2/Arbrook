#pragma once
#include <rsl/primitives>
#include <rsl/utilities>
#include <rsl/math>

#include "rendering/pipeline/base/graphicsstage.hpp"

namespace rythe::rendering
{
	struct light_render_stage : public graphics_stage<light_render_stage, light>
	{
		std::vector<light> m_lights;
		buffer_handle lightBuffer;
		virtual void setup(core::transform camTransf, camera& cam) override
		{
			lightBuffer = BufferCache::createConstantBuffer<light>("LightBuffer", 1, UsageType::STATICDRAW);
		}

		virtual void render(core::transform camTransf, camera& cam) override
		{
			m_lights.clear();
			for (auto& ent : m_filter)
			{
				auto& transf = ent.getComponent<core::transform>();
				auto& lightComp = ent.getComponent<light>();
				lightComp.lightPos = transf.position;
				m_lights.push_back(lightComp);
			}

			if (lightBuffer != nullptr)
			{
				lightBuffer->bufferData(m_lights.data(), m_lights.size());
			}
		}

		virtual rsl::priority_type priority() override { return LIGHT_PRIORITY; }

	};

}