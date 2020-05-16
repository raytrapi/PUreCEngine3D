#include <iostream>
#include <Windows.h>
#include "Motor/Motor.h"


class Ventana {
	private: 
		const char* nombreVentana;
		int comandoVentana;
		HWND hwnd;
		static MotorGrafico* motorGrafico;
	public: 
		static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		//static HDC ghDC;

	public: 
		Ventana(const char*, HINSTANCE, int);
		int abrirVentana();
		//static BOOL bSetupPixelFormat(HDC);

};
