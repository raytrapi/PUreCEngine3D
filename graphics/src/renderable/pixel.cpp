#include "pixel.h"

renderable::Pixel::Pixel(){
	p = new float[nPixel];
}

renderable::Pixel::~Pixel(){
	delete[]p;
}

void renderable::Pixel::setColor(float r, float g, float b, float a){
	this->p[0] = r>=0 && r<=1?r:0;
	this->p[1] = g >= 0 && g <= 1 ? g : 0;
	this->p[2] = b >= 0 && b <= 1 ? b : 0;
	this->p[3] = a >= 0 && a <= 1 ? a : 1;
}
