#pragma once
#include "platform/platform.hpp"
#include "containers/delegate.hpp"
#include "systems/system.hpp"

namespace rythe::core
{
	class Module
	{
	private:
		multicast_delegate<void()> m_initFuncs;
		multicast_delegate<void()> m_updateFuncs;
		multicast_delegate<void()> m_shutdownFuncs;

		std::unordered_map<id_type, std::unique_ptr<System>> m_systems;

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