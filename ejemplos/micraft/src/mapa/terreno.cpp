#include "terreno.h"


int Terreno::preProbabilidades(std::vector<Tipo> vecinos, std::vector<Tipo> descartar) {
	unsigned int casosTotales = 0;
	int* bloquesCercanos = new int[numeroTiposTierras];
	for (unsigned int i = 0; i < numeroTiposTierras; i++) {
		bool valido = true;
		Tipo tipo = (Tipo)i;
		for (int j = 0; j < descartar.size() && valido; j++) {
			if (descartar[j] == tipo) {
				valido = false;
			}
		}
		if (valido){
			switch (tipo) {
			case Tipo::VACIO:
				bloquesCercanos[i] = 1;
				casosTotales++;
				break;
			case Tipo::TIERRA_SECA:
				bloquesCercanos[i] = 0;
				//casosTotales++;
				break;
			case Tipo::TIERRA_VERDE:
				bloquesCercanos[i] = 5;
				casosTotales += 5;
				break;
			case Tipo::PIEDRA:
				bloquesCercanos[i] = -1;
				break;
			case Tipo::AGUA:
				bloquesCercanos[i] = 1;
				casosTotales++;
				break;
			default: 
				bloquesCercanos[i] = 1;
				casosTotales += 1;
				break;
			}
		} else {
			bloquesCercanos[i] = -10;
		}

	}
	for (int i = 0; i < vecinos.size(); i++) {
		
		switch (vecinos[i]) {
		case Tipo::TIERRA_SECA:
			//Comprobamos si hay agua cerca
			if (hay(Tipo::AGUA, vecinos)) {
				bloquesCercanos[(int)Tipo::TIERRA_VERDE]++;
				casosTotales++;
			}
			break;
		case Tipo::TIERRA_VERDE:
			//Comprobamos si hay agua cerca
			if (!hay(Tipo::AGUA, vecinos)) {
				bloquesCercanos[(int)Tipo::TIERRA_SECA]++;
				casosTotales++;
			}
			break;
		case Tipo::AGUA:
			if (!hay(Tipo::AGUA, vecinos)) {
				bloquesCercanos[(int)Tipo::AGUA]++;
				casosTotales++;
			}
			break;
		default:
			break;
		}
		bloquesCercanos[(int)vecinos[i]]++;
		casosTotales++;
	}
	float p = 0;
	for (int i = 0; i < numeroTiposTierras; i++) {
		if (bloquesCercanos[i] > 0) {
			p += (float)bloquesCercanos[i] / casosTotales * 100.f;
			probabilidades[i] = p;
		} else {
			probabilidades[i] = -1;
		}
	}
	delete[] bloquesCercanos;
	return 0;
}

bool Terreno::hay(Tipo tipo, std::vector<Tipo> vecinos) {
	for (int i = 0; i < vecinos.size(); i++) {
		if (vecinos[i] == tipo) {
			return true;
		}
	}
	return false;
}

Terreno::Terreno(short tamaño) {
	this->tamaño = tamaño;
	for (int i = 0; i < tamaño; i++) {
		terrenosVecinos.push_back(0);
	}
	for (int i = 0; i < numeroTiposTierras; i++) {
		probabilidades.push_back(-1);
	}
}

Terreno::~Terreno() {
	borrar(porcion);
	//TODO: Eliminar vecinos
}

Tipo** Terreno::generar(Direccion v) {
	generar();
	return porcion;
}
Tipo** Terreno::cogerPorcion() {
	return porcion;
}
Tipo** Terreno::generar() {
 	if (porcion != 0) {
		borrar(porcion);
	};
	//Recalcular Pesos
	std::vector<Tipo> vecinos;
	std::vector<Tipo> descartados;
	//descartados.push_back(Tipo::VACIO); //vacio
	//descartados.push_back(Tipo::PIEDRA); //Piedra
	preProbabilidades(vecinos,descartados);
	std::srand(std::time(0));
	porcion = new Tipo *[tamaño];
	for (int i = 0; i < tamaño; i++) {
		porcion[i] = new Tipo[tamaño];
	}
	for (int x = 0; x < tamaño; x++) {
		for (int y = 0; y < tamaño; y++) {
			int aleatorio= std::rand() % 101;
			Tipo bloque = Tipo::VACIO;
			//if (x > 0 || y > 0) {
				int i = 0;
				while (i < numeroTiposTierras && probabilidades[i] < aleatorio) {
					bloque = (Tipo)++i;
				};

			//}
			porcion[x][y] = bloque;
			
			//Recalcular pesos
			
			if (y == 0) {
				if (x == 0) {

				} else if (x == tamaño - 1) {
					vecinos.push_back(porcion[x - 1][y]);
				} else {
					vecinos.push_back(porcion[x - 1][y]);
				}
			} else if(y< tamaño -1){
				if (x == 0) {

				} else if (x == tamaño - 1) {
					vecinos.push_back(porcion[x - 1][y]);
					vecinos.push_back(porcion[x - 1][y-1]);
				} else {
					vecinos.push_back(porcion[x - 1][y]);
					vecinos.push_back(porcion[x - 1][y-1]);
				}
			} else {
				//Limite inferior
				if (x == 0) {

				} else if (x == tamaño - 1) {
					vecinos.push_back(porcion[x - 1][y]);
					vecinos.push_back(porcion[x - 1][y - 1]);
				} else {
					vecinos.push_back(porcion[x - 1][y]);
					vecinos.push_back(porcion[x - 1][y - 1]);
				}
			}
			preProbabilidades(vecinos, descartados);
		}
	}
	//generados.push_back(porcion);
	return porcion;
}

void Terreno::borrar(Tipo** porcion) {
	if (porcion != 0) {
		for (int i = 0; i < tamaño; i++) {
			delete[](porcion)[i];
		}
		delete[](porcion);
	}
}

Terreno* Terreno::coger(Direccion v) {
	return terrenosVecinos[(int)v];
}

void Terreno::informar(Terreno* tierra, Direccion d) {
	if (terrenosVecinos[(int)d] != 0) {
		return;
	}
	terrenosVecinos[(int)d] = tierra;
	
	switch (d) {
	case Direccion::ESTE:
		tierra->informar(this, Direccion::OESTE);

		if (terrenosVecinos[(int)Direccion::NORTE] != 0) {
			terrenosVecinos[(int)Direccion::NORTE]->informar(tierra, Direccion::SUROESTE);
			tierra->informar(terrenosVecinos[(int)Direccion::NORTE], Direccion::NORESTE);
		}
		break;
	case Direccion::NORTE:
		tierra->informar(this, Direccion::SUR);
		if (terrenosVecinos[(int)Direccion::ESTE] != 0) {
			terrenosVecinos[(int)Direccion::ESTE]->informar(tierra, Direccion::NOROESTE);
			tierra->informar(terrenosVecinos[(int)Direccion::NORTE], Direccion::SURESTE);
		}
		break;
	case Direccion::OESTE:
		tierra->informar(this, Direccion::ESTE);
		if (terrenosVecinos[(int)Direccion::NORTE] != 0) {
			terrenosVecinos[(int)Direccion::NORTE]->informar(tierra, Direccion::SURESTE);
			tierra->informar(terrenosVecinos[(int)Direccion::NORTE], Direccion::NOROESTE);
		}
		break;
	case Direccion::SUR:
		tierra->informar(this, Direccion::NORTE);
		terrenosVecinos[(int)Direccion::OESTE]->informar(tierra, Direccion::NORESTE);
		tierra->informar(terrenosVecinos[(int)Direccion::OESTE], Direccion::SUROESTE);
		break;
	}
	
}
