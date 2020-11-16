#include "dll.h"

template<class T>
inline utilidades::Libreria<T>::Libreria(const char * raiz) {
#ifdef _WIN32
	cookieRaiz=AddDllDirectory((PCWSTR) raiz);
#endif
}

template<class T>
inline void* utilidades::Libreria<T>::cargar(const char* fichero) {
	std::string sFichero = std::string(fichero);
	if (libreriasCargadas.contains(sFichero)) {
		return libreriasCargadas[sFichero];
	}
#ifdef _WIN32
	DWORD dw1 = GetLastError();
	DWORD dw2 = GetLastError();
	HINSTANCE hDLL = LoadLibrary(sFichero.c_str());
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
		/*StringCchPrintf((LPTSTR)lpDisplayBuf,
						LocalSize(lpDisplayBuf) / sizeof(TCHAR),
						TEXT("(err %d) %s"),
						dw, lpMsgBuf);
		//std::cerr << "Error al cargar librería [LoadLibrary: " << (LPCTSTR)lpDisplayBuf << "]" << std::endl;
		MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error al cargar librería"), MB_OK);

		LocalFree(lpMsgBuf);
		LocalFree(lpDisplayBuf);
		/**/
	}
	libreriasCargadas[sFichero] = hDLL;
	return hDLL;
#elif __linux__
	void* manejador;
	//std::cout<<"intento\r\n";
	manejador = dlopen(fichero, RTLD_LAZY);
	if (manejador == NULL) {
		std::cerr << "No ha podido cargar la librería [dlopen: err " << dlerror() << "]" << std::endl;
	}
	libreriasCargadas[sFichero] = manejador;
	return manejador;
#endif
	return NULL;
}



template<class T>
inline bool utilidades::Libreria<T>::descargar(const char* fichero) {
	std::string sFichero = std::string(fichero);
	if (!libreriasCargadas.contains(sFichero)) {
		return false;
	}
#ifdef _WIN32
	if (FreeLibrary((HINSTANCE)libreriasCargadas[sFichero])) {
		libreriasCargadas.erase(sFichero);
		return true;
	};
	return false;
#elif __linux__
	if (dlclose(libreriasCargadas[sFichero]) == 1) {
		libreriasCargadas.erase(sFichero);
		return true;
	};
#endif
	return false;
}

template<class T>
inline T* utilidades::Libreria<T>::cargarClase(void*& hDLL, const char* clase) {
#ifdef _WIN32
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
	void* hDLL = cargar(fichero);
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
#ifdef _WIN32
	if (cookieRaiz != NULL) {
		RemoveDllDirectory(cookieRaiz);
	}
#endif // _WIN32

}
template<class T>
std::map<std::string, void*> utilidades::Libreria<T>::libreriasCargadas;
