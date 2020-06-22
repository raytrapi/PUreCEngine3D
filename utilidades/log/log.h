
#ifndef __LOG
#define __LOG
#include "../utiles/utilidades.h"

#include <iostream>
#include <sstream>
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
			EXPORTAR_UTILIDADES enum NIVEL {FAT,ERR,WAR,INF,DEB};
			/*
			/*static void abrir(const char *);
			static void cerrar();
			static std::ostream& escribir();
			static std::ostream& escribir(utiles::Log::NIVEL);/**/
			static void escribir(std::string &s);
			static void escribir(std::string &s, utiles::Log::NIVEL nivel);
			template<class T>
			static void debug(T valor);
			template<class T>
			static void error(T valor);
			template<class T>
			static void fatal(T valor);
			//static void escribir(std::string& s, utiles::Log::NIVEL nivel,const char*, int);/**/
			/*template<class T>
			std::ostream& operator<<(T const& texto);/**/
			
			static Log& escribir();
	};
	template<class T>
	EXPORTAR_UTILIDADES Log& operator<<(Log& h, T const& texto);
	template<class T>
	inline void Log::debug(T valor) {
		std::string s;
		std::stringstream ss;
		ss << valor;
		s=ss.str();
		//s << std::endl;
		escribir(s, DEB);
	}
	template<class T>
	inline void Log::error(T valor) {
		std::string s;
		std::stringstream ss;
		ss << valor;
		ss >> s;
		//s << std::endl;
		escribir(s, ERR);
	}
	template<class T>
	inline void Log::fatal(T valor) {
		std::string s;
		std::stringstream ss;
		ss << valor;
		ss >> s;
		//s << std::endl;
		escribir(s, FAT);
	}

} /* namespace utiles */
#endif /* __LOG */

