#ifndef _HORMIGA
#define _HORMIGA

#include <timer/timer.h>
#include <cstdlib>
#include <ctime>
#include <log/log.h>

class Hormiga {
	long id;
	long x;
	long y;
	float energia;
public:
	Hormiga(long id,long x, long y, float energia);
	void mover(long limiteX,long limiteY);
	long cogerX() { return x; };
	long cogerY() { return y; };
};

#endif // !_HORMIGA
