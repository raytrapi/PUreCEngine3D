#include "ray.h"

std::vector<collider::Hit> collider::Ray::trace(float xOrigin, float yOrigin, float zOrigin, float xDirection, float yDirection, float zDirection, float distance) {
	//Calculamos el punto final de nuestro rayo
	float modulo = sqrtf(xDirection * xDirection + yDirection * yDirection + zDirection * zDirection);
	float xFinal = xOrigin + sin(modulo > 0 ? xDirection / modulo : 0.f) * distance;
	float yFinal = yOrigin + sin(modulo > 0 ? yDirection / modulo : 0.f) * distance;
	float zFinal = zOrigin + sin(modulo > 0 ? zDirection / modulo : 0.f) * distance;


	//Cogemos todos los objetos con colisión
	std::vector<Collider*> objetos;
	for (auto it = Entity::entidades[Entity::defaultStack].begin(); it != Entity::entidades[Entity::defaultStack].end(); it++) {
		if ((*it)->isActive()) {
			std::vector<Collider*>* colisiones = (*it)->getComponents<Collider>();
			if (colisiones != NULL) {
				for (auto itC = colisiones->begin(); itC != colisiones->end(); itC++) {
					//Comprobamos el rayo colisiona con el objeto
					if ((*itC)->isCollisionRay(xOrigin, yOrigin, zOrigin, xFinal, yFinal, zFinal)) {
						objetos.push_back((*itC));
					}
				}
			}
		}

	}
	//=[Entity::COLLIDER];
	//DBG("He lanzado un rayo");
	DBG("Tenemos % objetos con colisión", objetos.size());

	return std::vector<Hit>();
}
