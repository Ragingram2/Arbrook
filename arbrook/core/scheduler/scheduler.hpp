#pragma once
#include <unordered_map>
#include <memory>

#include <rsl/delegate>
#include <rsl/primitives>
#include <rsl/hash>

#include "core/engine/services/service.hpp"
#include "core/logging/logging.hpp"
#include "core/modules/module.hpp"

namespace rythe::core::scheduling
{
	class Scheduler : public Service
	{
	private:
		rsl::multicast_delegate<void()> m_initFuncs;
		rsl::multicast_delegate<void()> m_updateFuncs;
		rsl::multicast_delegate<void()> m_shutdownFuncs;

		std::unordered_map<rsl::id_type, std::unique_ptr<Module>> m_modules;

		bool m_initialize = false;

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