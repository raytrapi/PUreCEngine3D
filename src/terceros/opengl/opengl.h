#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h> 

#include "../../Motor/Motor.h"
class MotorGL :public MotorGrafico {
	private:
		
		HDC ghDC;
		HGLRC ghRC;
		BOOL bSetupPixelFormat(HDC);
	public:

		~MotorGL();
		void renderizar();
		void inicializar(HWND contexto, double ancho, double alto);
};