#include "hormiguero.h"


Hormiguero::Hormiguero(long x,long y, int _hormigas){
	this->x = x;
	this->y = y;
	//Creamos hormigas
	for (int i = 0; i < _hormigas; i++) {
		this->hormigas.push_back(new Hormiga(i,x, y,200));

	}
	
}

Hormiguero::~Hormiguero(){
	for (std::vector<Hormiga*>::iterator it = hormigas.begin(); it != hormigas.end(); it++) {
		delete (*it);
	}
	hormigas.clear();
}

long Hormiguero::cogerX(){
	return x;
}

long Hormiguero::cogerY(){
	return y;
}
