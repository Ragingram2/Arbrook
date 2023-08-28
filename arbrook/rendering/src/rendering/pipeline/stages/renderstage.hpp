#pragma once
#include <rsl/primitives>
#include <rsl/utilities>

#include "core/logging/logging.hpp"
#include "rendering/cache/cache.hpp"
#include "rendering/interface/definitions.hpp"
#include "rendering/pipeline/base/graphicsstage.hpp"
#include "rendering/components/components.hpp"

namespace rythe::rendering
{
	struct render_stage : public graphics_stage<render_stage, mesh_renderer, core::transform>
	{
		math::mat4 projection = math::perspective(math::radians(45.f), Screen_Width / Screen_Height, .1f, 100.0f);
		math::mat4 view;
		virtual void setup() override
		{
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				renderer.initialize(RI->getHwnd());

				auto& transf = ent.getComponent<core::transform>();
				view = math::lookAt(((math::vec3)transf.position), (((math::vec3)transf.position) + transf.forward()), math::vec3(0.0f,1.0f,0.0f));
				math::mat4 mat = { projection * view * (math::mat4)(transf.localMatrix)};
				buffer_handle buff = renderer.m_model.matrixBuffer;
				buff->bufferData(&mat, 1);
			}
			RI->checkError();
		}

		virtual void render() override
		{
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				auto& transf = ent.getComponent<core::transform>();
				//view = math::lookAt(((math::vec3)transf.position), (((math::vec3)transf.position) + transf.forward()), transf.up());
				//math::mat4 mat = { projection * view * ((math::mat4)transf.localMatrix) };
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