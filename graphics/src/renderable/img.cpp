#include "img.h"
namespace renderable{
	Img::Img(){
		ancho = Screen::getWidth();
		alto = Screen::getHeight();
		imagen = new Pixel**[ancho];
		for (int i = 0; i < ancho; i++) {
			imagen[i] = new Pixel*[alto];
			for (int j = 0; j < alto; j++) {
				imagen[i][j] = new Pixel;
			}
		}
	}

	Img::~Img(){
		if (imagen != 0) {
			for (int i = 0; i < ancho; i++) {
				for (int j = 0; j < alto; j++) {
					delete imagen[i][j];
				}
				delete []imagen[i];
			}
			delete [] imagen;
		}
		if (data != 0) {
			delete[] data;
		}
	}

	Object::TYPE Img::getType()	{
		return Object::TYPE::IMG;
	}


	void Img::setPixel(short int x, short int y,Pixel *p) {
		imagen[x][y]->setColor(p->R(), p->G(), p->B(), p->A());
		if (data != 0) {
			delete[] data;
			data = 0;
		}
	}
	void Img::setPixel(short int x, short int y, float r, float g, float b, float a){
		imagen[x][y]->setColor(r, g, b, a);
		if (data != 0) {
			delete[] data;
			data = 0;
		}
	}
	float* Img::getData(){
		if (data == 0) {
			data = new float[(alto * ancho * bPixel)];
			int pos = 0;
			for (int y = 0; y < alto; y++) {
				for (int x = 0; x < alto; x++) {
					Pixel *p = imagen[x][y];
					data[pos] = p->R();
					data[pos+1] = p->G();
					data[pos+2] = p->B();
					data[pos+3] = p->A();
					pos += 4;
				}
			}
		}
		return data;
	}/**/
}
