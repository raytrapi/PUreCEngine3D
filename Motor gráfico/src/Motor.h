#ifndef _MOTORGRAFICO
#define _MOTORGRAFICO
#ifndef EXPORTAR_MOTOR
	#ifdef WIN32
		#define EXPORTAR_MOTOR __declspec(dllexport)
	#else
		#define EXPORTAR_MOTOR
	#endif // WIN32
#endif // EXPORTAR_MOTOR
#include <Windows.h>


class EXPORTAR_MOTOR MotorGrafico{
	public:
		virtual void renderizar()=0;
		virtual void inicializar(HWND, double, double) = 0;

};

//template void EXPORTAR_MOTOR MotorGrafico::inicializar(HWND, double, double);


#endif // 