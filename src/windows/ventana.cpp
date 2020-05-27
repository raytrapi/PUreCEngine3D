#include "ventana.h"

modulos::graficos::Grafico * Ventana::motorGrafico;
Ventana::Ventana(const char* ventana, HINSTANCE hInstance, int nComando){
	nombreVentana = ventana;
    comandoVentana = nComando;
    WNDCLASS wc = { };
    wc.lpfnWndProc = Ventana::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = nombreVentana;
    RegisterClass(&wc);

    // Create the window.
    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        nombreVentana,                  // Window class
        nombreVentana,                  // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        hInstance,  // Instance handle
        NULL        // Additional application data
    );

}

LRESULT Ventana::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
    LONG    lRet = 1;
    //PAINTSTRUCT    ps;
    RECT rect;
    //HDC   ghDC;
    //HGLRC ghRC;
    
    utilidades::Libreria<Modulo> dll;
    Modulo* m;
    switch (uMsg){
        case WM_CREATE:
            //d::cout << "hola" << std::endl;
            GetClientRect(hwnd, &rect);
            //motorGrafico=(modulos::graficos::Grafico *)dll.crearInstancia("motor_grafico_gl.dll");
            m = dll.crearInstancia("motor_grafico_gl.dll");
            utiles::Log::escribir(std::to_string(m->tipo()));
            utiles::Log::escribir(std::string(m->nombre()));
            if (m->tipo() == Modulo::GRAFICO) {
                motorGrafico = (modulos::graficos::Grafico *)m;
            }else {
                delete m;
            }
            if (motorGrafico) {
                motorGrafico->inicializar(hwnd, rect.right, rect.bottom);
            }
            
            OutputDebugStringA("Hemos creado");
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:{
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hwnd, &ps);
               

            //FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            //EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


 
int Ventana::abrirVentana() {
    if (hwnd == NULL) {
        return 0;
    }
    ShowWindow(hwnd, comandoVentana);
    
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        if (motorGrafico) {
            motorGrafico->renderizar();
        }
    }
    return 0;
}


