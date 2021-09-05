#include "input.h"

bool Input::isKeyDown(Key key) {
   switch (key) {
      case Key::UP:
      case Key::DOWN:
      case Key::LEFT:
      case Key::RIGHT:
         for (auto map : mapeadas[key]) {
            Tecla k = teclas[map];
            if (k.estaPulsada()) {//teclas.find(map) != teclas.end() &&
               return true;
            }
         }
         break;
      default:
         return (teclas.find(key) != teclas.end() && teclas[key].estaPulsada());
         break;
   }
   return false;
}
bool Input::isKeyUp(Key key) {
    return (teclas.find(key) != teclas.end() && !teclas[key].estaPulsada());
}
bool Input::isKeyPress(Key key) { //TODO: Hacer que sea un evento onKeyPress
    return presionadas.find(key) != presionadas.end();
    
}
Key Input::traducirTecla(unsigned int key) {
    Key k = (Key) key;
    return k;
    /*if (key >= 0x41 && key <= 0x5A) { //De la A a la Z
       utiles::Log::debug(("Pulsamos la " + std::to_string(key)).c_str());
        k = (Key)(key - 0x40); //Uno menos para que empieze en 1
    }
    switch (key) {
       case 0x26:
       case 328: //Flecha Arriba
       case 17:
          k = Key::UP;
          break;
       case 0x27:
       case 333: //Flecha Derecha
       case 32: // D
          k = Key::RIGHT;
          break;
       case 0x28:
       case 31:
       case 336://Flecha abajo
          k = Key::DONW;
          break;
       case 0x25:
       case 331: //Flecha izquierda
       case 30:
          k = Key::LEFT;
          break;
       case 16:
          k = Key::Q;
          break;
       case 18:
          k = Key::E;
          break;
       
    }
    return k;/**/
}
void Input::setKeyDown(unsigned int key, long extra) {
    Key k = traducirTecla(key);

    if (k != Key::NONE) {
       Tecla t = teclas[k];
       teclas[k].pulsar();
       presionadas[k] = &t;
    }
}

void Input::setKeyUp(unsigned int key, long extra) {
    Key k = traducirTecla(key);
    if (k != Key::NONE) {
        teclas[k].soltar();
        /*for (int i = 0; i < eventosKeyPress.size(); i++) {
            eventosKeyPress[i](k);
        }*/
    }
}
void Input::resetKeyPress() {
    presionadas.clear();
}
/*void Input::onPress(void(*f)(Key)) {
    eventosKeyPress.push_back(f);
}/**/
std::map<Key, Tecla> Input::teclas;
std::map<Key, Tecla*> Input::presionadas;
std::map<Key, std::vector<Key>> Input::mapeadas = { 
   {Key::UP,{Key::W}},
   {Key::RIGHT,{Key::D}},
   {Key::DOWN,{Key::S}},
   {Key::LEFT,{Key::A}}
  };
//std::vector<void (*)(Key)> Input::eventosKeyPress;
