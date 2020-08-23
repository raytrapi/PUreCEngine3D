#include <iostream>
#ifdef WIN32__
    #include <windows.h>
    #include "windows/ventana.h"
#endif

#include "../modules/graphic/motor.h"
#include "../modules/tape/tape.h"
#include "../utilidades/timer/timer.h"
#include "../utilidades/log/log.h"

#include "cargaDLLs.h"

#include "../utilidades/global/screen.h"
#include "../utilidades/global/input.h"
#include "../utilidades/global/mouse.h"
#include "../graphics/src/renderable/renderable.h"
#include "../components/src/entity.h"

#ifdef WIN32__
int WINAPI WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR     lpCmdLine,
    int       nShowCmd){
    
    //CargaDLL librerias = CargaDLL();
    //CargaDLL::cargar("./modulos", ".");/**/

    Ventana ventana("MoGame", hInstance, nShowCmd, 1024,768,100,100);

    ventana.abrirVentana();


    return 0;
}
#else
void main(int numeroArgumentos, char** argumentos) {
    CargaDLL::cargar("./modulos", "."); 
    Input input;
    bool correcto = true;
    modules::Tape* cartucho=0;
    modules::graphics::Graphic* motorGrafico = 0;
    if (CargaDLL::hayModulos(Module::TAPE) > 0) {
        cartucho = CargaDLL::cogerModulo<modules::Tape>(Module::TAPE, "MINECRAFT");//HORMIGUERO: Hormigas buscando alimento
        //cartucho = CargaDLL::cogerModulo<modulos::Cartucho>(Modulo::CARTUCHO, "HORMIGUERO: Hormigas buscando alimento");
        Screen::setDimension(cartucho->getScreenWidth(), cartucho->getScreenHeight());
        Module::set(Module::MODULES_TYPE::TAPE, cartucho);
    }

    if (CargaDLL::hayModulos(Module::GRAPHIC) > 0) {
        motorGrafico = CargaDLL::cogerModulo<modules::graphics::Graphic>(Module::GRAPHIC, "OPENGL 4");
        Module::set(Module::MODULES_TYPE::GRAPHIC, motorGrafico);
        Renderable::setGraphicEngine(motorGrafico);
        if (cartucho){
            //cartucho->setGraphic(motorGrafico);
            correcto=motorGrafico->inicializar(0, cartucho->getScreenWidth(), cartucho->getScreenHeight());
            cartucho->start();
        } else {
           correcto = motorGrafico->inicializar(0, 800, 600);
        };
    }/**/

    while(motorGrafico && motorGrafico->isOpen()){
       Time::update();
       input.resetKeyPress();
       if (cartucho && cartucho->isRunning()) {
          //std::vector<void*>* renderizables = NULL;
          if (cartucho) {

             cartucho->update();
          }
       }
       if (motorGrafico) {
          motorGrafico->renderizar(Renderable::getRenderable());
          if (motorGrafico->isEnd()) {
             if (cartucho) {
               cartucho->setEnd();
             }
          }
       }
    }

    if (cartucho) {
        cartucho->destroy();
        delete cartucho;
    }
    Entity::destroy();
    if (motorGrafico) {
        motorGrafico->destroy();
        delete motorGrafico;
    }
}/**/
#endif