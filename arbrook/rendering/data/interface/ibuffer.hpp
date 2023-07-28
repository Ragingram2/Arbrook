#pragma once
#include <vector>
#include <concepts>

#include <rsl/primitives>

#include "core/core.hpp"
#include "rendering/data/interface/enumtypes.hpp"
#include "rendering/data/config.hpp"
#include EnumTypes_HPP_PATH

namespace rythe::rendering
{
	class ShaderCache;
	template<typename APIType>
	class IRenderInterface;
	namespace internal
	{
		struct inputlayout;
		struct shader;
		class RenderInterface;
	}
}

//This is where my addition notes will go
//Support owning multiple buffers
//possibly move currently bound buffers to the render interface

namespace rythe::rendering
{
	template<typename APIType>
	struct Ibuffer
	{
		friend class BufferCache;
		friend class IRenderInterface<internal::RenderInterface>;
		friend struct internal::inputlayout;
		friend struct internal::shader;
		friend struct buffer_handle;
	private:
		APIType m_impl;
	public:
		void initialize(TargetType target, UsageType usage) { m_impl.initialize(static_cast<internal::TargetType>(target), static_cast<internal::UsageType>(usage)); }
		void bind(int slot = 0, int offset = 0) { m_impl.bind(slot, offset); }
		template<typename elementType>
		void bufferData(elementType data[], int size = 0) { m_impl.bufferData(data, size); }

		std::string getName() { return m_impl.name; }
		void setName(std::string name) { m_impl.name = name; }
		unsigned int getId() { return m_impl.id; }
		void setId(unsigned int id) { m_impl.id = id; }
		TargetType getTargetType() { return static_cast<TargetType>(m_impl.m_target); }
	private:
		APIType& getImpl() { return m_impl; }
	};
}