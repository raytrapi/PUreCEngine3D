#include "string.h"
std::string utils::String::trim(std::string cadena) {
	if (cadena.length() == 0) {
		return cadena;
	}
	int posI = 0;
	int posF = cadena.length() - 1;

	while (posI < posF && cadena[posI] == ' ') {
		posI++;
	}
	while (posI > posF && cadena[posF] == ' ') {
		posF--;
	}
	return cadena.substr(posI, posF - posI + 1);
}

std::vector<std::string> utils::String::split(std::string cadena, char c) {
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