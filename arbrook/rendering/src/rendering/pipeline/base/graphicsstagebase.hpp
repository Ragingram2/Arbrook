#pragma once
#include <rsl/utilities>

#include "rendering/interface/definitions.hpp"
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
		virtual void setup() RYTHE_PURE;
		virtual void shutdown_impl() RYTHE_PURE;
	public:
		virtual ~graphics_stage_base() = default;
		virtual void render() RYTHE_PURE;
		virtual rsl::priority_type priority() RYTHE_IMPURE_RETURN(0);

		bool isInitialized() { return m_initialized; }
		void init()
		{
			m_initialized = true;
			setup();
		}
	};
}