#include "tape.h"

void modules::Tape::load(const char* project, modules::Tape* tape,std::function<void(const char*)>callback) {
   projectName = std::string(project);
   std::string pro = "H:/Desarrollo/motor_videjuegos_sandbox/micraft/src/main.cpp";

   std::string s="H:/Desarrollo/motor_videojuegos_2D/sandbox/"+std::string(project)+"/"+ std::string(project)+".dll";
   //projectName = s;
   callbackLoad = callback;
   //cinta = tape;
   bool existe=FileControl::fileChangeTime(pro.c_str(), [project]() {
      //if (cinta != 0) {
         //utili
      //}
      callbackLoad(project);
      //utiles::Log::debug("Cambio");
   },2000);/**/
   if (existe) {
      callbackLoad(projectName.c_str());
   }

}
std::string modules::Tape::projectName;
std::function<void(const char*)> modules::Tape::callbackLoad;
modules::Tape* cinta;