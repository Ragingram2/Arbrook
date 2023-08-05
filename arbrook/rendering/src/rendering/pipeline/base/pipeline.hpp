#pragma once
#include <unordered_map>
#include <map>
#include <memory>
#include <concepts>

#include <rsl/utilities>

#include "rendering/interface/definitions.hpp"
#include "rendering/pipeline/base/pipelinebase.hpp"
#include "rendering/pipeline/base/graphicsstage.hpp"



namespace rythe::rendering
{
	class Renderer;

	template<typename Self>
	class Pipeline : public PipelineBase
	{
		friend class Renderer;
		friend struct graphics_stage_base;
	private:
		virtual void setup() RYTHE_PURE;
	protected:
		static std::map<rsl::priority_type, std::unique_ptr<graphics_stage_base>> m_stages;

	public:
		virtual ~Pipeline() = default;

		void init() override
		{
			setup();
			for (auto& [_, stage] : m_stages)
			{
				stage->RI = &RI;
				stage->pipeline = this;
			}
		}

		void render() override
		{
			m_abort = false;
			RI.makeCurrent();
			for (auto& [_, stage] : m_stages)
			{
				if (!stage->isInitialized())
				{
					stage->init();
				}

				stage->render();

				if (m_abort)
					break;
			}
			RI.swapBuffers();
		}

		template<typename Type>
		static void attachStage()
		{
			auto ptr = new Type();
			m_stages.emplace(ptr->priority(), std::unique_ptr<graphics_stage_base>(ptr));
		}

		static void attachStage(std::unique_ptr<graphics_stage_base>&& stage)
		{
			m_stages.emplace(stage->priority(), std::forward<std::unique_ptr<graphics_stage_base>&&>(stage));
		}
	};

	template<typename Self>
	std::map<rsl::priority_type, std::unique_ptr<graphics_stage_base>> Pipeline<Self>::m_stages;
}