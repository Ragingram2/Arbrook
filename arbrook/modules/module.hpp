#pragma once
#include <rythe/delegate>

#include "platform/platform.hpp"
#include "systems/system.hpp"

namespace rythe::core
{
	class Module
	{
	private:
		rsl::multicast_delegate<void()> m_initFuncs;
		rsl::multicast_delegate<void()> m_updateFuncs;
		rsl::multicast_delegate<void()> m_shutdownFuncs;

		std::unordered_map<rsl::id_type, std::unique_ptr<System>> m_systems;

	public:
		Module() = default;
		virtual ~Module() = default;

		virtual void initialize();
		virtual void update();
		virtual void shutdown();

		template<typename systemType>
		void reportSystem();
	};
}

#include "modules/module.inl"