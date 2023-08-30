#pragma once
#include <rsl/utilities>
#include <rsl/math>

#include "core/components/transform.hpp"
#include "rendering/interface/definitions.hpp"
#include "rendering/components/camera.hpp"
#include "rendering/pipeline/base/pipelinebase.hpp"

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
		virtual void setup(core::transform camTransf, camera& cam) RYTHE_PURE;
		virtual void shutdown_impl() RYTHE_PURE;
	public:
		virtual ~graphics_stage_base() = default;
		virtual void render(core::transform camTransf, camera& cam) RYTHE_PURE;
		virtual rsl::priority_type priority() RYTHE_IMPURE_RETURN(0);

		bool isInitialized() { return m_initialized; }
		void init(core::transform camTransf, camera& cam)
		{
			m_initialized = true;
			setup(camTransf, cam);
		}
	};
}