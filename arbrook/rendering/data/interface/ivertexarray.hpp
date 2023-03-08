#pragma once

namespace rythe::rendering
{
	//makes this more like Irenderinterface
	template<typename APIType>
	struct Ivertexarray
	{
	private:
		APIType m_impl;
	public:
		APIType* operator->() { return &m_impl; }
	};
}