#pragma once
#include <rsl/utilities>

#include "rendering/data/definitions.hpp"

namespace rythe::rendering
{
	class PipelineBase
	{
	protected:
		bool m_abort = false;
	public:
		RenderInterface RI;//This should be the only real version
		virtual void init() RYTHE_PURE;
		virtual void render() RYTHE_PURE;
		virtual void shutdown() RYTHE_IMPURE

		void abort()
		{
			m_abort = true;
		}
	};
}
