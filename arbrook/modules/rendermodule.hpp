#pragma once
#include "logging/logging.hpp"
#include "modules/module.hpp"
#include <SFML/Graphics.hpp>


namespace rythe::rendering
{
	class RenderModule : public core::Module
	{
	public:
		sf::RenderWindow window;
		void initialize() override;
		void update() override;
		void shutdown() override;
	};
}
