#include "input.h"

bool Input::isKeyDown(Key key) {
    return (teclas.find(key)!=teclas.end() && teclas[key].estaPulsada());
}
bool Input::isKeyUp(Key key) {
    return (teclas.find(key) != teclas.end() && !teclas[key].estaPulsada());
}
bool Input::isKeyPress(Key key) {
    return presionadas.find(key) != presionadas.end();
    
}
Key Input::traducirTecla(unsigned int key) {
    Key k = Key::NONE;
    if (key >= 0x41 && key <= 0x5A) { //De la A a la Z
        k = (Key)(key - 0x40); //Uno menos para que empieze en 1
    } else {
        switch (key) {
        case 0x26:
            k = Key::UP;
            break;
        case 0x27:
            k = Key::RIGHT;
            break;
        case 0x28:
            k = Key::DONW;
            break;
        case 0x25:
            k = Key::LEFT;
            break;
        }
    }
    return k;
}
void Input::setKeyDown(unsigned int key, long extra) {
    Key k = traducirTecla(key);
    if (k != Key::NONE) {
        teclas[k].pulsar();
    }
}

void Input::setKeyUp(unsigned int key, long extra) {
    Key k = traducirTecla(key);
    if (k != Key::NONE) {
        Tecla t = teclas[k];
        t.pulsar();
        presionadas[k] = &t;
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
//std::vector<void (*)(Key)> Input::eventosKeyPress;
