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

#include <filesControl.h>
#include <compile.h>



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

modules::Tape* cartucho = 0;
modules::graphics::Graphic* motorGrafico = 0;
void cargarEscena(const char* projecto) {
   //utiles::Log::debug(path);
   if (cartucho) {
      cartucho->detener();
   }
   CargaDLL::liberarModulo(Module::TAPE);
   std::string sandbox("H:/Desarrollo/motor_videojuegos_2D/sandbox/");
   std::string ruta = sandbox + std::string(projecto);

   //TODO: Esto solo es para Ninja
   Compile::compileProject(ruta.c_str(),Compile::NINJA);
   //Con visual studios falla si hay un PDB, así que lo intentamos quitar
   if (std::filesystem::exists(ruta + std::string("/") + std::string(projecto) + std::string(".pdb"))) {
      std::filesystem::remove(ruta + std::string("/") + std::string(projecto) + std::string(".pdb"));
   }
   //----

   ruta += std::string("/")+std::string(projecto)+std::string(".dll");
   if (std::filesystem::exists(ruta)) {
      CargaDLL::cargar(ruta.c_str());
      //cartucho=

      cartucho = CargaDLL::cogerModulo<modules::Tape>(Module::TAPE);
      if (cartucho) {
         Screen::setDimension(cartucho->getScreenWidth(), cartucho->getScreenHeight());
         Module::set(Module::MODULES_TYPE::TAPE, cartucho);
         if (motorGrafico) {
            //motorGrafico->inicializar(0, cartucho->getScreenWidth(), cartucho->getScreenHeight());
            cartucho->start();
         }

      }/**/
   }
}
void main(int numeroArgumentos, char** argumentos) {
    CargaDLL::cargar("./modulos", "./"); 
    Input input;
    bool correcto = true;
    
    
    if (CargaDLL::hayModulos(Module::GRAPHIC) > 0) {
       motorGrafico = CargaDLL::cogerModulo<modules::graphics::Graphic>(Module::GRAPHIC, "OPENGL 4");
       Module::set(Module::MODULES_TYPE::GRAPHIC, motorGrafico);
    }/**/

    //--------
    //Esto lo hacemos a mano mientra no tengamos un menú en la aplicación que me permita hacerlo desd ahí
    fileControl fc;
    if (motorGrafico) {
       motorGrafico->inicializar(0, 800, 600);
       const char* escena = "micraft";
       motorGrafico->addOnFocus(fileControl::onFocus);
       modules::Tape::load(escena, cartucho, [](const char* path) {
          cargarEscena(path);
          //if
          

       });
       
    }
    //-----

    /*if (CargaDLL::hayModulos(Module::TAPE) > 0) {
        cartucho = CargaDLL::cogerModulo<modules::Tape>(Module::TAPE, "MINECRAFT");//HORMIGUERO: Hormigas buscando alimento
        //cartucho = CargaDLL::cogerModulo<modulos::Cartucho>(Modulo::CARTUCHO, "HORMIGUERO: Hormigas buscando alimento");
        Screen::setDimension(cartucho->getScreenWidth(), cartucho->getScreenHeight());
        Module::set(Module::MODULES_TYPE::TAPE, cartucho);
    }*/

    /*if (CargaDLL::hayModulos(Module::GRAPHIC) > 0) {
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
        cartucho->detener();
        delete cartucho;
    }
    Entity::destroy();
    if (motorGrafico) {
        motorGrafico->destroy();
        delete motorGrafico;
    }
}/**/
#endif