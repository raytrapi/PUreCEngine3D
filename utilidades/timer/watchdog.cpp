#include "watchdog.h"
namespace utiles {
   Watchdog::Watchdog(){
      instancia = this;
   }
   Watchdog::~Watchdog() {
      ejecutando = false; //Paramos el hilo
      if (hilo.joinable()) {
         hilo.join(); //Y esperamos a que se detenga
      }
      for (auto itr = controles.begin(); itr != controles.end(); itr++) {
         delete* itr; //Borramos cada tupla
      }
      controles.clear();
   }
   unsigned int Watchdog::setTimeOut(std::function<void()> callback, unsigned int milliseconds) {
      int yo = setInterval([yo, callback]() {clearInterval(yo); callback(); }, milliseconds);
      return yo;
   };
   void Watchdog::clearTimeOut(unsigned int id) {
      clearInterval(id);
   }
   unsigned int Watchdog::setInterval(std::function<void()> callback, unsigned int milliseconds) {
      //unsigned int id = controles.size();

      controles.push_back(new std::tuple< unsigned int, unsigned int, std::function<void()>, double >(
         ++ids, milliseconds, callback, 0
      ));
      if (controles.size() == 1) {
         ejecutando = true;
         delta = 0;
         anterior = std::chrono::system_clock::now();
         hilo = std::thread(&Watchdog::iteracion, instancia);
      }
      return ids;
   }

   void Watchdog::clearInterval(unsigned int id) {
      bool sinEncontrar = true;
      int i = 0;
      while( i<controles.size() && sinEncontrar) {
         if (std::get<0>(*controles[i]) == id) {
            controles.erase(controles.begin()+i);
            sinEncontrar=false;
         }
         i++;
         
      }
      if (controles.empty()) {
         
         ejecutando = false;
         if (hilo.joinable()) {
            hilo.join();
         }
      }
      
   }


   void Watchdog::iteracion() {
      while (ejecutando) {
         std::chrono::system_clock::time_point actual = std::chrono::system_clock::now();
         double milisegundos = std::chrono::duration_cast<std::chrono::milliseconds>(actual - anterior).count();
         delta = milisegundos > 0 ? milisegundos : 0;
         anterior = actual;
         
         for (auto itr = controles.begin(); itr != controles.end(); ) {
            std::get<3>(**itr) += (delta);
            unsigned int fin = std::get<1>(**itr);
            if (fin <= std::get<3>(**itr)) {
               std::get<3>(**itr) = 0;
               std::get<2>(**itr)();
            }
            if (itr != controles.end()) {
               itr++;
            }
         }
         std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
   }
   std::vector < std::tuple<unsigned int, unsigned int, std::function<void()>, double>*> Watchdog::controles;
   std::thread Watchdog::hilo;
   bool Watchdog::ejecutando = false;
   Watchdog * Watchdog::instancia = NULL;

   std::chrono::system_clock::time_point Watchdog::anterior = std::chrono::system_clock::now();
   double Watchdog::delta = 0;
   unsigned int Watchdog::ids = 0;
}