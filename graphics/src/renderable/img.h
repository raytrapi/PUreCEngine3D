#ifndef _RND_IMG
#define _RND_IMG


#include "../../../utilidades/global/screen.h"
#include "pixel.h"
#include "object.h"
#include "../motorExport.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Img :public Object {
		Pixel *** imagen=0;
		float* data = 0;
		int ancho;
		int alto;
		float right;
		float left;
		float top;
		float bottom;
		int bPixel=4;
		unsigned int idTextura = 0;
		void liberarImagen();
		void calcularUV();
	public:
		Img();
		~Img();
		Object::TYPE getType();
		//TODO: Crear método para redimensionar la imagen
		float* setSize(int width, int height);

		Pixel * getPixel(short int x, short int y) {
			return imagen[x][y];
		};
		void setPixel(short int x, short int y, Pixel* p);
		void setPixel(short int x, short int y, float r, float g, float b, float a);
		int getWidth() { return ancho; };
		int getHeight() { return alto; };
		void setPosition(float x, float y, float z);
		float* getData();
		float getRight();
		float getLeft();
		float getTop();
		float getBottom();
		unsigned int getId();
		void setId(unsigned int id);
	};
	
}
#endif // !_RND_IMG
