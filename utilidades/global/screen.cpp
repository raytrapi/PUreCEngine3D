#include "screen.h"
int Screen::getWidth() {
	return ancho;
};
int Screen::getHeight() {
	return alto;
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
}
int Screen::ancho = 0;
int Screen::alto = 0;
float Screen::ancho_2 = 0;
float Screen::alto_2 = 0;