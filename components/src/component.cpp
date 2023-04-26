#include "component.h"

Component::Component() { }
Component::~Component() {
	DBG("borro componente Generico");
	if (nombre != NULL) {
		delete[] nombre;
		nombre = NULL;
	}
}

void Component::setName(std::string name) {
	if (nombre != NULL) {
		delete[] nombre;
		nombre = NULL;
	}
	nombre = new char[name.length()+1];
	for (int i = 0; i < name.length(); i++) {
		nombre[i] = name[i];
	}
	nombre[name.length()] = '\0';
}
std::string Component::getName() {
	if(nombre!=NULL){
		return std::string(nombre);
	}
	return std::string("Componente ");
};
