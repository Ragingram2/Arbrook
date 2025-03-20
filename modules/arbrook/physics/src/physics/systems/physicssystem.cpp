#include "physicssystem.hpp"

namespace rythe::physics
{

	void PhysicsSystem::setup()
	{
		log::info("Initializing Physics System");
		JPH::RegisterDefaultAllocator();

		JPH::Trace = TraceImpl;
		JPH_IF_ENABLE_ASSERTS(JPH::AssertFailed = AssertFailedImpl;);

		JPH::Factory::sInstance = new JPH::Factory();
		JPH::RegisterTypes();

		physics_system.Init(cMaxBodies, 0, cMaxBodyPairs, cMaxContactConstraints, broad_phase_layer_interface, object_vs_broadphase_layer_filter, object_vs_object_layer_filter);
		temp_allocator = new JPH::TempAllocatorImpl(tempAlloc);
		job_system = new JPH::JobSystemSingleThreaded(2048);
		JPH::BodyInterface& body_interface = physics_system.GetBodyInterface();
		//Creating a body
		for (auto ent : m_filter)
		{
			auto& rb = ent.getComponent<rigidbody>();
			auto& col = ent.getComponent<collider>();
			auto& transf = ent.getComponent<core::transform>();
			auto* body = createBody(new JPH::BoxShape(JPH::Vec3(col.bounds.x, col.bounds.y, col.bounds.z)), transf.position, transf.rotation, rb.motionType);
			m_bodies.emplace(ent->id, body);
			body_interface.AddBody(m_bodies[ent-> id]->GetID(),rb.activationType);
		}

		physics_system.OptimizeBroadPhase();

	}

	void PhysicsSystem::update()
	{
		JPH::BodyInterface& body_interface = physics_system.GetBodyInterface();
		for (auto ent : m_filter)
		{
			auto body = m_bodies[ent->id];
			if (body == nullptr) continue;
			if (!body->IsActive()) continue;

			auto& transf = ent.getComponent<core::transform>();
			auto& rb = ent.getComponent<rigidbody>();

		
			auto vel = body->GetLinearVelocity();
			transf.position += math::vec3(vel.GetX(), vel.GetY(), vel.GetZ()) * cDeltaTime;
			auto pos = JPH::Vec3(transf.position.x, transf.position.y, transf.position.z);
			auto rot = JPH::Quat(math::quat::identity.i, math::quat::identity.j, math::quat::identity.k, math::quat::identity.w);
			body_interface.SetPosition(body->GetID(), pos, rb.activationType);
			//body_interface.SetRotation(bodyId, rot, rb.activationType);
		}
		physics_system.Update(cDeltaTime, 1, temp_allocator, job_system);
	}

	void PhysicsSystem::shutdown()
	{
		JPH::BodyInterface& body_interface = physics_system.GetBodyInterface();

		for (auto [ent, body] : m_bodies)
		{
			body_interface.RemoveBody(body->GetID());
			body_interface.DestroyBody(body->GetID());
		}

		// Unregisters all types with the factory and cleans up the default material
		JPH::UnregisterTypes();

		// Destroy the factory
		delete JPH::Factory::sInstance;
		JPH::Factory::sInstance = nullptr;
	}

	JPH::Body* PhysicsSystem::createBody(JPH::Shape* shape, math::vec3 position, math::quat rotation, JPH::EMotionType motionType)
	{
		JPH::ObjectLayer layer;
		if (motionType == JPH::EMotionType::Dynamic)
			layer = Layers::MOVING;
		else
			layer = Layers::NON_MOVING;

		JPH::BodyInterface& body_interface = physics_system.GetBodyInterface();
		JPH::BodyCreationSettings settings(shape, JPH::Vec3(position.x, position.y, position.z), JPH::Quat(rotation.i, rotation.j, rotation.k, rotation.w), motionType, layer);

		return body_interface.CreateBody(settings);
	}
}