#ifndef __WATCHDOG
#define __WATCHDOG
/**
* Clase que permite la gestión de tareas repetibles en el tiempo en intervalos de tiempo definido
*/

#include "../utiles/utilidades.h"
#include <thread>
#include <atomic>
#include <functional>
#include <vector>
#include <tuple>
#include <ctime>
#include <chrono>	

namespace utiles {
	class EXPORTAR_UTILIDADES Watchdog {
	public:
		Watchdog();
		//Watchdog(unsigned int milliseconds, std::function<void()> callback);
		~Watchdog();

		static unsigned int setInterval(std::function<void()> callback, unsigned int milliseconds);
		static void clearInterval(unsigned int);
		static unsigned int setTimeOut(std::function<void()> callback, unsigned int milliseconds);
	private:
		static std::vector < std::tuple<unsigned int, unsigned int, std::function<void()>, double>*> controles;
		static std::thread hilo;
		static bool ejecutando;
		void iteracion();
		static Watchdog * instancia;

		static std::chrono::system_clock::time_point anterior;
		static double delta;
		static unsigned int ids;
	};
}

#endif // !__WATCHDOG
