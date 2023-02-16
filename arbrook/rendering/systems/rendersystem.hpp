#pragma once
#include <SFML/Graphics.hpp>

#include "core/systems/system.hpp"
#include "core/engine/program.hpp"
#include "core/events/eventbus.hpp"
#include "core/events/defaults/exit_event.hpp"


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