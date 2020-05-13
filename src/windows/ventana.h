#include <Windows.h>


class Ventana {
	private: 
		const char* nombreVentana;
		HWND hwnd;
		int comandoVentana;

	public: static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	public: 
		Ventana(const char*, HINSTANCE, int);
		int abrirVentana();
};