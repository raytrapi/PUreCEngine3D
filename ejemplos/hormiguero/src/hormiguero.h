#ifndef _HORMIGUERO
#define _HORMIGUERO

#include "hormiga.h"
#include <vector>

class Hormiguero {
	std::vector<Hormiga*> hormigas;
	long x;
	long y;
public:
	Hormiguero(long x, long y, int hormigas);
	~Hormiguero();
	long cogerX();
	long cogerY();
	std::vector<Hormiga*> cogerHormigas() {
		return hormigas;
	};
};

#endif // !_HORMIGUERO
