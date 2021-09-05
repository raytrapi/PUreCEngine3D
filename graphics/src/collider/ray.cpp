#include "ray.h"

std::vector<collider::Hit> collider::Ray::trace(float xOigin, float yOigin, float zOigin, float xTarget, float yTarget, float zTarget, float distance) {
	//Cogemos todos los objetos con colisión
	std::vector<Collider*> objetos;
	for (auto it = Entity::entidades.begin(); it != Entity::entidades.end(); it++) {
		if ((*it)->isActive()) {
			std::vector<Collider*>* colisiones = (*it)->getComponents<Collider>();
			if (colisiones != NULL) {
				for (auto itC = colisiones->begin(); itC != colisiones->end(); itC++) {
					objetos.push_back((*itC));
				}
			}
		}

	}
	//=[Entity::COLLIDER];
	//DBG("He lanzado un rayo");
	DBG("Tenemos % objetos con colisión", objetos.size());
	return std::vector<Hit>();
}
