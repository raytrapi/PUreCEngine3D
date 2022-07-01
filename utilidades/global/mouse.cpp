#include "mouse.h"

/*bool Mouse::mouseOver() {
	return encima;
}/**/
std::tuple<double, double> Mouse::getPosition(){
	return { x, y };
}

void Mouse::setPosition(double _x, double _y) {
		x = _x;
		y = _y;
}
void Mouse::setButtomDown(BUTTOMS buttom, int mod) {
	botones[buttom] = true;
};
void Mouse::setButtomUp(BUTTOMS buttom, int mod) {
	botones[buttom] = false;
};
bool Mouse::isButtomPress(BUTTOMS buttom) {
	return botones[buttom];
};
/*void Mouse::setOver(bool over) {
	if (over != encima) {
		utiles::Log::debug((over)?"Encima":"Fuera");
	}
	encima = over;
}/**/
bool Mouse::encima;
double Mouse::x = 0;
double Mouse::y = 0;
std::map<double, bool> Mouse::botones;