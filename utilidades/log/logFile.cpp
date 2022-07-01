
#include "logFile.h"
namespace utiles {
	
	void LogFile::init(){
		
	}
	void LogFile::destroy() {
		
	}
	
	LogFile::LogFile() {
		fichero.open(nombreFichero, std::ios::app | std::ios::out);
		salida = new std::ostream(&fichero);

	}

	LogFile::~LogFile() {
		delete salida;
		if (fichero.is_open()) {
			fichero.close();
		}
	}

	void LogFile::escribirVirtual(std::string& s, utiles::Log::NIVEL nivel) {
		std::time_t ahora = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());


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


		os << std::put_time(std::localtime(&ahora), "%F %T%z") << "\t" << s << std::endl;
		fb.close();
	};
	

	/**/
	/*template<class T>
	std::ostream& Log::operator<<(T const& texto) {
		*(instancia->salida) << texto << std::endl;
		return instancia->salida;
	}/**/
	template<class T>
	LogFile&  operator<<(LogFile& h,T const& texto) {
		h.salida << texto<<std::endl;
		return *this;
	}

	

 	std::string LogFile::nombreFichero = "log.log";
	

	
} /* namespace utiles */
