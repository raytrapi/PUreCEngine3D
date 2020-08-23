#ifndef _JUEGOMINECRAFT
#define _JUEGOMINECRAFT
#define _USE_MATH_DEFINES
#include <tape.h>
#include <module.h>
#include <timer/timer.h>
#include <global/screen.h>
#include "../graphics/src/renderable/renderable.h"
#include "../graphics/src/renderable/img.h"
#include "../graphics/src/renderable/cube.h"
#include "mapa/terreno.h"
#include <cmath>
#include <list>
#include <global/input.h>

#include <component.h>
#include <entity.h>


class  Minecraft :public modules::Tape {
	float segundos = 0;
	renderable::Cube* cubo=0;

	int longitudTile=8;
	int tamañoVisualPixelTile = 10;
	int radio = 0;
	std::vector<Terreno *> terrenos;
	//renderable::Img* mapa;
	Entity* mapa;

	//Terreno terreno; //TODO: Revisar la destrucción o liberación de memoria
	//Tipo** porcion=0;
	//static void pressKey(Key);
	void generarTerreno();
	Terreno* generarTerreno(renderable::Img* renderableTail, Terreno*, Direccion origen);
	void pintarTerreno();
	//renderable::Img* cogerMapa();
public:
	Minecraft();
	void update();
	void start();
	void destroy();
	char* nombre() { return (char*)"MINECRAFT"; };
	
};
#endif // !_JUEGOMINECRAFT
