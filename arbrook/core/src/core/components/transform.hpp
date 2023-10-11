#pragma once
#include "core/math/math.hpp"
#include "core/ecs/entity.hpp"
#include "core/components/property.hpp"
namespace rythe::core
{
	struct transform
	{
		friend struct ecs::component_family<transform>;
	private:
		ecs::entity m_owner;
		math::mat4 m_localMatrix;

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

		math::vec3 up() { return m_localMatrix[1]; }
		math::vec3 right() { return m_localMatrix[0]; }
		math::vec3 forward() { return m_localMatrix[2]; }

		void set_owner(core::ecs::entity ent)
		{
			m_owner = ent;
		}

		math::mat4 from_world()
		{
			return math::inverse(to_world());
		}

		math::mat4 to_world()
		{
			if (m_owner && m_owner->parent)
			{
				transform parentTransf = m_owner->parent.getComponent<transform>();
				return parentTransf.to_world() * to_parent();
			}
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
}