#include "joltphysics.h"
#include "../../utilidades/timer/timer.h"
#include <math.h>
#include "../../components/modulos/collider/collider.h"
#include <physics/rigidBody.h>





  
void JoltPhysics::init(){
	//temp_allocator=Tempall;//((unsigned int)(1024 * 1024 * 10));//(10 * 1024 * 1024)
	//DBG("Inicializo JOLT");
	//RegisterDefaultAllocator();

	
	/*// Create a factory
	Factory::sInstance = new Factory();

	// Register all Jolt physics types
	RegisterTypes();

	//temp_allocator= TempAllocatorImpl(10 * 1024 * 1024);

	//job_system=JobSystemThreadPool(cMaxPhysicsJobs, cMaxPhysicsBarriers, thread::hardware_concurrency() - 1);
	/*physics_system.Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, broad_phase_layer_interface, MyBroadPhaseCanCollide, MyObjectCanCollide);
	//physics_system.SetBodyActivationListener(&body_activation_listener);
	//physics_system.SetContactListener(&contact_listener);
	body_interface = physics_system.GetBodyInterface();
	floor_shape_settings=BoxShapeSettings(Vec3(100.0f, 1.0f, 100.0f));
	floor_shape_result = floor_shape_settings.Create();
	floor_shape = floor_shape_result.Get();
	floor_settings = BodyCreationSettings(floor_shape, Vec3(0.0f, -1.0f, 0.0f), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
	floor = body_interface.CreateBody(floor_settings); // Note that if we run out of bodies this can return nullptr
	sphere_settings = BodyCreationSettings(new SphereShape(0.5f), Vec3(0.0f, 2.0f, 0.0f), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
	sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);
	body_interface.AddBody(floor->GetID(), EActivation::DontActivate);
	body_interface.SetLinearVelocity(sphere_id, Vec3(0.0f, -5.0f, 0.0f));
	physics_system.OptimizeBroadPhase();/**/
}

void JoltPhysics::destroy(){

}

void JoltPhysics::update(){
	 
}

void JoltPhysics::appendRigidBody(physics::RigidBody* rb){
	//Buscamos inicialmente el collider del cuerpo y si no lo encontramos no cargamos el cuerpo
	//cuerpos.push_back(rb);

	//DBG("Nuevo cuerpo rígido, tenemos %", rbs.size());
}
void JoltPhysics::appendCollider(Collider* c){
	physics::RigidBody* rb = (physics::RigidBody*)c->getParent();
	if (rb) {
		cuerpos.push_back({ rb, c });
		DBG("Nuevo cuerpo rígido, tenemos %", cuerpos.size());
	}
}
void JoltPhysics::changeCollider(Collider* c) {
	DBG("La caja a cambiado de tamaño");
	for (auto cuerpo : cuerpos) {
		if (std::get<1>(cuerpo) == c) {
			DBG("Encuentro el collider");
		}
	}
};

REGISTRAR_MODULO(JoltPhysics);