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
#include <watchdog.h>

#include <thread>




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
#ifdef WIN32
const char* extDLL = "dll";
#else
const char* extDLL = "so";
#endif // WIN32

bool recargarCartucho = false;
modules::Tape* cartucho = 0;
modules::graphics::Graphic* motorGrafico = 0;


void cargarEscena(const char* projecto) {
   //utiles::Log::debug(path);
   
   std::string sandbox("H:/Desarrollo/motor_videojuegos_2D/sandbox/");
   std::string ruta = sandbox + std::string(projecto);

   //TODO: Esto solo es para Ninja
   modules::Tape::load(projecto, cartucho, [ruta](const char* path) {
      Compile::compileProject(ruta.c_str(), Compile::NINJA);
      //cargarEscena(path);
      //if
   });
   
   
   //----
   

   ruta += std::string("/")+std::string(projecto)+std::string(".")+std::string(extDLL);
   FileControl::fileChangeTime(ruta.c_str(), [&,ruta]() {
      if (cartucho) {
         cartucho->detener();
      }
      CargaDLL::liberarModulo(Module::TAPE);
#ifdef WIN32
      //Con visual studios falla si hay un PDB, así que lo intentamos quitar
      std::string pdb = ruta.substr(0, ruta.size() - 3) + std::string("pdb");
      if (std::filesystem::exists(pdb)) {
         std::filesystem::remove(pdb);
      }
#endif // WIN32

      recargarCartucho = true;
      utiles::Log::debug(ruta);
      if (std::filesystem::exists(ruta)) {
         CargaDLL::cargar(ruta.c_str());
         //cartucho=

         cartucho = CargaDLL::cogerModulo<modules::Tape>(Module::TAPE);
         if (cartucho) {
            Screen::setDimension(cartucho->getScreenWidth(), cartucho->getScreenHeight());
            Module::set(Module::MODULES_TYPE::TAPE, cartucho);
            //if (motorGrafico) {
               ////motorGrafico->inicializar(0, cartucho->getScreenWidth(), cartucho->getScreenHeight());
              // cartucho->start();
            //}

         }/**/
      }
   },2000);
   
}
void run() {
   Input input;
   while (motorGrafico && motorGrafico->isOpen()) {
      Time::update();
      input.resetKeyPress();
      if (cartucho && cartucho->isRunning()) {
         //std::vector<void*>* renderizables = NULL;
         
         if (cartucho) {
            if (recargarCartucho) {
               cartucho->start();
               recargarCartucho = false;
            }
            try {
               cartucho->update();
               //std::thread game([]() {cartucho->update();});
               //game.join();
            } catch (std::exception e) {
               utiles::Log::error("Se ha producido una excepcion");
               utiles::Log::debug(e.what());
               cartucho->detener();
            }
         }
      }
      if (motorGrafico) {
         motorGrafico->renderizar(Renderable::getRenderable());
         if (motorGrafico->isEnd()) {
            if (cartucho) {
               cartucho->setEnd();
            }
         }/**/
      }
   }
}
void main(int numeroArgumentos, char** argumentos) {
    CargaDLL::cargar("./modulos", "./"); 
    
    bool correcto = true;
    const char* escena = "micraft";
    
    if (CargaDLL::hayModulos(Module::GRAPHIC) > 0) {
       motorGrafico = CargaDLL::cogerModulo<modules::graphics::Graphic>(Module::GRAPHIC, "OPENGL 4");
       Module::set(Module::MODULES_TYPE::GRAPHIC, motorGrafico);
    }/**/
    utiles::Watchdog wd;
    //--------
    //Esto lo hacemos a mano mientra no tengamos un menú en la aplicación que me permita hacerlo desd ahí
    FileControl fc;
    if (motorGrafico) {
       motorGrafico->inicializar(0, 800, 600);
       cargarEscena(escena);
       //motorGrafico->addOnFocus(fileControl::onFocus);
       
       
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
    run();
    //std::thread game(run);
    /*while (motorGrafico && motorGrafico->isOpen()) {
       //game.join();
       if (motorGrafico->isEnd()) {
       }
    }*/
    //game.join();
    /*std::thread game(run,motorGrafico,cartucho);
    while(motorGrafico && motorGrafico->isOpen()){
       //game.join();
       if (motorGrafico->isEnd()) {
       }
    }*/
    wd.~Watchdog();
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