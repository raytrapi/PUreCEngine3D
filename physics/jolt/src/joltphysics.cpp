#include "joltphysics.h"
#include "../../utilidades/timer/timer.h"
#include <math.h>
#include "../../components/modulos/collider/collider.h"
#include <physics/rigidBodyComponent.h>





  


void JoltPhysics::init(){
	//temp_allocator=Tempall;//((unsigned int)(1024 * 1024 * 10));//(10 * 1024 * 1024)
	DBG("Inicializo JOLT"); 
	JPH::RegisterDefaultAllocator();
	JPH::Trace = TraceImpl;
#ifdef EDITOR
#ifdef JPH_ENABLE_ASSERTS
	JPH::JPH_IF_ENABLE_ASSERTS(AssertFailed = AssertFailedImpl;)
#endif // JPH_ENABLE_ASSERTS
#endif // EDITOR

	// Create a factory
	JPH::Factory::sInstance = new JPH::Factory();
	// Register all Jolt physics types
	JPH::RegisterTypes();
	
	temp_allocator = new JPH::TempAllocatorImpl(10 * 1024 * 1024);
	
	//TODO: Esto hay que implementarlo de otra forma ya que si hay hilos estos de abajo deberían estar los primeros

	job_system=new JPH::JobSystemThreadPool(JPH::cMaxPhysicsJobs, JPH::cMaxPhysicsBarriers, JPH::thread::hardware_concurrency() - 1);
	physics_system = new JPH::PhysicsSystem();
	physics_system->Init(cMaxBodies, cNumBodyMutexes, cMaxBodyPairs, cMaxContactConstraints, broad_phase_layer_interface, MyBroadPhaseCanCollide, MyObjectCanCollide);
	physics_system->SetBodyActivationListener(&body_activation_listener);
	physics_system->SetContactListener(&contact_listener);
	
	body_interface = &physics_system->GetBodyInterface();
	/*BoxShapeSettings floor_shape_settings = BoxShapeSettings(Vec3(100.f, 1.f, 100.0f));
	auto floor_shape_result = floor_shape_settings.Create();
	auto floor_shape = floor_shape_result.Get();
	auto floor_settings = BodyCreationSettings(floor_shape, Vec3(0.0f, 0.0f, 0.0f), Quat::sIdentity(), EMotionType::Static, Layers::NON_MOVING);
	cuerpos.push_back({ 0,0,body_interface->CreateAndAddBody(floor_settings, EActivation::Activate) });
	/*sphere_settings = BodyCreationSettings(new SphereShape(0.5f), Vec3(0.0f, 2.0f, 0.0f), Quat::sIdentity(), EMotionType::Dynamic, Layers::MOVING);
	sphere_id = body_interface.CreateAndAddBody(sphere_settings, EActivation::Activate);
	body_interface.AddBody(floor->GetID());
	body_interface.SetLinearVelocity(sphere_id, Vec3(0.0f, -5.0f, 0.0f));/**/
	physics_system->OptimizeBroadPhase();/**/
}

void JoltPhysics::destroy(){
	if (sInstance) { 
		delete sInstance;
	}/**/
	if (temp_allocator) {
		delete temp_allocator;
	}
	if (body_interface) {
		for (auto cuerpo : cuerpos) {
			auto bodyId = std::get<2>(cuerpo);
			if (!bodyId.IsInvalid()) {
				body_interface->RemoveBody(bodyId);
				body_interface->DestroyBody(bodyId);
			}
		}

		delete body_interface;
	}
	if (job_system) {
		delete job_system;
	}

	if (physics_system) {
		delete physics_system;
	}
	// Destroy the factory
	delete Factory::sInstance;
	Factory::sInstance = nullptr;
}

void JoltPhysics::update(){
	for (auto cuerpo : cuerpos) {
		auto rb = std::get<0>(cuerpo);
		//auto [x, y, z] = rb->getEntity()->transformada->getPosition();
		auto cuerpoId = std::get<2>(cuerpo);
		if (!cuerpoId.IsInvalid() && rb && !rb->isStatic()) {
			Vec3 positionM = body_interface->GetCenterOfMassPosition(cuerpoId);
			Vec3 velocity = body_interface->GetLinearVelocity(cuerpoId);
			Vec3 position;
			Quat rotacion;
			body_interface->GetPositionAndRotation(cuerpoId,position,rotacion);
			
			//Vec3 position = body_interface->GetCenterOfMassPosition(cuerpoId);
			if (rb) {
				auto entidad = rb->getEntity();
				if (entidad) {
					entidad->transformada->setPosition(position.GetX(), position.GetY(), position.GetZ(), false);
					auto angulosEuler = rotacion.GetEulerAngles();
					entidad->transformada->setRotation(RadiansToDegrees(angulosEuler.GetX()), RadiansToDegrees(angulosEuler.GetY()), RadiansToDegrees(angulosEuler.GetZ()),false);
				}
				//DBG("Posicion=(%,%,%), Velocidad=(%,%,%)", position.GetX(), position.GetY(), position.GetZ(), velocity.GetX(), velocity.GetY(), velocity.GetZ());
			}
		}
	}
	physics_system->Update(Time::deltaTime(), 1, 1, &*temp_allocator, &*job_system);
}

void JoltPhysics::appendRigidBody(physics::RigidBodyComponent* rb){
	//Buscamos inicialmente el collider del cuerpo y si no lo encontramos no cargamos el cuerpo
	auto collider = rb->getEntity()->getComponent<Collider>();
	if (collider == 0) {
		return;
	}
	auto id=crearCuerpo(collider, rb);
	DBG("Nuevo collider, tenemos %", cuerpos.size());
	return;
	auto [x, y, z] = rb->getEntity()->transformada->getPosition();

	//Ahora buscamos si ya está añadido, si es así es una sustitución
	int i = 0;
	for (auto cuerpo : cuerpos) {
		auto rbT = std::get<0>(cuerpo);
		if(rbT==rb){
			auto bodyId = std::get<2>(cuerpo);
			if (!bodyId.IsInvalid()) {
				//body_interface->SetRestitution(cuerpoId, true);
				body_interface->SetObjectLayer(bodyId, rb->isStatic() ? Layers::NON_MOVING : Layers::MOVING);
				body_interface->SetPosition(bodyId, Vec3Arg(x, y, z), EActivation::Activate);
				//body_interface->Set(cuerpoId, Vec3Arg(x, y, z), EActivation::Activate);
				body_interface->SetAngularVelocity(bodyId, Vec3Arg(0, 0, 0));
				body_interface->SetLinearVelocity(bodyId, Vec3Arg(0, 0, 0));
				//body_interface->RemoveBody(bodyId);
				//body_interface->DestroyBody(bodyId);
				physics_system->OptimizeBroadPhase();
				return;
			}

			cuerpos.erase(cuerpos.begin() + i);
			break;
		}
		i++;
	}
//	auto collider = rb->getEntity()->getComponent<Collider>();
	BodyID cuerpoId;
	if (collider ) {
		//SphereShapeSettings esfera;
		//BoxShapeSettings caja(Vec3(x, y, z));
		cuerpoId = crearCuerpo(collider, rb);
		
	}
	cuerpos.push_back({ rb, collider,cuerpoId });
	physics_system->OptimizeBroadPhase();
	DBG("Nuevo cuerpo rígido, tenemos %", cuerpos.size());
	DBG("Posicion [%, %, %]", x,y,z);
}
void JoltPhysics::changeRigidBody(physics::RigidBodyComponent* rb){
	for (auto cuerpo : cuerpos) {
		auto rbC = std::get<0>(cuerpo);
		if (rbC == rb) {
			auto cuerpoId = std::get<2>(cuerpo);
			if (!cuerpoId.IsInvalid()) {
				switch (rb->getMode()){
					case physics::RigidBodyComponent::DINAMIC:
						body_interface->SetMotionType(cuerpoId, EMotionType::Dynamic, EActivation::Activate);
						body_interface->SetObjectLayer(cuerpoId, Layers::MOVING);
						break;
					default:
						body_interface->SetMotionType(cuerpoId, EMotionType::Static, EActivation::Activate);
						body_interface->SetObjectLayer(cuerpoId, Layers::NON_MOVING);
						break;
				}


			}
			return;
		}
	}
}
void JoltPhysics::appendCollider(Collider* c){
	physics::RigidBodyComponent* rb = c->getEntity()->getComponent<physics::RigidBodyComponent>();
	BodyID cuerpoId;
	if (rb) {
		auto id = crearCuerpo(c, rb);

		/*bool sinCuerpo = true;
		for (auto cuerpo : cuerpos) {
			auto rbT = std::get<0>(cuerpo);
			if (rbT == rb) {
				std::get<1>(cuerpo) = c;
				sinCuerpo = false;
				//cuerpoId = std::get<2>(cuerpo);
				break;
			}
		}
		if (sinCuerpo) {
			cuerpos.push_back({ rb,c,crearCuerpo(c, rb) });
		} /**/
		DBG("Nuevo collider, tenemos %", cuerpos.size());
	}
}
void JoltPhysics::changeCollider(Collider* c) {
	
	physics::RigidBodyComponent* rb = c->getEntity()->getComponent<physics::RigidBodyComponent>();
	if (rb) {
		for (auto cuerpo : cuerpos) {
			if (std::get<1>(cuerpo) == c) {
				switch (c->getTypeCollider()) {
				case Collider::BOX:
				{
					auto id = std::get<2>(cuerpo);
					auto [w, h, d] = ((BoxColliderComponent*)c)->getSize();
					w *= 0.5f;
					h *= 0.5f;
					d *= 0.5f;
					if (w < 0.06f) {
						w = 0.06f;
					}
					if (h < 0.06f) {
						h = 0.06f;
					}
					if (d < 0.06f) {
						d = 0.06f;
					}
					BoxShapeSettings boxS = BoxShapeSettings(Vec3(w, h, d));
					auto boxR = boxS.Create();
					if (boxR.IsValid()) {
						auto box = boxR.Get();
						body_interface->SetShape(id, box, true, EActivation::Activate);
					}
					auto [xC, yC ,zC]= ((BoxColliderComponent*)c)->getPosition();
					auto [x, y, z] = c->getEntity()->transform()->getPosition();
					body_interface->SetPosition(id, Vec3Arg(x+xC, y+yC, z+zC), EActivation::Activate);

				}
				break;
				}
				DBG("Encuentro el collider");
			}
		}
	}
}
void JoltPhysics::transformChanged(physics::RigidBodyComponent* rb){
	for (auto cuerpo : cuerpos) {
		auto rbC = std::get<0>(cuerpo);
		if (rbC == rb) {
			auto collider = std::get<1>(cuerpo);
			auto cuerpoId = std::get<2>(cuerpo);
			if (!cuerpoId.IsInvalid()) {
				auto [x, y, z] = rb->getEntity()->transformada->getPosition();
				auto [a, b, g] = rb->getEntity()->transformada->getRotation();
				auto [xC, yC, zC] = collider->getPosition();

				body_interface->SetPositionAndRotation(cuerpoId, Vec3Arg(x + xC, y + yC, z + zC), JPH::Quat::sEulerAngles(JPH::Vec3(a, b, g)), EActivation::Activate);
				//body_interface->SetRestitution(cuerpoId, true);
				
				body_interface->SetAngularVelocity(cuerpoId, Vec3Arg(0, 0, 0));
				body_interface->SetLinearVelocity(cuerpoId, Vec3Arg(0, 0, 0));

				//Vec3 velocity = body_interface->GetLinearVelocity(cuerpoId);
				
			}
			return;
		} else {
			auto cuerpoId = std::get<2>(cuerpo);
			//body_interface->SetRestitution(cuerpoId, true);
			if (!body_interface->IsActive(cuerpoId)) {
				body_interface->ActivateBody(cuerpoId);
			}
		}
	}
}
BodyID JoltPhysics::crearCuerpo(Collider* c, physics::RigidBodyComponent * rb) {
	//BodyCreationSettings sphere_settings(new SphereShape(0.5f), Vec3(x, y, z), Quat::sIdentity(), EMotionType::Dynamic, rb->isStatic() ? Layers::NON_MOVING : Layers::MOVING);
	//cuerpoId = body_interface->CreateAndAddBody(sphere_settings, EActivation::Activate);
	BodyID cuerpoId;
	switch (c->getTypeCollider()) {
		case Collider::BOX: 
		{
			auto [w, h, d] = ((BoxColliderComponent*)c)->getSize();
			auto [xC, yC, zC] = ((BoxColliderComponent*)c)->getPosition();
			auto [x, y, z] = rb->getEntity()->transformada->getPosition();
			w *= 0.5f;
			h *= 0.5f;
			d *= 0.5f;
			if (w < 0.06f) {
				w = 0.06f;
			}
			if (h < 0.06f) {
				h = 0.06f;
			}
			if (d < 0.06f) {
				d = 0.06f;
			}
			BoxShapeSettings boxS = BoxShapeSettings(Vec3(w, h, d));
			auto boxR = boxS.Create();
			if (boxR.IsValid()) {
				auto box = boxR.Get();
				
				BodyCreationSettings settings(box, Vec3(x + xC, y + yC, z + zC), Quat::sIdentity(), rb->isStatic() ? EMotionType::Static : EMotionType::Dynamic, rb->isStatic() ? Layers::NON_MOVING : Layers::MOVING);
				cuerpoId = body_interface->CreateAndAddBody(settings, EActivation::Activate);
				body_interface->SetRestitution(cuerpoId, 0);
			}
		}
		break;
		default:
			DBG("% -- %", (int)c->getType(), (int)Collider::BOX);
	}
	if (!cuerpoId.IsInvalid()) {
		cuerpos.push_back({ rb,c,cuerpoId });
	}
	return cuerpoId;
}
void JoltPhysics::pause(){
	//physics_system->Update
}

void JoltPhysics::resume(){
}


REGISTRAR_MODULO(JoltPhysics);