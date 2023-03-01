#pragma once
#include <memory>
#include <string>

#include <GLFW/glfw3.h>

#include "rendering/data/window.hpp"
#include "rendering/data/interface/shader.hpp"
//#include "rendering/data/texture.hpp"
//#include "rendering/data/buffer.hpp"


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
		void clear(int flags) { m_impl.clear(flags); }

		template<typename ShaderType>
		std::unique_ptr<shader> createShader(const std::string& filepath) { return m_impl.createShader(filePath); };
		template<typename ShaderType>
		std::unique_ptr<shader> getShader(const std::string& name) { return m_impl.getShader(name); }
		//std::unique_ptr<texture> createTexture(const std::string& filepath);
		////std::unique_ptr<texture1D> createTexture1D(const std::string& filepath);
		////std::unique_ptr<texture3D> createTexture3D(const std::string& filepath);
		//std::unique_ptr<buffer<constant, unsigned int>> createConstantBuffer();
	};
}