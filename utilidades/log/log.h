
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
//#define TRACE(m, ...) Log::trace(m, __VA_ARGS__)
//#define TRACE_STR(m, ...) Log::trace_str(m, __VA_ARGS__)
#define LOG_DBG(s, ...) utiles::Log::debug(s, __VA_ARGS__)
#define DBG(s, ...) utiles::Log::debug(s, __VA_ARGS__)
//#define TRACE_DBG_STR(m, ...) Log::debug_str(__VA_ARGS__)
//#define TRACE_ERR(m, ...) Log::error(__VA_ARGS__)
//#define TRACE_ERR_STR(m, ...) Log::error(__VA_ARGS__)
namespace utiles {
		
	class EXPORTAR_UTILIDADES Log {
		
		static std::string nombreFichero;
		
		std::filebuf fichero;
		static Log* instancia;
		template<typename T, typename... Targs>
		static std::string debug2( const char* text, T value, Targs... Fargs);
		static std::string debug2(const char* text);

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
			static void debug(T text);
			template<typename T, typename... Targs>
			static void debug(const char* text, T value, Targs... Fargs);
			
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
	inline void Log::debug(T text) {
		std::string s;
		std::stringstream ss;
		ss << text;
		s = ss.str();
		//s << std::endl;
		escribir(s, DEB);
	}
	template<typename T, typename... Targs>
	inline void Log::debug(const char* text, T value, Targs... Fargs) {
		std::string s;
		std::stringstream ss;
		for (; *text != '\0'; text++) {
			if (*text == '%') {
				ss << value;
				ss << debug2(text + 1, Fargs...);
				s = ss.str();
				escribir(s, DEB);
				return;
			} else {
				ss << *text;
			}
		}
		s = ss.str();
		escribir(s, DEB);
	}
	template<typename T, typename... Targs>
	inline std::string Log::debug2(const char* text, T value, Targs... Fargs) {
		std::stringstream ss;
		for (; *text != '\0'; text++) {
			if (*text == '%') {
				ss << value;
				ss<<debug2(text + 1, Fargs...);
				return ss.str();
			} else {
				ss << *text;
			}
		}
		return ss.str();
	}
	inline std::string Log::debug2(const char* text) {
		std::stringstream ss;
		ss << text;
		return ss.str();
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

