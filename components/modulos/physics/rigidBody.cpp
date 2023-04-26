#include "entity.h"
#include "rigidBody.h"

physics::RigidBody::RigidBody(Entity* entity, modules::graphics::Graphic* g, Component* p) {
	entidad = entity;
	graphic = g;
	/*DBG("Creamos un cuerpo Rígido");
	if (graphic != NULL && fisicas==NULL) {
		fisicas = graphic->getPhysics();
	}

	if (fisicas != NULL) {
		DBG("Tengo fisicas");
		fisicas->appendRigidBody(this);
	} else {
		DBG("NOOOO Tengo físicas");
	}/**/
}
