#pragma once

#include <rsl/math>
#include <rsl/logging>

#include "core/systems/system.hpp"
#include "core/components/transform.hpp"
#include "physics/components/rigidbody.hpp"
#include "physics/components/collider.hpp"
#include "physics/systems/joltboilerplate.hpp"

namespace rythe::physics
{
	inline JPH::TempAllocator* temp_allocator;
	inline JPH::JobSystem* job_system;
	class PhysicsSystem : public core::System<PhysicsSystem, core::transform, rigidbody, collider>
	{
	public:
		const rsl::uint tempAlloc = 10 * 1024 * 1024;
		const rsl::uint cMaxBodies = 1024;
		const rsl::uint cMaxBodyPairs = 1024;
		const rsl::uint cMaxContactConstraints = 1024;
		const float cDeltaTime = 1.0f / 60.0f;

		std::unordered_map<rsl::id_type, JPH::Body*> m_bodies;

		BPLayerInterfaceImpl broad_phase_layer_interface;
		ObjectVsBroadPhaseLayerFilterImpl object_vs_broadphase_layer_filter;
		ObjectLayerPairFilterImpl object_vs_object_layer_filter;
		MyBodyActivationListener body_activation_listener;
		MyContactListener contact_listener;

		JPH::PhysicsSystem physics_system;


		void setup();
		void update();
		void shutdown();

		JPH::Body* createBody(JPH::Shape* shape,math::vec3 position, math::quat rotation, JPH::EMotionType motionType);
	};
}
