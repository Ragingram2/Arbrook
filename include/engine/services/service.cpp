#include <engine/services/service.hpp>

namespace rythe::core
{
	void Service::initialize()
	{
		std::cout << "Initializing program service" << std::endl;
	}

	void Service::update()
	{
		std::cout << "Program service tick" << std::endl;
	}

	void Service::kill()
	{
		std::cout << "Killing Program service " << std::endl;
	}
}