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
	
	
	CodeBase::TYPE_OPERATION tipo = CodeBase::MOVE;
	Input* input;
protected:
	void refresh(CodeBase::TYPE_OPERATION type = CodeBase::MOVE) { updating = true; tipo = type; };
public:
	Code(Entity* e, modules::graphics::Graphic* g, Component* p = NULL) :Component(e, g,p) {};
	~Code();
	template<class T>
	T* linkClass(void * parent=NULL);
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
		codigoBase->setEntity(e);
	}
	Input* getInput() {
		return input;
	}
	void setInput(Input*i) {
		codigoBase->setInput(i); 
		input = i;
	}
	TYPE_COMPONENT componentType() { return CODE; };
	
};
template<class T>
inline T* Code::linkClass(void* parent) {
	modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
	if (std::is_base_of<CodeBase, T>::value) {
		T* codigo = new T();
		codigoBase = (CodeBase *)codigo;
		codigoBase->init();
		//DBG("Entidad ... ", entidad);
		codigoBase->setEntity(entidad);
		codigoBase->setParent(parent);
		codigoBase->setInput(g->getInput());
		codigoBase->setGlobal(g->getGlobal());
		codigoBase->setGraphic(g);
		return (T *)codigoBase;
	}
	return NULL;
};
#endif // !__CODE


