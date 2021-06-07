#include "modelo.h"

std::string renderable::model::Model::trim(std::string cadena) {
	int posI = 0;
	int posF = cadena.length()-1;

	while (posI < posF && cadena[posI] == ' ') {  
		posI++;
	} 
	while (posI > posF && cadena[posF] == ' ') {
		posF--;
	}
	return cadena.substr(posI,posF-posI+1);
}

std::vector<std::string> renderable::model::Model::split(std::string cadena, char c) {
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

std::vector<Entity*>* renderable::model::Model::load(std::string fileName) {
	int posicionPunto=fileName.rfind('.');
	if (posicionPunto > 0) {
		std::string extension = fileName.substr(posicionPunto + 1); //TODO: Convertir a minusculas para asegurarnos de que la extensión exista
		if (extension == "obj") {
			return Obj::load(fileName);
		}
	}
	return nullptr;
}
