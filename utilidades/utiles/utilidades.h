
#ifndef _UTILIDADES
#define _UTILIDADES
	#ifdef _WIN32
		//#ifdef EXPORTAR_UTILIDADES
		   #define EXPORTAR_UTILIDADES   __declspec(dllexport)
		//#else
		//   #define EXPORTAR_UTILIDADES   __declspec(dllimport)
		//#endif
	#else
		#define EXPORTAR_UTILIDADES
	#endif
#endif
