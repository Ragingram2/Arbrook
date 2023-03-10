#pragma once
#include <memory>
#include <string>
#include <fstream>

#include <GL/glew.h>

#include "core/math/math.hpp"
#include "core/logging/logging.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/OpenGL/shader.hpp"

#include "rendering/data/texturehandle.hpp"
#include "rendering/data/interface/window.hpp"

#include <stb/stb_image.h>
#define STB_IMAGE_IMPLEMENTATION

namespace rythe::rendering::internal
{
	class RenderInterface
	{
	public:
		void initialize(window& hwnd, math::ivec2 res, const std::string& name)
		{
			hwnd.initialize(res, name);
			window::makeCurrent();

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
		void swapBuffers(window& hwnd)
		{
			glfwSwapBuffers(hwnd.getWindow());
		}


		void drawArrays(unsigned int mode, int first, int count)
		{
			glDrawArrays(mode, first, count);
		}

		void drawArraysInstanced(unsigned int mode, int first, int count, int instanceCount)
		{
			glDrawArraysInstanced(mode, first, count, instanceCount);
		}

		void drawIndexed(unsigned int mode, int count, unsigned int type, const void* indecies)
		{
			glDrawElements(mode, count, type, indecies);
		}

		void drawIndexdInstanced(unsigned int mode, int count, unsigned int type, const void* indecies, int instanceCount)
		{
			glDrawElementsInstanced(mode, count, type, indecies, instanceCount);
		}

		void bind(shader* shader)
		{
			glUseProgram(shader->m_programId);
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

		//move file handling elsewhere
		void createShader(shader* shader, const std::string& name, const std::string& filepath)
		{
			auto source = loadSource(filepath);

			shader->m_name = name;
			auto& programId = shader->m_programId = glCreateProgram();

			unsigned int vs = compileShader(GL_VERTEX_SHADER, source.vertexSource);
			unsigned int fs = compileShader(GL_FRAGMENT_SHADER, source.fragSource);

			glAttachShader(programId, vs);
			glAttachShader(programId, fs);
			glLinkProgram(programId);
			glValidateProgram(programId);

			glDeleteShader(vs);
			glDeleteShader(fs);
		}

		//move file handling elsewhere, specify default Texture params
		texture_handle createTexture2D(texture* texture, const std::string& name, const std::string& filepath, texture_parameters params = { rendering::WrapMode::REPEAT ,rendering::WrapMode::REPEAT,GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR })
		{
			texture->m_name = name;
			auto& resolution = texture->m_params.m_resolution;
			auto& channels = texture->m_params.m_channels;
			unsigned int& id = texture->m_id;
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<GLint>(params.m_wrapModeS));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<GLint>(params.m_wrapModeT));
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, params.m_minFilterMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, params.m_magFilterMode);
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
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, resolution.x, resolution.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->m_data);
				break;
			case 3:
				glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, resolution.x, resolution.y, 0, GL_BGR, GL_UNSIGNED_BYTE, texture->m_data);
				break;
			}
			//make this optional
			glGenerateMipmap(GL_TEXTURE_2D);

			return texture;
		}
		////std::unique_ptr<texture1D> createTexture1D(const std::string& filepath);
		////std::unique_ptr<texture3D> createTexture3D(const std::string& filepath);
		//std::unique_ptr<buffer<constant, unsigned int>> createConstantBuffer();

	private:
		shader_source loadSource(const std::string& filepath);
		unsigned int compileShader(unsigned int type, const std::string& source);
		static void debugCallback(unsigned int source, unsigned int type, unsigned int id, unsigned int  severity, int length, const char* message, const void* userparam);
		static void debugCallbackARB(unsigned int source, unsigned int type, unsigned int id, unsigned int  severity, int length, const char* message, const void* userparam);
		static void debugCallbackAMD(unsigned int id, unsigned int category, unsigned int  severity, int length, const char* message, void* userparam);
	};

	inline shader_source RenderInterface::loadSource(const std::string& filepath)
	{
		std::ifstream stream(filepath);

		enum class ShaderType
		{
			NONE = -1,
			VERTEX = 0,
			FRAG = 1
		};

		std::string line;
		std::stringstream ss[2];
		ShaderType type = ShaderType::NONE;

		while (getline(stream, line))
		{
			if (line.find("#shader") != std::string::npos)
			{
				if (line.find("vertex") != std::string::npos)
				{
					type = ShaderType::VERTEX;
				}
				else if (line.find("fragment") != std::string::npos)
				{
					type = ShaderType::FRAG;
				}
			}
			else
			{
				ss[(int)type] << line << "\n";
			}
		}

		return { ss[0].str(),ss[1].str() };
	}
	inline unsigned int RenderInterface::compileShader(unsigned int type, const std::string& source)
	{
		unsigned int id = glCreateShader(type);
		const char* src = source.c_str();
		glShaderSource(id, 1, &src, nullptr);
		glCompileShader(id);

		int result;
		glGetShaderiv(id, GL_COMPILE_STATUS, &result);

		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)__builtin_alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);

		if (result == GL_FALSE)
		{
			log::error(message);
			glDeleteShader(id);
			return 0;
		}

		return id;
	}
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