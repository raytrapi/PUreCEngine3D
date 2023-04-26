#ifndef __MODULOS
#define __MODULOS
#ifdef _WIN32
	#include <Windows.h>
	#ifdef EXPORTAR_MODULO
		#define EXPORTAR_MODULO   __declspec(dllexport)
	#else
		#define EXPORTAR_MODULO   __declspec(dllimport)
	#endif
#else
	#define EXPORTAR_MODULO
#endif // WIN32
#include "../../utilidades/log/log.h"
#include <string>
#include <sstream>
#include <map>
#include <type_traits>

namespace modules {
	extern class Tape;
	namespace graphics {
		extern class Graphic;
	}
	namespace resources {
		extern class Resource;
	}
	extern class Audio;
}/**/

class EXPORTAR_MODULO Module {

public:
	enum MODULES_TYPE {
		GRAPHIC,
		TAPE,
		PHYSICS,
		CODE,
		RESOURCES,
		AUDIO,
		INTERFACE
	};
private:
	static std::map<MODULES_TYPE, Module*> modulos;
public:

	virtual char* nombre() = 0;
	virtual MODULES_TYPE tipo() = 0;
	virtual void init() {};
	virtual void destroy() {};
	template<class T>
	void debug(T valor);

	template<class T>
	static T* get();
	
	static void set(MODULES_TYPE type, Module* );
};

template<class T>
inline void Module::debug(T valor) {
	std::string s;
	std::stringstream ss;
	ss << valor;
	ss >> s;
	//s << std::endl;
	utiles::Log::escribir(s, utiles::Log::DEB);
}

template<class T>
inline T* Module::get() {
	if (std::is_same<T, modules::graphics::Graphic>::value ) {
		return (T*) modulos[MODULES_TYPE::GRAPHIC];
	}
	if (std::is_same<T, modules::Tape>::value) {
		return (T*)modulos[MODULES_TYPE::TAPE];
	}
	if (std::is_same<T, modules::resources::Resource>::value) {
		return (T*)modulos[MODULES_TYPE::RESOURCES];
	}
	if (std::is_same<T, modules::Audio>::value) {
		return (T*)modulos[MODULES_TYPE::AUDIO];
	}
	return NULL;
}

#define REGISTRAR_MODULO(classname) \
	extern "C" Module * crearInstancia() {\
			Module *m=(Module *) new classname();\
			m->init();\
			return m;\
	}\
	extern "C" void destroy(Module * p) {\
		if(p) {p->destroy();delete p;};p=NULL;\
	}
	#ifdef _WIN32
	extern "C" __declspec(dllexport) Module * crearInstancia();
	extern "C" __declspec(dllexport) void destroy(Module*);
	#endif
#endif // !__MODULOS


