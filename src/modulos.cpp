#include "modulos.h" 



bool Modulo::isInputKeyDown(Key key) {
    return teclas[key].estaPulsada();
}

void Modulo::setInputKeyDown(Key key) {
    teclas[key].pulsar();
}

void Modulo::setInputKeyUp(Key key) {
    teclas[key].soltar();
}
std::map<Key, Tecla> Modulo::teclas;