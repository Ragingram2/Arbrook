#pragma once
#include "graphics/pipeline/base/pipelineprovider.hpp"

namespace rythe::rendering
{
	template<typename PipelineType>
	std::vector<std::unique_ptr<PipelineType>> pipeline_provider<PipelineType>::m_pipelines;
}