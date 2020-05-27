#ifndef _MOTORGRAFICO
#define _MOTORGRAFICO
#ifdef WIN32
	#include <Windows.h>
	//#define EXPORTAR_MODULO_GRAFICO __declspec(dllexport)
	#ifdef EXPORTAR_MODULO_GRAFICO
		#define EXPORTAR_MODULO_GRAFICO   __declspec(dllexport)
	#else
		#define EXPORTAR_MODULO_GRAFICO   __declspec(dllimport)
	#endif
#else
	#define EXPORTAR_MODULO_GRAFICO
#endif // WIN32



#include <modulos.h>

namespace modulos {
	namespace graficos {
		class EXPORTAR_MODULO_GRAFICO Grafico:public Modulo {
		public:
			virtual void renderizar() = 0;
			virtual void inicializar(void*, double, double) = 0;
			Modulo::TIPOS_MODULOS tipo() { return Modulo::GRAFICO; };
			
		};

	}
}



#endif // 