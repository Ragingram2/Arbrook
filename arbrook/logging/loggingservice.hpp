#pragma once
#include "engine/services/service.hpp"
#include "logging/logging.hpp"

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