#include "rendering/data/vertexarray.hpp"

namespace rythe::rendering
{
	void vertexarray::initialize()
	{
		glGenVertexArrays(1, &m_id);
	}

	void vertexarray::bind()
	{
		glBindVertexArray(m_id);
	}

	void vertexarray::unbind()
	{
		glBindVertexArray(0);
	}
}
