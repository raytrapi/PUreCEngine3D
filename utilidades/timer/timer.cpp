#include "timer.h"

void Time::update(){
	std::chrono::system_clock::time_point actual = std::chrono::system_clock::now();
	double milisegundos = std::chrono::duration_cast<std::chrono::milliseconds>(actual - anterior).count();
	delta = milisegundos>0?milisegundos/1000:0;
	//double microsegundos = std::chrono::duration_cast<std::chrono::microseconds>(actual - anterior).count();
	//delta = microsegundos > 0 ? microsegundos / 1000000 : 0;

	anterior = actual;
}
void Time::reset() {
	delta = 0;
	anterior = std::chrono::system_clock::now();
}
double Time::deltaTime() {
	return delta;
}
std::chrono::system_clock::time_point Time::anterior = std::chrono::system_clock::now();
double Time::delta=0;