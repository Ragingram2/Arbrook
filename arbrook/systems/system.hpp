#pragma once
#include "platform/platform.hpp"
//#include "containers/delegate.hpp"

namespace rythe::core
{
	class System
	{
	public:
		System() = default;
		virtual ~System() = default;

		virtual void initialize() {};
		virtual void update() {};
		virtual void shutdown() {};
	};
}

#include "systems/system.inl"
