#include"main.h"
REGISTRAR_MODULO(Minecraft);

void Minecraft::update() {
	std::chrono::system_clock::time_point anterior = std::chrono::system_clock::now();
	
	//cubo->pX += (10 * Time::deltaTime());
	//cubo->pY += (1 * Time::deltaTime());
	//cubo->pZ += (1 * Time::deltaTime());

	cubo->rX += (20 * Time::deltaTime());
	cubo->rY += (35 * Time::deltaTime());
	cubo->rZ += (40 * Time::deltaTime());


	std::chrono::system_clock::time_point actual = std::chrono::system_clock::now();
	double delta = std::chrono::duration_cast<std::chrono::nanoseconds>(actual - anterior).count();
	/*if (tiempoEjecucion > 0) {
		tiempoEjecucion = (tiempoEjecucion + delta) * 0.5;
	}
	else {
		tiempoEjecucion = delta;
	}/**/
	segundos += Time::deltaTime();
	if (segundos >= 1) {
		segundos = 0;
		debug(delta);
	}
	/**/
}

void Minecraft::start() {
	cubo = Renderable::createRenderable<renderable::Cube>();
	cubo->pX = 500;
	cubo->pY = 500;
	cubo->pZ = 0;
	cubo->rX = 0;
	cubo->rY = 0;
	cubo->rZ = 0;
	cubo->l = 100;
}

void Minecraft::destroy(){
}
