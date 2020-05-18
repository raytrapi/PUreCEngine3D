#ifndef __VENTANAWND
#define __VENTANAWND



#include <iostream>
#include <Windows.h>
#include "..\Motor gráfico\src\Motor.h"
#include "dll/dll.h"
#include "..\Motor gráfico\terceros\opengl\src\opengl.h"


class Ventana {
	private: 
		const char* nombreVentana;
		int comandoVentana;
		HWND hwnd;
		static MotorGrafico* motorGrafico;
		static void* puntero;
	public: 
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		//static HDC ghDC;

	public: 
		Ventana(const char*, HINSTANCE, int);
		int abrirVentana();
		//static BOOL bSetupPixelFormat(HDC);

};
#endif // !__VENTANAWND