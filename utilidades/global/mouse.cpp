#include "mouse.h"

bool Mouse::mouseOver() {
	return encima;
}

void Mouse::getPosition(float& _x, float& _y) {
	_x = x;
	_y = y;
	
	
}

void Mouse::setPosition(float x, float y, unsigned long flags) {
	//if (flags & 0x10) { //0x10 ->Boton central en Windows pulsado
		this->x = Screen::getWidthNormal(x);
		this->y = Screen::getHeightNormal(y);
	//}
	//utiles::Log::debug(x);
	//utiles::Log::debug(y);
}

void Mouse::setOver(bool over) {
	if (over != encima) {
		utiles::Log::debug((over)?"Encima":"Fuera");
	}
	encima = over;
}
bool Mouse::encima;
float Mouse::x;
float Mouse::y;