#include "rendering/systems/rendersystem.hpp"

namespace rythe::rendering
{
	void Renderer::setup()
	{
		log::info("Initializing Render System");
		if (!glfwInit())
			return;

		m_window.initialize(math::ivec2(600, 600), "Arbrook");

		if (!m_window)
		{
			glfwTerminate();
			log::error("Window initialization failed");
			return;
		}

		window::makeCurrent();

		m_renderApi.initialize(m_window);
	}

	void Renderer::update()
	{
		window::makeCurrent();

		m_window.setSwapInterval(1);

		if (m_window.shouldClose())
		{
			rythe::core::events::exit evnt(0);
			raiseEvent(evnt);
			return;
		}

		m_renderApi.clear(GL_COLOR_BUFFER_BIT);
		m_renderApi.setClearColor(math::vec4(0.0));

		for (auto& ent : m_filter)
		{
			auto& renderComp = ent.getComponent<sprite_renderer>();
			auto& transf = ent.getComponent<core::transform>();
			auto& example = ent.getComponent<core::exampleComp>();

			auto& shader = renderComp.m_shader;
			auto& texture = renderComp.m_texture;
			m_renderApi.bind(shader);
			m_renderApi.bind(texture);
			renderComp.vao->bind();

			m_renderApi.setUniform(shader, "u_position", transf.position);
			m_renderApi.setUniform(shader, "u_time", example.time);

			m_renderApi.drawIndexed(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

			renderComp.vao->unbind();
		}

		m_window.swapBuffers();
		m_window.pollEvents();
	}

	void Renderer::shutdown()
	{
		glfwTerminate();
	}

	void Renderer::debugCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userparam)
	{
		if (id == 131185) // Filter out annoying Nvidia message of: Buffer you made will use VRAM because you told us that you want it to allocate VRAM.
			return;

		rsl::cstring s;
		switch (source)
		{
		case GL_DEBUG_SOURCE_API:
			s = "OpenGL";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER:
			s = "Shader compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY:
			s = "Third party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION:
			s = "Application";
			break;
		case GL_DEBUG_SOURCE_OTHER:
			s = "Other";
			break;
		default:
			s = "Unknown";
			break;
		}

		rsl::cstring t;

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR:
			t = "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
			t = "Deprecation";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
			t = "Undefined behavior";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE:
			t = "Performance";
			break;
		case GL_DEBUG_TYPE_PORTABILITY:
			t = "Portability";
			break;
		case GL_DEBUG_TYPE_MARKER:
			t = "Marker";
			break;
		case GL_DEBUG_TYPE_PUSH_GROUP:
			t = "Push";
			break;
		case GL_DEBUG_TYPE_POP_GROUP:
			t = "Pop";
			break;
		case GL_DEBUG_TYPE_OTHER:
			t = "Misc";
			break;
		default:
			t = "Unknown";
			break;
		}

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH:
			log::error("[{}-{}] {}: {}", s, t, id, message);
			__debugbreak();
			break;
		case GL_DEBUG_SEVERITY_MEDIUM:
			log::warn("[{}-{}] {}: {}", s, t, id, message);
			break;
		case GL_DEBUG_SEVERITY_LOW:
			log::debug("[{}-{}] {}: {}", s, t, id, message);
			break;
		case GL_DEBUG_SEVERITY_NOTIFICATION:
			log::debug("[{}-{}] {}: {}", s, t, id, message);
			break;
		default:
			log::debug("[{}-{}] {}: {}", s, t, id, message);
			break;
		}
	}

	void Renderer::debugCallbackARB(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userparam)
	{
		rsl::cstring s;
		switch (source)
		{
		case GL_DEBUG_SOURCE_API_ARB:
			s = "OpenGL";
			break;
		case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
			s = "Window system";
			break;
		case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
			s = "Shader compiler";
			break;
		case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
			s = "Third party";
			break;
		case GL_DEBUG_SOURCE_APPLICATION_ARB:
			s = "Application";
			break;
		case GL_DEBUG_SOURCE_OTHER_ARB:
			s = "Other";
			break;
		default:
			s = "Unknown";
			break;
		}

		rsl::cstring t;

		switch (type)
		{
		case GL_DEBUG_TYPE_ERROR_ARB:
			t = "Error";
			break;
		case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
			t = "Deprecation";
			break;
		case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
			t = "Undefined behavior";
			break;
		case GL_DEBUG_TYPE_PERFORMANCE_ARB:
			t = "Performance";
			break;
		case GL_DEBUG_TYPE_PORTABILITY_ARB:
			t = "Portability";
			break;
		case GL_DEBUG_TYPE_OTHER_ARB:
			t = "Misc";
			break;
		default:
			t = "Unknown";
			break;
		}

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH_ARB:
			log::error("[{}-{}] {}: {}", s, t, id, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM_ARB:
			log::warn("[{}-{}] {}: {}", s, t, id, message);
			break;
		case GL_DEBUG_SEVERITY_LOW_ARB:
			log::debug("[{}-{}] {}: {}", s, t, id, message);
			break;
		default:
			log::debug("[{}-{}] {}: {}", s, t, id, message);
			break;
		}
	}

	void Renderer::debugCallbackAMD(unsigned int id, unsigned int category, unsigned int severity, int length, const char* message, void* userparam)
	{
		rsl::cstring c;
		switch (category)
		{
		case GL_DEBUG_CATEGORY_API_ERROR_AMD:
			c = "OpenGL";
			break;
		case GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD:
			c = "Window system";
			break;
		case GL_DEBUG_CATEGORY_DEPRECATION_AMD:
			c = "Deprecation";
			break;
		case GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD:
			c = "Undefined behavior";
			break;
		case GL_DEBUG_CATEGORY_PERFORMANCE_AMD:
			c = "Performance";
			break;
		case GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD:
			c = "Shader compiler";
			break;
		case GL_DEBUG_CATEGORY_APPLICATION_AMD:
			c = "Application";
			break;
		case GL_DEBUG_CATEGORY_OTHER_AMD:
			c = "Other";
			break;
		default:
			c = "Unknown";
			break;
		}

		switch (severity)
		{
		case GL_DEBUG_SEVERITY_HIGH_AMD:
			log::error("[{}] {}: {}", c, id, message);
			break;
		case GL_DEBUG_SEVERITY_MEDIUM_AMD:
			log::warn("[{}] {}: {}", c, id, message);
			break;
		case GL_DEBUG_SEVERITY_LOW_AMD:
			log::debug("[{}] {}: {}", c, id, message);
			break;
		default:
			log::debug("[{}] {}: {}", c, id, message);
			break;
		}
	}
}