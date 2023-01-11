#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/program.hpp"
#include "logging/loggingservice.hpp"
#include "events/eventbus.hpp"
#include "events/defaults/exit_event.hpp"
#include "scheduler/scheduler.hpp"
#include "modules/testmodule.hpp"
#include "modules/rendermodule.hpp"

using namespace rythe::core;
namespace rendering = rythe::rendering;
namespace events = rythe::core::events;



int main()
{
	ServiceRegistry registry;
	registry.register_service<LoggingService>();
	registry.register_service<events::EventBus>();
	scheduling::Scheduler* scheduler = registry.register_service<scheduling::Scheduler>();
	scheduler->reportModule<rendering::RenderModule>();

	Program program(registry);
	registry.get_service<events::EventBus>()->bindToEvent(events::exit::id, &Program::exit);
	program.initialize();

	while (program.m_running)
	{
		program.update();
	}

	//sf::Event event;
	//while (window.pollEvent(event))
	//{
	//	if (event.type == sf::Event::Closed)
	//	{
	//		program.kill();
	//		window.close();
	//	}
	//}

	//window.clear();
	//window.display();

	return 0;
}


