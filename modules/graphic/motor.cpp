#include "motor.h"
#include "../../components/src/entity.h"
//#include "../../vendors/glfw/nuklear_glfw_gl4.h"
#include "../general.h"
void modules::graphics::Graphic::addEntity(void* entity) {
	/*int noEncontre = true;
	std::vector<Entity*> entities = Entity::getEntities();
	for (auto itr = entities.begin(); itr != entities.end() && noEncontre; itr++) {
		if (entity == (*itr)) {
			noEncontre = false;
		}
	}
	if (noEncontre) {
		entities.push_back(entity);
	}/**/
	updateEntity(entity);
}

void modules::graphics::Graphic::removeEntity(void* entity) {
	/*std::vector<Entity*> entities = Entity::getEntities();
	for (auto itr = entities.begin(); itr != entities.end(); itr++) {
		if (entity == (*itr)) {
			entities.erase(itr);
			//delete (*itr);
			return;
		}
	}/**/
}

void modules::graphics::Graphic::removeEntities() {
	/*bool seguir = true;
	for (auto itr = entities.begin(); itr != entities.end() && seguir; itr++) {
		
		seguir = false;
		//entities.erase(itr);
		delete (*itr);
	}
	entities.clear();/**/
}
void modules::graphics::Graphic::removeAll() {
	removeEntities();
	removeAllFocus();
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

void modules::graphics::Graphic::removeAllFocus() {
	onFocusTapes.clear();
}

/*void  modules::graphics::Graphic::loadTexture(std::string name, std::string path, TYPE_TEXTURE type) {
	switch (type) {
		case modules::graphics::Graphic::NONE:
			break;
		case modules::graphics::Graphic::IMG:
			break;
		default:
			break;
	}
	//if(texturas.e)
	//texturas[name] = new Texture();
}/**/

std::vector<void(*)(bool)> modules::graphics::Graphic::onFocus;
std::vector<modules::Tape*> modules::graphics::Graphic::onFocusTapes;
bool modules::graphics::Graphic::open = false;

bool modules::graphics::Graphic::controlarRedimension = false;






//std::vector<std::tuple<Key, std::function<void(Key)>, bool>> Input::controlTeclasPulsadas;
//Input* Input::instancia;