#ifndef _JUEGOMINECRAFT
#define _JUEGOMINECRAFT
#define _USE_MATH_DEFINES
#include"../cartucho/src/cartucho.h"
#include <modulos.h>
#include <timer/timer.h>
#include <nucleo/screen.h>
#include "../graphics/src/renderable/renderable.h"
#include "../graphics/src/renderable/cube.h"
#include <cmath>
#include <list>


class  Minecraft :public modulos::Cartucho {
	float segundos = 0;
	renderable::Cube* cubo;
public:
	void update();
	void start();
	void destroy();
	char* nombre() { return (char*)"MINECRAFT"; };
};
#endif // !_JUEGOMINECRAFT
