#include "timer.h"

void Time::update(){
	std::chrono::system_clock::time_point actual;
	double milisegundos = 0;
	while (milisegundos == 0) {
		actual = std::chrono::system_clock::now();
		milisegundos = std::chrono::duration_cast<std::chrono::milliseconds>(actual - anterior).count();
	}
	delta = milisegundos>0?milisegundos/1000.0f:0;
	
	/*if (delta > 1.2) {
		delta = 1;
	}/**/
	//double microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(actual - anterior).count();
	//delta = microsegundos > 0 ? microsegundos / 1000000 : 0;

	anterior = actual;
}
void Time::reset() {
	delta = 0;
	anterior = std::chrono::system_clock::now();
}
void Time::freeze(bool stop) {
	if (stop) {
		congelado = std::chrono::system_clock::now();
	} else {
		std::chrono::system_clock::time_point actual=std::chrono::system_clock::now();
		anterior = actual-(congelado-anterior);
	}
};
/**
* devuelve los microsegundos desde la última operación
* @return microsegundos
*/
double Time::deltaTime() {
	return delta;
}
double Time::diff(std::chrono::system_clock::time_point previus) {
	std::chrono::system_clock::time_point actual = std::chrono::system_clock::now();
	return std::chrono::duration_cast<std::chrono::milliseconds>(actual - previus).count();
}
std::chrono::system_clock::time_point Time::time() {
	return std::chrono::system_clock::now();
}

std::chrono::system_clock::time_point Time::anterior = std::chrono::system_clock::now();
std::chrono::system_clock::time_point Time::congelado;
double Time::delta=0;