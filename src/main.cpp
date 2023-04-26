#include <iostream>
#include <string>
#ifdef WIN32__
    #include <windows.h>
    #include "windows/ventana.h"
#endif

#include "../utilidades/global/input.h"
#include "../modules/graphic/motor.h"
#include "../modules/graphic/interface.h"
#include "../modules/tape/tape.h"
#include "../modules/resources/resource.h"
#include "../modules/audio/audio.h"
#include "../modules/physics/physics.h"
#include "../utilidades/timer/timer.h"
#include "../utilidades/log/log.h"
#include "../graphics/src/log/logEntity.h"

#include "cargaDLLs.h"


#include "../utilidades/global/screen.h"
#include "../utilidades/global/mouse.h"
#include "../graphics/src/renderable/renderable.h"
#include "../components/src/entity.h"

#include <filesControl.h>
#include <compile.h>
#include <watchdog.h> 

#include <thread>

#include <locale>


#include "proyectos/proyecto.h"

#include <array>


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


//#define NK_IMPLEMENTATION
//#include "nuklear.h"

int recargarCartucho = 0;
modules::Tape* cartucho = 0;
modules::graphics::Graphic* motorGrafico = 0;
modules::resources::Resource* recursos = 0;
modules::engine::Physics* motorFisico = 0;
modules::Audio* audio = 0;
std::string carpertaProyecto = "";
std::string proyecto = "";
Input input;
Global global;
modules::graphics::Interface *interfaz;
static void cargarCartucho(char * ruta) {
   
#ifdef WIN32
//Con visual studios falla si hay un PDB, as� que lo intentamos quitar
   std::string rutaS = std::string(ruta);
	
   std::string pdb = rutaS.substr(0, rutaS.size() - 3) + std::string("pdb");
   if (std::filesystem::exists(pdb)) {
      std::filesystem::remove(pdb);
   }/**/
#endif // WIN32 
   //DBG(ruta);
   if (std::filesystem::exists(ruta)) {
      CargaDLL::cargar(ruta);
      //cartucho=

      cartucho = CargaDLL::cogerModulo<modules::Tape>(Module::TAPE);
      if (cartucho) {
          //cartucho->setInput(&input); 
         recargarCartucho = 1;
         //Screen::setDimension(cartucho->getScreenWidth(), cartucho->getScreenHeight());
         Module::set(Module::MODULES_TYPE::TAPE, cartucho);
         //if (motorGrafico) {
            ////motorGrafico->inicializar(0, cartucho->getScreenWidth(), cartucho->getScreenHeight());
           // cartucho->start();
         //}

      }/**/
   }

}
std::string rutaTape = "";
void reiniciarTape();
void compilarTape(bool conReinicio = false) {
    if (global.compileState != StateCompile::COMPILING) {
        global.compileState = StateCompile::COMPILING;
        Compile::compileProject(Proyecto::cogerRutaCompilacionProyecto(), Compile::NINJA, [&]() {
            utiles::Log::debug("Codigo Compilado");
            //Ahora tenemos que analizar si todo se ha compilado bien
            Compile::checkCompiled(Proyecto::cogerRutaCompilacionProyecto());
            if (conReinicio) {
                if (global.compileState == StateCompile::COMPILED) {
                   global.reloadTape = true;
                    
                }
            }/**/
        });
    }
}
void reiniciarTape() {
   std::string ruta = rutaTape;
    if (cartucho) {
       
          if (!cartucho->isStoping()) {

             cartucho->onEnd([&, ruta]() {

                modules::Tape* miCartucho = cartucho;
             //utiles::Log::debug("Fichero descargado");
             //utiles::Watchdog::setTimeOut([ruta] {
             char* miRuta = NULL;
             int longitud = 0;
             while (ruta[longitud++] != 0) {};
             miRuta = new char[longitud];
             for (int i = 0; i < longitud; i++) {
                miRuta[i] = ruta[i];
             }
             CargaDLL::liberarModulo(Module::TAPE);
             //Borramos las entidades
             Entity::destroy();
             cargarCartucho(miRuta);
             delete miCartucho;
             //cartucho = 0;

          //}, 10);

             });
             cartucho->sendStop();
          }
       
    }else {
        cargarCartucho((char *)ruta.c_str());
    }
}
void cargarEscena() {
   //utiles::Log::debug(path);
   
   //std::string sandbox("H:/Desarrollo/motor_videojuegos_2D/sandbox/");
   //td::string ruta = sandbox + std::string(projecto);

   //TODO: Esto solo es para Ninja
   modules::Tape::load(Proyecto::cogerRutaCodigoProyecto(), cartucho, []() {
      //Obtenemos la fecha de la ultima modificacion del fichero con FileControl::getLastTime //get last modification date with FileControl::getLastTime
      std::filesystem::file_time_type fechaMasReciente = FileControl::getLastTime(Proyecto::cogerRutaCodigoProyecto());
      //Obtenemos la fecha de la dll generada  //Get the date of the dll generated
      rutaTape = Proyecto::cogerRutaCompilacionProyecto() + std::string("/") + Proyecto::cogerNombreProyecto() + std::string(".") + std::string(extDLL);
		std::filesystem::file_time_type fechaDLL = FileControl::getLastTime(rutaTape.c_str());
	
		//Sacamos en Debug la fecha de la dll y la fecha mas reciente del fichero //Debug the date of the dll and the most recent file
		DBG("Fecha DLL: " + std::to_string(fechaDLL.time_since_epoch().count()));
        DBG("Fecha Mas Reciente: " + std::to_string(fechaMasReciente.time_since_epoch().count()));
  
		//Si fechaDLL es m�s antigua que fechaMasReciente compilamos //If fechaDLL is older than fechaMasReciente we compile
      if (fechaDLL < fechaMasReciente) {
         compilarTape(true);
      } else {
		   //Cargamos el cartucho //Load the tape
		   //cargarCartucho((char *)rutaTape.c_str());
      }
      /*if (cartucho) {
         if (!cartucho->isStoping()) {
            cartucho->sendStop();
            cartucho->onEnd([] {

               Compile::compileProject(Proyecto::cogerRutaCompilacionProyecto(), Compile::NINJA);
            });
         }
         //cartucho->detener();
      } else {
         Compile::compileProject(Proyecto::cogerRutaCompilacionProyecto(), Compile::NINJA);
      }/**/
      
      
      //cargarEscena(path);
      //if
   });
   
   
   //----
   

   std::string ruta = "";
   ruta+= Proyecto::cogerRutaCompilacionProyecto()+std::string("/") + Proyecto::cogerNombreProyecto() + std::string(".") + std::string(extDLL);
   rutaTape = ruta;
   //if (std::filesystem::exists(ruta)) {
   //   std::filesystem::remove(ruta);
   //}
   
   /* //OJO CON ESTO
   FileControl::fileChangeTime(ruta.c_str(), [&](char* ruta) {

       reiniciarTape();
     
   }, 1000);/**/

}

void bucleJuego(bool* jugando, bool* renderizando, modules::graphics::Graphic* motorGrafico, Entity * entidades=NULL, modules::engine::Physics* motorFisicas=NULL, bool *hayMuertos=NULL) {
    *renderizando = false;
    Time::update();
    //global.deltaTime = Time::deltaTime();
    //input.resetKeyPress();
    
    if (recargarCartucho > 0 && cartucho!=NULL && cartucho->isRunning() && !cartucho->isStoping()) {
       
        //std::vector<void*>* renderizables = NULL;
        if (cartucho) {
            if (recargarCartucho != 1) {
               
                try {
                    if (!cartucho->isOrderStop()) {
                        input.checkKeysPress();
                        //TODO: Corregir para evitar que si hay un c�digo lento el resto se vea comprometido
                        if (entidades == NULL) {
                            //Entity::preUpdateCode();
                            //Entity::updateCode();
                        }else {
									   //�Ejecutamos esto con una frecuencia determinada? 
                              //�Ser�a interesante que est� en un hilo aparte?
                              if (motorFisicas != NULL) {
										   motorFisicas->update();
                              }

                              entidades->preUpdateCode();
									   //Ejecutar las f�sicas
                            
                              
                           entidades->updateCode();
                           if (hayMuertos) {
                              *hayMuertos=entidades->updateLifeTime();
                           }
                        }
                        cartucho->update();
                        //Sleep(150);
                        //while (*renderizando) {
                        //}
                    }
                }
                catch (std::exception e) {
                    utiles::Log::error("Se ha producido una excepcion");
                    utiles::Log::debug(e.what());
                    cartucho->stop();
                }
            }
        }
    }
    *renderizando = true;
    //Sleep(2000);
}

void run(bool*jugando, bool* renderizando,modules::graphics::Graphic *motorGrafico,Entity * entidades=NULL, modules::engine::Physics* motorFisicas = NULL, bool* hayMuertos = NULL) {
   
    int tiempo = 0;
    float fps = -1;
   while (motorGrafico && motorGrafico->isOpen()) {
      /*tiempo += Time::deltaTime();
      while (tiempo >= 1) {
          tiempo -= 1;
          if (motorGrafico->getGlobal()->fps == 0) {
              motorGrafico->getGlobal()->fps=fps;
          }else {
              motorGrafico->getGlobal()->fps = (fps + motorGrafico->getGlobal()->fps) / 2.0f;
          }
          DBG("FPS %", motorGrafico->getGlobal()->fps);
          fps = -1;
      }
      fps++;/**/
      /*if (Time::deltaTime() < (1000 / 60)) {
         std::this_thread::sleep_for(std::chrono::duration<double,std::milli>( (1000 / 60) - Time::deltaTime()));
      }/**/
      //if (fps < 60) {

      if(global.executing== StateExecuting::PLAY && !global.paused){
        bucleJuego(jugando,renderizando,motorGrafico, entidades,motorFisicas,hayMuertos);
      } else {
         if (global.executing == StateExecuting::PLAY && global.paused) {
            global.executing = StateExecuting::PAUSED;
            Time::freeze(true);
         } else if(global.executing == StateExecuting::PAUSED && !global.paused){
            global.executing = StateExecuting::PLAY;
            Time::freeze(false);
         }
      }
     
	    	
      //}
      //Sleep(10);// ((1.0f / 30.0f) - Time::deltaTime()) * 1000);
   }
   
   (*jugando) = false;
}


void pintadoJuego(bool * jugando, bool * renderizando, bool sinHilo =true, Entity* entidades=NULL, modules::engine::Physics* motorFisicas = NULL) {
    entidades->setGraphic(motorGrafico);
    std::thread* hiloJuego;
    bool hayMuertos=false;
    if (!sinHilo) {
        hiloJuego=new std::thread(run, jugando, renderizando, motorGrafico, entidades, motorFisicas,&hayMuertos);
    }
    bool primeraVez = true;
    motorGrafico->init();
    std::thread* compilador = NULL;
    while (*jugando && motorGrafico && motorGrafico->isOpen()) {//motorGrafico && motorGrafico->isOpen()) {
       if (global.executing == StateExecuting::STOPING) {
          global.executing = StateExecuting::RELOADING;
          reiniciarTape();
       }
        //run(&jugando, motorGrafico);
        if (motorGrafico) {
            if (recargarCartucho > 0 && cartucho && cartucho->isRunning() && !primeraVez) {
                if (cartucho) {
                    if (recargarCartucho == 1) {

                        try {
                            if (!cartucho->isStoping()) {
                               //Tenemos que borrar las entidades
                               entidades->clear();
                              DBG("Comenzamos el cartucho de juego");
                              cartucho->start();
                              //Ahora aplicamos las f�sicas la primera vez
                              if (motorFisicas!=NULL) {
                                 motorFisicas->init();
                              }
                              //DBG("kk");
                              entidades->startCodes(0, &input);
                            }
                            recargarCartucho = 2; 
                            global.executing = StateExecuting::STOP;
                        }
                        catch (std::exception e) {
                            utiles::Log::error("Se ha producido una excepcion");
                            utiles::Log::debug(e.what());
                        }
                    }else {
                        try {
                            if (cartucho->isRunning() && cartucho->isOrderStop()) {
                                utiles::Log::debug("Se est� comenzando la detenci�n");
                                input.resetAllKeysPress();
                                recargarCartucho = 0;
                                entidades->stopCodes();
                                cartucho->stop();
                                //entidades->destroy();
                            }
                            else if(sinHilo) {
                               // bucleJuego(jugando, renderizando, motorGrafico,entidades,motorFisicas);
                               if (global.executing == StateExecuting::PLAY && !global.paused) {
                                  bucleJuego(jugando, renderizando, motorGrafico, entidades, motorFisicas, &hayMuertos);
                               } else {
                                  if (global.executing == StateExecuting::PLAY && global.paused) {
                                     global.executing = StateExecuting::PAUSED;
                                     Time::freeze(true);
                                  } else if (global.executing == StateExecuting::PAUSED && !global.paused) {
                                     global.executing = StateExecuting::PLAY;
                                     Time::freeze(false);
                                  } else {
                                     Time::reset();
                                     if (global.reloadTape) {
                                        global.executing = StateExecuting::RELOADING;
                                        reiniciarTape();
                                        global.reloadTape = false;
                                     }
                                  }
                               }
                            }
                        }catch (std::exception e) {
                            utiles::Log::error("Se ha producido una excepcion");
                            utiles::Log::debug(e.what());
                            cartucho->stop();
                        }
                    }
                }
            }
            primeraVez = false;
            motorGrafico->preRender();
            bool conRendeJuego = false;
            if (cartucho && cartucho->isRunning()) {
                // if (nk_begin(&ctx, "Game", nk_rect(10, 10, 300, 300), NK_WIDGET_VALID)) {
                //*renderizando = true;
                //while (!(*renderizando)) {};
                motorGrafico->render(Renderable::getRenderable());
                conRendeJuego = true;
                //*renderizando = false;
                //Sleep(10);
                // }
                // nk_end(&ctx);
               //motorGrafico->renderizarTexto
            }
            motorGrafico->renderInterface();
            motorGrafico->postRender(conRendeJuego);
            if (hayMuertos) {
               //Destruimos los muertos
               entidades->destroyDead();
               hayMuertos = false;
            }
            if (global.compileState == StateCompile::NEEDCOMPILE) {
                compilador = new std::thread(compilarTape, true);
                //compilador.
            }
            else {
                if (compilador != NULL) {
                    compilador = NULL;
                }
            }
            if (motorGrafico->isEnd()) {
                if (cartucho) {
                    cartucho->setEnd();
                }
            }/**/
        }
        if (global.executing == StateExecuting::RELOAD_PROJECT) {
           //Cargamos el proyecto
           if (Proyecto::cargarProyecto(global.folderProject.c_str())) {
               if (Proyecto::estaCargado()) {
                  cargarEscena();
               }
               reiniciarTape();
               global.reloadTape = false;
               global.executing = StateExecuting::RELOADING;
           } else {
              global.executing = StateExecuting::STOPING;
           }

        }
        /*if (global.reloadTape) {
           reiniciarTape();
           global.reloadTape = false;
           global.executing = StateExecuting::RELOADING;
        }/**/
    }
    if (compilador != NULL) {
        compilador->join();
    }
    if (!sinHilo) {
        hiloJuego->join();
    }
    
}

bool procesarParametros(int numeroArgumentos, char** argumentos);


/****************************************************************************/
void main(int numeroArgumentos, char** argumentos) {
   Entity* entidades = new Entity();
   //std::setlocale(LC_ALL, "es_ES.UTF-8");
   std::setlocale(LC_ALL, "en_EN.UTF-8");
   Screen::setDimension(2000, 1000);
   if (numeroArgumentos > 1) {
      if (!procesarParametros(numeroArgumentos, argumentos)) {
         return;
      };
   }/**/
   /*char** parametros = new char* [4];
   parametros[0] = "a";
   parametros[1] = "-g";
   parametros[2] = "prueba";
   parametros[3] = "H:/Desarrollo/motor_videjuegos_sandbox";
   if (!procesarParametros(4, parametros)) {
      return;
   };
   delete[] parametros;
   /**/
   //Creamos un LOG de Entidades
   
   //DBG("--------------------------");
   CargaDLL::cargar("./modulos", "./");

   bool correcto = true;
   utiles::LogEntity* logEntity=NULL;
   if (CargaDLL::hayModulos(Module::GRAPHIC) > 0) {
      motorGrafico = CargaDLL::cogerModulo<modules::graphics::Graphic>(Module::GRAPHIC, "OPENGL 4");
      Module::set(Module::MODULES_TYPE::GRAPHIC, motorGrafico);
	  //interfaz=
      //Como tenemos gr�ficos cambiamos de log
      motorGrafico->setGlobal(&global);
      motorGrafico->setInput(input);
      motorGrafico->setEntity(entidades);
      motorGrafico->setFrameBuffer(true);
      
   }/**/
   //Ahora cargamos la librer�a de recursos
   if (CargaDLL::hayModulos(Module::RESOURCES) > 0){
      recursos = CargaDLL::cogerModulo<modules::resources::Resource>(Module::RESOURCES, "RESOURCES WITH LOAD FILES");
      Module::set(Module::RESOURCES, recursos);
   }
   //Cargamos la librer�a de f�sicas
   if (CargaDLL::hayModulos(Module::PHYSICS) > 0) {
       //motorFisico = CargaDLL::cogerModulo<modules::engine::Physics>(Module::PHYSICS, "Physics JOLT");
       motorFisico = CargaDLL::cogerModulo<modules::engine::Physics>(Module::PHYSICS);
       if (motorFisico == NULL) {
          DBG("No se ha podido cargar el m�dulo de f�sicas");
       }
       Module::set(Module::PHYSICS, motorFisico);
       if (motorGrafico) {
           motorGrafico->setPhysics(motorFisico);
       }
   }

   //TODO: MOVER A LA PARTE DE JUEGO
   if (CargaDLL::hayModulos(Module::AUDIO) > 0) {
      audio = CargaDLL::cogerModulo<modules::Audio>(Module::AUDIO, "Audio OpenAL");//
      Module::set(Module::AUDIO, audio);
   }
    utiles::Watchdog wd;
    //--------
    //Esto lo hacemos a mano mientra no tengamos un men� en la aplicaci�n que me permita hacerlo desd ah�
    FileControl fc;

    /*char** parametros = new char* [4];
    parametros[0] = (char*)"a";
    parametros[1] = (char*)"-l";
    parametros[2] = (char*)"H:/Desarrollo/motor_videjuegos_sandbox/micraft";*/
    if (!procesarParametros(4, argumentos)) {
       return;
    };
    //delete[] parametros;/**/

    
    if (motorGrafico) {
       motorGrafico->inicializar(0, Screen::getWidth(), Screen::getHeight());
       utiles::Log* lTemp = motorGrafico->getLog();
       if (lTemp != NULL) {
           //DBG("PASAMOS a LOG Gr�fico");
           //logEntity = lTemp;
           utiles::Log::setInstanceId(motorGrafico->getIdInstanceLog());
           //DBG("HH");
           //DBG("------------------------");/**/
           //utiles::Log::setInstanceId(0);
       }
       //if (Proyecto::estaCargado()) {
       //   cargarEscena();
       //}
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
        if (cartucho){
            //cartucho->setGraphic(motorGrafico);
            correcto=motorGrafico->inicializar(0, cartucho->getScreenWidth(), cartucho->getScreenHeight());
            cartucho->start();
        } else {
           correcto = motorGrafico->inicializar(0, 800, 600);
        };
    }/**/
    bool jugando = true;
    bool renderizando = false;
    bool recargando = false;
    
    pintadoJuego(&jugando, &renderizando,true,entidades, motorFisico); //false es con hilo, true sin hilos
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
        cartucho->stop();
        delete cartucho;
    }
    //Activamos el log de disco //Active log of disc
    utiles::Log::setInstanceId(0);
    Entity::destroy();
    if (motorGrafico) {
        motorGrafico->destroy();
        delete motorGrafico;
    }
    if (recursos) {
       delete recursos;
    }
    if (audio) {
       delete audio;
    }
    if (motorFisico) {
        delete motorFisico;
    }
    delete entidades;
    utiles::Log::destroy();
}/**/
#endif


bool procesarParametros(int numeroArgumentos, char** argumentos) {

   int pos = 1;
   while (pos < numeroArgumentos) {
      char* param = argumentos[pos];
      //C++ no tiene switch para cadenas
      if (strcmp(param, "-g") == 0) { //Genera un proyecto vacio
         if (pos + 2 >= numeroArgumentos) {
#ifdef WIN32
            MessageBox(NULL, "Se ha de indicar tanto el nombre como la ruta del proyecto", TEXT("Motor de videojuegos version 1.0"), MB_OK);
#else
            std::cout << "Motor de videojuegos version 1.0\r\n"Se ha de indicar tanto el nombre como la ruta del proyecto"\r\n" << ayuda;
#endif // WIN32
            return false;
         }
         const char* error = Proyecto::generarProyecto(argumentos[pos + 1], argumentos[pos + 2]);
         pos += 3;
         if (error) {
#ifdef WIN32
            MessageBox(NULL, error, TEXT("Motor de videojuegos version 1.0"), MB_OK);
#else
            std::cout << "Motor de videojuegos version 1.0\r\n" << error << std::endl;
#endif // WIN32
            return false;
         }
         return true;
      } else if (strcmp(param, "-l") == 0) {
         if (pos + 1 >= numeroArgumentos) {
#ifdef WIN32
            MessageBox(NULL, "Se ha de indicar la ruta del proyecto", TEXT("Motor de videojuegos version 1.0"), MB_OK);
#else
            std::cout << "Motor de videojuegos version 1.0\r\n"Se ha de indicar la ruta del proyecto"\r\n" << ayuda;
#endif // WIN32
            return false;
         }
         //carpertaProyecto = std::string();
         //if (!Proyecto::cargarProyecto(argumentos[pos + 1])) {
         //   return false;
        // } else {
            global.folderProject = std::string(argumentos[pos + 1]);
            global.executing = StateExecuting::RELOAD_PROJECT;
         //}
         
         pos += 2;
         return true;
      } else if (strcmp(param, "-h") == 0) {
         std::string ayuda;
         ayuda += "-g name path\t\tGenerara proyecto\r\n";
         ayuda += "-l path\t\tCargar proyecto indicado en la ruta\r\n";
         ayuda += "-h\t\tAyuda\r\n";
#ifdef WIN32
         MessageBox(NULL, ayuda.c_str(), TEXT("Motor de videojuegos version 1.0"), MB_OK);
#else
         std::cout<<"Motor de videojuegos version 1.0\r\n"<<ayuda;
#endif // WIN32
         return false;
      }
      pos++;
   }
   return false;
}
//Global global;
