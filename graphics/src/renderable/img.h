#ifndef _RND_IMG
#define _RND_IMG


#include "../../../utilidades/nucleo/screen.h"
#include "pixel.h"
#include "object.h"
#include "../motor.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Img :public Object {
		Pixel *** imagen=0;
		float* data = 0;
		int ancho;
		int alto;
		int bPixel=4;
	public:
		Img();
		~Img();
		Object::TYPE getType();
		//TODO: Crear método para redimensionar la imagen
		//void 

		Pixel * getPixel(short int x, short int y) {
			return imagen[x][y];
		};
		void setPixel(short int x, short int y, Pixel* p);
		void setPixel(short int x, short int y, float r, float g, float b, float a);
		int getWidth() { return ancho; };
		int getHeight() { return alto; };
		float* getData();
	};
	
}
#endif // !_RND_IMG
