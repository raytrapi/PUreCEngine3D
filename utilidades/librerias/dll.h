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
		 template<class K>
		 void obtenerFuncion(const char* fichero, const char* funcion, K* param);
	};
	template<class T >
	template<class K >
	inline void Libreria<T>::obtenerFuncion(const char* fichero, const char* funcion, K* param)	{
		void* hDLL = cargar(fichero);
#ifdef WIN32
		typedef void (WINAPI* PCTOR2)(K* x);
		PCTOR2 f = (PCTOR2)GetProcAddress((HINSTANCE)hDLL, funcion);
		if (f != NULL) {
			f(param);
		}
#elif __linux__
		K* (*f)();
		*(void**)(&f) = dlsym(hDLL, clase);
		if (f != NULL) {
			(*f)(param);
			//return (*f)();
		}
#endif
		//return NULL;
	}
}

#include "dll.cpp"


#endif // !__DLL
