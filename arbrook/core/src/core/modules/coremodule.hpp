#pragma once
#include "core/modules/module.hpp"
#include "core/logging/logging.hpp"

namespace rythe::rendering
{
	class CoreModule : public core::Module
	{
	public:
		void setup()
		{
			log::debug("Initializing Core Module");
		}
	};
}