#include "motor.h"

void modules::graphics::Graphic::addEntity(void* entity) {
	int noEncontre = true;
	for (auto itr = entities.begin(); itr != entities.end() && noEncontre; itr++) {
		if (entity == (*itr)) {
			noEncontre = false;
		}
	}
	if (noEncontre) {
		entities.push_back(entity);
	}
	updateEntity(entity);
}

void modules::graphics::Graphic::removeEntity(void* entity) {
	bool seguir = true;
	for (auto itr = entities.begin(); itr != entities.end() && seguir; itr++) {
		if (entity == (*itr)) {
			seguir = false;
			entities.erase(itr);
		}
	}
}
