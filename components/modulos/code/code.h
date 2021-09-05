#ifndef __CODE
#define __CODE
#include <type_traits>
#include "../src/component.h"
#include "../src/codeBase.h"

class EXPORTAR_COMPONENTE Code : public Component {
	CodeBase* codigoBase = NULL;
	bool updating = false;
	
	
	CodeBase::TYPE_OPERATION tipo = CodeBase::MOVE;
protected:
	void refresh(CodeBase::TYPE_OPERATION type = CodeBase::MOVE) { updating = true; tipo = type; };
public:
	template<class T>
	void linkClass();
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
};
template<class T>
inline void Code::linkClass() {
	if (std::is_base_of<CodeBase, T>::value) {
		codigoBase = new T();
		codigoBase->setEntity(entidad);
	}
};
#endif // !__CODE

