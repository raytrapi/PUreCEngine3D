#include "entity.h"
#include <../../utilidades/timer/timer.h>
#include "../../components/modulos/code/code.h"
#include "../../graphics/src/modelos_graficos/obj.h"
#include "../../graphics/src/modelos_graficos/model.h"

std::map<unsigned, std::vector<Entity*>> Entity::entidades;
unsigned Entity::defaultStack = 0;
std::vector<unsigned> Entity::entidadesStacks; 
Entity* Entity::instancia = NULL;
  
Transform* Entity::transform() { 
	return transformada;
}  

bool Entity::decreaseLife() {
	if (vida > -1) {
		vida -=  Time::deltaTime();
		if (vida <= 0) {
			vida = 0;
			return true;
		}
	}
	return false;
};
void Entity::setLifeTime(float miliseconds) {
	vida = miliseconds;
}
bool Entity::updateLifeTime(unsigned stack) {
	bool muertos = false;
	for (int i = 0; i < entidades[stack].size(); i++) {
		muertos =muertos || entidades[stack][i]->decreaseLife();
	}
	return muertos;
}
void Entity::destroyDead(unsigned stack) {
	auto entidadesT = &entidades[stack];
	for (int i = 0; i < entidadesT->size(); i++) {
		if (entidadesT->operator[](i)->vida == 0) {
			entidadesT->operator[](i)->erase();
			
			i--;
		}
	}
}
/**
* Call start method for all Code components 
*/
void Entity::startCodes(unsigned stack,Input *input) { 
	//Coge todos los componentes de todas las entidades y bucas aquellos componentes que sean Codigo. Luego llama al método Start;
	for (int i = 0; i < entidades[stack].size(); i++) { 
		std::vector<Code*> *codigos =  entidades[stack][i]->getComponents<Code>();
		for (int j = 0; j < codigos->size(); j++) {
			codigos->operator[](j)->setInput(input);
			codigos->operator[](j)->start(); 
		}
	}
	
}
void Entity::stopCodes(unsigned stack) {
	//Coge todos los componentes de todas las entidades y bucas aquellos componentes que sean Codigo. Luego llama al método Start;
	for (int i = 0; i < entidades[stack].size(); i++) {
		std::vector<Code*>* codigos = entidades[stack][i]->getComponents<Code>();
		for (int j = 0; j < codigos->size(); j++) {
			codigos->operator[](j)->destroy();
		}
	}

}
void Entity::updateCode() {
	
	auto lasEntidades = entidades[defaultStack];//Hacemos una copia para evitar que falle si el update de código añade o quita entidades

	for (auto entidad:lasEntidades) {
		if (entidad->isActive()) {
			std::vector<Code*>* codigos = (std::vector<Code*>*)entidad->getComponents<Code>();
			if (codigos != NULL) {
				for (auto itrC = codigos->begin(); itrC != codigos->end(); itrC++) {
					(*itrC)->update();
					
				}
			}
			/*if ((*itrE)->actualizarRender) {
				(*itrE)->actualizarRender = false;
				(*itrE)->update();
			}/**/
			
		}
	}
}

void Entity::setRenderUpdatable() {
	actualizarRender = true;
}
void Entity::preUpdateCode(){
	for (auto itrE = entidades[defaultStack].begin(); itrE != entidades[defaultStack].end(); itrE++) {
		if ((*itrE)->isActive()) {
			std::vector<Code*>* codigos = (std::vector<Code*>*)(*itrE)->getComponents<Code>();
			if (codigos != NULL) {
				for (auto itrC = codigos->begin(); itrC != codigos->end(); itrC++) {
					(*itrC)->preUpdate();
				}
			}
		}
	}

}
void Entity::erase() {
	graphic->removeEntity(this);
	delete this;

};
void Entity::clear() {
	for (auto entidad : entidades) {
		for (auto ent : entidad.second) {
			for (auto componente : ent->componentesOrden) {
				delete componente;
			}
			ent->componentesOrden.clear();
			ent->componentes.clear();
			delete ent;
		}
	}
	entidades.clear();
	entidadesStacks.clear();
	idEntidadMax = 0;
	//std::vector<Component*> componentesOrden;
	//std::map<Entity::TIPO, std::vector<Component*>> componentes;
};
std::vector<Component*>* Entity::getComponents() {
	return &this->componentesOrden;
}



void modules::graphics::Graphic::updateEntities(unsigned stack, modules::graphics::Graphic::TYPE_OPERATION type) {
	std::vector<Entity*> entidades = Entity::getEntities(stack);
	for (auto entidad : entidades) {
		if (entidad->isActive() && entidad->isUpdatingRender()) {
			updateEntity(entidad, type);
		}
	}
	
}

void Collider::recalcular() {
	cX = entidad->transform()->position()->x;
	cY = entidad->transform()->position()->y;
	cZ = entidad->transform()->position()->z;
};



modules::graphics::Graphic* Entity::graphic = NULL;
unsigned int Entity::idEntidadMax = 0;