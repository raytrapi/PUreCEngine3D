#ifndef __DLL
#define __DLL
#ifdef _WIN32
#include <windows.h>
#include <strsafe.h>
#elif __linux__
#include <stdlib.h>
#include <dlfcn.h>
#endif
#include <map>
#include <string>

namespace utilidades {
	struct cmp_str {
		bool operator()(char const* a, char const* b) const {
			return std::strcmp(a, b) < 0;
		}
	};

	template<class T>
	class Libreria {
	#ifdef _WIN32
		typedef T* (WINAPI* PCTOR) ();
	#endif
		static std::map<std::string, void*> libreriasCargadas;
		void* cookieRaiz = NULL;
	public:
		Libreria() {};
		Libreria(const char *);
		~Libreria();
		 void* cargar(const char* fichero);
		 bool descargar(const char* fichero);
		 T* cargarClase(void*& hDLL, const char* clase);
		 T* crearInstancia(const char* fichero);
		 static T* cogerModulo(Module::MODULES_TYPE);
	};
}

#include "dll.cpp"


#endif // !__DLL
