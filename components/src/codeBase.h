#ifndef __CODEBASE
#define __CODEBASE
#include "exportar.h"
#include <log.h>
#include <vector>
//#include "../modulos/renderables/renderable.h"
//#include "../../graphics/src/renderable/cube.h"
#include "entity.h"
//extern class Entity;
class EXPORTAR_COMPONENTE CodeBase {
	Entity* entidad;
	
public:
	enum TYPE_OPERATION {
		ALL,
		MOVE
	};
	virtual void preUpdate() {};
	virtual void update() {
		//utiles::Log::debug("Actualizo el Objeto");
	};
	void setEntity(Entity* laEntidad);
	virtual void start() {};
	virtual void destroy() {};
	template<class T>
	std::vector<T*>* getComponents();
	template<class T>
	T* getComponent();
	void refresh() {
		refresh(TYPE_OPERATION::MOVE);
	};
	void refresh(TYPE_OPERATION type) { 
		entidad->update((Entity::TYPE_OPERATION)type); 
	};

	Transform * transform() {
		return entidad->transform();
	};
	 
	
};

template<class T>
inline std::vector<T*>* CodeBase::getComponents() {
	if (entidad) {
		return entidad->getComponents<T>();
	} else {
		return NULL;
	}
}
template<class T>
inline T* CodeBase::getComponent() {
	if (entidad) {
		return entidad->getComponent<T>();
	} else {
		return NULL;
	}
}
inline 
void CodeBase::setEntity(Entity* laEntidad) {
	this->entidad = laEntidad;
}

#endif // !__CODEBASE

