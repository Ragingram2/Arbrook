#include "modules/testmodule.hpp"

namespace rythe::core
{
	void TestModule::setup()
	{
		log::debug("Initialized Test Module");
		reportSystem<TestSystem>();
		//reportSystem<FlipSystem>();
	}
}