#pragma once
#include "core/core.hpp"
#include "graphics/rendering.hpp"
#include "input/input.hpp"
#include "../../components/camerasettings.hpp"

namespace rythe::game
{
	using namespace rythe::core::events;
	namespace fs = std::filesystem;
	namespace ast = rythe::core::assets;

	class CameraControls : public core::System<CameraControls, core::transform, gfx::camera, camera_settings>
	{
	public:
		core::ecs::entity camera;

	private:
		math::vec2 mousePos;
		math::vec2 lastMousePos;
		math::vec2 mouseDelta;
		math::vec2 rotationDelta;

		float yaw = 0;
		float pitch = 0;

	public:
		void setup();
		void update();

		void mouselook(mouse_input& input);
		void move(moveInput& input);

		void orbit(core::ecs::entity& ent, mouse_input& input);
		void freeLook(core::ecs::entity& ent, mouse_input& input);

		core::ecs::entity& getCameraEntity()
		{
			return camera;
		}

		gfx::camera& getCamera()
		{
			return camera.getComponent<gfx::camera>();
		}
	};
}