#ifndef __DLL
#define __DLL
#ifdef WIN32
#include <windows.h>
#include <strsafe.h>
#elif __linux__
#include <stdlib.h>
#include <dlfcn.h>
#endif
namespace utilidades {
	template<class T>
	class DLL {
	#ifdef WIN32
		typedef T* (WINAPI* PCTOR) ();
	#endif
	public:
		void* cargarDLL(const char* fichero);
		T* cargarClase(void*& hDLL, const char* clase);
	};
}



#endif // !__DLL
