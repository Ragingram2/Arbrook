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

#include <stb/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION

namespace rythe::rendering::internal
{
	class RenderInterface
	{
	private:
		window hwnd;
	public:
		void initialize(math::ivec2 res, const std::string& name)
		{
			log::debug("Initializing OpenGL");
			hwnd.initialize(res, name);
			hwnd.makeCurrent();

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			if (glewInit() != GLEW_OK)
			{
				log::error("Something went wrong when initializing GLEW");
				return;
			}

			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

			if (GLEW_AMD_debug_output)
				glDebugMessageCallbackAMD(&RenderInterface::debugCallbackAMD, nullptr);
			else if (GLEW_KHR_debug)
				glDebugMessageCallback(&RenderInterface::debugCallback, nullptr);
			else if (GLEW_ARB_debug_output)
				glDebugMessageCallbackARB(&RenderInterface::debugCallbackARB, nullptr);
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

		void drawIndexdInstanced(PrimitiveType mode, unsigned int indexCount, unsigned int instanceCount, unsigned int startIndex, unsigned int baseVertex, unsigned int startInstance)
		{
			glDrawElementsInstanced(static_cast<GLenum>(mode), indexCount, static_cast<GLenum>(DataType::UINT), reinterpret_cast<void*>(startIndex), instanceCount);
		}

		void bind(shader* shader)
		{
			glUseProgram(shader->m_programId);
			activeShader = shader;
		}

		void bind(texture_handle handle)
		{
			//glActiveTexture
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindTexture(GL_TEXTURE_2D, handle);
		}

		void unbind(shader* shader)
		{
			//Destructor for shader?
			glUseProgram(0);
			//glDeleteProgram(shader->m_programId);
		}

		void unbind(texture_handle handle)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void clear(int flags)
		{
			glClear(flags);
		}

		void setClearColor(math::vec4 color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
		}

		void enableStencil()
		{
			glEnable(GL_STENCIL_TEST);
		}

		void disableStencil()
		{
			glDisable(GL_STENCIL_TEST);
		}

		void setClearStencil()
		{

		}

		void setStencilOp(unsigned int fail, unsigned int zfail, unsigned int zpass)
		{
			glStencilOp(fail, zfail, zpass);
		}

		void setStencilFunc(unsigned int func, int ref, unsigned int mask)
		{
			glStencilFunc(func, ref, mask);
		}

		//createVAO();

		void createShader(shader* shader, const std::string& name, const shader_source& source)
		{
			shader->initialize(name, source);
		}

		//move file handling elsewhere, specify default Texture params
		texture_handle createTexture2D(texture* texture, const std::string& name, const std::string& filepath, texture_parameters params = { rendering::WrapMode::REPEAT ,rendering::WrapMode::REPEAT,rendering::FilterMode::LINEAR_MIPMAP_LINEAR, rendering::FilterMode::LINEAR })
		{
			texture->m_name = name;
			auto& resolution = texture->m_params.m_resolution;
			auto& channels = texture->m_params.m_channels;
			unsigned int& id = texture->m_id;
			glGenTextures(1, &id);
			glBindTexture(static_cast<GLenum>(TargetType::TEXTURE2D), id);

			glTexParameteri(static_cast<GLenum>(TargetType::TEXTURE2D), GL_TEXTURE_WRAP_S, static_cast<GLint>(params.m_wrapModeS));
			glTexParameteri(static_cast<GLenum>(TargetType::TEXTURE2D), GL_TEXTURE_WRAP_T, static_cast<GLint>(params.m_wrapModeT));
			glTexParameteri(static_cast<GLenum>(TargetType::TEXTURE2D), GL_TEXTURE_MIN_FILTER, static_cast<GLint>(params.m_minFilterMode));
			glTexParameteri(static_cast<GLenum>(TargetType::TEXTURE2D), GL_TEXTURE_MAG_FILTER, static_cast<GLint>(params.m_magFilterMode));
			stbi_set_flip_vertically_on_load(true);

			texture->m_data = stbi_load(filepath.c_str(), &resolution.x, &resolution.y, &channels, 0);
			if (!texture->m_data)
			{
				log::error("Image failed to load");
				return nullptr;
			}

			//make some enums for the data formats
			switch (channels)
			{
			case 4:
				glTexImage2D(static_cast<GLenum>(TargetType::TEXTURE2D), 0, GL_RGBA, resolution.x, resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->m_data);
				break;
			case 3:
				glTexImage2D(static_cast<GLenum>(TargetType::TEXTURE2D), 0, GL_RGB, resolution.x, resolution.y, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->m_data);
				break;
			}
			//make this optional
			glGenerateMipmap(static_cast<GLenum>(TargetType::TEXTURE2D));

			return texture;
		}
		////std::unique_ptr<texture1D> createTexture1D(const std::string& filepath);
		////std::unique_ptr<texture3D> createTexture3D(const std::string& filepath);
		template<typename dataType>
		void createBuffer(buffer* buffer, TargetType target, UsageType usage, dataType* data = nullptr, int size = 0)
		{
			buffer->initialize(target, usage);
			if (data)
			{
				buffer->bufferData(data, size);
			}
		}
		//std::unique_ptr<buffer<constant, unsigned int>> createConstantBuffer();

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