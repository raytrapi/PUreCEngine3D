#ifndef _CARTUCHO
#define _CARTUCHO
#ifdef _WIN32
#include <Windows.h>

#ifdef EXPORTAR_MODULO_CARTUCHO
#define EXPORTAR_MODULO_CARTUCHO   __declspec(dllexport)
#else
#define EXPORTAR_MODULO_CARTUCHO   __declspec(dllimport)
#endif
#else
#define EXPORTAR_MODULO_CARTUCHO
#endif // WIN32



#include <modulos.h>
#include <vector>

namespace modulos {

	class EXPORTAR_MODULO_CARTUCHO Cartucho :public Modulo {
	protected:

		std::vector<void *> renders;
	public:
		virtual void update() {};
		virtual void start() {};
		virtual void destroy() {};
		~Cartucho() {
			
			for (int i = 0; i < renders.size();i++) {
				delete renders[i];
			}
		};
		std::vector<void*> renderes() {
			return renders;
		}
		Modulo::TIPOS_MODULOS tipo() { return Modulo::CARTUCHO; };
		std::vector<void*>* getRenderizables() { return &renders; };
	};

}



#endif // 