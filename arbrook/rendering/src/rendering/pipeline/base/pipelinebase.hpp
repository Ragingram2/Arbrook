#pragma once
#include <rsl/utilities>
#include <rsl/math>

#include "core/components/transform.hpp"
#include "rendering/interface/definitions.hpp"
#include "rendering/components/camera.hpp"

namespace rythe::rendering
{
	class PipelineBase
	{
	protected:
		bool m_abort = false;
	public:
		RenderInterface RI;//This should be the only real version
		virtual void init() RYTHE_PURE;
		virtual void render(core::transform camTransf, camera& cam) RYTHE_PURE;
		virtual void shutdown() RYTHE_IMPURE

		void abort()
		{
			m_abort = true;
		}
	};
}
