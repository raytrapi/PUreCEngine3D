#include "screen.h"
int Screen::getWidth() {
	return ancho;
};
int Screen::getHeight() {
	return alto;
}
void Screen::setDimension(int width, int height) {
	ancho = width;
	alto = height;
}
int Screen::ancho = 0;
int Screen::alto = 0;