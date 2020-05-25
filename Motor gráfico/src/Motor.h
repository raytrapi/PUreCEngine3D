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


namespace modulos {
	namespace graficos {
		class EXPORTAR_MODULO_GRAFICO Grafico {
		public:
			virtual void renderizar() = 0;
			virtual void inicializar(HWND, double, double) = 0;

		};

	}
}
//template void EXPORTAR_MOTOR MotorGrafico::inicializar(HWND, double, double);
#define REGISTRAR_MOTOR_GRAFICO(classname) \
	extern "C" modulos::graficos::Grafico * crearInstancia() {\
			return (modulos::graficos::Grafico *) new classname();\
	}\
	extern "C" void destroy(modulos::graficos::Grafico* p) {\
	    delete p;\
	}
#ifdef _WIN32
extern "C" __declspec(dllexport) modulos::graficos::Grafico * crearInstancia();
extern "C" __declspec(dllexport) void destroy(modulos::graficos::Grafico*); 
#endif

#endif // 