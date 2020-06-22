#include "ventana.h"

modulos::graficos::Grafico * Ventana::motorGrafico=NULL;
modulos::Cartucho* Ventana::cartucho=NULL;
Ventana::Ventana(const char* ventana, HINSTANCE hInstance, int nComando,int ancho, int alto, int x, int y){
	nombreVentana = ventana;
    comandoVentana = nComando;
    WNDCLASS wc = { };
    wc.lpfnWndProc = Ventana::WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = nombreVentana;
    RegisterClass(&wc);
    CargaDLL::cargar("./modulos", ".");
    // Create the window.
    Screen::setDimension(ancho, alto);
    hwnd = CreateWindowEx(
        0,                              // Optional window styles.
        nombreVentana,                  // Window class
        nombreVentana,                  // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        x, y, ancho, alto,

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
    
    //utilidades::Libreria<Modulo> dll(".");
    //Modulo* m;
    switch (uMsg){
        case WM_CREATE:
            //d::cout << "hola" << std::endl;
            GetClientRect(hwnd, &rect);
            /*utiles::Log::escribir()<<m->tipo();
            utiles::Log::escribir()<<m->nombre();/**/
            //motorGrafico=(modulos::graficos::Grafico *)dll.crearInstancia("motor_grafico_gl.dll");
           /* m = dll.crearInstancia("./modulos\\motor_grafico_gl.dll");
            utiles::Log::escribir(std::to_string(m->tipo()));
            utiles::Log::escribir(std::string(m->nombre()));
            if (m->tipo() == Modulo::GRAFICO) {
                motorGrafico = (modulos::graficos::Grafico *)m;
            }else {
                delete m;
            }/**/
            if (CargaDLL::hayModulos(Modulo::GRAFICO)>0) {
                motorGrafico = CargaDLL::cogerModulo<modulos::graficos::Grafico>(Modulo::GRAFICO);
                motorGrafico->inicializar(hwnd, rect.right, rect.bottom);
            }/**/
            if (CargaDLL::hayModulos(Modulo::CARTUCHO) > 0) {
                cartucho =CargaDLL::cogerModulo<modulos::Cartucho>(Modulo::CARTUCHO, "MINECRAFT");
                cartucho->start();
            }/**/
            /*if (motorGrafico) {
                motorGrafico->inicializar(hwnd, rect.right, rect.bottom);
            }/**/
            
            OutputDebugStringA("Hemos creado");
            break;
        case WM_DESTROY:
            cartucho = NULL;
            motorGrafico = NULL;
            CargaDLL::descargar();
            PostQuitMessage(0);
            return 0;

        case WM_PAINT:{
            //PAINTSTRUCT ps;
            //HDC hdc = BeginPaint(hwnd, &ps);
               

            //FillRect(hdc, &ps.rcPaint, (HBRUSH)(COLOR_WINDOW + 1));

            //EndPaint(hwnd, &ps);
        }
        return 0;
        break;
        case WM_KEYDOWN: 
            switch (wParam) {
                case 0x41:
                    Modulo::setInputKeyDown(Key::A);
            }

            break;
        

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


 
int Ventana::abrirVentana() {
    if (hwnd == NULL) {
        return 0;
    }
    ShowWindow(hwnd, comandoVentana);
    
    MSG msg = { };
    Time::reset();
    while (GetMessage(&msg, NULL, 0, 0)) {
        Time::update();
        TranslateMessage(&msg);
        DispatchMessage(&msg);
        std::vector<void*> *renderizables=NULL;
        if (cartucho) {
            
            cartucho->update();
        }
        if (motorGrafico) {
            motorGrafico->renderizar(Renderable::getRenderable());
        }/**/
        /*if (motorGrafico) {
            motorGrafico->renderizar();
        }/**/
        
    }
    if (CargaDLL::hayModulos(Modulo::CARTUCHO) > 0) {
        CargaDLL::cogerModulo<modulos::Cartucho>(Modulo::CARTUCHO)->destroy();
    }
    return 0;
}


