#include "tape.h"

void modules::Tape::load(const char* projectFolderSrc, modules::Tape* tape,std::function<void()>callback) {
   //projectName = std::string(project);
   //std::string pro = "H:/Desarrollo/motor_videjuegos_sandbox/micraft/src/main.cpp";

   //std::string s="H:/Desarrollo/motor_videojuegos_2D/sandbox/"+std::string(project)+"/"+ std::string(project)+".dll";
   //projectName = s;
   callbackLoad = callback;
   //cinta = tape;
   bool existe=FileControl::fileChangeTime(projectFolderSrc, []() {
      //if (cinta != 0) {
         //utili
      //}
      callbackLoad();
      //utiles::Log::debug("Cambio");
   },1000);/**/
   if (existe) {
      //callbackLoad();
   }

}
std::string modules::Tape::projectName;
std::function<void()> modules::Tape::callbackLoad;
modules::Tape* cinta;