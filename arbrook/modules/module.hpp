#pragma once
#include <rythe/primitives>
#include <rythe/delegate>
#include <rythe/hash>

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

		std::unordered_map<rsl::id_type, std::unique_ptr<SystemBase>> m_systems;

		bool m_initialize = false;

	public:
		Module() = default;
		virtual ~Module() = default;

		void onInitialize();
		void onUpdate();
		void onShutdown();

		virtual void setup() {};
		virtual void update() {};
		virtual void shutdown() {};

		template<typename systemType>
		void reportSystem();
	};
}

#include "modules/module.inl"