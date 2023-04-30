#pragma once
#include <memory>
#include <string>

#include "rendering/data/bufferhandle.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/shaderhandle.hpp"
#include "rendering/data/shadersource.hpp"
#include "rendering/data/interface/enumtypes.hpp"
#include "rendering/data/interface/ishader.hpp"
#include "rendering/data/config.hpp"
#include Shader_HPP_PATH
#include Texture_HPP_PATH
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
		void initialize(math::ivec2 res, const std::string& name, GLFWwindow* window = nullptr) { m_impl.initialize(res, name, window); }
		void close() { m_impl.close(); }
		GLFWwindow* getWindow() { return m_impl.getWindow(); }
		internal::window& getHwnd() { return m_impl.getHwnd(); }
		void makeCurrent() { m_impl.makeCurrent(); }
		void setSwapInterval(int interval) { m_impl.setSwapInterval(interval); }
		bool shouldWindowClose() { return m_impl.shouldWindowClose(); }
		void pollEvents() { m_impl.pollEvents(); }
		void swapBuffers() { m_impl.swapBuffers(); }

		void drawArrays(PrimitiveType mode, unsigned int startVertex, unsigned int vertexCount) { m_impl.drawArrays(static_cast<internal::PrimitiveType>(mode), startVertex, vertexCount); }
		void drawArraysInstanced(PrimitiveType mode, unsigned int vertexCount, unsigned int instanceCount, unsigned int startVertex, unsigned int startInstance) { m_impl.drawArraysInstanced(static_cast<internal::PrimitiveType>(mode), vertexCount, instanceCount, startVertex, startInstance); }
		void drawIndexed(PrimitiveType mode, unsigned int indexCount, unsigned int startIndex, unsigned int baseVertex) { m_impl.drawIndexed(static_cast<internal::PrimitiveType>(mode), indexCount, startIndex, baseVertex); }
		void drawIndexedInstanced(PrimitiveType mode, unsigned int indexCount, unsigned int instanceCount, unsigned int startIndex, unsigned int baseVertex, unsigned int startInstance) { m_impl.drawIndexedInstanced(static_cast<internal::PrimitiveType>(mode), indexCount, instanceCount, startIndex, baseVertex, startInstance); }

		void clear(ClearBit flags) { m_impl.clear(static_cast<internal::ClearBit>(flags)); }
		void setClearColor(math::vec4 color) { m_impl.setClearColor(color); }
		void setClearColor(math::vec3 color, float alpha = 1.0f) { m_impl.setClearColor(math::vec4(color, alpha)); }
		void setClearColor(float r, float g, float b, float alpha = 1.0f) { m_impl.setClearColor(math::vec4(r, g, b, alpha)); }

		void enableDepthTest() { m_impl.enableDepthTest(); }
		void disableDepthTest() { m_impl.disableDepthTest(); }
		void enableDepthWrite() { m_impl.enableDepthWrite(); }
		void disableDepthWrite() { m_impl.disableDepthWrite(); }
		void setDepthFunction(DepthFuncs function) { m_impl.setDepthFunction(static_cast<internal::DepthFuncs>(function)); }
		void enableStencilTest() { m_impl.enableStencilTest(); }
		void disableStencilTest() { m_impl.disableStencilTest(); }
		void setStencilOp(Face face, StencilOp fail, StencilOp zfail, StencilOp zpass) { m_impl.setStencilOp(static_cast<internal::Face>(face), static_cast<internal::StencilOp>(fail), static_cast<internal::StencilOp>(zfail), static_cast<internal::StencilOp>(zpass)); }
		void setStencilFunction(Face face, DepthFuncs func, unsigned int ref, unsigned int mask) { m_impl.setStencilFunction(static_cast<internal::Face>(face), static_cast<internal::DepthFuncs>(func), ref, mask); }
		void updateDepthStencil() { m_impl.updateDepthStencil(); }

		void setViewport(float numViewPorts = 1, float topLeftX = 0, float topLeftY = 0, float width = 0, float height = 0, float minDepth = 0, float maxDepth = 1) { m_impl.setViewport(numViewPorts, topLeftX, topLeftY, width, height, minDepth, maxDepth); }
		//void setScissorTest();
		//void setBlend(bool blend);
		//void setBlendParam();


		//void setLineWidth();

		shader_handle createShader(Ishader<internal::shader>* shader, const std::string& name, const shader_source& source) { m_impl.createShader(&shader->getImpl(), name, source); return shader; };
		texture_handle createTexture2D(Itexture<internal::texture>* texture, const std::string& name, const std::string& filepath) { m_impl.createTexture2D(&texture->getImpl(), name, filepath); return texture; }
		//texture_handle createTexture1D(texture1D* texture1d, const std::string& name,const std::string& filepath);
		//texture_handle createTexture3D(texture3D* texture3d, const std::string& name,const std::string& filepath);
		//texture_handle createCubeTexture();
		template<typename elementType>
		buffer_handle createBuffer(Ibuffer<internal::buffer>* buffer, TargetType target, UsageType usage, elementType* data = nullptr, int size = 1) { m_impl.createBuffer(&buffer->getImpl(), static_cast<internal::TargetType>(target), static_cast<internal::UsageType>(usage), data, size); return buffer; }
		//void createRenderTarget()

		void checkError() { m_impl.checkError(); }
	};
}