#ifndef __VENTANAWND
#define __VENTANAWND



#include <iostream>
#include <Windows.h>
#include <Windowsx.h>
#include "../modules/graphic/motor.h"
#include "../modules/tape/tape.h"
#include "../utilidades/timer/timer.h"
#include "../utilidades/librerias/dll.h"
#include "../utilidades/log/log.h"
#include "../cargaDLLs.h"
//#include "..\Motor gráfico\terceros\opengl\src\opengl.h"
#include "../utilidades/global/screen.h"
#include "../utilidades/global/input.h"
#include "../utilidades/global/mouse.h"
#include "../graphics/src/renderable/renderable.h"
#include <vector>



class Ventana {
	private: 
		const char* nombreVentana;
		int comandoVentana;
		HWND hwnd;
		static modules::graphics::Graphic* motorGrafico;
		static modules::Tape* cartucho;
		static Input input;
		static Mouse mouse;
		
	public: 
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		//static HDC ghDC;

	public: 
		Ventana(const char* ventana, HINSTANCE hInstance, int nComando, int ancho, int alto, int x, int y);
		int abrirVentana();
		//static BOOL bSetupPixelFormat(HDC);

};
#endif // !__VENTANAWND