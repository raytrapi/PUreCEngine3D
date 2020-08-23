#ifndef _ENTITY
#define _ENTITY

#include "../../modules/graphic/motor.h"
#include "../modulos/shader/shader.h"
#include "../modulos/renderables/renderable.h"
#include "../../modules/src/module.h"
#include "../../graphics/src/renderable/img.h"
#include "component.h"
#include "exportar.h"
#include <type_traits>
#include <map>
#include <vector>
struct EXPORTAR_COMPONENTE Entity {
	enum TIPO {
		RENDERABLE,
		SHADER
	};
	int id = -1;
	static std::vector<Entity*> entidades;
	std::vector<Component*> componentesOrden;
	std::map<Entity::TIPO,std::vector<Component *>> componentes;
public:
	enum EXPORTAR_COMPONENTE TYPE {
		EMPTY,
		IMG,
		CUBE
	};
	Entity() {
		id = entidades.size();
		entidades.push_back(this);
		/*modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->addEntity(this);
		}/**/
	}
	~Entity() {
		for (auto itr = componentes.begin(); itr != componentes.end(); itr++) {
			for (int i = 0; i < itr->second.size(); i++) {
				delete itr->second[i];
			}
			itr->second.clear();
		}
		componentes.clear();
	};
	static void destroy() {
		for (auto itr = entidades.begin(); itr != entidades.end(); itr++) {
			modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
			if (g) {
				g->removeEntity(*itr);
			}/**/
			delete (*itr);
			
		}

		entidades.clear();
	}
	template <class T>
	std::vector<Component*>* getComponent();
	template <class T>
	T* addComponent();

	template <Entity::TYPE Type>
	static Entity* create();

	int getId() { return id; };

};

template<class T>
inline std::vector<Component *>* Entity::getComponent() {
	std::vector<Component*> componente;
	if (std::is_same<T, Shader>::value) {
		return &componentes[SHADER];
	}
	if (std::is_same<T, RenderableComponent>::value) {
		//TODO: OJO, aquí devolvemos todos los renderables no sólo el tipo que me piden por ejemplo si pido img me devuelve todo, incluso los mesh
		return &componentes[RENDERABLE];
	}
	return NULL;
}

template<class T>
inline T* Entity::addComponent() {
	T* c = NULL;
	Component* comp = NULL;
	if (std::is_same<T, Shader>::value) {
		c = new T();
		comp = (Component*)c;
		componentes[SHADER].push_back(comp);
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		//Quito lo de abajo ya que muevo la parte de notificación de shader a el componente shader
		/*if (g) {
			//g->getEntity(this)->
			((Shader*)comp)->setEntity(g->getEntity(this));
		}/**/
	} else if (std::is_base_of<renderable::Object, T>::value) {
		c = new T();
		comp = new RenderableComponent((renderable::Object*)c);
		componentes[RENDERABLE].push_back(comp);
		modules::graphics::Graphic *g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->addEntity(this);
		}/**/
	}
	if (c != NULL) {
		comp->setEntity(this);
		//TODO: ¿ACTUALIZAR AL COMPONENTE GRÁFICO?
		componentesOrden.push_back(comp);
	}
	return c;
}

template<Entity::TYPE Type>
inline Entity* Entity::create() {
	Entity* e = NULL;
	switch (Type) {
	case Entity::EMPTY:
		e = new Entity();
		break;
	case Entity::IMG:
		e = new Entity();
		break;
	case Entity::CUBE:
		e = new Entity();
		break;
	default:
		break;
	}
	return e;
}


#endif // !_ENTITY