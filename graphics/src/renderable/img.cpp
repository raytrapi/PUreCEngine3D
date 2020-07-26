#include "img.h"
namespace renderable{
	void Img::liberarImagen() {
		if (imagen != 0) {
			for (int i = 0; i < ancho; i++) {
				for (int j = 0; j < alto; j++) {
					delete imagen[i][j];
				}
				delete[]imagen[i];
			}
			delete[] imagen;
		}
		if (data != 0) {
			delete[] data;
		}
	}
	void Img::calcularUV() {
		float y=(float)pY/ (float)Screen::getHeight();
		float x= (float)pX/ (float)Screen::getWidth();
		top = (float)alto / (float)Screen::getHeight()+y;
		bottom = y;
		left = x;
		right = (float)ancho / (float)Screen::getWidth() + x;
	}
	Img::Img(){
		/*ancho = Screen::getWidth();
		alto = Screen::getHeight();
		imagen = new Pixel**[ancho];
		for (int i = 0; i < ancho; i++) {
			imagen[i] = new Pixel*[alto];
			for (int j = 0; j < alto; j++) {
				imagen[i][j] = new Pixel;
			}
		}*/
	}

	Img::~Img(){
		liberarImagen();
	}

	Object::TYPE Img::getType()	{
		return Object::TYPE::IMG;
	}

	float* Img::setSize(int width, int height) {
		liberarImagen();
		ancho = width;
		alto = height;
		imagen = new Pixel * *[ancho];
		for (int i = 0; i < ancho; i++) {
			imagen[i] = new Pixel * [alto];
			for (int j = 0; j < alto; j++) {
				imagen[i][j] = new Pixel;
			}
		}
		//float proporcionAncho = 1 / Screen::getWidth();
		//float proporcionAlto = 1 / Screen::getHeight();
		calcularUV();
		return getData();
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
	void Img::setPosition(float x, float y, float z) {
		pX = x;
		pY = y;
		pZ = z;
		calcularUV();
	}
	float* Img::getData(){
		if (data == 0) {
			long tamaño = (alto * ancho * bPixel);
			data = new float[tamaño];
			long pos = 0;
			for (int y = 0; y < alto; y++) {
				for (int x = 0; x < ancho; x++) {
					Pixel *p = imagen[x][y];
					data[pos++] = p->R();
					data[pos++] = p->G();
					data[pos++] = p->B();
					data[pos++] = p->A();
				}
			}
		}
		return data;
	}
	float Img::getRight() {
		return right;
	}
	float Img::getLeft() {
		return left;
	}
	float Img::getTop() {
		return top;
	}
	float Img::getBottom() {
		return bottom;
	}
	unsigned int Img::getId() {
		return idTextura;
	}
	void Img::setId(unsigned int id) {
		idTextura = id;
	}
	/**/
}
