#ifndef __VENTANAWND
#define __VENTANAWND



#include <iostream>
#include <Windows.h>
#include "../graphics/src/motor.h"
#include "../cartucho/src/cartucho.h"
#include "../utilidades/timer/timer.h"
#include "../utilidades/librerias/dll.h"
#include "../utilidades/log/log.h"
#include "../cargaDLLs.h"
//#include "..\Motor gr�fico\terceros\opengl\src\opengl.h"
#include "../utilidades/nucleo/screen.h"
#include "../graphics/src/renderable/renderable.h"
#include <vector>



class Ventana {
	private: 
		const char* nombreVentana;
		int comandoVentana;
		HWND hwnd;
		static modulos::graficos::Grafico* motorGrafico;
		static modulos::Cartucho* cartucho;
		
	public: 
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		//static HDC ghDC;

	public: 
		Ventana(const char* ventana, HINSTANCE hInstance, int nComando, int ancho, int alto, int x, int y);
		int abrirVentana();
		//static BOOL bSetupPixelFormat(HDC);

};
#endif // !__VENTANAWND