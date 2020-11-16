#ifndef _COMPONENT
#define _COMPONENT
#include "exportar.h"
#include <log.h>
//#include
extern struct Entity;

class EXPORTAR_COMPONENTE Component{
protected: 
	Entity* entidad = NULL;
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