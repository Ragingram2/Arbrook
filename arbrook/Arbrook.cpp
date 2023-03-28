#include <iostream>
#include <SFML/Graphics.hpp>

#include "core/core.hpp"
#include "sandbox/modules/testmodule.hpp"
#include "rendering/modules/rendermodule.hpp"

using namespace rythe::core;

namespace gfx = rythe::rendering;
namespace events = rythe::core::events;

int main()
{
	//Setting up service registry and program
	ServiceRegistry registry;
	Program program(registry);

	//Register services
	registry.register_service<LoggingService>();
	pointer<events::EventBus> eventBus = registry.register_service<events::EventBus>();
	registry.register_service<scheduling::Scheduler>();
	pointer<ecs::Registry> ecsReg = registry.register_service<ecs::Registry>();

	//Register events
	eventBus->bind<events::exit,Program,&Program::exit>(Program::Instance());

	//Report modules
	scheduling::Scheduler* scheduler = registry.get_service<scheduling::Scheduler>();
	scheduler->reportModule<gfx::RenderModule>();
	scheduler->reportModule<TestModule>();


	//Initialize engine
	Program::Instance().initialize();

	//Update loop
	while (Program::Instance().m_running)
	{
		Program::Instance().update();
	}

	return 0;
}


