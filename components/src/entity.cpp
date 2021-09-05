#include "entity.h"
#include "../modulos/code/code.h"
std::vector<Entity*> Entity::entidades;
  
Transform* Entity::transform() { 
	return transformada;
}
/**
* Call start method for all Code components 
*/
void Entity::startCodes() {
	//Coge todos los componentes de todas las entidades y bucas aquellos componentes que sean Codigo. Luego llama al método Start;
	for (int i = 0; i < entidades.size(); i++) { 
		std::vector<Code*> *codigos =  entidades[i]->getComponents<Code>();
		for (int j = 0; j < codigos->size(); j++) {
			codigos->operator[](j)->start(); 
		}
	}
	
}
void Entity::updateCode() {
	for (auto itrE = entidades.begin(); itrE != entidades.end(); itrE++) {
		if ((*itrE)->isActive()) {
			std::vector<Code*>* codigos = (std::vector<Code*>*)(*itrE)->getComponents<Code>();
			if (codigos != NULL) {
				for (auto itrC = codigos->begin(); itrC != codigos->end(); itrC++) {
					(*itrC)->update();
					
				}
			}
			if ((*itrE)->actualizarRender) {
				(*itrE)->actualizarRender = false;
				(*itrE)->update();
			}
			
		}
	}
}void Entity::setRenderUpdatable() {
	actualizarRender = true;
}
void Entity::preUpdateCode(){
	for (auto itrE = entidades.begin(); itrE != entidades.end(); itrE++) {
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