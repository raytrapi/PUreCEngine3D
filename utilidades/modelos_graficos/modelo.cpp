#include "modelo.h"

std::string utiles::model::Model::trim(std::string cadena) {
	int posI = 0;
	int posF = cadena.length()-1;

	while (posI < posF && cadena[posI] == ' ') { 
		posI++;
	} 
	while (posI > posF && cadena[posF] == ' ') {
		posF--;
	}
	return cadena.substr(posI,posF-posI);
}

std::vector<std::string> utiles::model::Model::split(std::string cadena, char c) {
	// TODO: Insertar una instrucción "return" aquí
	std::vector<std::string> palabras;
	std::string palabra = "";
	for (int i = 0; i < cadena.length(); i++) {
		if (cadena[i] == c) {
			palabras.push_back(palabra);
			palabra = "";
		} else {
			palabra += cadena[i];
		}
	}
	palabras.push_back(palabra);
	return palabras;
}
