
#ifndef __LOG
#define __LOG
#include "../utiles/utilidades.h"

#include <iostream>
#include <string>
#include <fstream>
#include <chrono>
#include <time.h>
#include <iomanip>
namespace utiles {
		
	class EXPORTAR_UTILIDADES Log {
		
		static std::string nombreFichero;
		
		std::filebuf fichero;
		static Log* instancia;
		public:
			std::ostream* salida;
			Log();
			~Log();
			//static std::filebuf fichero;
			//static std::ostream* os;
			EXPORTAR_UTILIDADES enum NIVEL {ERR,WAR,INF,DEB};
			/*
			/*static void abrir(const char *);
			static void cerrar();
			static std::ostream& escribir();
			static std::ostream& escribir(utiles::Log::NIVEL);/**/
			static void escribir(std::string &s);
			static void escribir(std::string &s, utiles::Log::NIVEL nivel);
			//static void escribir(std::string& s, utiles::Log::NIVEL nivel,const char*, int);/**/
			/*template<class T>
			std::ostream& operator<<(T const& texto);/**/
			
			static Log& escribir();
	};
	template<class T>
	EXPORTAR_UTILIDADES Log& operator<<(Log& h, T const& texto);
	

} /* namespace utiles */
#endif /* __LOG */

