#include "entity.h"
#include "../../components/modulos/code/code.h"
#include "../../graphics/src/modelos_graficos/obj.h"
#include "../../graphics/src/modelos_graficos/model.h"

std::map<unsigned, std::vector<Entity*>> Entity::entidades;
unsigned Entity::defaultStack = 0;

  
Transform* Entity::transform() { 
	return transformada;
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
void Entity::updateCode() {
	for (auto itrE = entidades[defaultStack].begin(); itrE != entidades[defaultStack].end(); itrE++) {
		if ((*itrE)->isActive()) {
			std::vector<Code*>* codigos = (std::vector<Code*>*)(*itrE)->getComponents<Code>();
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
}void Entity::setRenderUpdatable() {
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


void modules::graphics::Graphic::updateEntities(unsigned stack, modules::graphics::Graphic::TYPE_OPERATION type) {
	std::vector<Entity*> entidades = Entity::getEntities(stack);
	for (auto entidad : entidades) {
		if (entidad->isUpdatingRender()) {
			updateEntity(entidad, type);
		}
	}
	
}

void collider::Collider::recalcular() {
	cX = entidad->transform()->position()->x;
	cY = entidad->transform()->position()->y;
	cZ = entidad->transform()->position()->z;
};


modules::graphics::Graphic* Entity::graphic = NULL;