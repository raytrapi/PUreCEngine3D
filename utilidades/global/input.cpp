#include "input.h"
#include "screen.h"

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
bool Input::isKeyPress(Key key, bool always) { //TODO: Hacer que sea un evento onKeyPress
   return teclas[key].estaPulsada(always);
   /*if (always) {
      return presionadas.find(key) != presionadas.end();
   } else {
      return presionadas.find(key) != presionadas.end() && teclas[key].estaPulsada(true);
   }/**/
}
void Input::onKeyPress(Key key, std::function<void(Key)> f) {
    //DBG("dir %", this);
    controlTeclasPulsadas.push_back({ key,f,false });
};
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

void Input::setDelayTime(Key key, float time) {
   teclas[key].setDelay(time);
};
void Input::setRepeatTime(Key key, float time) {
   teclas[key].setRepeat(time);
};
void Input::resetTime(Key key) {
   teclas[key].resetTime();
};
void  Input::checkKeysPress() {
    for (int i = 0; i < controlTeclasPulsadas.size(); i++) {
        auto control = controlTeclasPulsadas[i];
		if (isKeyDown(std::get<0>(control))) {
            if (!std::get<2>(control)) {
                std::get<2>(controlTeclasPulsadas[i]) = true;
				std::get<1>(control)(std::get<0>(control));
            }
		} else {
            if (std::get<2>(control)) {
                std::get<2>(controlTeclasPulsadas[i]) = false;
            }
		}
	}/**/
	
};


/*********/
/* RATÓN */
/*********/
std::tuple<float, float, float> Input::getMouse3DPosition(float xScreen, float yScreen, bool enEditor) {
   float x = xMouse - xScreen;
   float y = yMouse - yScreen;
   if (x < 0 || x > Screen::ancho || y < 0 || y > Screen::alto) {
      x = 0;
      y = 0;
   }
   
   return { x, y,0 };
}
void Input::setMousePosition(float x, float y, float width, float height, float xScreen, float yScreen) {
   xMouse = x;
   yMouse = y;
}


/*void Input::onPress(void(*f)(Key)) {
    eventosKeyPress.push_back(f);
}/**/
std::map<Key, Tecla> Input::teclas;
std::map<Key, Tecla*> Input::presionadas;
std::map<Key, std::vector<Key>> Input::mapeadas = { 
   {Key::UP,{Key::W,Key::ARROW_UP}},
   {Key::RIGHT,{Key::D, Key::ARROW_RIGHT}},
   {Key::DOWN,{Key::S, Key::ARROW_DOWN}},
   {Key::LEFT,{Key::A, Key::ARROW_LEFT}}
  };
//std::vector<void (*)(Key)> Input::eventosKeyPress;
float Input::xMouse;
float Input::yMouse;