#include "modules/testmodule.hpp"
#include "systems/testsystem.hpp"

namespace rythe::core
{
	void TestModule::initialize()
	{
		log::debug("Initialized Test Module");
		reportSystem<TestSystem>();

		Module::initialize();
	}
}