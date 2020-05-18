#include <iostream>
#ifdef WIN32
    #include <windows.h>
    #include "windows/ventana.h"
#endif


#ifdef WIN32
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd){
    
   
    Ventana ventana("Prueba", hInstance, nShowCmd);

    ventana.abrirVentana();


    return 0;
}
#else
void main(int numeroArgumentos, char** argumentos) {
    std::cout << "Hola" << std::endl;
}/**/
#endif