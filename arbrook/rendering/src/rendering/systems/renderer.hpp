#pragma once
#include <memory>
#include <rsl/logging>
#include <rsl/math>

#include "core/systems/system.hpp"
#include "rendering/pipeline/base/graphicsstage.hpp"
#include "rendering/pipeline/base/pipelineprovider.hpp"
#include "rendering/pipeline/base/pipeline.hpp"
#include "rendering/pipeline/defaultpipeline.hpp"
#include "rendering/components/components.hpp"


namespace rythe::rendering
{
	class Renderer : public core::System<camera>
	{
	public:
		static std::unique_ptr<pipeline_provider_base> m_provider;
		static PipelineBase* m_pipeline;
		RenderInterface* RI;

		Renderer() : System<camera>()
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