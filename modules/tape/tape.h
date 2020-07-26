#ifndef _CARTUCHO
#define _CARTUCHO


#include "../src/module.h"
#include "../graphic/motor.h"
#include <vector>

namespace modules {

	class EXPORTAR_MODULO Tape :public Module {
	protected:

		std::vector<void *> renders;
		short int ancho=800;
		short int alto=600;
		bool ejecutando = true;
		virtual void setScreenSize(short int width, short int height) {};
		//modules::graphics::Graphic* Graphic = 0;
	public:
		//void setGraphic(modules::graphics::Grafico* graphic) { Graphic = graphic; };
		virtual void update() {};
		virtual void start() {};
		virtual void destroy() {};
		
		short int getScreenWidth() { return ancho; };
		short int getScreenHeight() { return alto; };
		void setEnd() { ejecutando = false; };
		bool isRunning() { return ejecutando; };
		~Tape() {
			
			for (int i = 0; i < renders.size();i++) {
				delete renders[i];
			}
			ejecutando = false;
		};
		std::vector<void*> renderes() {
			return renders;
		}
		Module::MODULES_TYPE tipo() { return Module::TAPE; };
		std::vector<void*>* getRenderizables() { return &renders; };
	};

}



#endif // 