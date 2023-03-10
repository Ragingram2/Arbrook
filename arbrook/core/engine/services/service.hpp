#pragma once
#include <memory>
#include <iostream>

#include "core/platform/platform.hpp"

namespace rythe::core
{
	class Service
	{
	public:
		bool m_running = true;
	public:
		Service() = default;
		MOVE_FUNCS(Service)
		virtual ~Service() = default;

		virtual void initialize() RYTHE_PURE;
		virtual void update() RYTHE_PURE;
		virtual void shutdown() RYTHE_PURE;
	};
}