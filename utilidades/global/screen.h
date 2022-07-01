#ifndef _SCREEN
#define _SCREEN

#include "../utiles/utilidades.h"
class EXPORTAR_UTILIDADES Screen {
	 static int ancho;
	 static int alto;
	 static float ancho_2;
	 static float alto_2;
public:
	static int getWidth();
	static int getHeight();
	
	static float getWidthNormal(double n);
	static float getHeightNormal(double n);
	static void setDimension(int width, int height);
};


#endif // !_SCREEN
