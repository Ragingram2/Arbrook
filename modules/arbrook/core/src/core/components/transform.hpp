#pragma once
#include <rsl/math>
namespace rythe::core
{
	struct transform
	{
	public:

		math::vec3 position = math::vec3(0.0f);
		math::vec3 scale = math::vec3(1.0f);
		math::quat rotation = math::quat(1.0f, 0.0f, 0.0f, 0.0f);

		math::vec3 up() { return rotation.up(); }
		math::vec3 right() { return rotation.right(); }
		math::vec3 forward() { return rotation.forward(); }

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