#pragma once
#include "core/engine/services/service.hpp"
#include "core/logging/logging.hpp"

namespace rythe::core
{
	class LoggingService : public Service
	{
	public:
		LoggingService() = default;
		MOVE_FUNCS(LoggingService)
		virtual ~LoggingService() = default;

		virtual void initialize() override;
		virtual void update() override;
		virtual void shutdown() override;
	};
}