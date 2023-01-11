#pragma once
#include "platform/platform.hpp"

namespace rythe::core
{
	class Module
	{
	public:
		Module() = default;
		virtual ~Module() = default;

		virtual void initialize() RYTHE_PURE;
		virtual void update() RYTHE_PURE;
		virtual void shutdown() RYTHE_PURE;
	};
}