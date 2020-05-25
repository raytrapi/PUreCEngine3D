
#ifndef SRC_UTILES_LOG_H_
#define SRC_UTILES_LOG_H_
#include "../utiles/utilidades.h"

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>
namespace utiles {
		
	class EXPORTAR_UTILIDADES Log {
		
		static std::string nombreFichero;
		public:
			//static std::filebuf fichero;
			//static std::ostream* os;
			EXPORTAR_UTILIDADES enum NIVEL {ERR,WAR,INF,DEB};
			/*template<class T>
			Log& operator<<(T const& texto);
			/*static void abrir(const char *);
			static void cerrar();
			static std::ostream& escribir();
			static std::ostream& escribir(utiles::Log::NIVEL);/**/
			static void escribir(std::string &s);
			static void escribir(std::string &s, utiles::Log::NIVEL nivel);
			//static void escribir(std::string& s, utiles::Log::NIVEL nivel,const char*, int);/**/

	};
	


} /* namespace utiles */
#endif /* SRC_UTILES_LOG_H_ */

