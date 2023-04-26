#ifndef _COMPONENT
#define _COMPONENT
#include "exportar.h"
#include <log.h>
#include "../../utilidades/supervisor/src/reflexivo.h"
#include "../../modules/src/module.h"


enum TYPE_COMPONENT {
	GENERIC,
	CODE
};

//#include
extern class Entity;
extern class modules::graphics::Graphic;
class EXPORTAR_COMPONENTE Component{
	bool activo = true;
protected: 
	Entity* entidad = NULL;
	modules::graphics::Graphic* graphic = NULL;
	char* nombre=NULL;
	virtual void whenChargeEntity() {

	}
	Component* padre=NULL;
	std::vector<Parametro> propiedades;
	virtual void cargarPropiedades() {  };
	void addPropiedad(Parametro p) {
		propiedades.push_back(p);
	};
public:
	Component();
	~Component();
	Component(Entity* entity,modules::graphics::Graphic* g, Component* p=NULL) {
		entidad = entity;
		graphic = g;
		padre = p;
		//loadEntity();
	}
	
	virtual TYPE_COMPONENT componentType() { return GENERIC; };
	void setEntity(Entity* entity) {
		entidad = entity;
		whenChargeEntity();
	}
	Entity* getEntity() {
		return entidad;
	}
	virtual void destroy() {};
	void setName(std::string name);
	std::string getName();
	void setGraphic(modules::graphics::Graphic* g) { graphic = g; };
	void setActive(bool active) { this->activo = active; };
	bool isActive() { return activo; };
	
	Component* getParent() {
		return padre;
	};
	void setParent(Component* p) {
		padre = p;
	}
	template<class T>
	T* addComponent();
	std::vector<Parametro> getProperties() { return propiedades; };


	virtual void transformChanged() {};
};

#define PUBLIC() 
#define EDITABLE()\
	protected:\
	void loadParameters() override;


#endif //_COMPONENT
