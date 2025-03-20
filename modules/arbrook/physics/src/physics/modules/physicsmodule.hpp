#pragma once
#include "core/modules/module.hpp"
#include "core/logging/logging.hpp"
#include "physics/systems/physicssystem.hpp"

namespace rythe::physics
{
	class PhysicsModule : public core::Module
	{
	public:
		void setup()
		{
			log::info("Initializing Physics Module");
			reportSystem<PhysicsSystem>();
		}
	};
}