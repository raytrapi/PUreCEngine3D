
#ifndef __LOG_FILE
#define __LOG_FILE
#include "../utiles/utilidades.h"
#include "log.h"
#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>
#include <time.h>
#include <iomanip>
namespace utiles {
	class EXPORTAR_UTILIDADES LogFile : public Log {
		static std::string nombreFichero;
		std::filebuf fichero;
		std::ostream* salida;
		void init();
		void destroy();
	public:
		LogFile();
		~LogFile();
		void escribirVirtual(std::string& s, utiles::Log::NIVEL nivel = utiles::Log::NIVEL::INF);
	};
}
#endif /* __LOG_FILE */

