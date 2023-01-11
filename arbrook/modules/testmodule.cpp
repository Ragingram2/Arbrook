#include "modules/testmodule.hpp"

namespace rythe::core
{
	void TestModule::initialize()
	{
		log::debug("Initialized Test System");
	}

	void TestModule::update()
	{
		//log::debug("Tick");
	}

	void TestModule::shutdown()
	{

	}
}