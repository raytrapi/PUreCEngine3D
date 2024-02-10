#ifndef _JOLT_PHYSICS_1
#define _JOLT_PHYSICS_1

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
#include <Jolt/Physics/Body/BodyActivationListener.h>
#include <Jolt/Physics/Collision/ObjectLayer.h>

/**/

// STL includes
#include <iostream>
#include <cstdarg>
#include <thread>/**/
#include <type_traits>
#include <vector>
#include <tuple>


using namespace JPH;

namespace Layers{
	static constexpr JPH::ObjectLayer NON_MOVING = 0;
	static constexpr JPH::ObjectLayer MOVING = 1;
	static constexpr JPH::ObjectLayer NUM_LAYERS = 2;
};

/// Class that determines if two object layers can collide
static bool MyObjectCanCollide(ObjectLayer inObject1, ObjectLayer inObject2){
	switch (inObject1){
		case Layers::NON_MOVING:
			return inObject2 == Layers::MOVING; // Non moving only collides with moving
		case Layers::MOVING:
			return true; // Moving collides with everything
		default:
			JPH_ASSERT(false);
			return false;
	}
};

// Each broadphase layer results in a separate bounding volume tree in the broad phase. You at least want to have
// a layer for non-moving and moving objects to avoid having to update a tree full of static objects every frame.
// You can have a 1-on-1 mapping between object layers and broadphase layers (like in this case) but if you have
// many object layers you'll be creating many broad phase trees, which is not efficient. If you want to fine tune
// your broadphase layers define JPH_TRACK_BROADPHASE_STATS and look at the stats reported on the TTY.
namespace BroadPhaseLayers{
	static constexpr JPH::BroadPhaseLayer NON_MOVING(0);
	static constexpr JPH::BroadPhaseLayer MOVING(1);
	static constexpr JPH::uint NUM_LAYERS(2);
};

// BroadPhaseLayerInterface implementation
// This defines a mapping between object and broadphase layers.
class BPLayerInterfaceImpl final : public JPH::BroadPhaseLayerInterface{
	public:
		BPLayerInterfaceImpl(){
			// Create a mapping table from object to broad phase layer
			mObjectToBroadPhase[Layers::NON_MOVING] = BroadPhaseLayers::NON_MOVING;
			mObjectToBroadPhase[Layers::MOVING] = BroadPhaseLayers::MOVING;
		}

		virtual JPH::uint GetNumBroadPhaseLayers() const override{
			return BroadPhaseLayers::NUM_LAYERS;
		}

		virtual JPH::BroadPhaseLayer GetBroadPhaseLayer(JPH::ObjectLayer inLayer) const override{
			JPH_ASSERT(inLayer < Layers::NUM_LAYERS);
			return mObjectToBroadPhase[inLayer];
		}

	#if defined(JPH_EXTERNAL_PROFILE) || defined(JPH_PROFILE_ENABLED)
		virtual const char* GetBroadPhaseLayerName(JPH::BroadPhaseLayer inLayer) const override		{
			switch ((JPH::BroadPhaseLayer::Type)inLayer){
				case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::NON_MOVING:	return "NON_MOVING";
				case (JPH::BroadPhaseLayer::Type)BroadPhaseLayers::MOVING:		return "MOVING";
				default:	JPH_ASSERT(false); return "INVALID";
			}
		}
	#endif // JPH_EXTERNAL_PROFILE || JPH_PROFILE_ENABLED

	private:
		JPH::BroadPhaseLayer					mObjectToBroadPhase[Layers::NUM_LAYERS];
};

// Function that determines if two broadphase layers can collide
static bool MyBroadPhaseCanCollide(ObjectLayer inLayer1, BroadPhaseLayer inLayer2) {
	switch (inLayer1) {
		case Layers::NON_MOVING:
			return inLayer2 == BroadPhaseLayers::MOVING;
		case Layers::MOVING:
			return true;
		default:
			JPH_ASSERT(false);
			return false;
	}
};

// An example contact listener
class MyContactListener : public JPH::ContactListener{
	public:
		// See: ContactListener
		virtual JPH::ValidateResult OnContactValidate(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::CollideShapeResult& inCollisionResult) override 		{
			DBG("Contact validate callback % --> %",inBody1.GetID().GetSequenceNumber(), inBody2.GetID().GetSequenceNumber());
			// Allows you to ignore a contact before it is created (using layers to not make objects collide is cheaper!)
			return JPH::ValidateResult::AcceptAllContactsForThisBodyPair;
		}

		virtual void OnContactAdded(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override	{
			//DBG("A contact was added");
		}

		virtual void OnContactPersisted(const JPH::Body& inBody1, const JPH::Body& inBody2, const JPH::ContactManifold& inManifold, JPH::ContactSettings& ioSettings) override		{
			//DBG("A contact was persisted");
		}

		virtual void OnContactRemoved(const JPH::SubShapeIDPair& inSubShapePair) override{
			//DBG("A contact was removed");
		}
};

// An example activation listener
class MyBodyActivationListener : public JPH::BodyActivationListener{
	public:
		virtual void OnBodyActivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override{
			//DBG("A body got activated");
		}

		virtual void OnBodyDeactivated(const JPH::BodyID& inBodyID, JPH::uint64 inBodyUserData) override{
			//DBG("A body went to sleep");
	}
};






/**/
class JoltPhysics : public modules::engine::Physics {


	//TODO: Esta forma de almacenar los cuerpos puede ser lenta. Revisar

	std::vector<std::tuple<physics::RigidBodyComponent*,Collider*, BodyID>> cuerpos; //Cuerpo rígidos

	JPH::Factory* sInstance = 0;
	JPH::TempAllocatorImpl* temp_allocator=0;
	JPH::JobSystemThreadPool* job_system=0;
	JPH::PhysicsSystem *physics_system=0;
	const JPH::uint cMaxBodies = 1024;
	const JPH::uint cNumBodyMutexes = 0;
	const JPH::uint cMaxBodyPairs = 1024;
	const JPH::uint cMaxContactConstraints = 1024;
	BPLayerInterfaceImpl broad_phase_layer_interface;
	MyBodyActivationListener body_activation_listener;
	MyContactListener contact_listener;
	BodyInterface* body_interface=0;


	const float cDeltaTime = 1.0f / 60.0f;
	/*BoxShapeSettings floor_shape_settings;
	ShapeSettings::ShapeResult floor_shape_result;
	ShapeRefC floor_shape;
	BodyCreationSettings sphere_settings;
	BodyCreationSettings floor_settings;
	Body* floor;
	BodyID sphere_id;
	const float cDeltaTime = 1.0f / 60.0f;
	uint step = 0;
	/**/
	BodyID crearCuerpo(Collider* c, physics::RigidBodyComponent* rb);
	//void addCuerpo(Collider* c, physics::RigidBody* rb);
public:
	
	char* nombre() { return (char*)"Physics JOLT"; };
	void init();
	void destroy();
	void update();
	void appendRigidBody(physics::RigidBodyComponent* rb);
	void changeRigidBody(physics::RigidBodyComponent*);
	void appendCollider(Collider* c);
	void changeCollider(Collider* c);
	void transformChanged(physics::RigidBodyComponent*);
	void pause();
	void resume();
};


#endif // !_PYSHICS_1_0
