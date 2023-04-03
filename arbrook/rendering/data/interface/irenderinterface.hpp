#pragma once
#include <memory>
#include <string>

#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/texture.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/interface/enumtypes.hpp"
#include "rendering/data/config.hpp"
#include Shader_HPP_PATH
#include Buffer_HPP_PATH
#include Window_HPP_PATH
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	template<typename APIType>
	class IRenderInterface
	{
	private:
		APIType m_impl;
	public:
		void initialize(math::ivec2 res, const std::string& name) { m_impl.initialize(res, name); }
		void close() { m_impl.close(); }
		GLFWwindow* getWindow() { return m_impl.getWindow(); }
		internal::window& getHwnd() { return m_impl.getHwnd(); }
		void makeCurrent() { m_impl.makeCurrent(); }
		void setSwapInterval(int interval) { m_impl.setSwapInterval(interval); }
		bool shouldWindowClose() { return m_impl.shouldWindowClose(); }
		void pollEvents() { m_impl.pollEvents(); }
		void swapBuffers() { m_impl.swapBuffers(); }

		void drawArrays(PrimitiveType mode, unsigned int startVertex, unsigned int vertexCount) { m_impl.drawArrays(static_cast<internal::PrimitiveType>(mode), startVertex, vertexCount); }
		void drawArraysInstanced(PrimitiveType mode, unsigned int vertexCount, unsigned int instanceCount, unsigned int startVertex, unsigned int startInstance) { m_impl.drawArraysInstanced(static_cast<internal::PrimitiveType>(mode), vertexCount, instanceCount, startVertex, instanceCount, startInstance); }
		void drawIndexed(PrimitiveType mode, unsigned int indexCount, unsigned int startIndex, unsigned int baseVertex) { m_impl.drawIndexed(static_cast<internal::PrimitiveType>(mode), indexCount, startIndex, baseVertex); }
		void drawIndexdInstanced(PrimitiveType mode, unsigned int indexCount, unsigned int instanceCount, unsigned int startIndex, unsigned int baseVertex, unsigned int startInstance) { m_impl.drawIndexedInstanced(static_cast<internal::PrimitiveType>(mode), indexCount, instanceCount, startIndex, baseVertex, startInstance); }

		//void bind();//render targets
		void bind(shader_handle handle) { m_impl.bind(handle.m_shader); }
		void bind(texture_handle handle) { m_impl.bind(handle); }
		void unbind(shader_handle handle) { m_impl.unbind(handle.m_shader); }
		void unbind(texture_handle handle) { m_impl.unbind(handle); }
		void clear(int flags) { m_impl.clear(flags); }

		void setClearColor(math::vec4 color) { m_impl.setClearColor(color); }
		void setClearColor(math::vec3 color, float alpha = 1.0f) { m_impl.setClearColor(math::vec4(color, alpha)); }
		void setClearColor(float r, float g, float b, float alpha = 1.0f) { m_impl.setClearColor(math::vec4(r, g, b, alpha)); }

		void enableStencil() { m_impl.enableStencil(); }
		void disableStencil() { m_impl.disableStencil(); }
		void setClearStencil() { m_impl.setClearStencil(); }
		void setStencilOp() { m_impl.setStencilOp(); }
		void setStencilFunc() { m_impl.setStencilFunc(); }

		//void setViewport();
		//void setScissorTest();
		//void setBlend(bool blend);
		//void setBlendParam();
		//void setDepthTest();
		//void setDepthWrite();
		//void setDepthFunction();

		//void setLineWidth();

		shader_handle createShader(internal::shader* shader, const std::string& name, const shader_source& source) { m_impl.createShader(shader, name, source); return shader; };
		texture_handle createTexture2D(texture* texture, const std::string& name, const std::string& filepath) { return m_impl.createTexture2D(texture, name, filepath); }
		//texture_handle createTexture1D(texture1D* texture1d, const std::string& name,const std::string& filepath);
		//texture_handle createTexture3D(texture3D* texture3d, const std::string& name,const std::string& filepath);
		//texture_handle createCubeTexture();
		template<typename dataType>
		buffer_handle createBuffer(internal::buffer* buffer, TargetType target, UsageType usage, dataType* data = nullptr, int size = 0) { m_impl.createBuffer(buffer, target, usage, data, size); return buffer; }
		//void createInputLayout() ??? what is this?
		//void createRenderTarget()

		void checkError() { m_impl.checkError(); }
	};
}