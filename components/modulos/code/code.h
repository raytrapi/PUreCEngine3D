#ifndef __CODE
#define __CODE
#include <type_traits>
#include "../../components/src/entity.h"
#include "../../src/component.h"
#include "../../src/codeBase.h"
#include "../../../utilidades/global/input.h"

class EXPORTAR_COMPONENTE Code : public Component {
	friend class InterfaceGL;
	CodeBase* codigoBase = NULL;
	bool updating = false;
	std::string nombreCodigo;
	
	CodeBase::TYPE_OPERATION tipo = CodeBase::MOVE;
	Input* input;
	std::string serializar();
	int desserializar(std::string s, int pos = 0);
	bool interfazImGUI_C(ImGuiContext* imgui);
	
protected:
	void refresh(CodeBase::TYPE_OPERATION type = CodeBase::MOVE) { updating = true; tipo = type; };
	int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
	void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);

public:
	Code(Entity* e, modules::graphics::Graphic* g, Component* p = NULL) :Component(e, g,p) {};
	~Code();
	template<class T>
	T* linkClass(void * parent=NULL);
	CodeBase* linkDirectClass(CodeBase* base, void* parent = NULL);
	void update() {
		if (codigoBase != NULL) {
			codigoBase->update();
		}
	}
	void preUpdate() {
		if (codigoBase != NULL) {
			codigoBase->preUpdate();
			if (updating) {
				codigoBase->update();
				updating = false;
			}
		}
	}
	void start() {
		if(codigoBase != NULL) {
			codigoBase->start();
			
		}
	}
	void destroy() {
		if (codigoBase != NULL) {
			codigoBase->destroy();
		}
	}
	void setEntity(Entity * e) {
		if (codigoBase) {
			codigoBase->setEntity(e);
		}
	}
	Input* getInput() {
		return input;
	}
	void setInput(Input*i) {
		if (codigoBase) {
			codigoBase->setInput(i);
		}
		input = i;
	}
	
	TYPE_COMPONENT componentType() { return CODE; };

	void unlinkCodeBase();
	void relinkCodeBase();

	


	void setName(const char* n);
	std::string getName() override;

	TYPE_OBJECT_SERIALIZABLES getType() { return TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_CODE; };
};
template<class T>
inline T* Code::linkClass(void* parent) {
	
	if (std::is_base_of<CodeBase, T>::value) {
		T* codigo = new T();
		//codigoBase = (CodeBase *)codigo;
		linkDirectClass((CodeBase*)codigo, parent);
		
		return (T *)codigoBase;
	}
	return NULL;
}

;
#endif // !__CODE


