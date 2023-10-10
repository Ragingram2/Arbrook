#pragma once
#include <rsl/math>

#include "core/components/property.hpp"
#include "core/ecs/entity.hpp"
#include "core/ecs/component_family.hpp"
#include "rendering/interface/definitions.hpp"

namespace rythe::rendering
{
	struct camera
	{
		friend struct core::ecs::component_family<camera>;
	private:
		core::ecs::entity m_owner;
		//float m_nearZ;
		//float m_farZ;
		//float m_fov;

		//void set_nearZ(float val) { m_nearZ = val; }
		//void set_farZ(float val) { m_farZ = val; }
		//void set_fov(float val) { m_fov = val; }

		//float get_nearZ() { return m_nearZ; }
		//float get_farZ() { return m_farZ; }
		//float get_fov() { return m_fov; }

	public:
		//camera() : nearZ(this, &m_nearZ, &camera::set_nearZ, &camera::get_nearZ), farZ(this, &m_farZ, &camera::set_farZ, &camera::get_farZ), fov(this, &m_fov, &camera::set_fov, &camera::get_fov) {}

		//core::Property<camera, float> nearZ;
		//core::Property<camera, float> farZ;
		//core::Property<camera, float> fov;
		float nearZ = 0.01f;
		float farZ = 100.f;
		float fov = 60;
		math::mat4 projection;
		math::mat4 view;

		math::mat4 calculate_view(math::vec3 scale, math::quat orientation, math::vec3 position)
		{
			math::mat4 view(1.f);
			view = math::compose(scale, orientation, position);
			view = math::inverse(view);
			return view;
		}

		math::mat4 calculate_projection()
		{
			auto ratio = ((float)Screen_Width) / Screen_Height;
			auto fovx = math::deg2rad(fov);
			auto invTanHalfFovx = 1.f / math::tan(fovx * 0.5f);
			auto depthScale = farZ / (farZ - nearZ);
			projection = math::float4x4(
				invTanHalfFovx, 0.f, 0.f, 0.f,
				0.f, invTanHalfFovx * ratio, 0.f, 0.f,
				0.f, 0.f, -depthScale, 1.f,
				0.f, 0.f, -nearZ * depthScale, 0.f);
			return projection;
		}
	};
}