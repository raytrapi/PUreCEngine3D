#include"hormiga.h"

Hormiga::Hormiga(long id,long x, long y, float energia){
	this->id = id;
	this->x = x;
	this->y = y;
	this->energia = energia;
	std::srand(std::time(0)+id);
	int angulo = std::rand() % 360;
	direccion = angulo * M_PI / 180;//Angulo en radianes
	buscarDireccion(angulo - 60, angulo + 60);
}

void Hormiga::mover(long limiteX1, long limiteY1, long limiteX2, long limiteY2) {
	if (distancia <= 0) {
		long direccionGrados = direccion * 180 / M_PI;
		buscarDireccion(direccionGrados - 60, direccionGrados +60);
	}
	//double dt = Time::deltaTime();
	double velocidad = 0.9;// Time::deltaTime() * 5;
	x += (cos(direccion))* velocidad;
	y += (sin(direccion))* velocidad;
	distancia -= velocidad;
	energia -= 0.01;// *Time::deltaTime();
	if (x < limiteX1) {
		x = limiteX1;
		long direccionGrados = direccion * 180 / M_PI;
		buscarDireccion(300- direccionGrados, 360- direccionGrados);
	} else if(x > limiteX2) {
		x = limiteX2;
		long direccionGrados = direccion * 180 / M_PI;
		buscarDireccion(300 - direccionGrados, 360 - direccionGrados);
	}
	if (y < limiteY1) {
		long direccionGrados = direccion * 180 / M_PI;
		buscarDireccion(300 - direccionGrados, 360 - direccionGrados);
		y = limiteY1;
	} else if (y > limiteY2) {
		y = limiteY2;
		long direccionGrados = direccion * 180 / M_PI;
		buscarDireccion(300 - direccionGrados, 360 - direccionGrados);
	}
}

void Hormiga::buscarDireccion(int gradoInferior, int gradoSuperior) {
	if (gradoInferior > gradoSuperior) {
		int gradoIntermedio = gradoSuperior;
		gradoSuperior = gradoInferior;
		gradoInferior = gradoIntermedio;
	}
	int angulo=(std::rand() % (gradoSuperior-gradoInferior))+gradoInferior;
	direccion = angulo * M_PI / 180;//Angulo en radianes
	distancia = std::rand() % (int)(energia * 0.01);
}
