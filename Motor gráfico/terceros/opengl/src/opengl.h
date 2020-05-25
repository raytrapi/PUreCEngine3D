#ifndef __MOTORGL
#define __MOTORGL


#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h> 

#include "../../../src/motor.h"
#include "../../imagenes/imagen.h"
#include "../../imagenes/png.h"
//#include <utilidades.h>
#include <log.h>
class  MotorGL:public modulos::graficos::Grafico {
	private:
		
		HDC ghDC;
		HGLRC ghRC;
		BOOL bSetupPixelFormat(HDC);
		imagenes::Imagen* imagen;
	public:
		MotorGL();
		~MotorGL();
		void renderizar();
		void inicializar(HWND contexto, double ancho, double alto);
};
#endif // !__MOTORGL
