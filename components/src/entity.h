#ifndef _ENTITY
#define _ENTITY

#include "../../modules/graphic/motor.h"
#include "../modulos/cameras/camera.h"
#include "../modulos/collider/collider.h"
#include "../modulos/audio/audio.h"

#include "../modulos/renderables/renderableComponent.h"
#include "../modulos/shader/shaderComponent.h"
#include "../modulos/physics/rigidBodyComponent.h"
#include "../modulos/collider/boxColliderComponent.h"
#include "../modulos/interface/interfaceComponent.h"
//#include "../modulos/code/code.h"
#include "../../modules/src/module.h"
#include "../modulos/renderables/objects/cube.h"
#include "../modulos/renderables/objects/mesh.h"
#include "../modulos/renderables/objects/line.h"
/*#include "../modulos/renderables/objects/img.h"
#include "../modulos/renderables/objects/line.h"/**/
/*#include "../../graphics/src/renderable/cube.h"
#include "../../graphics/src/renderable/mesh.h"
#include "../../graphics/src/renderable/line.h"
/*#include "../../graphics/src/renderable/img.h"
#include "../../graphics/src/renderable/line.h"/**/
#include "../modulos/light/light.h"
#include "../../utilidades/project/genericFile.h"
#include "../../utilidades/utiles/handler.h"
#include "../../utilidades/utiles/pointers.h"
#include "transform.h"
#include "component.h"
#include "exportar.h"
#include <type_traits>
#include <map>
#include <vector>
#include <tuple>
#include "transform.h"
#include <mutex>
extern class Code;
extern class modules::graphics::Interface;
namespace renderable {
	extern class Text;
}
namespace collider {
	extern class Ray;
}
struct EXPORTAR_COMPONENTE Entity {
	enum EXPORTAR_COMPONENTE TYPE {
		EMPTY,
		IMG,
		CUBE,
		MESH,
		LIGHT,
		INTERFACE
		/**/
	};
	static unsigned long idEntidadMax;
	enum TIPO {
		RENDERABLE,
		SHADER,
		CAMERA,
		CODE,
		COLLIDER,
		AUDIO,
		PHYSICS,
		LUZ,
		INTERFAZ
	};
	enum TYPE_OPERATION { ALL, MOVE };
	unsigned long id = 1001;
	friend collider::Ray;
	static std::map<unsigned,std::vector<Entity*>> entidades;
	static std::vector<unsigned> entidadesStacks;
	static unsigned defaultStack;
	static Entity* instancia;
	std::vector<Component*> componentesOrden;
	std::map<Entity::TIPO,std::vector<Component *>> componentes;
	std::map<const char*, std::vector<Component*>, cmp_str>	componentesDinamicos;//TODO: Optimizar esto con una estructura para almacenar cadenas tipo árbol
	Transform* transformada=NULL;
	Entity* padre = NULL;
	unsigned pila = 0;
	std::vector<Entity*> hijos;

	void borrarHijo(Entity * hijo);

	friend class modules::graphics::Interface;
	std::string nombre = "";
	std::map<std::string, std::string> texturas;
	bool active=true;
	bool visible = false;
	bool actualizarRender = false;

	bool actualizarVertices = true;
	bool actualizarTextura = true;
	static modules::graphics::Graphic* graphic;
	bool onTop = false;
	float vida = -1;
	bool decreaseLife();
	void erase();
	float* getModel();

	std::string serializar();
	friend void procesarNivel();
	static int desserializar(std::string s, int pos, modules::graphics::Graphic* g=0);
	/*friend class Component;
	static int desserializar(std::string s, int pos, Component* c);
	static int desserializar(std::string s, int pos, RenderableComponent* c);/**/
	friend class Component;
	template<class T, class K>
	int desserializarObjeto(std::string s, int pos, K* c);

	int saveState(std::vector<unsigned char>* data, bool withID=false, int pos=-1);
	void restoreState(std::vector<unsigned char>* data=0, bool withID = false);
	TYPE tipoEntidad;

	std::vector<std::function<void(Entity*)>>funcionesCierre;

private:
	float model[16];
	bool changeModel = false;
	static unsigned long getNewId();
	static void renewIds();
	static std::mutex idMutex;
	bool seleccionado = false;

public:
	
	Entity(unsigned stack=0,int pos=-1) {
		id = getNewId();
		pila = stack;
		if (instancia == NULL) {
			instancia = this;
		} else {
			if (pos > -1 && pos<entidades[stack].size()) {
				entidades[stack].insert(entidades[stack].begin() + pos, this);
				//entidades[stack].push_back(this);
			} else {
				entidades[stack].push_back(this);
			}
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
		//DBG("NEW sobre %", this);
	}
	Entity* create(unsigned stack = 0, int pos = -1){
		//DBG("Nueva sobre %", this);
		return new Entity(stack, pos);
	}
	~Entity() {
		
		for (auto funcionCierre : funcionesCierre) {
			if (funcionCierre != nullptr) {
				funcionCierre(this);
			}
		}
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

	/* Funciones de muerte */
	//void onDelete(std::function<void(Entity*)>*funtion) {funcionesCierrePunteros.push_back(funtion);};
	int onDelete(std::function<void(Entity*)>function);
	void removeOnDelete(int pos);

	/* Funciones de vida*/

	void setLifeTime(float miliseconds);
	
	void setGraphic(modules::graphics::Graphic* g) {
		graphic = g;
	}
	static void destroy(bool all=false) {

		//modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (graphic!=NULL) {
			for (auto entidades : Entity::entidades) {
				for (auto entidad : entidades.second) {
					if (all || entidad->id != 0) {
						graphic->removeEntity(entidad);
					}
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
		renewIds();
	}
	void setOnTop(bool onTop) {
		this->onTop = onTop;
	}
	bool isOnTop() {
		return onTop;
	}
	static std::vector<Entity*> getEntities(unsigned stack = 0) { return entidades[stack]; }
	static std::vector<Entity*> getEntities(unsigned stack, Entity* parent);
	static std::map<unsigned, std::vector<Entity*>>* getAllEntities() { return &entidades; }
	//Obtiene la lista de claves de las entidades //get keys of the all entities
	static std::vector<unsigned> getEntitiesStacks();
	template <class T>
	static std::vector<T*> getAllGlobalComponents(bool active=false);

	

	std::vector<Component*>* getComponents();
	void deleteComponents();
	
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
	T* getComponent(const char* name);


	Component* addComponent(Component* component, Component* parent=0, bool dinamic=false, const char* name=0);



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
	unsigned long getId() { return id; };

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
	bool isVisible() {
		return visible;
	}
	void setUpdatingRender(bool updating) {
		actualizarRender = updating;
	}
	bool isUpdatingRender() {
		if (actualizarRender || (graphic && graphic->isChangeCamera(graphic->getActiveCamera(),false))) {
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
	void setParent(Entity* e);
	int getChildNumber() { return hijos.size(); };
	void removeParent() {
		padre->removeChild(this);
		padre = NULL;
	}
	Entity* getParent() { return padre; };
	void appendChild(Entity* child) {
		hijos.push_back(child);
		transformada->appendChild(child);
		
	}
	void removeChild(Entity* child){
		borrarHijo(child);
		
		
	}
	Transform * getTransform() { return transformada; };
	static void clear();
	static void checkLifeCicle(float delta);

	bool isSelected() { return seleccionado; }
	void setSelected(bool selecting) { seleccionado = selecting; }


	static void controlInterface(std::tuple<int, int> pos, int buttonPress=-1);
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
	}else if (std::is_same<T, graphics::ShaderComponent>::value) {
		return (std::vector<T*>*) &componentes[SHADER];
	}else if (std::is_same<T, Camera>::value) {
		return (std::vector<T*>*) &componentes[CAMERA];
	} else if (std::is_same<T, Code>::value) {
		return (std::vector<T*>*) &componentes[CODE];
	} else if (std::is_base_of<Collider, T>::value) {
		return (std::vector<T*>*) &componentes[COLLIDER];
	} else if (std::is_same<T, Audio>::value) {
		return (std::vector<T*>*) &componentes[AUDIO];
	} else if (std::is_same<T, physics::RigidBodyComponent>::value) {
		return (std::vector<T*>*) &componentes[PHYSICS];
	} else if (std::is_same<T, LightComponent>::value) {
		return (std::vector<T*>*) &componentes[LUZ];
	} else if (std::is_same<T, InterfaceComponent>::value) {
		return (std::vector<T*>*) & componentes[INTERFAZ];
	}
		
	return NULL;
}
template <class T>
inline T* Entity::getComponent(const char* nombre) {
	auto componentes = getAllGlobalComponents<T>();
	for (auto componente : componentes) {
		if (strcmp(componente->getName().c_str(), nombre)) {
			return componente;
		}
	}
	return NULL;
}
template <class T>
inline T* Entity::getComponent() {
	//std::vector<T*> componente;
	if (std::is_same<T, graphics::ShaderComponent>::value) {
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
	} else if (std::is_same<T, physics::RigidBodyComponent>::value) {
		if (componentes[PHYSICS].size() > 0) {
			return (T*)componentes[PHYSICS][0];
		} 
	} else if (std::is_same<T, LightComponent>::value) {
		if (componentes[LUZ].size() > 0) {
			return (T*)componentes[LUZ][0];
		}
	} else if (std::is_same<T, InterfaceComponent>::value) {
		if (componentes[INTERFAZ].size() > 0) {
			return (T*)componentes[INTERFAZ][0];
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
	}else if (std::is_same<T, graphics::ShaderComponent>::value) {
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
	} else if (std::is_same<T, physics::RigidBodyComponent>::value) {
		return (std::vector<T*>*) & componentes[PHYSICS];
	} else if (std::is_same<T, LightComponent>::value) {
		return (std::vector<T*>*) & componentes[LUZ];
	} else if (std::is_same<T, InterfaceComponent>::value) {
		return (std::vector<T*>*) & componentes[INTERFAZ];
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
inline Component* Entity::addComponent(Component* component, Component* parent, bool dinamic, const char * name) {
	if (dinamic) {
		component->setEntity(this);
		componentesDinamicos[name].push_back(component);
		if (parent) {
			component->setParent(parent);
		}
	}
	if (component != NULL) {
		//component->setEntity(this);
		//TODO: ¿ACTUALIZAR AL COMPONENTE GRÁFICO?
		componentesOrden.push_back(component);
		//if (std::is_base_of<renderable::Object, T>::value) {
		//	return (T*)(((RenderableComponent*)component)->getRenderable());
		//} else {
		return component;
		//}
	}
	return NULL;
}
template <class T>
inline T* Entity::addComponent(Component* component) {
	if (std::is_same<T, graphics::ShaderComponent>::value) {
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
	} else if (std::is_same<T, physics::RigidBodyComponent>::value) {
		componentes[PHYSICS].push_back(component);
		if (this->graphic) {
			((physics::RigidBodyComponent*)component)->setPhysics(this->graphic->getPhysics());
		}
	} else if (std::is_same<T, LightComponent>::value) {
		componentes[LUZ].push_back(component);
	} else if (std::is_same<T, InterfaceComponent>::value) {
		componentes[INTERFAZ].push_back(component);
	}
	return (T*)addComponent(component, 0,false);
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
	if (std::is_same<T, graphics::ShaderComponent>::value) {
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
	} else if (std::is_same<T, physics::RigidBodyComponent>::value) {
		return componentes[PHYSICS].size() > 0;
	} else if (std::is_same<T, LightComponent>::value) {
		return componentes[LUZ].size() > 0;
	} else if (std::is_same<T, InterfaceComponent>::value) {
		return componentes[INTERFAZ].size() > 0;
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
	graphics::ShaderComponent* shaders = NULL;
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
		r = e->addComponent<RenderableComponent>();
		r->add<renderable::Cube>();
		r->setUpdated(true);/**/
		break;
	case Entity::TYPE::MESH:
		e = new Entity(stack);
		r = e->addComponent<RenderableComponent>();
		r->add<renderable::Mesh>();

		break;
	case Entity::TYPE::LIGHT:
		e = new Entity(stack);
		e->addComponent<LightComponent>();
		/*shaders = e->addComponent<graphics::ShaderComponent>();
		shaders->loadShader("shaders/gizmo_vertex_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/gizmo_fragment_mesh.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		shaders->loadShader("shaders/shadow_map_vertex_dbg.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/shadow_map_fragment_dbg.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);/**/
		break;
	case Entity::TYPE::INTERFACE:
	{
		e = new Entity(stack);
		e->addComponent<InterfaceComponent>();
		/*r = e->addComponent<RenderableComponent>();
		auto img=r->add<renderable::Img>();
		img->setSize(Screen::getWidth(), Screen::getWidth());/**/
	}
		break;
	default:
		break;
	}
	if (e) {
		e->tipoEntidad = Type;
	}
	return e;
}
template<class T, class K>
inline int Entity::desserializarObjeto(std::string s, int pos, K* c) {
	if (std::is_same<K, RenderableComponent>::value) {
		//RenderableComponent* cR = c;
		//auto o = cR->add<renderable::Cube>();
		//auto o = c->add<T>();
	}
	//o->desserializar(s, pos);

	return s.length();
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
		graphics::ShaderComponent* shaders = entidad->addComponent<graphics::ShaderComponent>();
		shaders->setMaterial("ColorSolido");
		{
			shaders->setClicking();
			shaders->setOutline();
		}
		//shaders->compileShader();
	} else if (std::is_same<T, renderable::Cube>::value) {
		//Le añadimos ademas el componente Shader
		graphics::ShaderComponent* shaders = entidad->addComponent<graphics::ShaderComponent>();
		//shaders->loadShader("shaders/vertex_basic.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		//COLOR
		//shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		//shaders->loadShader("shaders/fragment_texture.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		shaders->setMaterial("Color");

		//Sombra
		//shaders->loadShader("shaders/shadow_map_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		//shaders->loadShader("shaders/shadow_map_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		shaders->setShadow();

		{//TODO: Si estamos en editor
			//Selección
			shaders->setClicking();
			//shaders->loadShader(, Graphics::Shader::TYPE_SHADER::VERTEX);
			//shaders->loadShader(, Graphics::Shader::TYPE_SHADER::FRAGMENT);
			//Marcado (outlining)
			//shaders->loadShader("shaders/editor/outline_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			//shaders->loadShader("shaders/editor/outline_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
			shaders->setOutline();
			//shaders->loadShader("shaders/editor/collision_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			//shaders->loadShader("shaders/editor/collision_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		}

		//shaders->loadShader("shaders/fragment_solid_color_light.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		//shaders->compileShader();
		//g->updateEntity(this);/**/
	} else if (std::is_same<T, renderable::Mesh>::value || std::is_same<T, renderable::Text>::value) {
		//Le añadimos ademas el componente Shader
		graphics::ShaderComponent* shaders = entidad->addComponent<graphics::ShaderComponent>();
		//DBG("Cargamos los shaders shaders/vertex_basic_mesh.glsl y shaders/fragment_texture.glsl");
		/*shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/fragment_texture.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);

		shaders->loadShader("shaders/shadow_map_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/shadow_map_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);

		{//TODO: Si estamos en editor
			shaders->loadShader("shaders/editor/entidadID_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			shaders->loadShader("shaders/editor/entidadID_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		}/**/
		shaders->setMaterial("Color");

		//Sombra
		//shaders->loadShader("shaders/shadow_map_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		//shaders->loadShader("shaders/shadow_map_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		shaders->setShadow();

		{//TODO: Si estamos en editor
			//Selección
			shaders->setClicking();
			//shaders->loadShader(, Graphics::Shader::TYPE_SHADER::VERTEX);
			//shaders->loadShader(, Graphics::Shader::TYPE_SHADER::FRAGMENT);
			//Marcado (outlining)
			//shaders->loadShader("shaders/editor/outline_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			//shaders->loadShader("shaders/editor/outline_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
			shaders->setOutline();
			//shaders->loadShader("shaders/editor/collision_vertex.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
			//shaders->loadShader("shaders/editor/collision_fragment.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		}

		//shaders->compileShader();
		//g->updateEntity(this);
	} else if (std::is_same<T, renderable::Line>::value) {
		graphics::ShaderComponent* shaders = entidad->addComponent<graphics::ShaderComponent>();
		shaders->loadShader("shaders/vertex_line.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/fragment_line.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		//shaders->compileShader();
	} else {
		graphics::ShaderComponent* shaders = entidad->addComponent<graphics::ShaderComponent>();
		shaders->loadShader("shaders/vertex_basic_mesh.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
		shaders->loadShader("shaders/fragment_solid_color_light.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
		//shaders->compileShader();
	}/**/

	visible = true;
	objeto = c;
	objeto->setRenderable(this);
	entidad->visible = true;
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
inline  std::vector<T*> Entity::getAllGlobalComponents(bool active) {
	std::vector<T*> respuesta;
	auto entidadesStack = getAllEntities();
	for (auto es : *entidadesStack) {
		for (auto entidad : es.second) {
			if (!active || entidad->active) {
				auto objetos = entidad->getComponents<T>();
				if (objetos) {
					for (auto ob : *objetos) {
						respuesta.push_back(ob);
					}
				}
			}
		}
	}/**/
	
	return respuesta;
};


#endif // !_ENTITY