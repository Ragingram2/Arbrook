#include "sandbox/modules/testmodule.hpp"

namespace rythe::core
{
	void TestModule::setup()
	{
		log::info("Initializing Test Module");
		//reportSystem<TestSystem>();
	}
}