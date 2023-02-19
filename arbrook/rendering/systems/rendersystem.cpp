#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	void Renderer::setup()
	{
		core::log::debug("Render System setup");
		if (!glfwInit())
			return;

		window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			core::log::error("Window Failed Initialization");
			return;
		}
	}

	void Renderer::update()
	{
		glfwMakeContextCurrent(window);

		if (glfwWindowShouldClose(window))
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glBegin(GL_TRIANGLES);
		glVertex2f(-0.5f, -0.5f);
		glVertex2f(0.0f, 0.5f);
		glVertex2f(0.5f, -0.5f);
		glEnd();

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	void Renderer::shutdown()
	{
		glfwTerminate();
	}
}