#include"hormiga.h"

Hormiga::Hormiga(long id,long x, long y, float energia){
	this->id = id;
	this->x = x;
	this->y = y;
	this->energia = energia;
	std::srand(std::time(0));
	
}

void Hormiga::mover(long limiteX, long limiteY) {
	
	int r = std::rand() % 3;
	long desplazamientoX = r-1;
	r = std::rand() % 3;
	long desplazamientoY = r -1;
	x += (desplazamientoX);// *Time::deltaTime());
	y += (desplazamientoY);// * Time::deltaTime());
	if (x < 0) {
		x = 0;
	} else if(x > limiteX) {
		x = limiteX;
	}
	if (y < 0) {
		y = 0;
	} else if (y > limiteY) {
		y = limiteY;
	}
}
