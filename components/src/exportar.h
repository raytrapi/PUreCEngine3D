#ifndef _EXP_COMPONENTE
#define _EXP_COMPONENTE
#ifdef _WIN32
#include <Windows.h>

#ifdef EXPORTAR_COMPONENTE
#define EXPORTAR_COMPONENTE   __declspec(dllexport)
#else
#define EXPORTAR_COMPONENTE   __declspec(dllimport)
#endif
#else
#define EXPORTAR_COMPONENTE
#endif // WIN32

#endif // !_EXP_COMPONENTE
