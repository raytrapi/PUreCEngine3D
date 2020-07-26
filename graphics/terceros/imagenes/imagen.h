#ifndef __IMAGEN
#define __IMAGEN
#include <malloc.h>
//#include"../../../src/modulos.h"
#include"../../src/motorExport.h"
namespace imagenes {
	class EXPORTAR_MODULO_GRAFICO Imagen {
		int longitud = 0;
		int ancho = 0;
		int alto = 0;
		float* datos=NULL;
	public:
		~Imagen();
		int cogerLongitud();
		void setDatos(float*);
		float* cogerDatos();
		void ponerAncho(int);
		int cogerAncho();
		void ponerAlto(int);
		int cogerAlto();

	};
}

#endif // !__IMAGEN
