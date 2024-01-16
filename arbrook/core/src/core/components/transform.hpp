#pragma once
#include "core/math/math.hpp"
#include "core/components/property.hpp"
namespace rythe::core
{
	struct transform
	{
		//void set_position(math::vec3 val) { m_position = val; m_localMatrix = math::compose(m_scale, m_rotation, m_position); }
		//void set_scale(math::vec3 val) { m_scale = val; m_localMatrix = math::compose(m_scale, m_rotation, m_position); }
		//void set_rotation(math::quat val) { m_rotation = val; m_localMatrix = math::compose(m_scale, m_rotation, m_position); }

		//math::vec3 get_position() { return m_position; }
		//math::vec3 get_scale() { return m_scale; }
		//math::quat get_rotation() { return m_rotation; }
	public:

		//Property<transform, math::vec3> position;
		//Property<transform, math::vec3> scale;
		//Property<transform, math::quat> rotation;

		math::vec3 position = math::vec3(0.0f);
		math::vec3 scale = math::vec3(1.0f);
		math::quat rotation = math::quat(1.0f, 0.0f, 0.0f, 0.0f);

		math::vec3 up() { return rotation.up(); }
		math::vec3 right() { return rotation.right(); }
		math::vec3 forward() { return rotation.forward(); }

		void set_owner(/*core::ecs::entity ent*/)
		{
			//m_owner = ent;
		}

		math::mat4 from_world()
		{
			return math::inverse(to_world());
		}

		math::mat4 to_world()
		{
			//if (m_owner && m_owner->parent)
			//{
			//	transform parentTransf = m_owner->parent.getComponent<transform>();
			//	return parentTransf.to_world() * to_parent();
			//}
			return to_parent();
		}

		math::mat4 from_parent()
		{
			return math::inverse(to_parent());
		}

		math::mat4 to_parent()
		{
			return math::compose(scale, rotation, position);
		}
	};

	inline math::vec3 transformDirection(core::transform transf, const math::vec3& direction) { return  transf.rotation * direction; }
	inline math::vec3 inverseTransformDirection(core::transform transf, const math::vec3& direction) { return math::inverse(transf.rotation) * direction; }
}