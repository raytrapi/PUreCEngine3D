#ifndef __DLL
#define __DLL
#ifdef _WIN32
#include <windows.h>
#include <strsafe.h>
#elif __linux__
#include <stdlib.h>
#include <dlfcn.h>
#endif
namespace utilidades {
	template<class T>
	class Libreria {
	#ifdef _WIN32
		typedef T* (WINAPI* PCTOR) ();
	#endif
	public:
		Libreria() {};
		~Libreria();
		 void* cargarDLL(const char* fichero);
		 T* cargarClase(void*& hDLL, const char* clase);
		 T* crearInstancia(const char* fichero);
	};

}
#include <dll.cpp>


#endif // !__DLL
