#ifndef __MOTORGL
#define __MOTORGL


#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h> 


#include "../../../src/motor.h"
#include "../../imagenes/imagen.h"
#include "../../imagenes/png.h"
#include "../../src/modulos.h"
#include "../src/renderable/object.h"
#include "../src/renderable/pixel.h"
#include "../src/renderable/img.h"
//#include <utilidades.h>
#include <log.h>
#include <modulos.h>
#include <vector>
class  MotorGL:public modulos::graficos::Grafico {
	private:
		
		HDC ghDC;
		HGLRC ghRC;
		BOOL bSetupPixelFormat(HDC);
		imagenes::Imagen* imagen;
		float color = 0;
		bool subiendo = true;
		double ancho;
		double alto;
	public:
		MotorGL();
		~MotorGL();
		void renderizar();
		void renderizar(void *);
		void inicializar(void * contexto, double ancho, double alto);
		char* nombre() { return (char*)"OPEN GL"; };
		
};
#endif // !__MOTORGL
