#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	void Renderer::setup()
	{
		log::info("Initializing Render System");
		if (!glfwInit())
			return;

		api.initialize(math::ivec2(600, 600), "Arbrook");

		if (!api.getWindow())
		{
			glfwTerminate();
			log::error("Window initialization failed");
			return;
		}
	}

	void Renderer::update()
	{
		api.makeCurrent();

		api.setSwapInterval(1);

		if (api.shouldWindowClose())
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		api.clear(GL_COLOR_BUFFER_BIT);
		api.setClearColor(0x64 / 255.0f, 0x95 / 255.0f, 0xED / 255.0f, 1.0f);

		for (auto& ent : m_filter)
		{
			auto& renderComp = ent.getComponent<sprite_renderer>();
			auto& transf = ent.getComponent<core::transform>();
			auto& example = ent.getComponent<core::exampleComp>();

			auto& shader = renderComp.m_shader;
			auto& texture = renderComp.m_texture;
			api.bind(shader);
			api.bind(texture);
			renderComp.vao.bind(api.getHwnd());

			shader->setUniform("u_position", transf.position);
			shader->setUniform("u_time", example.time);

			api.drawIndexed(PrimitiveType::TRIANGLESLIST, 6, DataType::UINT, nullptr);

			renderComp.vao.unbind();
		}

		api.swapBuffers();
		api.pollEvents();

		api.checkError();
	}

	void Renderer::shutdown()
	{
		glfwTerminate();
		api.close();
	}
}