#pragma once
#include <string>

#include "rendering/data/textureparameters.hpp"
#include "rendering/interface/enumtypes.hpp"
#include "rendering/data/handles/texturehandle.hpp"
#include "rendering/interface/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	class TextureCache;
	template<typename APIType>
	class IRenderInterface;
	template<typename dataType>
	struct data_handle;
	namespace internal
	{
		struct inputlayout;
		struct texture;
		class RenderInterface;
	}
}

namespace rythe::rendering
{
	template<typename APIType>
	struct Itexture
	{
		friend class TextureCache;
		friend class IRenderInterface<internal::RenderInterface>;
		friend struct internal::inputlayout;
		friend struct data_handle<Itexture<internal::texture>>;
	private:
		APIType m_impl;
	public:
		void bind() { m_impl.bind(); }
		void loadData(const std::string& filepath) { m_impl.loadData(filepath); }

		unsigned int getId() { return m_impl.id; }
		const std::string& getName() { return m_impl.name; }

	private:
		APIType& getImpl() { return m_impl; }
	};
}