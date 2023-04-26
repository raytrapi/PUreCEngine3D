#ifndef _JOLT_PHYSICS_STATICA
#define _JOLT_PHYSICS_STATICA

#include <physics.h>
#include <entity.h>
#include <transform.h>


#include <Jolt/Jolt.h>

// Jolt includes
#include <Jolt/RegisterTypes.h>
#include <Jolt/Core/Factory.h>
#include <Jolt/Core/TempAllocator.h>
#include <Jolt/Core/JobSystemThreadPool.h>
#include <Jolt/Physics/PhysicsSettings.h>
#include <Jolt/Physics/PhysicsSystem.h>
#include <Jolt/Physics/Collision/Shape/BoxShape.h>
#include <Jolt/Physics/Collision/Shape/SphereShape.h>
#include <Jolt/Physics/Body/BodyCreationSettings.h>
#include <Jolt/Physics/Body/BodyActivationListener.h>/**/

// STL includes
#include <iostream>
#include <cstdarg>
#include <thread>/**/

#include <vector>
#include <tuple>

JPH_SUPPRESS_WARNINGS
using namespace JPH;
using namespace std;

namespace Layers {
	static constexpr uint8 NON_MOVING = 0;
	static constexpr uint8 MOVING = 1;
	static constexpr uint8 NUM_LAYERS = 2;
};
namespace BroadPhaseLayers
{
	static constexpr BroadPhaseLayer NON_MOVING(0);
	static constexpr BroadPhaseLayer MOVING(1);
	static constexpr uint NUM_LAYERS(2);
};
class BPLayerInterfaceImpl final : public BroadPhaseLayerInterface
{
public:
	BPLayerInterfaceImpl()
	{
		// Create a mapping table from object to broad phase layer
		mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
		mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
	}

	virtual uint					GetNumBroadPhaseLayers() const override
	{
		return BroadPhaseLayers::NUM_LAYERS;
	}

	virtual BroadPhaseLayer			GetBroadPhaseLayer(ObjectLayer inLayer) const override
	{
		JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
		return mObjectToBroadPhase[inLayer];
	}

#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
	virtual const char* GetBroadPhaseLayerName(BroadPhaseLayer inLayer) const override
	{
		switch ((BroadPhaseLayer::Type)inLayer)
		{
		case (BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:	return "NON_MOVING";
		case (BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:		return "MOVING";
		default:													JPH_ASSERT(false); return "INVALID";
		}
	}
#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

private:
	BroadPhaseLayer					mObjectToBroadPhase[Layers::NUM_LAYERS];
};

// Function that determines if two broadphase layers can collide
static bool MyBroadPhaseCanCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2)
{
	switch (inLayer1)
	{
	case Layers::NON_MOVING:
		return inLayer2 == BroadPhaseLayers::MOVING;
	case Layers::MOVING:
		return true;
	default:
		JPH_ASSERT(false);
		return false;
	}
}
/**/
class JoltPhysicsStatica {
	//TODO: Esta forma de almacenar los cuerpos puede ser lenta. Revisar
	std::vector<std::tuple<physics::RigidBody*,Collider*>> cuerpos; //Cuerpor rígidos


	//TempAllocatorImpl temp_allocator;//((unsigned int)(1024 * 1024 * 10));//(10 * 1024 * 1024);
	//JobSystemThreadPool job_system(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);
	/*const uint cMaxBodies = 1024;
	const uint cNumBodyMutexes = 0;
	const uint cMaxBodyPairs = 1024;
	const uint cMaxContactConstraints = 1024;
	BPLayerInterfaceImpl broad_phase_layer_interface;
	PhysicsSystem physics_system;
	//MyBodyActivationListener body_activation_listener;
	//MyContactListener contact_listener;
	BodyInterface& body_interface;
	BoxShapeSettings floor_shape_settings;
	ShapeSettings::ShapeResult floor_shape_result;
	ShapeRefC floor_shape;
	BodyCreationSettings sphere_settings;
	BodyCreationSettings floor_settings;
	Body* floor;
	BodyID sphere_id;
	const float cDeltaTime = 1.0f / 60.0f;
	uint step = 0;
	/**/
public:
	void init();
};


#endif // 
