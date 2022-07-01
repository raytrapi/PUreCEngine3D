#ifndef __MOTORGL
#define __MOTORGL


#include <Windows.h>
#include <gl\gl.h>
#include <gl\glu.h> 



#include "../../imagenes/imagen.h"
#include "../../imagenes/png.h"
#include "../src/renderable/object.h"
#include "../src/renderable/pixel.h"
#include "../src/renderable/cube.h"
#include "../src/renderable/img.h"


//Luego quitaremos
#include "../../utilidades/global/mouse.h"

//#include <utilidades.h>
#include <log.h>
#include <module.h>
#include <motor.h>
#include <vector>
class  MotorGL:public modules::graphics::Graphic {
	private:
		
		HDC ghDC;
		HGLRC ghRC;
		BOOL bSetupPixelFormat(HDC);
		imagenes::Imagen* imagen;
		float color = 0;
		bool subiendo = true;
		double ancho;
		double alto;

		float xMouse = 0;
		float yMouse = 0;
		float anguloX = 0;
		float anguloY = 0;

		void inicializarLuz();
		void renderizarCubo(renderable::Cube *);
		void renderizarImagen(renderable::Img* img);
	public:
		MotorGL();
		~MotorGL();
		void preRender() {};
		void render();
		void render(void *);
		void renderInterface() {};
		void postRender() {};
		bool inicializar(void * contexto, double ancho, double alto);
		char* nombre() { return (char*)"OPENGL 2"; };
		
		void ponerCamara(float posX, float posY, float posZ, float targetX, float targetY, float targetZ);
		bool addTexture(float* image, unsigned int length, int width, int height, int& idTexture, modules::graphics::TextureImg::FORMAT_COLOR typeColor) { return true; }
		Entity* drawLine(float* vertex, unsigned countVertex, float r, float g, float b, float a, unsigned width = 1);
};
#endif // !__MOTORGL
