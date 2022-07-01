#ifndef _TIME
#define _TIME
#include <ctime>
#include <chrono>	
#include "../utiles/utilidades.h"
 class EXPORTAR_UTILIDADES Time {
	static std::chrono::system_clock::time_point anterior;
	
	static double delta;
	
public:
	static double deltaTime();
	static void update();
	static void reset();
	static std::chrono::system_clock::time_point time();
	static double diff(std::chrono::system_clock::time_point previus);
};


#endif // !_TIME
