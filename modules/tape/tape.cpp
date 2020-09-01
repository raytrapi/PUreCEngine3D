#include "tape.h"

void modules::Tape::load(const char* project, modules::Tape* tape,void(* callback)(const char *)) {
   projectName = std::string(project);
   std::string pro = "H:/Desarrollo/motor_videjuegos_sandbox/micraft/src/main.cpp";

   std::string s="H:/Desarrollo/motor_videojuegos_2D/sandbox/"+std::string(project)+"/"+ std::string(project)+".dll";
   //projectName = s;
   callbackLoad = callback;
   //cinta = tape;
   bool existe=fileControl::fileChange(pro.c_str(), []() {
      //if (cinta != 0) {
         //utili
      //}
      callbackLoad(projectName.c_str());
      //utiles::Log::debug("Cambio");
   });/**/
   if (existe) {
      callbackLoad(projectName.c_str());
   }
}
std::string modules::Tape::projectName;
void (* modules::Tape::callbackLoad)(const char*);
modules::Tape* cinta;