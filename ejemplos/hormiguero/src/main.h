#ifndef _JUEGOHORMIGUERO
#define _JUEGOHORMIGUERO
#define _USE_MATH_DEFINES
#include"../cartucho/src/cartucho.h"
#include <modulos.h>
#include <timer/timer.h>
#include <nucleo/screen.h>
#include "../graphics/src/renderable/renderable.h"
#include "../graphics/src/renderable/pixel.h"
#include "hormiguero.h"
#include "hormiga.h"
#include <cmath>
#include <list>



class  JHormiguero :public modulos::Cartucho {
	float *lienzo;
	bool subiendo = true;
	float c = 0;
	
	//Controlo tiempos
	double segundos = 0;
	double tiempoEjecucion = 0;


	//Variables del juego
	Hormiguero *hormiguero;
	long xHormiguero;
	long yHormiguero;

public:
	void update();
	void start();
	void destroy();
	char* nombre() { return (char*)"HORMIGUERO: Hormigas buscando alimento"; };
};
#endif // !_JUEGOHORMIGUERO
