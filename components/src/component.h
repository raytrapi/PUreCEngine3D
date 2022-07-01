#ifndef _COMPONENT
#define _COMPONENT
#include "exportar.h"

#include <log.h>
#include "../../modules/src/module.h"
//#include
extern class Entity;
extern class modules::graphics::Graphic;
class EXPORTAR_COMPONENTE Component{
protected: 
	Entity* entidad = NULL;
	modules::graphics::Graphic* graphic = NULL;
	char* nombre=NULL;
	virtual void whenChargeEntity() {

	}
public:
	Component();
	~Component();
	Component(Entity* entity) {
		entidad = entity;
		//loadEntity();
	}
	void setEntity(Entity* entity) {
		entidad = entity;
		whenChargeEntity();
	}
	virtual void destroy() {};
	void setName(std::string name);
	void setGraphic(modules::graphics::Graphic* g) { graphic = g; };
};


#endif //_COMPONENT
