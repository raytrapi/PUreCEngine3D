#ifndef _COMPONENT
#define _COMPONENT
#include "exportar.h"
#include <log.h>
#include "../../utilidades/supervisor/src/reflexivo.h"
#include "../../modules/src/module.h"
#include "../../utilidades/project/serializer/serializer.h"
#include "../../utilidades/project/serializer/deserializer.h"
#include "../../utilidades/project/serializer/deserializer.h"
#include "../../utilidades/project/genericFile.h"
#include <imgui.h>
#include "../../graphics/terceros/opengl4/src/imgui/imgui_controles.h"

enum TYPE_COMPONENT {
	GENERIC,
	CODE
};

//#include
extern class Entity;
extern class modules::graphics::Graphic;
class EXPORTAR_COMPONENTE Component {
	bool activo = true;
protected:
	friend class Entity;
	Entity* entidad = NULL;
	modules::graphics::Graphic* graphic = NULL;
	char* nombre = NULL;
	virtual void whenChargeEntity() {

	}
	Component* padre = NULL;
	std::vector<Parametro> propiedades;
	virtual void cargarPropiedades() {  };
	void addPropiedad(Parametro p) {
		propiedades.push_back(p);
	};

	virtual std::string serializar() { return ""; };
	friend class Entity;
	static int desserializar(std::string s, int pos, Entity* e);
	virtual int desserializar(std::string s, int pos = 0) { return pos; };

	friend class InterfaceGL;
	virtual bool interfazImGUI_C(ImGuiContext* imgui) { return true; };
	bool interfazImGUI(ImGuiContext* imgui,bool header=true, int iPos=0);
	virtual int saveState_interno(std::vector<unsigned char>* data, bool withID = false) {	return 0; }
	virtual void restoreState_interno(std::vector<unsigned char>* data=0, bool withID = false, int pos = -1) { }
	static bool interfazActivo;
public:
	Component();
	~Component();
	Component(Entity* entity,modules::graphics::Graphic* g, Component* p=NULL) {
		entidad = entity;
		graphic = g;
		padre = p;
		//loadEntity();
	}
	
	//virtual TYPE_COMPONENT componentType() { return GENERIC; };
	virtual TYPE_OBJECT_SERIALIZABLES getType() = 0;
	void setEntity(Entity* entity) {
		entidad = entity;
		whenChargeEntity();
	}
	Entity* getEntity() {
		return entidad;
	}
	virtual void destroy() {};
	void setName(std::string name);
	virtual std::string getName();
	void setGraphic(modules::graphics::Graphic* g) { graphic = g; };
	modules::graphics::Graphic* getGraphic() { return graphic; };
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

	int saveState(std::vector<unsigned char>* data, bool withID = false) { 
		int longitud = 0;
		if (withID) { 
			longitud+=Serializer::serialize(data, this);
		}; 
		std::vector<unsigned char> dataT;
		auto l=saveState_interno(&dataT, withID);
		longitud+=Serializer::serialize(data, &dataT);
		//longitud += Serializer::serialize(data, l);
		return longitud;
	};
	void restoreState(std::vector<unsigned char>* data = 0, bool withID = false) { 
		int longitud = 0;
		if (data != 0) {
			Deserializer::setBytes(data);
		}
		
		//Deserializer::deserialize(&longitud);
		//std::vector<unsigned char> data2;
		//Deserializer::extract(&data2, longitud);
		//Deserializer::stackBytes(&data2);
		restoreState_interno(0, withID);
		//Deserializer::unstackBytes();

	};
	virtual bool controlMouse(int x, int y, int buttonPress) { return false; };
};

#define PUBLIC() 
#define EDITABLE()\
	protected:\
	void loadParameters() override;


#endif //_COMPONENT



