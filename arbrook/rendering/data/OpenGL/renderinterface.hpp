#pragma once
#include <memory>
#include <string>
#include <fstream>

#include <GL/glew.h>

#include "core/math/math.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/config.hpp"

#include Window_HPP_PATH
#include Shader_HPP_PATH
#include Buffer_HPP_PATH
#include Texture_HPP_PATH

//#include <stb/stb_image.h>
//#define STB_IMAGE_IMPLEMENTATION

namespace rythe::rendering::internal
{
	class RenderInterface
	{
	private:
		window hwnd;
	public:
		void initialize(math::ivec2 res, const std::string& name, GLFWwindow* window = nullptr)
		{
			log::debug("Initializing OpenGL");
			hwnd.initialize(res, name, window);
			hwnd.makeCurrent();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			if (glewInit() != GLEW_OK)
			{
				log::error("Something went wrong when initializing GLEW");
				return;
			}

#ifdef _DEBUG
			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

			if (GLEW_AMD_debug_output)
				glDebugMessageCallbackAMD(&RenderInterface::debugCallbackAMD, nullptr);
			else if (GLEW_KHR_debug)
				glDebugMessageCallback(&RenderInterface::debugCallback, nullptr);
			else if (GLEW_ARB_debug_output)
				glDebugMessageCallbackARB(&RenderInterface::debugCallbackARB, nullptr);
#endif
		}

		void close()
		{

		}

		GLFWwindow* getWindow()
		{
			return hwnd.getWindow();
		}

		window& getHwnd()
		{
			return hwnd;
		}

		void makeCurrent()
		{
			hwnd.makeCurrent();
		}

		void setSwapInterval(int interval)
		{
			hwnd.setSwapInterval(interval);
		}

		bool shouldWindowClose()
		{
			return hwnd.shouldClose();
		}

		void pollEvents()
		{
			hwnd.pollEvents();
		}

		void swapBuffers()
		{
			glfwSwapBuffers(hwnd.getWindow());
		}

		void drawArrays(PrimitiveType mode, unsigned int startVertex, unsigned int vertexCount)
		{
			glDrawArrays(static_cast<GLenum>(mode), startVertex, vertexCount);
		}

		void drawArraysInstanced(PrimitiveType mode, unsigned int vertexCount, unsigned int instanceCount, unsigned int startVertex, unsigned int startInstance)
		{
			glDrawArraysInstanced(static_cast<GLenum>(mode), startVertex, vertexCount, instanceCount);
		}

		void drawIndexed(PrimitiveType mode, unsigned int indexCount, unsigned int startIndex, unsigned int baseVertex)
		{
			glDrawElements(static_cast<GLenum>(mode), indexCount, static_cast<GLenum>(DataType::UINT), reinterpret_cast<void*>(startIndex));
		}

		void drawIndexedInstanced(PrimitiveType mode, unsigned int indexCount, unsigned int instanceCount, unsigned int startIndex, unsigned int baseVertex, unsigned int startInstance)
		{
			glDrawElementsInstanced(static_cast<GLenum>(mode), indexCount, static_cast<GLenum>(DataType::UINT), reinterpret_cast<void*>(startIndex), instanceCount);
		}

		void clear(internal::ClearBit flags)
		{
			glClear(static_cast<int>(flags));
		}

		void setClearColor(math::vec4 color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void setViewport(float numViewPorts = 1, float topLeftX = 0, float topLeftY = 0, float width = 0, float height = 0, float minDepth = 0, float maxDepth = 1)
		{
			if (width == 0 && height == 0)
			{
				width = hwnd.m_resolution.x;
				height = hwnd.m_resolution.y;
			}

			glViewport(topLeftX, topLeftY, width, height);
			glDepthRange(minDepth, maxDepth);

		}

		void depthTest(bool enable)
		{
			glEnable(enable);
		}

		void depthWrite(bool enable)
		{
			glDepthMask(enable);
		}

		void setStencilMask(int mask)
		{
			glStencilMask(mask);
		}

		void setDepthFunction(internal::DepthFuncs function)
		{
			glDepthFunc(static_cast<GLenum>(function));
		}

		void enableStencilTest()
		{
			glEnable(GL_STENCIL_TEST);
		}

		void disableStencilTest()
		{
			glDisable(GL_STENCIL_TEST);
		}

		void setStencilOp(Face face, StencilOp fail, StencilOp  zfail, StencilOp  zpass)
		{
			glStencilOpSeparate(static_cast<GLenum>(face), static_cast<GLenum>(fail), static_cast<GLenum>(zfail), static_cast<GLenum>(zpass));
		}

		void setStencilFunction(Face face, DepthFuncs func, unsigned int ref, unsigned int mask)
		{
			//The function definition is wrong here
			glStencilFuncSeparate(static_cast<GLenum>(face), static_cast<GLenum>(func), ref, mask);
		}

		void updateDepthStencil()
		{

		}

		//createVAO();

		void createShader(shader* shader, const std::string& name, const shader_source& source)
		{
			shader->initialize(name, source);
		}

		void createTexture2D(texture* texture, const std::string& name, const std::string& filepath, texture_parameters params = { rendering::WrapMode::REPEAT ,rendering::WrapMode::REPEAT, rendering::FilterMode::LINEAR, rendering::FormatType::RGBA8UN, 1 }, bool generateMipMaps = false)
		{
			texture->name = name;
			texture->initialize(TargetType::TEXTURE2D, params, generateMipMaps);
			texture->loadData(filepath);
		}
		////std::unique_ptr<texture1D> createTexture1D(const std::string& filepath);
		////std::unique_ptr<texture3D> createTexture3D(const std::string& filepath);
		template<typename elementType>
		void createBuffer(buffer* buffer, TargetType target, UsageType usage, elementType* data = nullptr, int size = 1)
		{
			buffer->initialize<elementType>(target, usage, size * sizeof(elementType));
			if (data)
			{
				buffer->bufferData<elementType>(data, size);
			}
		}

		void checkError()
		{

		}

	private:
		static void debugCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int  severity, int length, const char* message, const void* userparam);
		static void debugCallbackARB(unsigned int source, unsigned int type, unsigned int id, unsigned int  severity, int length, const char* message, const void* userparam);
		static void debugCallbackAMD(unsigned int id, unsigned int category, unsigned int  severity, int length, const char* message, void* userparam);
	};

	inline void RenderInterface::debugCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userparam)
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
	inline void RenderInterface::debugCallbackARB(unsigned int source, unsigned int type, unsigned int id, unsigned int severity, int length, const char* message, const void* userparam)
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
	inline void RenderInterface::debugCallbackAMD(unsigned int id, unsigned int category, unsigned int severity, int length, const char* message, void* userparam)
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