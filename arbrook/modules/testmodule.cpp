#include "modules/testmodule.hpp"

namespace rythe::core
{
	void TestModule::setup()
	{
		log::debug("Initialized Test Module");
		reportSystem<TestSystem>();
	}

	//void TestModule::update()
	//{
	//	Module::update();
	//}

	//void TestModule::shutdown()
	//{
	//	log::debug("Shutdown Test Module");

	//	Module::shutdown();
	//}
}