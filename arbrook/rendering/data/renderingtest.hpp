#pragma once
#include <rythe/delegate>

#include "core/ecs/ecs.hpp"
#include "rendering/data/definitions.hpp"

namespace rythe::rendering
{
	using function_delegate = rsl::delegate<void(inputlayout*, RenderInterface*)>;
	using function_ptr = void(*)(inputlayout*, RenderInterface*);
	struct rendering_test
	{
	private:
		function_delegate m_setupFunc;
		function_delegate m_updateFunc;
		function_delegate m_destroyFunc;
		inputlayout layout;

	public:
		rendering_test() = default;
		rendering_test(function_ptr setup, function_ptr update, function_ptr destroy)
		{
			m_setupFunc = setup;
			m_updateFunc = update;
			m_destroyFunc = destroy;
		}

		void setup(RenderInterface* api)
		{
			m_setupFunc(&layout,api);
		}

		void update(RenderInterface* api)
		{
			m_updateFunc(&layout,api);
		}

		void destroy(RenderInterface* api)
		{
			m_destroyFunc(&layout,api);
		}
	};
}