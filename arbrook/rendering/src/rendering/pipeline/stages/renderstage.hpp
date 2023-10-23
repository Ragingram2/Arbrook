#pragma once
#include <rsl/primitives>
#include <rsl/utilities>
#include <rsl/math>

#include "core/logging/logging.hpp"
#include "core/components/transform.hpp"
#include "rendering/cache/cache.hpp"
#include "rendering/interface/definitions.hpp"
#include "rendering/pipeline/base/graphicsstage.hpp"
#include "rendering/components/components.hpp"

namespace rythe::rendering
{
	struct render_stage : public graphics_stage<render_stage, mesh_renderer, core::transform>
	{
		virtual void setup(core::transform camTransf, camera& cam) override
		{
			RI->depthTest(true);
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();

				auto& transf = ent.getComponent<core::transform>();
				cam.calculate_view(&camTransf);
				cam.calculate_projection();
				camData mat = { cam.projection, cam.view, transf.to_world() };
				renderer.model->initialize(RI->getHwnd(), renderer.material->m_shader, renderer.model->meshHandle, renderer.instanced);
				renderer.dirty = false;
				buffer_handle buff = renderer.model->cameraBuffer;
				buff->bufferData(&mat, 1);
			}
			RI->checkError();
		}

		virtual void render(core::transform camTransf, camera& cam) override
		{
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				if (renderer.dirty)
				{
					renderer.model->initialize(RI->getHwnd(), renderer.material->m_shader, renderer.model->meshHandle, renderer.instanced);
					renderer.dirty = false;
				}
				auto& transf = ent.getComponent<core::transform>();
				cam.calculate_view(&camTransf);
				camData mat = { cam.projection, cam.view, transf.to_world() };
				buffer_handle buff = renderer.model->cameraBuffer;
				buff->bufferData(&mat, 1);
				renderer.material->bind();
				renderer.model->bind();
				if (renderer.model->indexBuffer != nullptr)
					RI->drawIndexed(PrimitiveType::TRIANGLESLIST, renderer.model->meshHandle->indices.size(), 0, 0);
				else
					RI->drawArrays(PrimitiveType::TRIANGLESLIST, 0, renderer.model->meshHandle->vertices.size());
			}
			RI->checkError();
		}

		virtual rsl::priority_type priority() override
		{
			return OPAQUE_PRIORITY;
		}
	};
}