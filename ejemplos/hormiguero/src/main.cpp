#include"main.h"
REGISTRAR_MODULO(JHormiguero);

void JHormiguero::update() {
	std::chrono::system_clock::time_point anterior = std::chrono::system_clock::now();
	float radio=2;
	float linea = Screen::getWidth() * 4.f;
	std::vector<Hormiga*>hormigas = hormiguero->cogerHormigas();
	for (std::vector<Hormiga*>::iterator it = hormigas.begin(); it != hormigas.end(); it++) {
		Hormiga* hormiga = (*it);
		long posicion = (hormiga->cogerY() * linea + hormiga->cogerX() * 4);
		lienzo[posicion++] = 0;
		lienzo[posicion++] = 0;
		lienzo[posicion++] = 0;
		lienzo[posicion++] = 0;
	}

	for (float r = 0; r < M_PI*2; r += 0.01f) {
		long x = xHormiguero + (radio * cos(r));
		long y = yHormiguero + (radio * sin(r));
		long posicion = (y * linea + x * 4);
		lienzo[posicion++] = 0;
		lienzo[posicion++] = 1;
		lienzo[posicion++] = 0;
		lienzo[posicion++] = 1; 
	}/**/
	
	for (std::vector<Hormiga*>::iterator it = hormigas.begin(); it != hormigas.end(); it++) {
		Hormiga* hormiga = (*it);
		hormiga->mover(Screen::getWidth(),Screen::getHeight());
		long posicion = (hormiga->cogerY() * linea + hormiga->cogerX() * 4);
		lienzo[posicion++] = 1;
		lienzo[posicion++] = 1;
		lienzo[posicion++] = 1;
		lienzo[posicion++] = 1;
	}/**/
	/*long posicion = 0;
	for (long y = 0; y < Screen::getHeight(); y++) {
		for (long x = 0; x < Screen::getWidth(); x++) {
			lienzo[posicion++] = 1;
			lienzo[posicion++] = 0;
			lienzo[posicion++] = 0;
			lienzo[posicion++] = 1;
		}
	}/**/
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

void JHormiguero::start() {
	xHormiguero = Screen::getWidth() * 0.5;
	yHormiguero = Screen::getHeight() * .5;
	hormiguero = new Hormiguero(xHormiguero, yHormiguero, 100);
	//Creamos un render de tipo gráfico
	lienzo=Renderable::createRenderable<renderable::Img>()->getData();
}

void JHormiguero::destroy(){
	delete hormiguero;
}
