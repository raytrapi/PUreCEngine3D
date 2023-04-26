#ifndef __CODEBASE
#define __CODEBASE
#include "exportar.h"
#include "estructurasCodigo.h"
#include <log.h>
#include <vector>
//#include "../modulos/renderables/renderable.h"
//#include "../../graphics/src/renderable/cube.h"
#include "../../utilidades/global/input.h"
#include "entity.h"
#include "../../utilidades/supervisor/src/reflexivo.h"
//extern class Entity;
class EXPORTAR_COMPONENTE CodeBase {
	modules::graphics::Graphic* motorGrafico;
	Entity* entidad=NULL;
	void* padre=NULL; //Objeto de usuario que contiene el código
	Input* input=NULL;
	Global* global = NULL;
	std::vector<Propiedad> propiedades;
protected:
	std::vector<Parametro> parametros;
	virtual void loadParameters() {  };
	void addParameter(Parametro p) {
		parametros.push_back(p);
	};
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
	void setParent(void* parent);
	void* getParent();
	Entity* getEntity();
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

	Transform * getTransform() {
		return entidad->transform();
	};
	 
	Input* getInput() {
		return input;
	}
	void setInput(Input* i) {
		input = i;
	}
	Global* getGlobal() {
		return global;
	}
	void setGlobal(Global* g) {
		global = g;
	}
	modules::graphics::Graphic* getGraphic() { return motorGrafico; }
	void setGraphic(modules::graphics::Graphic* g) { motorGrafico = g; }


	/*Esta parte sirve solo para el editor*/

	std::vector<Propiedad> getProperties();
	/**
	* carga una propiedad en el editor
	* @param void* variable variable que se presentará en el editor
	* @param const char* nombre Nombre que se mostrará en el editor
	*/
	void setProperty(void* variable, const char* nombre);

	std::vector<Parametro> getParameters() { return parametros; };
	void init() { loadParameters(); };
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

inline void CodeBase::setParent(void* parent) {
	padre = parent;
}

inline void* CodeBase::getParent() {
	return padre;
}

inline Entity* CodeBase::getEntity() {
	return entidad;
}

inline std::vector<Propiedad> CodeBase::getProperties(){
	return propiedades;
}

inline void CodeBase::setProperty(void* variable, const char* nombre){
	propiedades.push_back({ nombre,variable });
}

#endif // !__CODEBASE

