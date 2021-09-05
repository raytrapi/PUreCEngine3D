
#include "log.h"

namespace utiles {
	Log::Log(){
		fichero.open(nombreFichero, std::ios::app | std::ios::out);
		salida=new std::ostream(&fichero);
	}
	Log::~Log() {
		delete salida;
		if (fichero.is_open()) {
			fichero.close();
		}
	}
	
	void Log::escribir(std::string &s) {
		escribir(s, utiles::Log::NIVEL::INF);
	} 
	void Log::escribir(std::string& s, utiles::Log::NIVEL nivel) {
		std::filebuf fb;
		fb.open(nombreFichero, std::ios::app);
		std::ostream os(&fb);
		switch (nivel) {
			case utiles::Log::FAT:
				os << "FAT\t";
				break;

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

		os << std::put_time(std::localtime(&ahora), "%F %T%z") << "\t"  << s << std::endl;
		fb.close();
	}
	Log& Log::escribir() {
		if (instancia == NULL) {
			instancia = new Log();
		}
		return (*instancia);
	}

	/**/
	/*template<class T>
	std::ostream& Log::operator<<(T const& texto) {
		*(instancia->salida) << texto << std::endl;
		return instancia->salida;
	}/**/
	template<class T>
	Log&  operator<<(Log& h,T const& texto) {
		h.salida << texto<<std::endl;
		return *this;
	}

	

 	std::string Log::nombreFichero = "log.log";
	Log* Log::instancia=NULL;
	
} /* namespace utiles */
