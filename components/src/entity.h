#ifndef _ENTITY
#define _ENTITY

#include "../../modules/graphic/motor.h"
#include "../modulos/shader/shader.h"
#include "../modulos/cameras/camera.h"
#include "../modulos/collider/collider.h"
//#include "../modulos/code/code.h"
#include "../modulos/renderables/renderable.h"
#include "../../modules/src/module.h"
#include "../../graphics/src/renderable/img.h"
#include "../../graphics/src/renderable/cube.h"
#include "../../graphics/src/renderable/mesh.h"
#include "transform.h"
#include "component.h"
#include "exportar.h"
#include <type_traits>
#include <map>
#include <vector>
#include "transform.h"
extern class Code;
namespace collider {
	extern class Ray;
}
struct EXPORTAR_COMPONENTE Entity {
	enum TIPO {
		RENDERABLE,
		SHADER,
		CAMERA,
		CODE,
		COLLIDER
	};
	enum TYPE_OPERATION { ALL, MOVE };
	int id = -1;
	friend collider::Ray;
	static std::vector<Entity*> entidades;
	std::vector<Component*> componentesOrden;
	std::map<Entity::TIPO,std::vector<Component *>> componentes;
	Transform* transformada;
	std::string nombre = "";
	std::map<std::string, std::string> texturas;
	bool active=true;
	bool actualizarRender = false;
public:
	enum EXPORTAR_COMPONENTE TYPE {
		EMPTY,
		IMG,
		CUBE,
		MESH
		/**/
	};
	Entity() {
		id = entidades.size();
		entidades.push_back(this);
		/*modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->addEntity(this);
		}/**/
		transformada = new Transform(this);
	}
	~Entity() {
		for (auto itr = componentes.begin(); itr != componentes.end(); itr++) {
			for (int i = 0; i < itr->second.size(); i++) {
				try {
					//TODO: REVISAR EL BORRADO
					Component* c = itr->second[i];
					if (c) {
						//delete c;
						itr->second[i] = NULL;
					}

					//delete ();
				} catch (std::exception e) {
					utiles::Log::debug(e.what());
				}
			}
			itr->second.clear();
		}
		componentes.clear();
		bool seguir = true;
		for (auto itr = entidades.begin(); itr != entidades.end() && seguir; itr++) {
			if (*itr == this) {
				/*modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
				if (g) {
					//g->removeEntity(*itr);
				}/**/
				entidades.erase(itr);
				//itr = entidades.begin(); //Reiniciamos para evitar fallos
				break;
				seguir = false;
			}
		}
		delete transformada;
	};
	static void destroy() {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		auto itr = entidades.begin();
		while (itr!=entidades.end()){
			
			if (g) {
				g->removeEntity(*itr);
			}/**/
			Entity* e = *itr;
			delete e;
			itr = entidades.begin();
		}

		entidades.clear();
	}

	template <class T>
	std::vector<T*>* getComponents();
	/**
	* Get the List of components in the entity, but return if the type of renderable is K
	*/
	template <class T,class K>
	std::vector<T*>* getComponents();
	/**
	* 	  Get the first component that is of the same class than T
	*/
	template <class T>
	T* getComponent();
	template <class T>
	T* addComponent();

	template <Entity::TYPE Type>
	static Entity* create();
	static void startCodes();

	int getId() { return id; };

	/**
	* Actualiza el componte gráfico 
	*/
	virtual void update(TYPE_OPERATION type=MOVE) {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->updateEntity(this, (modules::graphics::Graphic::TYPE_OPERATION)type);
		}
	}
	/**
	* 	  Llama a los métodos update de cada componente Code
	*/
	static void updateCode();
	/**
	* 	  Llama a los métodos preUpdate de cada componente Code
	*/
	static void preUpdateCode();
	Transform* transform();
	void setName(std::string name) {
		nombre = name;
	}
	std::string getName() {
		return nombre;
	}
	/**
	*  Activa o desactiva la entidad para su representación  
	*/
	void setActive(bool active) {
		this->active = active;
	}
	bool isActive() {
		return active;
	}
	void setRenderUpdatable();
};

template<class T>
inline std::vector<T *>* Entity::getComponents() {
	//std::vector<T*> componente;
	if (std::is_same<T, Shader>::value) {
		return (std::vector<T*>*) &componentes[SHADER];
	}else if (std::is_same<T, Camera>::value) {
		return (std::vector<T*>*) &componentes[CAMERA];
	} else if (std::is_same<T, Code>::value) {
		return (std::vector<T*>*) &componentes[CODE];
	} else if (std::is_base_of<Collider, T>::value) {
		return (std::vector<T*>*) & componentes[COLLIDER];
	} else if (std::is_same<T, RenderableComponent>::value) {
		//TODO: OJO, aquí devolvemos todos los renderables no sólo el tipo que me piden por ejemplo si pido img me devuelve todo, incluso los mesh
		return (std::vector<T*>*) &componentes[RENDERABLE];
	}
	return NULL;
}
template <class T>
inline T* Entity::getComponent() {
	//std::vector<T*> componente;
	if (std::is_same<T, Shader>::value) {
		if (componentes[SHADER].size() > 0) {
			return (T*)componentes[SHADER][0];
		}
	} else if (std::is_same<T, Camera>::value) {
		if (componentes[CAMERA].size() > 0) {
			return (T*) componentes[CAMERA][0];
		}
	} else if (std::is_same<T, Code>::value) {
		if (componentes[CODE].size() > 0) {
			return (T*)componentes[CODE][0];
		}
	} else if (std::is_base_of<Collider, T>::value) {
		if (componentes[COLLIDER].size() > 0) {
			return (T*)componentes[COLLIDER][0];
		}
	} else if (std::is_same<T, RenderableComponent>::value) {
		if (componentes[RENDERABLE].size() > 0) {
			return (T*)componentes[RENDERABLE][0];
		}
	}
	return NULL;
}
template <class T, class K>
std::vector<T*>* Entity::getComponents() {
	//std::vector<T*> componente;
	if (std::is_same<T, Shader>::value) {
		return (std::vector<T*>*) & componentes[SHADER];
	} else if (std::is_same<T, Camera>::value) {
		return (std::vector<T*>*) & componentes[CAMERA];
	} else if (std::is_same<T, Code>::value) {
		return (std::vector<T*>*) & componentes[CODE];
	} else if (std::is_base_of<renderable::Object, K>::value) {
		//TODO:: Esto está mál hay que cambiar para que devuelva solo los timpos que pide
		return (std::vector<T*>*) & componentes[RENDERABLE];
	} else if (std::is_same<T, RenderableComponent>::value) {
		//TODO: OJO, aquí devolvemos todos los renderables no sólo el tipo que me piden por ejemplo si pido img me devuelve todo, incluso los mesh
		return (std::vector<T*>*) & componentes[RENDERABLE];
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
		//modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		//Quito lo de abajo ya que muevo la parte de notificación de shader a el componente shader
		/*if (g) {
			//g->getEntity(this)->
			((Shader*)comp)->setEntity(g->getEntity(this));
		}/**/
	} else if (std::is_same<T, Camera>::value) {
		c = new T();
		comp = (Component*)c;
		componentes[CAMERA].push_back(comp);
//		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();

	} else if (std::is_base_of<Collider, T>::value) {
		c = new T();
		comp = (Component*)c;
		componentes[COLLIDER].push_back(comp);

	} else if (std::is_same<T, Code>::value) {
		utiles::Log::debug("Cargamos un codigo");
		c = new T();
		utiles::Log::debug("Enlazamos la entidad");
		//c->setEntity(this);

		comp = (Component*)c;
		componentes[CODE].push_back(comp);
		comp->setEntity(this);
		//		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();

	} else if (std::is_base_of<renderable::Object, T>::value) {
		c = new T();
		comp = new RenderableComponent((renderable::Object*)c);
		componentes[RENDERABLE].push_back(comp);
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		
		if (std::is_same<T, renderable::Img>::value) {
			//Le añadimos ademas el componente Shader
			Shader* shaders = addComponent<Shader>();
			shaders->loadShader("shaders/vertex_texture.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_texture.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
			/*shaders->loadShader("shaders/vertex_basic.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_solid_color.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);*/
			shaders->compileShader();
		}else if (std::is_same<T, renderable::Cube>::value) {
			//Le añadimos ademas el componente Shader
			Shader* shaders = addComponent<Shader>();
			//shaders->loadShader("shaders/vertex_basic.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_solid_color_light.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
			shaders->compileShader();
			//g->updateEntity(this);
		} else if (std::is_same<T, renderable::Mesh>::value) {
			//Le añadimos ademas el componente Shader
			Shader* shaders = addComponent<Shader>();
			LOG_DBG("Cargamos los saders shaders/vertex_basic_mesh.glsl y shaders/fragment_texture.glsl");
			shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_texture.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
			shaders->compileShader();
			//g->updateEntity(this);
		}
		if (g) {
			g->addEntity(this);
		}/**/
		/**/
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
	modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
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
		if (g) {
			//g->addEntity(e);
		}
		e->addComponent<renderable::Cube>();
		break;
	case Entity::MESH:
		e = new Entity();
		e->addComponent<renderable::Mesh>();
		break;
	default:
		break;
	}
	return e;
}


#endif // !_ENTITY