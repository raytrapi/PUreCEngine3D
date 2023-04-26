#ifndef _ENTITY
#define _ENTITY

#include "../../modules/graphic/motor.h"
#include "../modulos/shader/shader.h"
#include "../modulos/cameras/camera.h"
#include "../modulos/collider/collider.h"
#include "../modulos/audio/audio.h"
#include "../modulos/physics/rigidBody.h"
//#include "../modulos/code/code.h"
#include "../modulos/renderables/renderable.h"
#include "../../modules/src/module.h"
#include "../../graphics/src/renderable/cube.h"
#include "../../graphics/src/renderable/mesh.h"
#include "../../graphics/src/renderable/line.h"
#include "../modulos/light/light.h"
/*#include "../../graphics/src/renderable/img.h"
#include "../../graphics/src/renderable/line.h"/**/

#include "transform.h"
#include "component.h"
#include "exportar.h"
#include <type_traits>
#include <map>
#include <vector>
#include <tuple>
#include "transform.h"
extern class Code;
extern class modules::graphics::Interface;
namespace renderable {
	extern class Text;
}
namespace collider {
	extern class Ray;
}
struct EXPORTAR_COMPONENTE Entity {
	static unsigned int idEntidadMax;
	enum TIPO {
		RENDERABLE,
		SHADER,
		CAMERA,
		CODE,
		COLLIDER,
		AUDIO,
		PHYSICS,
		LUZ
	};
	enum TYPE_OPERATION { ALL, MOVE };
	int id = -1;
	friend collider::Ray;
	static std::map<unsigned,std::vector<Entity*>> entidades;
	static std::vector<unsigned> entidadesStacks;
	static unsigned defaultStack;
	static Entity* instancia;
	std::vector<Component*> componentesOrden;
	std::map<Entity::TIPO,std::vector<Component *>> componentes;
	Transform* transformada=NULL;
	Entity* padre = NULL;
	unsigned pila = 0;
	//std::vector<Entity*> hijos;
	friend class modules::graphics::Interface;
	std::string nombre = "";
	std::map<std::string, std::string> texturas;
	bool active=true;
	bool actualizarRender = false;

	bool actualizarVertices = true;
	bool actualizarTextura = true;
	static modules::graphics::Graphic* graphic;
	bool onTop = false;
	float vida = -1;
	bool decreaseLife();
	void erase();
public:
	enum EXPORTAR_COMPONENTE TYPE {
		EMPTY,
		IMG,
		CUBE,
		MESH,
		LIGHT
		/**/
	};
	Entity(unsigned stack=0) {
		id = idEntidadMax++;
		pila = stack;
		if (instancia == NULL) {
			instancia = this;
		} else {
			entidades[stack].push_back(this);

			//Comprobamos si el vector de entidadesStacks contien el stack //check if the entidadesStack contain the stack
			bool noContiene = true;
			auto itr = entidadesStacks.begin();
			while (noContiene && itr != entidadesStacks.end()) {
				if ((*itr) == stack) {
					noContiene = false;
				}
				itr++;
			}
			if (noContiene) {
				entidadesStacks.push_back(stack);
			}
			//if(entidadesStacks.)

			/*modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
			if (g) {
				g->addEntity(this);
			}/**/
		}
		transformada = new Transform(this);
	}
	~Entity() {
		//componentes.clear();
		//DBG("Borramos entidad");
		for (int i = 0;i< componentesOrden.size(); i++) {
			delete componentesOrden[i];
		}
		componentesOrden.clear();
		componentes.clear();
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
		if (transformada != NULL) {
			delete transformada;
			transformada = NULL;
		}
		
		/*for (auto itr = entidades.begin(); itr != entidades.end() && seguir; itr++) {
			if (*itr == this) {
				entidades.erase(itr);
				//itr = entidades.begin(); //Reiniciamos para evitar fallos
				break;
				seguir = false;
			}
		}/**/
	};
	void setLifeTime(float miliseconds);
	
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

		clear();
	}
	void setOnTop(bool onTop) {
		this->onTop = onTop;
	}
	bool isOnTop() {
		return onTop;
	}
	static std::vector<Entity*> getEntities(unsigned stack = 0) { return entidades[stack]; }
	static std::map<unsigned, std::vector<Entity*>>* getAllEntities() { return &entidades; }
	//Obtiene la lista de claves de las entidades //get keys of the all entities
	static std::vector<unsigned> getEntitiesStacks();
	template <class T>
	static std::vector<T*> getAllGlobalComponents();

	

	std::vector<Component*>* getComponents();
	
	template <class T>
	std::vector<T*>* getComponents();
	template <class T>
	std::vector<T*> getAllComponents();
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
	T* addComponent(Component* component, Component* parent);
	/*template <class T>
	std::tuple<T*, Component*> createComponent(Component* parent);/**/
	template <class T>
	bool has();
	template <Entity::TYPE Type>
	static Entity* create(unsigned stack=-1);
	static void startCodes(unsigned stack=0, Input *input=NULL);
	static void stopCodes(unsigned stack = 0);
	static bool updateLifeTime(unsigned stack = 0);
	static void destroyDead(unsigned stack = 0);
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
		if (actualizarRender || graphic->isChangeCamera(graphic->getActiveCamera(),false)) {
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
	Transform * getTransform() { return transformada; };
	static void clear();

};
template<class T>
inline std::vector<T*> Entity::getAllComponents() {
	std::vector<T*> componentes;
	for (auto componentesDic : this->entidades) {
		for (auto componente : componentesDic.second) {
			std::vector<T*>* componentesInternos = componente->getComponents<T>();
			for (auto componenteInterno : *componentesInternos) {
				componentes.push_back(componenteInterno);
			}
		}
		
	}
	return componentes;
}

template<class T>
inline std::vector<T *>* Entity::getComponents() {
	//std::vector<T*> componente;
	if (std::is_same<T, RenderableComponent>::value) {
		//TODO: OJO, aquí devolvemos todos los renderables no sólo el tipo que me piden por ejemplo si pido img me devuelve todo, incluso los mesh
		return (std::vector<T*>*) & componentes[RENDERABLE];
	}else if (std::is_same<T, graphics::Shader>::value) {
		return (std::vector<T*>*) &componentes[SHADER];
	}else if (std::is_same<T, Camera>::value) {
		return (std::vector<T*>*) &componentes[CAMERA];
	} else if (std::is_same<T, Code>::value) {
		return (std::vector<T*>*) &componentes[CODE];
	} else if (std::is_base_of<Collider, T>::value) {
		return (std::vector<T*>*) & componentes[COLLIDER];
	} else if (std::is_same<T, Audio>::value) {
		return (std::vector<T*>*) & componentes[AUDIO];
	} else if (std::is_same<T, physics::RigidBody>::value) {
		return (std::vector<T*>*) & componentes[PHYSICS];
	} else if (std::is_same<T, LightComponent>::value) {
		return (std::vector<T*>*) & componentes[LUZ];
	}
		
	return NULL;
}
template <class T>
inline T* Entity::getComponent() {
	//std::vector<T*> componente;
	if (std::is_same<T, graphics::Shader>::value) {
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
	} else if (std::is_same<T, RenderableComponent>::value){ 
		if (componentes[RENDERABLE].size() > 0) {
			return (T*)componentes[RENDERABLE][0];
		}
	} else if (std::is_same<T, Audio>::value) {
		//DBG("Intento localizar componente Audio");
		if (componentes[AUDIO].size() > 0) {
			return (T*)componentes[AUDIO][0];
		}
	} else if (std::is_base_of<renderable::Object, T>::value) {
		if (componentes[RENDERABLE].size() > 0) {
			return (T*)(((RenderableComponent*)componentes[RENDERABLE][0])->getRenderable());
		}
	} else if (std::is_same<T, physics::RigidBody>::value) {
		return (T*)componentes[PHYSICS][0];
	} else if (std::is_same<T, LightComponent>::value) {
		return (T*)componentes[LUZ][0];
	}
	return NULL;
}
template <class T, class K>
std::vector<T*>* Entity::getComponents() {
	//std::vector<T*> componente;
	if (std::is_same<T, RenderableComponent>::value) {
		//TODO: OJO, aquí devolvemos todos los renderables no sólo el tipo que me piden por ejemplo si pido img me devuelve todo, incluso los mesh
		return (std::vector<T*>*) & componentes[RENDERABLE];
	}else if (std::is_same<T, graphics::Shader>::value) {
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
	} else if (std::is_same<T, physics::RigidBody>::value) {
		return (std::vector<T*>*) & componentes[PHYSICS];
	} else if (std::is_same<T, LightComponent>::value) {
		return (std::vector<T*>*) & componentes[LUZ];
	}
	return NULL;
}

/*template <class T>
inline std::tuple<T*, Component*> createComponent(Component* parent) {
	T* c = NULL;
	Component* comp = NULL;
	c = new T(this, this->graphic, parent);
	comp = (Component*)c;
	
	return { c,comp };
}/**/

template<class T>
inline T* Entity::addComponent() {
	//auto [c, comp] = createComponent<T>(NULL);
	T* c = NULL;
	Component* comp = NULL;
	c = new T(this, this->graphic, NULL);
	comp = (Component*)c;
	if (c != NULL) {
		//comp->setGraphic(this->graphic);
		addComponent<T>(comp);
	}
	return c;
}
template <class T>
inline T* Entity::addComponent(Component* component) {
	if (std::is_same<T, graphics::Shader>::value) {
		componentes[SHADER].push_back(component);
	} else if (std::is_same<T, Camera>::value) {
		componentes[CAMERA].push_back(component);
	} else if (std::is_base_of<Collider, T>::value) {
		componentes[COLLIDER].push_back(component);
		//component->setEntity(this);
	} else if (std::is_same<T, Code>::value) {
		componentes[CODE].push_back(component);
		//comp->setEntity(this);
	} else if (std::is_same<T, RenderableComponent>::value) {
		componentes[RENDERABLE].push_back(component);
		//modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();

		/*if (graphic) {
			graphic->addEntity(this);
		}/**/
		/**/
	} else if (std::is_same<T, Audio>::value) {
		componentes[AUDIO].push_back(component);
		//comp->setEntity(this);
	} else if (std::is_same<T, physics::RigidBody>::value) {
		componentes[PHYSICS].push_back(component);
		((physics::RigidBody*)component)->setPhysics(this->graphic->getPhysics());
	}else if (std::is_same<T, LightComponent>::value) {
		componentes[LUZ].push_back(component);
	}

	if (component != NULL) {
		//component->setEntity(this);
		//TODO: ¿ACTUALIZAR AL COMPONENTE GRÁFICO?
		componentesOrden.push_back(component);
		//if (std::is_base_of<renderable::Object, T>::value) {
		//	return (T*)(((RenderableComponent*)component)->getRenderable());
		//} else {
		return (T*)component;
		//}
	}
	return NULL;
};
template <class T>
inline T* Entity::addComponent(Component* component, Component* parent) {
	T* c = (T*)component;
	if (component == NULL) {
		T* c2 = NULL;
		Component* comp = NULL;
		c2 = new T(this, this->graphic, parent);
		comp = (Component*)c2;
		if (c2 != NULL) {
			//comp->setGraphic(this->graphic);
			addComponent<T>(comp);
			c = c2;
		}
	}
	
	return c;
};
template <class T>
inline bool Entity::has() {
	if (std::is_same<T, graphics::Shader>::value) {
		return componentes[SHADER].size()>0;
	} else if (std::is_same<T, Camera>::value) {
		return componentes[CAMERA].size() > 0;
	} else if (std::is_same<T, Code>::value) {
		return componentes[CODE].size() > 0;
	} else if (std::is_base_of<Collider, T>::value) {
		return componentes[COLLIDER].size() > 0;
	} else if (std::is_same<T, RenderableComponent>::value) {
		return componentes[RENDERABLE].size() > 0;
	} else if (std::is_same<T, Audio>::value) {
		return componentes[AUDIO].size() > 0;
	} else if (std::is_base_of<renderable::Object, T>::value) {
		return componentes[RENDERABLE].size() > 0;
	} else if (std::is_same<T, physics::RigidBody>::value) {
		return componentes[PHYSICS].size() > 0;
	} else if (std::is_same<T, LightComponent>::value) {
		return componentes[LUZ].size() > 0;
	}
	return false;
}
template<Entity::TYPE Type>
inline Entity* Entity::create(unsigned stack) {
	if (stack == -1) {
		stack = graphic->getStack();
	}
	//modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
	Entity* e = NULL;
	RenderableComponent* r = NULL; 
	graphics::Shader* shaders = NULL;
	switch (Type) {
	case Entity::TYPE::EMPTY:
		e = new Entity(stack);
		break;
	case Entity::TYPE::IMG:
		e = new Entity(stack);
		r = e->addComponent<RenderableComponent>();
		r->add<renderable::Mesh>();
		break;
	case Entity::TYPE::CUBE:
		e = new Entity(stack);
		//if (g) {
			////g->addEntity(e);
		//}
		r = e->addComponent<RenderableComponent>();
		r->add<renderable::Cube>();
		break;
	case Entity::TYPE::MESH:
		e = new Entity(stack);
		r = e->addComponent<RenderableComponent>();
		r->add<renderable::Mesh>();
		
		break;
	case Entity::TYPE::LIGHT:
		e = new Entity(stack);
		e->addComponent<LightComponent>();
		shaders = e->addComponent<graphics::Shader>();
		shaders->loadShader("shaders/gizmo_vertex_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/gizmo_fragment_mesh.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		shaders->loadShader("shaders/shadow_map_vertex_dbg.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/shadow_map_fragment_dbg.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		break;
	default:
		break;
	}
	return e;
}

template<class T>
inline T* RenderableComponent::add(renderable::Object* o) {

	T* c = (T*)o;
	if (o == NULL) {
		c = new T();
		objetoPropio = true;
	}
	if (std::is_same<T, renderable::Img>::value) {
		//Le añadimos ademas el componente Shader
		graphics::Shader* shaders = entidad->addComponent<graphics::Shader>();
		//shaders->loadShader("shaders/vertex_texture.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/fragment_texture.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		//shaders->compileShader();
	} else if (std::is_same<T, renderable::Cube>::value) {
		//Le añadimos ademas el componente Shader
		graphics::Shader* shaders = entidad->addComponent<graphics::Shader>();
		//shaders->loadShader("shaders/vertex_basic.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/fragment_texture.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		//shaders->loadShader("shaders/fragment_solid_color_light.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		//shaders->compileShader();
		//g->updateEntity(this);
	} else if (std::is_same<T, renderable::Mesh>::value || std::is_same<T, renderable::Text>::value) {
		//Le añadimos ademas el componente Shader
		graphics::Shader* shaders = entidad->addComponent<graphics::Shader>();
		//DBG("Cargamos los shaders shaders/vertex_basic_mesh.glsl y shaders/fragment_texture.glsl");
		shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/fragment_texture.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);

		shaders->loadShader("shaders/shadow_map_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/shadow_map_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);

		{//TODO: Si estamos en editor
			shaders->loadShader("shaders/editor/entidadID_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/editor/entidadID_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		}
		//shaders->compileShader();
		//g->updateEntity(this);
	} else if (std::is_same<T, renderable::Line>::value) {
		graphics::Shader* shaders = entidad->addComponent<graphics::Shader>();
		shaders->loadShader("shaders/vertex_line.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/fragment_line.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		//shaders->compileShader();
	} else {
		graphics::Shader* shaders = entidad->addComponent<graphics::Shader>();
		shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/fragment_solid_color_light.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		//shaders->compileShader();
	}/**/


	objeto = c;
	objeto->setRenderable(this);

	return c;
}

inline std::vector<unsigned> Entity::getEntitiesStacks() {
	return entidadesStacks;
};

template<class T>
inline T* Component::addComponent() {
	DBG("Añado un componente con Padre");
	T* h = entidad->addComponent<T>(NULL,this);
	//h->padre = this;
	return h;
};

template <class T>
inline  std::vector<T*> Entity::getAllGlobalComponents() {
	std::vector<T*> respuesta;
	auto entidadesStack = getAllEntities();
	for (auto es : *entidadesStack) {
		for (auto entidad : es.second) {
			auto objetos = entidad->getComponents<T>();
			for (auto ob : *objetos) {
				respuesta.push_back(ob);
			}
		}
	}/**/
	
	return respuesta;
};
#endif // !_ENTITY