#pragma once
#include "core/modules/module.hpp"
#include "core/logging/logging.hpp"

#include "rendering/systems/rendertestsystem.hpp"
#include "rendering/systems/renderpipeline.hpp"

namespace rythe::rendering
{
	namespace log = core::log;

	class RenderModule : public core::Module
	{
	public:
		void setup() override;
	};
}