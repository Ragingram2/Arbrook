#pragma once
#include <rsl/logging>

#include "core/modules/module.hpp"

namespace rythe::rendering
{
	namespace log = rsl::log;
	class CoreModule : public core::Module
	{
	public:
		void setup()
		{
			log::debug("Initializing Core Module");
		}
	};
}