#ifndef _INTERFACE
#define _INTERFACE


#include "../src/module.h"
#include "../../utilidades/log/log.h"
#include "../../utilidades/global/global.h"
//#include "../../utilidades/global/input.h"



namespace modules {
	namespace graphics {
		class EXPORTAR_MODULO Interface :public Module {
		protected:
			Global* global=NULL;
		public:
			virtual void render() = 0;
			Module::MODULES_TYPE tipo() { return Module::MODULES_TYPE::INTERFACE; };
			void setGlobal(Global* g) { global = g; };
		};
	}
}

/*inline virtual modulos::graficos::Grafico::~Grafico() {
	Renderable::clearRenderable();
}
/**/


#endif // 