#pragma once
#include <SFML/Graphics.hpp>

#include "modules/module.hpp"
#include "systems/rendersystem.hpp"
#include "logging/logging.hpp"

namespace rythe::rendering
{
	namespace log = core::log;

	class RenderModule : public core::Module
	{
	public:
		sf::RenderWindow window;

		void setup() override;
	};
}