#ifndef _SCREEN
#define _SCREEN

#include "../utiles/utilidades.h"
 class EXPORTAR_UTILIDADES Screen {
	 static int ancho;
	 static int alto;
public:
	static int getWidth();
	static int getHeight();
	static void setDimension(int width, int height);
};


#endif // !_SCREEN
