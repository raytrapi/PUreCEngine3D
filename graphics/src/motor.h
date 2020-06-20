#ifndef _MOTORGRAFICO
#define _MOTORGRAFICO
#ifdef _WIN32
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
#include <list>
//#include "renderable/renderable.h"
namespace modulos {
	namespace graficos {
		class EXPORTAR_MODULO_GRAFICO Grafico:public Modulo {
			//std::list<void*>elementosRenderizar;
			//TODO: Ver si aceleramos el pintado si procesamos nosotros la capa.
			//byte* lienzo = null;
		public:
			/*~Grafico() {
				//Renderable::clearRenderable();
			};/**/
			virtual void renderizar() = 0;
			virtual void renderizar(void *) = 0;
			//virtual void insertarMapaBits(byte*, double ancho, double alto, double x, double y, double z)=0;
			virtual void inicializar(void*, double, double) = 0;
			Modulo::TIPOS_MODULOS tipo() { return Modulo::TIPOS_MODULOS::GRAFICO; };
			
		};

	}
}
/*inline virtual modulos::graficos::Grafico::~Grafico() {
	Renderable::clearRenderable();
}
/**/

#endif // 