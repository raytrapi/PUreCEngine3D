#include "entity.h"

std::vector<Entity*> Entity::entidades;

Transform* Entity::transform() { 
	return transformada;
}
 