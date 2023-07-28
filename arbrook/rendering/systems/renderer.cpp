#include "rendering/systems/renderer.hpp"

namespace rythe::rendering
{
	std::unique_ptr<pipeline_provider_base> Renderer::m_provider;
	PipelineBase* Renderer::m_pipeline;
}