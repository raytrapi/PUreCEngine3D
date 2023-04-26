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
#include <Jolt/Physics/Body/BodyActivationListener.h>/**/

// STL includes
#include <iostream>
#include <cstdarg>
#include <thread>/**/

#include <vector>
#include <tuple>




/**/
class JoltPhysics : public modules::engine::Physics {
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
	char* nombre() { return (char*)"Physics JOLT"; };
	void init();
	void destroy();
	void update();
	void appendRigidBody(physics::RigidBody* rb);
	void appendCollider(Collider* c);
	void changeCollider(Collider* c);
};


#endif // !_PYSHICS_1_0
