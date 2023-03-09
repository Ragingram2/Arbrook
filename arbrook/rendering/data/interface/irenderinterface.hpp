#pragma once
#include <memory>
#include <string>

#include "rendering/data/shader.hpp"
#include "rendering/data/texture.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/interface/iwindow.hpp"
#include "rendering/data/config.hpp"

namespace rythe::rendering
{
	template<typename APIType>
	class IRenderInterface
	{
	private:
		APIType m_impl;
	public:
		void initialize(Iwindow<internal::window>& hwnd, math::ivec2 res, const std::string& name) { m_impl.initialize(*hwnd, res, name); }

		void drawArrays(unsigned int mode, int first, int count) { m_impl.drawArrays(mode, first, count); }
		void drawArraysInstanced(unsigned int mode, int first, int count, int instanceCount) { m_impl.drawArraysInstanced(mode, first, count, instanceCount); }
		void drawIndexed(unsigned int mode, int count, unsigned int type, const void* indecies) { m_impl.drawIndexed(mode, count, type, indecies); }
		void drawIndexdInstanced(unsigned int mode, int count, unsigned int type, const void* indecies, int instanceCount) { m_impl.drawIndexedInstanced(mode, count, type, indecies, instanceCount); }

		//void bind();//render targets
		void bind(shader_handle handle) { m_impl.bind(handle); }
		void bind(texture_handle handle) { m_impl.bind(handle); }
		void unbind(shader_handle handle) { m_impl.unbind(handle); }
		void unbind(texture_handle handle) { m_impl.unbind(handle); }
		void clear(int flags) { m_impl.clear(flags); }

		void setUniform(shader_handle shader, const std::string& uniformName, math::vec4 value) { m_impl.setUniform(shader, uniformName, value); }
		void setUniform(shader_handle shader, const std::string& uniformName, math::vec3 value) { m_impl.setUniform(shader, uniformName, value); }
		void setUniform(shader_handle shader, const std::string& uniformName, math::vec2 value) { m_impl.setUniform(shader, uniformName, value); }
		void setUniform(shader_handle shader, const std::string& uniformName, float value) { m_impl.setUniform(shader, uniformName, value); }
		void setUniform(shader_handle shader, const std::string& uniformName, math::ivec4 value) { m_impl.setUniform(shader, uniformName, value); }
		void setUniform(shader_handle shader, const std::string& uniformName, math::ivec3 value) { m_impl.setUniform(shader, uniformName, value); }
		void setUniform(shader_handle shader, const std::string& uniformName, math::ivec2 value) { m_impl.setUniform(shader, uniformName, value); }
		void setUniform(shader_handle shader, const std::string& uniformName, int value) { m_impl.setUniform(shader, uniformName, value); }

		void setClearColor(math::vec4 color) { m_impl.setClearColor(color); }
		void setClearColor(math::vec3 color, float alpha = 1.0f) { m_impl.setClearColor(math::vec4(color, alpha)); }
		void setClearColor(float r, float g, float b, float alpha = 1.0f) { m_impl.setClearColor(math::vec4(r, g, b, alpha)); }

		void enableStencil() { m_impl.enableStencil(); }
		void disableStencil() { m_impl.disableStencil(); }
		void setClearStencil() { m_impl.setClearStencil(); }
		void setStencilOp() { m_impl.setStencilOp(); }
		void setStencilFunc() { m_impl.setStencilFunc(); }

		void setViewport();
		void setScissorTest();
		void setBlend(bool blend);
		void setBlendParam();
		void setDepthTest();
		void setDepthWrite();
		void setDepthFunction();

		//void setLineWidth();

		shader_handle createShader(shader* shader, const std::string& name, const std::string& filepath) { return m_impl.createShader(shader, name, filepath); };
		texture_handle createTexture2D(texture* texture, const std::string& name, const std::string& filepath) { return m_impl.createTexture2D(texture, name, filepath); }
		//texture_handle createTexture1D(texture1D* texture1d, const std::string& name,const std::string& filepath);
		//texture_handle createTexture3D(texture3D* texture3d, const std::string& name,const std::string& filepath);
		//texture_handle createCubeTexture();
		//buffer_handle createConstantBuffer();
		//buffer_handle createIndexBuffer();
		//buffer_handle createVertexBuffer();
		//void createInputLayout() ??? what is this?
		//void createRenderTarget()
	};
}