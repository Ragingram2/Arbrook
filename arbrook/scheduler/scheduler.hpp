#pragma once
#include <unordered_map>
#include <memory>

#include "engine/services/service.hpp"
#include "types/types.hpp"
#include "modules/module.hpp"
#include "containers/delegate.hpp"

namespace rythe::core::scheduling
{
	class Scheduler : public Service
	{
	private:
		multicast_delegate<void()> m_initFuncs;
		multicast_delegate<void()> m_updateFuncs;

		std::unordered_map<id_type, std::unique_ptr<Module>> m_modules;

	public:
		Scheduler() = default;
		virtual ~Scheduler() = default;

		void initialize() override;
		void update() override;
		void kill() override;

		template<typename moduleType>
		void reportModule();
	};
}

#include "scheduler.inl"