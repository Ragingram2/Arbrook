#pragma once
#include <memory>
#include <iostream>

#include "platform/platform.hpp"

namespace rythe::core
{
	class Service
	{
	public:
		Service() = default;
		MOVE_FUNCS(Service)
		virtual ~Service() = default;

		virtual void initialize() RYTHE_PURE;
		virtual void update() RYTHE_PURE;
		virtual void shutdown() RYTHE_PURE;
	};
}