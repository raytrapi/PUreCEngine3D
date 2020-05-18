#include "imagen.h"

namespace imagenes {
	Imagen::~Imagen() {
		if (datos != NULL) { 
			free(datos);
		} 
	}
	int Imagen::cogerLongitud() {
		return longitud;
	}

	void Imagen::setDatos(float* crudo) {
		datos = crudo;
	}

	float* Imagen::cogerDatos() {
		return datos;
	}
	void Imagen::ponerAncho(int valor) {
		ancho=valor;
	}
	int Imagen::cogerAncho() {
		return ancho;
	}
	void Imagen::ponerAlto(int valor) {
		alto = valor;
	}

	int Imagen::cogerAlto() {
		return alto;
	}

}