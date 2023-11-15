#pragma once
#include <rsl/primitives>
#include <rsl/utilities>
#include <rsl/math>

#include "core/logging/logging.hpp"
#include "core/components/transform.hpp"
#include "rendering/cache/cache.hpp"
#include "rendering/interface/definitions/definitions.hpp"
#include "rendering/pipeline/base/graphicsstage.hpp"
#include "rendering/components/components.hpp"

namespace rythe::rendering
{
	using renderFunc = void(core::transform, camera);
	struct render_stage : public graphics_stage<render_stage, mesh_renderer, core::transform>
	{
	private:
		static rsl::multicast_delegate<renderFunc> m_onRender;
	public:
		virtual void setup(core::transform camTransf, camera& cam) override
		{
			cam.calculate_view(&camTransf);
			cam.calculate_projection();
			camData mat = { cam.projection, cam.view, math::mat4(1.0f) };
			RI->depthTest(true);
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				auto& transf = ent.getComponent<core::transform>();
				mat.model = transf.to_world();
				renderer.model->initialize(renderer.material->shader, renderer.model->meshHandle, renderer.instanced);
				renderer.dirty = false;
				renderer.model->cameraBuffer->bufferData(&mat, 1);
			}
			RI->checkError();
		}

		virtual void render(core::transform camTransf, camera& cam) override
		{
			cam.calculate_view(&camTransf);
			camData mat = { cam.projection, cam.view, math::mat4(1.0f) };
			for (auto& ent : m_filter)
			{
				auto& renderer = ent.getComponent<mesh_renderer>();
				if (renderer.dirty)
				{
					renderer.model->initialize(renderer.material->shader, renderer.model->meshHandle, renderer.instanced);
					renderer.dirty = false;
				}
				auto& transf = ent.getComponent<core::transform>();
				mat.model = transf.to_world();
				renderer.model->cameraBuffer->bufferData(&mat, 1);
				renderer.material->bind();
				renderer.model->bind();
				if (renderer.model->indexBuffer != nullptr)
					RI->drawIndexed(PrimitiveType::TRIANGLESLIST, renderer.model->meshHandle->indices.size(), 0, 0);
				else
					RI->drawArrays(PrimitiveType::TRIANGLESLIST, 0, renderer.model->meshHandle->vertices.size());
			}
			m_onRender(camTransf, cam);
			//RI->checkError();
		}

		virtual rsl::priority_type priority() override { return OPAQUE_PRIORITY; }

		template <class T, void(T::* Func)(core::transform, camera)>
		static void addRender(T* ptr)
		{
			m_onRender.push_back<T, Func>(*ptr);
		}
	};

	inline rsl::multicast_delegate<renderFunc> render_stage::m_onRender;
}