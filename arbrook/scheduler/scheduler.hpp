#pragma once
#include <unordered_map>
#include <memory>

#include <rythe/delegate>
#include <rythe/primitives>
#include <rythe/hash>

#include "engine/services/service.hpp"
#include "logging/logging.hpp"
#include "modules/module.hpp"

namespace rythe::core::scheduling
{
	class Scheduler : public Service
	{
	private:
		rsl::multicast_delegate<void()> m_initFuncs;
		rsl::multicast_delegate<void()> m_updateFuncs;
		rsl::multicast_delegate<void()> m_shutdownFuncs;

		std::unordered_map<rsl::id_type, std::unique_ptr<Module>> m_modules;

	public:
		Scheduler() = default;
		virtual ~Scheduler() = default;

		void initialize() override;
		void update() override;
		void shutdown() override;

		template<typename moduleType>
		void reportModule();
	};
}

#include "scheduler.inl"