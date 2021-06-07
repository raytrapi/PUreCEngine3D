#ifndef _CARTUCHO
#define _CARTUCHO


#include "../src/module.h"
#include "../graphic/motor.h"
#include <vector>
#include "../../utilidades/files/filesControl.h"
#include <string>
#include <functional>
#include "../../components/src/entity.h"

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
		static std::function<void()> callbackLoad;
		static Tape* cinta;
		bool detener = false;
		bool deteniendo = false;

		std::function<void()>callback=NULL;
	public:
		//void setGraphic(modules::graphics::Grafico* graphic) { Graphic = graphic; };
		virtual void update() {};
		virtual void start() {};
		virtual void destroy() {};
		void stop() {
			ejecutando = false;
			deteniendo = true;
			detener = false;
			modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
			if (g) {
				g->removeAll();
				
			}
			
			destroy();
			//deteniendo = false;
			if (callback) {
				callback();
			}
		}
		void sendStop() {
			detener = true;
			//deteniendo = false;
		}
		bool isStoping() { return deteniendo; };
		bool isOrderStop() { return detener; };
		
		void onEnd(std::function<void()>callback) {
			this->callback = callback;
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
			callback == NULL;
			
		};
		std::vector<void*> renderes() {
			return renders;
		}
		Module::MODULES_TYPE tipo() { return Module::TAPE; };
		std::vector<void*>* getRenderizables() { return &renders; };
		static void load(const char* project, modules::Tape* tape, std::function<void()>);

	};

}



#endif // 