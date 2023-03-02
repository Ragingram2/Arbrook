#pragma once
#include <string>

#include "rendering/data/interface/texture.hpp"
namespace rythe::rendering
{
	template<typename APIType>
	class ITextureCache
	{
	private:
		static APIType m_impl;
	public:
		static texture* createTexture2D(const std::string& name, const std::string& filepath) { return m_impl.createTexture2D(name, filepath); }
		static texture* getTexture2D(const std::string& name) { return m_impl.getTexture2D(name); }
	};
}