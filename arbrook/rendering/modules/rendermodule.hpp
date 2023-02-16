#pragma once
#include <SFML/Graphics.hpp>

#include "core/modules/module.hpp"
#include "core/logging/logging.hpp"

#include "rendering/systems/rendersystem.hpp"

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