#pragma once
#include <memory>
#include <string>

#include "rendering/data/window.hpp"
#include "rendering/data/shader.hpp"
#include "rendering/data/texture.hpp"
#include "rendering/data/texturehandle.hpp"
#include "rendering/data/shaderhandle.hpp"

namespace rythe::rendering
{
	template<typename APIType>
	class IRenderInterface
	{
	private:
		APIType m_impl;
	public:
		void initialize(window& hwnd) { m_impl.initialize(hwnd); }
		void drawArray() { m_impl.drawArray(); }
		void drawArrayInstanced() { m_impl.drawArrayInstanced(); }
		void drawIndexed(unsigned int mode, int count, unsigned int type, const void* indecies) { m_impl.drawIndexed(mode, count, type, indecies); }
		void drawIndexdInstanced() { m_impl.drawIndexedInstanced(); }
		//void bind();//render targets
		void bind(shader_handle handle) { m_impl.bind(handle); }
		void bind(texture_handle handle) { m_impl.bind(handle); }
		void unbind(shader_handle handle) { m_impl.unbind(handle); }
		void unbind(texture_handle handle) { m_impl.unbind(handle); }
		void clear(int flags) { m_impl.clear(flags); }
		shader_handle createShader(shader* shader, const std::string& name, const std::string& filepath) { return m_impl.createShader(shader, name, filepath); };
		texture_handle createTexture2D(texture* texture, const std::string& name, const std::string& filepath) { return m_impl.createTexture2D(texture, name, filepath); }
		////std::unique_ptr<texture1D> createTexture1D(const std::string& filepath);
		////std::unique_ptr<texture3D> createTexture3D(const std::string& filepath);
		//std::unique_ptr<buffer<constant, unsigned int>> createConstantBuffer();
	};
}