
#include "log.h"

namespace utiles {
	void Log::escribir(std::string &s) {
		escribir(s, utiles::Log::NIVEL::INF);
	} 
	void Log::escribir(std::string& s, utiles::Log::NIVEL nivel) {
		std::filebuf fb;
		fb.open(nombreFichero, std::ios::app);
		std::ostream os(&fb);
		switch (nivel) {
			case utiles::Log::ERR:
				os << "ERR\t";
				break;
			case utiles::Log::WAR:
				os << "WAR\t";
				break;
			case utiles::Log::INF:
				os << "INF\t";
				break;
			case utiles::Log::DEB:
				os << "DEB\t";
				break;
		}
		std::time_t ahora = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

		os << std::put_time(std::localtime(&ahora), "%F %R%z") << "\t" << __TIME__ << "\t" << s << std::endl;
		fb.close();
	}/**/
	std::string Log::nombreFichero = "log.log";
} /* namespace utiles */
