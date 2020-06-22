#ifndef __MODULOS
#define __MODULOS
#ifdef _WIN32
	#include <Windows.h>
	//#ifdef EXPORTAR_MODULO
		#define EXPORTAR_MODULO   __declspec(dllexport)
	//#else
	//	#define EXPORTAR_MODULO   __declspec(dllimport)
	//#endif
#else
	#define EXPORTAR_MODULO
#endif // WIN32
#include "../utilidades/log/log.h"
#include <string>
#include <sstream>
#include <map>

class Tecla {
	bool pulsada = false;
public:
	bool estaPulsada() { return pulsada; };
	void pulsar() { pulsada = true; };
	void soltar() { pulsada = false; };
};
enum class EXPORTAR_MODULO Key {
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z, UP, DONW, LEFT, RIGHT
};

class EXPORTAR_MODULO Modulo {
	static std::map <Key, Tecla> teclas;
public:
	enum TIPOS_MODULOS {
		GRAFICO,
		CARTUCHO
	};

	virtual char* nombre() = 0;
	virtual TIPOS_MODULOS tipo() = 0;
	template<class T>
	void debug(T valor);

	static bool isInputKeyDown(Key key);
	static void setInputKeyDown(Key key);
	static void setInputKeyUp(Key key);
};

template<class T>
inline void Modulo::debug(T valor) {
	std::string s;
	std::stringstream ss;
	ss << valor;
	ss >> s;
	//s << std::endl;
	utiles::Log::escribir(s, utiles::Log::DEB);
}

#define REGISTRAR_MODULO(classname) \
	extern "C" Modulo * crearInstancia() {\
			return (Modulo *) new classname();\
	}\
	extern "C" void destroy(Modulo * p) {\
	    delete p;\
	}
	#ifdef _WIN32
	extern "C" __declspec(dllexport) Modulo * crearInstancia();
	extern "C" __declspec(dllexport) void destroy(Modulo*);
	#endif
#endif // !__MODULOS


