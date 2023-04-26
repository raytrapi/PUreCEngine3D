#include "screen.h"
int Screen::getWidth() {
	return ancho;
};
int Screen::getHeight() {
	return alto;
}
float Screen::getScaleWidth() {
	return escalaAncho;
};
float Screen::getScaleHeight() {
	return escalaAlto;
}
float Screen::getWidthNormal(double n) {
	return ((float)n/ancho_2)-1;
}
float Screen::getHeightNormal(double n) {
	return ((float)n / alto_2) - 1;
}
void Screen::setDimension(int width, int height) {
	if (ancho != width) {
		ancho = width;
		ancho_2 = 0.5f * ancho;
	}
	if (alto != height) {
		alto = height;
		alto_2 = 0.5f * alto;
	}
	if (ancho > alto) {
		escalaAlto = (float)alto/ 2.f;
		escalaAncho = escalaAlto * ((float)ancho / (float)alto);
	} else {
		//float proporcion = alto / ancho;
		escalaAncho = (float)ancho/2.f;
		escalaAlto = escalaAncho * ((float)alto / (float)ancho);
	}/**/
}
int Screen::ancho = 0;
int Screen::alto = 0;
float Screen::ancho_2 = 0;
float Screen::alto_2 = 0;
float Screen::escalaAncho = 1000.f;
float Screen::escalaAlto = 1000.f;