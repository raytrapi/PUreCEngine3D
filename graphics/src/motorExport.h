#ifndef _MOTORGRAFICOEXPORT
#define _MOTORGRAFICOEXPORT
#ifdef _WIN32
#include <Windows.h>
//#define EXPORTAR_MODULO_GRAFICO __declspec(dllexport)
#ifdef EXPORTAR_MODULO_GRAFICO
#define EXPORTAR_MODULO_GRAFICO   __declspec(dllexport)
#else
#define EXPORTAR_MODULO_GRAFICO   __declspec(dllimport)
#endif
#else
#define EXPORTAR_MODULO_GRAFICO
#endif // WIN32

#endif