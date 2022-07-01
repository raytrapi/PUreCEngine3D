#ifndef _EXP_AUDIO
#define _EXP_AUDIO
#ifdef _WIN32
#include <Windows.h>

#ifdef EXPORTAR_AUDIO
#define EXPORTAR_AUDIO   __declspec(dllexport)
#else
#define EXPORTAR_AUDIO   __declspec(dllimport)
#endif
#else
#define EXPORTAR_AUDIO
#endif // WIN32

#endif // !_EXP_AUDIO
