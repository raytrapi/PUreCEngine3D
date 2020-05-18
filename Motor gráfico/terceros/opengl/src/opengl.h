#ifndef __MOTORGL
#define __MOTORGL


#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h> 

#include "../../../src/Motor.h"
#include "../../imagenes/imagen.h"
#include "../../imagenes/png.h"
class EXPORTAR_MOTOR MotorGL :public MotorGrafico {
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