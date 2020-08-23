#ifndef _HORMIGA
#define _HORMIGA
#define _USE_MATH_DEFINES
#include <cmath>
#include <timer/timer.h>
#include <cstdlib>
#include <ctime>
#include <log/log.h>

class Hormiga {
	long id;
	float x;
	float y;
	float energia;
	float direccion=-1;
	float distancia=10;
	
public:
	Hormiga(long id,long x, long y, float energia);
	void mover(long limiteX1, long limiteY1, long limiteX2,long limiteY2);
	long cogerX() { return (long)x; };
	long cogerY() { return (long)y; };
	void buscarDireccion(int gradoInferior, int gradoSuperior); //Obtendrá el nuevo destino
};

#endif // !_HORMIGA
