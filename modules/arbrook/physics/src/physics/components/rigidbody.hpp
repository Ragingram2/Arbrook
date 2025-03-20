#pragma once
#include <Jolt/Jolt.h>
#include <Jolt/Physics/Body/MotionType.h>
#include <Jolt/Physics/EActivation.h>

namespace rythe::physics
{
	struct rigidbody
	{
		float mass;
		JPH::EMotionType motionType;
		JPH::EActivation activationType;
	};
}