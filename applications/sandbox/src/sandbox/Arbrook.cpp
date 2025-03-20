#include <iostream>
#include "core/utils/profiler.hpp"

#include "core/core.hpp"
#include "graphics/modules/rendermodule.hpp"
#include "modules/testmodule.hpp"
#include "input/modules/inputmodule.hpp"
#include "physics/modules/physicsmodule.hpp"


using namespace rythe::core;

namespace gfx = rythe::rendering;
namespace events = rythe::core::events;
namespace input = rythe::input;
namespace physics = rythe::physics;

__declspec(dllexport) DWORD NvOptimusEnablement = 0x0000001;

int main()
{
	//Setting up service registry and program
	ServiceRegistry registry;
	Program program(registry);

	//Register services
	registry.register_service<LoggingService>();
	pointer<events::EventBus> eventBus = registry.register_service<events::EventBus>();
	registry.register_service<scheduling::Scheduler>();
	registry.register_service<ecs::Registry>();

	//Register events
	eventBus->bind<events::exit,Program,&Program::exit>(Program::Instance());

	//Report modules
	scheduling::Scheduler* scheduler = registry.get_service<scheduling::Scheduler>();
	scheduler->reportModule<gfx::RenderModule>();
	scheduler->reportModule<input::InputModule>();
	//scheduler->reportModule<physics::PhysicsModule>();
	scheduler->reportModule<TestModule>();

	//Initialize engine
	Program::Instance().initialize();

	float currentFrame = 0;
	float lastFrame = 0;
	//Update loop
	while (Program::Instance().m_running)
	{
		FrameMark;
		Time::previousDeltaTime = Time::deltaTime;
		currentFrame = glfwGetTime();
		Time::deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		Program::Instance().update();
	}

	return 0;
}


