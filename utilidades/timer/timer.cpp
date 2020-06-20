#include "timer.h"

void Time::update(){
	std::chrono::system_clock::time_point actual = std::chrono::system_clock::now();
	delta = std::chrono::duration_cast<std::chrono::milliseconds>(actual - anterior).count();
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