#ifndef __PNG
#define __PNG

//#include<png.h>
#include<malloc.h>
#include"imagen.h"
//#include"../../../src/modulos.h"
#include"motorExport.h"
namespace imagenes {
	class EXPORTAR_MODULO_GRAFICO PNG {
		
		public:
			static   Imagen * cargar(const char* nombreFichero);
	};
}
#endif // !__PNG
//template EXPORTAR_MOTOR inline imagenes::Imagen* imagenes::PNG::cargar(const char*);