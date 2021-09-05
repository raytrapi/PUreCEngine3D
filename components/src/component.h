#ifndef _COMPONENT
#define _COMPONENT
#include "exportar.h"

#include <log.h>
#include "../../modules/src/module.h"
//#include
extern struct Entity;
extern class modules::graphics::Graphic;
class EXPORTAR_COMPONENTE Component{
protected: 
	Entity* entidad = NULL;
	modules::graphics::Graphic* graphic = NULL;
public:
	Component();
	virtual ~Component();
	Component(Entity* entity) {
		entidad = entity;
	}
	void setEntity(Entity* entity) {
		entidad = entity;
	}
};


#endif //_COMPONENT
