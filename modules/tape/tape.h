#ifndef _CARTUCHO
#define _CARTUCHO


#include "../src/module.h"
#include "../graphic/motor.h"
#include <vector>
#include "../../utilidades/files/filesControl.h"
#include <string>
#include <functional>

namespace modules {

	class EXPORTAR_MODULO Tape :public Module {
	protected:

		std::vector<void *> renders;
		short int ancho=800;
		short int alto=600;
		bool ejecutando = true;
		virtual void setScreenSize(short int width, short int height) {};
		//modules::graphics::Graphic* graphic = 0;
		static std::string projectName;
		static std::function<void(const char*)> callbackLoad;
		static Tape* cinta;
	public:
		//void setGraphic(modules::graphics::Grafico* graphic) { Graphic = graphic; };
		virtual void update() {};
		virtual void start() {};
		virtual void destroy() {};
		void detener() {
			ejecutando = false;

			modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
			if (g) {
				g->removeEntities();
			}
			destroy();
		}
		virtual void onFocus(bool) {};

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
		static void load(const char* project, modules::Tape* tape, std::function<void(const char*)>);
	};

}



#endif // 