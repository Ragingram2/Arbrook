#include <iostream>
#include <SFML/Graphics.hpp>

#include "engine/program.hpp"
#include "logging/loggingservice.hpp"
#include "scheduler/scheduler.hpp"
#include "modules/testmodule.hpp"
#include "modules/rendermodule.hpp"

using namespace rythe::core;
namespace rendering = rythe::rendering;

int main()
{
	ServiceRegistry registry;
	registry.register_service<LoggingService>();
	scheduling::Scheduler* scheduler = registry.register_service<scheduling::Scheduler>();
	scheduler->reportModule<rendering::RenderModule>();
	scheduler->reportModule<TestModule>();

	Program program(registry);
	program.initialize();

	log::debug("Hello world");

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


