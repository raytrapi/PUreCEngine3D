#ifndef _ENTITY
#define _ENTITY

#include "../../modules/graphic/motor.h"
#include "../modulos/shader/shader.h"
#include "../modulos/cameras/camera.h"
#include "../modulos/collider/collider.h"
#include "../modulos/audio/audio.h"
//#include "../modulos/code/code.h"
#include "../modulos/renderables/renderable.h"
#include "../../modules/src/module.h"
#include "../../graphics/src/renderable/img.h"
#include "../../graphics/src/renderable/cube.h"
#include "../../graphics/src/renderable/mesh.h"
#include "../../graphics/src/renderable/line.h"

#include "transform.h"
#include "component.h"
#include "exportar.h"
#include <type_traits>
#include <map>
#include <vector>
#include "transform.h"
extern class Code;
namespace renderable {
	extern class Text;
}
namespace collider {
	extern class Ray;
}
struct EXPORTAR_COMPONENTE Entity {
	enum TIPO {
		RENDERABLE,
		SHADER,
		CAMERA,
		CODE,
		COLLIDER,
		AUDIO
	};
	enum TYPE_OPERATION { ALL, MOVE };
	int id = -1;
	friend collider::Ray;
	static std::map<unsigned,std::vector<Entity*>> entidades;
	static unsigned defaultStack;
	std::vector<Component*> componentesOrden;
	std::map<Entity::TIPO,std::vector<Component *>> componentes;
	Transform* transformada;
	Entity* padre = NULL;
	unsigned pila = 0;
	//std::vector<Entity*> hijos;
	std::string nombre = "";
	std::map<std::string, std::string> texturas;
	bool active=true;
	bool actualizarRender = false;

	bool actualizarVertices = true;
	bool actualizarTextura = true;
	static modules::graphics::Graphic* graphic;
public:
	enum EXPORTAR_COMPONENTE TYPE {
		EMPTY,
		IMG,
		CUBE,
		MESH
		/**/
	};
	Entity(unsigned stack=0) {
		id = entidades.size();
		pila = stack;
		entidades[stack].push_back(this);
		
		/*modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->addEntity(this);
		}/**/
		transformada = new Transform(this);
	}
	~Entity() {
		//componentes.clear();
		DBG("Borramos entidad");
		for (int i = 0;i< componentesOrden.size(); i++) {
			delete componentesOrden[i];
		}
		componentesOrden.clear();
		
		/*for (auto itr = componentes.begin(); itr != componentes.end(); itr++) {
			for (int i = 0; i < itr->second.size(); i++) {
				try {
					//TODO: REVISAR EL BORRADO
					Component* c = itr->second[i];
					if (c) {
						delete c;
						//c->destroy();
						itr->second[i] = NULL;
					}

					//delete ();
				} catch (std::exception e) {
					utiles::Log::debug(e.what());
				}
			}
			itr->second.clear();
		}*/
		//componentes.clear();
		bool seguir = true;
		delete transformada;
		
		/*for (auto itr = entidades.begin(); itr != entidades.end() && seguir; itr++) {
			if (*itr == this) {
				entidades.erase(itr);
				//itr = entidades.begin(); //Reiniciamos para evitar fallos
				break;
				seguir = false;
			}
		}/**/
	};
	void setGraphic(modules::graphics::Graphic* g) {
		graphic = g;
	}
	static void destroy() {

		//modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (graphic!=NULL) {
			for (auto entidades : Entity::entidades) {
				for (auto entidad : entidades.second) {
					graphic->removeEntity(entidad);
				}
			}
			/*auto itr = entidades.begin();
			while (itr != entidades.end()) {
				g->removeEntity(*itr);
				//delete (*itr);
				itr++;
			}/**/
		}

		entidades.clear();
	}
	static std::vector<Entity*> getEntities(unsigned stack = 0) { return entidades[stack]; }
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
	template <class T>
	T* addComponent(Component* component);
	template <class T>
	bool has();
	template <Entity::TYPE Type>
	static Entity* create(unsigned stack=0);
	static void startCodes(unsigned stack=0, Input *input=NULL);

	int getId() { return id; };

	/**
	* Actualiza el componte gráfico 
	*/
	virtual void update(TYPE_OPERATION type=MOVE) {
		//modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (graphic) {
			graphic->updateEntity(this, (modules::graphics::Graphic::TYPE_OPERATION)type);
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
	void setUpdatingRender(bool updating) {
		actualizarRender = updating;
	}
	bool isUpdatingRender() {
		if (actualizarRender) {
			actualizarRender = false;
			return true;
		}
		return false;
	}
	bool isUpdatingVertex() {
		if (actualizarVertices) {
			actualizarVertices = false;
			return true;
		}
		return false;
	}
	void setUpdatingVertex(bool updating) {
		actualizarVertices = updating;
	}
	bool isUpdatingTexture() {
		if (actualizarTextura) {
			actualizarTextura = false;
			return true;
		}
		return false;
	}
	void setUpdatingTexture(bool updating) {
		actualizarTextura = updating;
	}
	void setRenderUpdatable();
	//void loadOBJ(const char* file, float directioY = -1.f);
	void setParent(Entity* e) { padre = e; e->appendChild(this); };
	void removeParent() {
		padre->removeChild(this);
		padre = NULL;
	}
	Entity* getParent() { return padre; };
	void appendChild(Entity* child) {
		transformada->appendChild(child);
	}
	void removeChild(Entity* child){
		transformada->removeChild(child);
		
	}
};

template<class T>
inline std::vector<T *>* Entity::getComponents() {
	//std::vector<T*> componente;
	if (std::is_same<T, RenderableComponent>::value) {
		//TODO: OJO, aquí devolvemos todos los renderables no sólo el tipo que me piden por ejemplo si pido img me devuelve todo, incluso los mesh
		return (std::vector<T*>*) & componentes[RENDERABLE];
	}else if (std::is_same<T, Shader>::value) {
		return (std::vector<T*>*) &componentes[SHADER];
	}else if (std::is_same<T, Camera>::value) {
		return (std::vector<T*>*) &componentes[CAMERA];
	} else if (std::is_same<T, Code>::value) {
		return (std::vector<T*>*) &componentes[CODE];
	} else if (std::is_base_of<collider::Collider, T>::value) {
		return (std::vector<T*>*) & componentes[COLLIDER];
	} else if (std::is_same<T, Audio>::value) {
		return (std::vector<T*>*) & componentes[AUDIO];
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
	} else if (std::is_base_of<collider::Collider, T>::value) {
		if (componentes[COLLIDER].size() > 0) {
			return (T*)componentes[COLLIDER][0];
		}
	} else if (std::is_same<T, RenderableComponent>::value){ 
		if (componentes[RENDERABLE].size() > 0) {
			return (T*)componentes[RENDERABLE][0];
		}
	} else if (std::is_same<T, Audio>::value) {
		DBG("Intento localizar componente Audio");
		if (componentes[AUDIO].size() > 0) {
			return (T*)componentes[AUDIO][0];
		}
	} else if (std::is_base_of<renderable::Object, T>::value) {
		if (componentes[RENDERABLE].size() > 0) {
			return (T*)(((RenderableComponent*)componentes[RENDERABLE][0])->getRenderable());
		}
	}
	return NULL;
}
template <class T, class K>
std::vector<T*>* Entity::getComponents() {
	//std::vector<T*> componente;
	if (std::is_same<T, RenderableComponent>::value) {
		//TODO: OJO, aquí devolvemos todos los renderables no sólo el tipo que me piden por ejemplo si pido img me devuelve todo, incluso los mesh
		return (std::vector<T*>*) & componentes[RENDERABLE];
	}else if (std::is_same<T, Shader>::value) {
		return (std::vector<T*>*) & componentes[SHADER];
	} else if (std::is_same<T, Camera>::value) {
		return (std::vector<T*>*) & componentes[CAMERA];
	} else if (std::is_same<T, Code>::value) {
		return (std::vector<T*>*) & componentes[CODE];
	} else if (std::is_base_of<renderable::Object, K>::value) {
		//TODO:: Esto está mál hay que cambiar para que devuelva solo los timpos que pide
		return (std::vector<T*>*) & componentes[RENDERABLE];
	} else if (std::is_same<T, Audio>::value) {
		return (std::vector<T*>*) & componentes[AUDIO];
	}
	return NULL;
}


template<class T>
inline T* Entity::addComponent() {
	T* c = NULL;
	Component* comp = NULL;
	if (std::is_base_of<renderable::Object, T>::value) {
		c = new T();
		comp = new RenderableComponent((renderable::Object*)c);
	}else{
		c = new T();
		comp = (Component*)c;
	}

	if (c != NULL) {
		comp->setGraphic(this->graphic);
		addComponent<T>(comp);
	}
	return c;
}
template <class T>
inline T* Entity::addComponent(Component* component) {
	if (std::is_same<T, Shader>::value) {
		componentes[SHADER].push_back(component);
	} else if (std::is_same<T, Camera>::value) {
		componentes[CAMERA].push_back(component);
	} else if (std::is_base_of<collider::Collider, T>::value) {
		componentes[COLLIDER].push_back(component);
		//component->setEntity(this);
	} else if (std::is_same<T, Code>::value) {
		componentes[CODE].push_back(component);
		//comp->setEntity(this);
	} else if (std::is_base_of<renderable::Object, T>::value) {
		componentes[RENDERABLE].push_back(component);
		//modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (std::is_same<T, renderable::Img>::value) {
			//Le añadimos ademas el componente Shader
			Shader* shaders = addComponent<Shader>();
			shaders->loadShader("shaders/vertex_texture.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_texture.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
			/*shaders->loadShader("shaders/vertex_basic.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_solid_color.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);*/
			//shaders->compileShader();
		} else if (std::is_same<T, renderable::Cube>::value) {
			//Le añadimos ademas el componente Shader
			Shader* shaders = addComponent<Shader>();
			//shaders->loadShader("shaders/vertex_basic.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_solid_color_light.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
			//shaders->compileShader();
			//g->updateEntity(this);
		}else if (std::is_same<T, renderable::Mesh>::value || std::is_same<T, renderable::Text>::value) {
			//Le añadimos ademas el componente Shader
			Shader* shaders = addComponent<Shader>();
			//DBG("Cargamos los shaders shaders/vertex_basic_mesh.glsl y shaders/fragment_texture.glsl");
			shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_texture.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
			//shaders->compileShader();
			//g->updateEntity(this); 
		} else if (std::is_same<T, renderable::Line>::value) {
			Shader* shaders = addComponent<Shader>(); 
			shaders->loadShader("shaders/vertex_line.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_line.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);/**/ 
			//shaders->compileShader();
		} else {
			Shader* shaders = addComponent<Shader>();
			shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/fragment_solid_color_light.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
			//shaders->compileShader();
		}
		if (graphic) {
			graphic->addEntity(this);
		}/**/
		/**/
	} else if (std::is_same<T, Audio>::value) {
		componentes[AUDIO].push_back(component);
		//comp->setEntity(this);
	}

	if (component != NULL) {
		component->setEntity(this);
		//TODO: ¿ACTUALIZAR AL COMPONENTE GRÁFICO?
		componentesOrden.push_back(component);
		if (std::is_base_of<renderable::Object, T>::value) {
			return (T*)(((RenderableComponent*)component)->getRenderable());
		} else {
			return (T*)component;
		}
	}
	return NULL;
};
template <class T>
inline bool Entity::has() {
	if (std::is_same<T, Shader>::value) {
		return componentes[SHADER].size()>0;
	} else if (std::is_same<T, Camera>::value) {
		return componentes[CAMERA].size() > 0;
	} else if (std::is_same<T, Code>::value) {
		return componentes[CODE].size() > 0;
	} else if (std::is_base_of<collider::Collider, T>::value) {
		return componentes[COLLIDER].size() > 0;
	} else if (std::is_same<T, RenderableComponent>::value) {
		return componentes[RENDERABLE].size() > 0;
	} else if (std::is_same<T, Audio>::value) {
		return componentes[AUDIO].size() > 0;
	} else if (std::is_base_of<renderable::Object, T>::value) {
		return componentes[RENDERABLE].size() > 0;
	}
	return false;
}
template<Entity::TYPE Type>
inline Entity* Entity::create(unsigned stack) {
	//modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
	Entity* e = NULL;
	switch (Type) {
	case Entity::EMPTY:
		e = new Entity(stack);
		break;
	case Entity::IMG:
		e = new Entity(stack);
		break;
	case Entity::CUBE:
		e = new Entity(stack);
		//if (g) {
			////g->addEntity(e);
		//}
		e->addComponent<renderable::Cube>();
		break;
	case Entity::MESH:
		e = new Entity(stack);
		e->addComponent<renderable::Mesh>();
		break;
	default:
		break;
	}
	return e;
}


#endif // !_ENTITY