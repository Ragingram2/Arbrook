#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/program.hpp"
#include "logging/loggingservice.hpp"
#include "events/eventbus.hpp"
#include "events/defaults/exit_event.hpp"
#include "scheduler/scheduler.hpp"
#include "modules/testmodule.hpp"
#include "modules/windowmodule.hpp"

using namespace rythe::core;
//namespace rendering = rythe::rendering;
namespace window = rythe::window;
namespace events = rythe::core::events;

int main()
{
	//Setting up service registry and program
	ServiceRegistry registry;
	Program program(registry);

	//Register services
	registry.register_service<LoggingService>();
	registry.register_service<events::EventBus>();
	registry.register_service<scheduling::Scheduler>();

	//Register events
	registry.get_service<events::EventBus>()->bind<events::exit,Program,&Program::exit>();

	//Report modules
	scheduling::Scheduler* scheduler = registry.get_service<scheduling::Scheduler>();
	scheduler->reportModule<window::WindowModule>();

	//Initialize engine
	Program::Instance().initialize();

	//Update loop
	while (Program::Instance().m_running)
	{
		Program::Instance().update();
	}

	return 0;
}


