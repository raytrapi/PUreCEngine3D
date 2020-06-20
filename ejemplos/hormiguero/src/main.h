#ifndef _HORMIGUERO
#define _HOMIGUERO
#include"../cartucho/src/cartucho.h"
#include <modulos.h>
#include <timer.h>
#include <screen.h>
#include "../graphics/src/renderable/renderable.h"
#include "../graphics/src/renderable/pixel.h"
class  Hormiguero :public modulos::Cartucho {
	int iteraciones = 0;
	renderable::Img *lienzo;
	bool subiendo = true;
public:
	void update();
	void start();
	void destroy();
	char* nombre() { return (char*)"HORMIGUERO: Hormigas buscando alimento"; };
};
#endif // !_HORMIGUERO
