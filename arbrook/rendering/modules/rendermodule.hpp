#pragma once
#include "core/modules/module.hpp"
#include "core/logging/logging.hpp"

#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	namespace log = core::log;

	class RenderModule : public core::Module
	{
	public:
		void setup() override;
	};
}