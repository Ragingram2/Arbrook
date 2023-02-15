#pragma once
#include <SFML/Graphics.hpp>

#include "systems/system.hpp"
#include "engine/program.hpp"
#include "events/eventbus.hpp"
#include "events/defaults/exit_event.hpp"


namespace rythe::rendering
{
	namespace log = core::log;

	class RenderSystem : public core::System<core::transform,core::renderComp>
	{
	public:
		sf::RenderWindow window;

		RenderSystem() = default;
		virtual ~RenderSystem() = default;

		void setup() override;
		void update() override;
		void shutdown() override;
	};
}