#include "pixel.h"

renderable::Pixel::Pixel(){
	p = new float[nPixel];
}

renderable::Pixel::~Pixel(){
	delete[]p;
}

void renderable::Pixel::setColor(float r, float g, float b, float a){
	this->p[0] = r < 0 ? 0 : (r > 1 ? 1 : r);
	this->p[1] = g < 0 ? 0 : (g > 1 ? 1 : g);
	this->p[2] = b < 0 ? 0 : (b > 1 ? 1 : b);
	this->p[3] = a < 0 ? 0 : (a > 1 ? 1 : a);
}
