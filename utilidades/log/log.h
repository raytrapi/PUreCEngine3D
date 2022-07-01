
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
#include <codecvt>
#include <locale>


//#define TRACE(m, ...) Log::trace(m, __VA_ARGS__)
//#define TRACE_STR(m, ...) Log::trace_str(m, __VA_ARGS__)
#define LOG_DBG(s, ...) utiles::Log::debug(s, __VA_ARGS__)
#define DBG(s, ...) utiles::Log::debug(s, __VA_ARGS__)
#define ERR(s, ...) utiles::Log::error(s, __VA_ARGS__)
#define DBG_F(s, ...) utiles::Log::debugF(s, __VA_ARGS__)
#define INFO(s, ...) utiles::Log::info(s, __VA_ARGS__)
//#define TRACE_DBG_STR(m, ...) Log::debug_str(__VA_ARGS__)
//#define TRACE_ERR(m, ...) Log::error(__VA_ARGS__)
//#define TRACE_ERR_STR(m, ...) Log::error(__VA_ARGS__)
namespace utiles {
	extern class LogFile;
	class EXPORTAR_UTILIDADES Log {
		
		//static std::string nombreFichero;
		//std::filebuf fichero;
		static std::vector<Log*> instancias;
		static unsigned idInstanciaActual;
		template<typename T, typename... Targs>
		static std::string debug2( const char* text, T value, Targs... Fargs);
		static std::string debug2(const char* text);
		template<typename T, typename... Targs>
		static std::string error2(const char* text, T value, Targs... Fargs);
		static std::string error2(const char* text);
		//static void escribirPantalla(const char* text);

		public:
			//std::ostream* salida;
			Log(bool select=true);
			
			
			static void destroy();
			static void setInstanceId(unsigned idInstance);
			static int getNumberInstances();
			static const char* to_utf8(std::string text, const std::locale& loc=std::locale(".1252"));
			//static std::filebuf fichero;
			//static std::ostream* os;
			EXPORTAR_UTILIDADES enum NIVEL {FAT,ERR,WAR,INF,DEB};
			template <class T>
			static void prepararEscribir(T texto,utiles::Log::NIVEL nivel = utiles::Log::NIVEL::INF);
			static void escribir(std::string &s, utiles::Log::NIVEL nivel = utiles::Log::NIVEL::INF);
			static void escribirF(std::string& s, utiles::Log::NIVEL nivel = utiles::Log::NIVEL::INF);
			virtual void escribirVirtual(std::string& s, utiles::Log::NIVEL nivel = utiles::Log::NIVEL::INF)=0;
			/*
			/*static void abrir(const char *);
			static void cerrar();
			static std::ostream& escribir();
			static std::ostream& escribir(utiles::Log::NIVEL);/**/
			template<class T>
			static void debug(T text);
			template<typename T, typename... Targs>
			static void debug(const char* text, T value, Targs... Fargs);
			template<class T>
			static void debugF(T text);
			template<typename T, typename... Targs>
			static void debugF(const char* text, T value, Targs... Fargs);
			
			template<class T>
			static void info(T text);
			template<typename T, typename... Targs>
			static void info(const char* text, T value, Targs... Fargs);


			template<class T>
			static void error(T text);
			template<typename T, typename... Targs>
			static void error(const char* text, T value, Targs... Fargs);
			template<class T>
			static void fatal(T valor);
			//static void escribir(std::string& s, utiles::Log::NIVEL nivel,const char*, int);/**/
			/*template<class T>
			std::ostream& operator<<(T const& texto);/**/
			
			static Log& escribir();
	};
	template<class T>
	inline void Log::prepararEscribir(T text,utiles::Log::NIVEL nivel) {
		std::string s;
		std::stringstream ss;
		ss << text;
		s = ss.str();
		//s << std::endl;
		escribir(s, nivel);
	};
	template<class T>
	inline void Log::debug(T text) {
		prepararEscribir(text, DEB);
	}
	template<typename T, typename... Targs>
	void Log::debug(const char* text, T value, Targs... Fargs) {
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
	template<class T>
	inline void Log::debugF(T text) {
		std::string s;
		std::stringstream ss;
		ss << text;
		s = ss.str();
		//s << std::endl;
		escribirF(s, DEB);
	}
	template<typename T, typename... Targs>
	void Log::debugF(const char* text, T value, Targs... Fargs) {
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
		escribirF(s, DEB);
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
	void Log::info(T valor) {
		prepararEscribir(valor, INF);
	}
	template<typename T, typename... Targs>
	void Log::info(const char* text, T value, Targs... Fargs) {
		std::string s;
		std::stringstream ss;
		for (; *text != '\0'; text++) {
			if (*text == '%') {
				ss << value;
				ss << error2(text + 1, Fargs...);
				s = ss.str();
				escribir(s, INF);
				return;
			}
			else {
				ss << *text;
			}
		}
		s = ss.str();
		escribir(s, INF);
	}

	template<class T>
	void Log::error(T valor) {
		prepararEscribir(valor, ERR);
	}
	template<typename T, typename... Targs>
	void Log::error(const char* text, T value, Targs... Fargs) {
		std::string s;
		std::stringstream ss;
		for (; *text != '\0'; text++) {
			if (*text == '%') {
				ss << value;
				ss << error2(text + 1, Fargs...);
				s = ss.str();
				escribir(s, ERR);
				return;
			} else {
				ss << *text;
			}
		}
		s = ss.str();
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

	template<typename T, typename... Targs>
	inline std::string Log::error2(const char* text, T value, Targs... Fargs) {
		std::stringstream ss;
		for (; *text != '\0'; text++) {
			if (*text == '%') {
				ss << value;
				ss << error2(text + 1, Fargs...);
				return ss.str();
			} else {
				ss << *text;
			}
		}
		return ss.str();
	}
	inline std::string Log::error2(const char* text) {
		std::stringstream ss;
		ss << text;
		return ss.str();
	}

} /* namespace utiles */
#endif /* __LOG */

