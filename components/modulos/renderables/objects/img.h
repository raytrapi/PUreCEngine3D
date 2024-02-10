#ifndef _RND_IMG
#define _RND_IMG


#include "../../../utilidades/global/screen.h"
#include "pixel.h"
#include "object.h"
#include "../../../src/exportar.h"
namespace renderable {
	class EXPORTAR_COMPONENTE Img :public Object {
		Pixel *** imagen=0;
		float* data = 0;
		float ancho=0;
		float alto=0;
		float right=0;
		float left=0;
		float top=0;
		float bottom=0;
		int bPixel=4;
		unsigned int idTextura = 0;
		void liberarImagen();
		void calcularUV();

		bool conMinimap = true;
		bool pixelado = false;

		bool editable = false;
	public:
		Img();
		~Img();
		Object::TYPE getType();
		//TODO: Crear método para redimensionar la imagen
		float* setSize(float width, float height);

		Pixel * getPixel(short int x, short int y) {
			return imagen[x][y];
		};
		void setPixel(short int x, short int y, Pixel* p);
		void setPixel(short int x, short int y, float r, float g, float b, float a);
		float getWidth() { return ancho; };
		float getHeight() { return alto; };
		void setPosition(float x, float y, float z);
		float* getData();
		float getRight();
		float getLeft();
		float getTop();
		float getBottom();
		unsigned int getId();
		void setId(unsigned int id);

		bool isMinMap() { return conMinimap; };
		void setMinMap(bool set = true) { conMinimap = set; };
		bool isNearest() { return pixelado; };
		void setNearest(bool set = true) { pixelado = set; };
		bool isEditable() { return editable; };
		void setEditable(bool set = true) { editable = set; };

	};
	
}
#endif // !_RND_IMG
