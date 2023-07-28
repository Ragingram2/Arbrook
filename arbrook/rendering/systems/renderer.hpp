#pragma once
#include <memory>

#include "core/systems/system.hpp"
#include "rendering/pipeline/renderstage.hpp"
#include "rendering/pipeline/pipelineprovider.hpp"
#include "rendering/pipeline/pipeline.hpp"
#include "rendering/components/mesh_renderer.hpp"


namespace rythe::rendering
{
	namespace log = core::log;
	namespace math = core::math;

	class Renderer : public core::System<mesh_renderer>
	{
	public:
		static std::unique_ptr<pipeline_provider_base> m_provider;
		static PipelineBase* m_pipeline;
		RenderInterface* RI;

		Renderer() : System<mesh_renderer>()
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
		}

		void update()
		{
			if (RI->shouldWindowClose())
			{
				rythe::core::events::exit evnt(0);
				raiseEvent(evnt);
				return;
			}

			m_pipeline->render();

			RI->pollEvents();
		}

		void shutdown()
		{
			m_pipeline->shutdown();
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