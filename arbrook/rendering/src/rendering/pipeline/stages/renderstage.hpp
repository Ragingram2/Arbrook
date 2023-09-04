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
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				renderer.initialize(RI->getHwnd());

				auto& transf = ent.getComponent<core::transform>();
				cam.projection = math::perspective(math::radians(45.f), Screen_Width / Screen_Height, .1f, 100.0f);
				cam.view = math::lookAt(static_cast<math::vec3>(camTransf.position), static_cast<math::vec3>(camTransf.position + camTransf.forward()), camTransf.up());
				math::mat4 mat = { cam.projection * cam.view * static_cast<math::mat4>(transf.localMatrix)};
				buffer_handle buff = renderer.m_model.matrixBuffer;
				buff->bufferData(&mat, 1);
			}
			RI->checkError();
		}

		virtual void render(core::transform camTransf, camera& cam) override
		{
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				//auto& transf = ent.getComponent<core::transform>();
				//math::mat4 mat = { cam.projection * cam.view * static_cast<math::mat4>(transf.localMatrix) };
				//buffer_handle buff = renderer.m_model.matrixBuffer;
				//buff->bufferData(&mat, 1);
				renderer.bind();
				RI->drawArrays(PrimitiveType::TRIANGLESLIST, 0, 6);
			}
			RI->checkError();
		}

		virtual rsl::priority_type priority() override
		{
			return OPAQUE_PRIORITY;
		}
	};
}