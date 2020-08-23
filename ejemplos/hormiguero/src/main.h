#ifndef _JUEGOHORMIGUERO
#define _JUEGOHORMIGUERO
#define _USE_MATH_DEFINES

#include <module.h>
#include <tape.h>
#include <timer/timer.h>
#include <global/screen.h>
#include "../graphics/src/renderable/renderable.h"
#include "../graphics/src/renderable/pixel.h"
#include "hormiguero.h"
#include "hormiga.h"
#include <cmath>
#include <list>
#include <cstdlib>
#include <ctime>


class  JHormiguero :public modules::Tape {
	float *lienzo=0; //Lienzo de pintado final
	float * entorno = 0; //Representa todo aquello inmutable como el hormiguero
	int *comida = 0; //Contiene información de comida
	float *hormonasHormiga = 0; //Contiene información de hormonas
	float* hormonasComida = 0; //Contiene información de hormonas
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
