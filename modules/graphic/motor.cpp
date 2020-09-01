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
	for (auto itr = entities.begin(); itr != entities.end(); itr++) {
		if (entity == (*itr)) {
			entities.erase(itr);
			delete (*itr);
			return;
		}
	}
}

void modules::graphics::Graphic::removeEntities() {
	bool seguir = true;
	for (auto itr = entities.begin(); itr != entities.end() && seguir; itr++) {
		seguir = false;
		entities.erase(itr);
		delete (*itr);
	}
}

void modules::graphics::Graphic::addOnFocus(void(*callback)(bool)) {
	onFocus.push_back(callback);
}

void modules::graphics::Graphic::addOnFocus(Tape* juego) {
	onFocusTapes.push_back(juego);
}
void modules::graphics::Graphic::removeOnFocus(Tape* juego) {
	int pos = -1;
	for (int i = 0; i < onFocusTapes.size(); i++) {
		if (onFocusTapes[i] == juego) {
			pos = i;
		}
	}
	if (pos != -1) {
		onFocusTapes.erase(onFocusTapes.begin()+pos);
	}
}


std::vector<void(*)(bool)> modules::graphics::Graphic::onFocus;
std::vector<modules::Tape*> modules::graphics::Graphic::onFocusTapes;
bool modules::graphics::Graphic::open = false;