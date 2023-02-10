#pragma once
#include <SFML/Graphics.hpp>

#include "logging/logging.hpp"
#include "modules/module.hpp"
#include "engine/program.hpp"
#include "events/eventbus.hpp"
#include "events/defaults/exit_event.hpp"

namespace rythe::window
{
	class WindowModule : public core::Module
	{
	public:
		sf::RenderWindow window;

		void setup() override;
		void update() override;
		void shutdown() override;
	};
}