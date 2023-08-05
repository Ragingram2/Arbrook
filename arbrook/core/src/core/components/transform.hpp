#pragma once
#include "core/math/math.hpp"
#include "core/components/property.hpp"
namespace rythe::core
{
	struct transform
	{
	private:
		math::mat4 m_localMatrix;
		math::mat4 m_worldMatrix;

		math::vec3 m_position = math::vec3(0.0f);
		math::vec3 m_scale = math::vec3(1.0f);
		math::quat m_rotation = math::quat(0.0f, 0.0f, 0.0f, 1.0f);

		void set_position(math::vec3 val) { m_position = val; m_localMatrix = math::compose(m_scale, m_rotation, m_position); }
		void set_scale(math::vec3 val) { m_scale = val; m_localMatrix = math::compose(m_scale, m_rotation, m_position); }
		void set_rotation(math::quat val) { m_rotation = val; m_localMatrix = math::compose(m_scale, m_rotation, m_position); }

		math::vec3 get_position() { return m_position; }
		math::vec3 get_scale() { return m_scale; }
		math::quat get_rotation() { return m_rotation; }
	public:
		transform() :
			position(this, &m_position, &transform::set_position, &transform::get_position),
			scale(this, &m_scale, &transform::set_scale, &transform::get_scale),
			rotation(this, &m_rotation, &transform::set_rotation, &transform::get_rotation),
			localMatrix(&m_localMatrix) {}

		Property<transform, math::vec3> position;
		Property<transform, math::vec3> scale;
		Property<transform, math::quat> rotation;
		Property<transform, math::mat4> localMatrix;

		math::vec3 up() { return m_localMatrix.row1; }
		math::vec3 right() { return m_localMatrix.row0; }
		math::vec3 forward() { return m_localMatrix.row2; }
	};
}