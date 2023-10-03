#pragma once
#include <memory>
#include <rsl/logging>
#include <rsl/math>

#include "core/ecs/ecs.hpp"
#include "core/systems/system.hpp"
#include "rendering/pipeline/base/graphicsstage.hpp"
#include "rendering/pipeline/base/pipelineprovider.hpp"
#include "rendering/pipeline/base/pipeline.hpp"
#include "rendering/pipeline/defaultpipeline.hpp"
#include "rendering/components/components.hpp"


namespace rythe::rendering
{
	inline void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		core::events::key_input input{ key, scancode, action, mods };
		core::events::EventBus::raiseEvent<core::events::key_input>(input);
	}

	inline void mouse_callback(GLFWwindow* window, double xpos, double ypos)
	{
		core::events::mouse_input input{ xpos, ypos };
		core::events::EventBus::raiseEvent<core::events::mouse_input>(input);
	}

	class Renderer : public core::System<core::transform, camera>
	{
	public:
		static std::unique_ptr<pipeline_provider_base> m_provider;
		static PipelineBase* m_pipeline;
		RenderInterface* RI;

		Renderer() : System<core::transform, camera>()
		{
			setPipeline<DefaultPipeline>();
		}
		virtual ~Renderer() = default;

		void setup()
		{
			log::info("Initializing Render Pipeline");
			if (!glfwInit())
				return;

			m_pipeline = m_provider->get(0);
			RI = &m_pipeline->RI;

			if (!RI->getWindow())
			{
				glfwTerminate();
				log::error("Window initialization failed");
				return;
			}

			glfwSetKeyCallback(RI->getWindow(), key_callback);
			glfwSetCursorPosCallback(RI->getWindow(), mouse_callback);
			glfwSetInputMode(RI->getWindow(), GLFW_CURSOR, GLFW_CURSOR);
		}

		void update()
		{
			if (RI->shouldWindowClose())
			{
				rythe::core::events::exit evnt(0);
				raiseEvent(evnt);
				return;
			}

			auto& camEnt = getCameraEntity();
			auto& transf = camEnt.getComponent<core::transform>();
			auto& cam = camEnt.getComponent<camera>();
			cam.calculate_projection();
			m_pipeline->render(transf, getCamera());

			RI->pollEvents();
		}

		void shutdown()
		{
			m_pipeline->shutdown();
		}

		core::ecs::entity& getCameraEntity()
		{
			return m_filter[0];
		}

		camera& getCamera()
		{
			return m_filter[0].getComponent<camera>();
		}

		template<typename Type>
		static void setPipeline()
		{
			m_provider = std::make_unique<pipeline_provider<Type>>();
		}

		static PipelineBase* getCurrentPipeline()
		{
			return m_pipeline;
		}
	};

}