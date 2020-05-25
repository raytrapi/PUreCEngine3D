#include "dll.h"
template<class T>
inline void* utilidades::Libreria<T>::cargarDLL(const char* fichero) {
#ifdef WIN32
	HINSTANCE hDLL = LoadLibrary(fichero);
	if (hDLL == NULL) {
		LPVOID lpMsgBuf;
		LPVOID lpDisplayBuf;
		DWORD dw = GetLastError(); 

		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR)&lpMsgBuf,
			0, NULL);

		lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT,
											(lstrlen((LPCTSTR)lpMsgBuf) + 40) * sizeof(TCHAR));
		StringCchPrintf((LPTSTR)lpDisplayBuf,
						LocalSize(lpDisplayBuf) / sizeof(TCHAR),
						TEXT("(err %d) %s"),
						dw, lpMsgBuf);
		//std::cerr << "Error al cargar librería [LoadLibrary: " << (LPCTSTR)lpDisplayBuf << "]" << std::endl;
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error al cargar librería"), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);

	}
	return hDLL;
#elif __linux__
	void* manejador;
	//std::cout<<"intento\r\n";
	manejador = dlopen(fichero, RTLD_LAZY);
	if (manejador == NULL) {
		std::cerr << "No ha podido cargar la librería [dlopen: err " << dlerror() << "]" << std::endl;
	}
	return manejador;
#endif
	return NULL;
}
template<class T>
inline T* utilidades::Libreria<T>::cargarClase(void*& hDLL, const char* clase) {
#ifdef WIN32
	PCTOR instancia = (PCTOR)GetProcAddress((HINSTANCE)hDLL, clase);
	if (instancia != NULL) {
		return instancia();
	}
#elif __linux__
	T* (*instancia)();
	*(void**)(&instancia) = dlsym(hDLL, clase);
	if (instancia != NULL) {
		return (*instancia)();
	}
#endif
	return NULL;
}
template<class T>
inline T* utilidades::Libreria<T>::crearInstancia(const char* fichero) {
	void* hDLL = cargarDLL(fichero);
#ifdef WIN32
	PCTOR instancia = (PCTOR)GetProcAddress((HINSTANCE)hDLL, "crearInstancia");
	if (instancia != NULL) {
		return instancia();
	}
#elif __linux__
	T* (*instancia)();
	*(void**)(&instancia) = dlsym(hDLL, clase);
	if (instancia != NULL) {
		return (*instancia)();
	} 
#endif
	return NULL; 
}
template<class T>
inline utilidades::Libreria<T>::~Libreria() {
}
	
