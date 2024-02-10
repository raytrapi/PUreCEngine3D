#include "model.h"



std::vector<imports::ModelData *> imports::Model::load(const char* fileName) {
	return load(fileName,1.0f);
}

std::vector<imports::ModelData*> imports::Model::load(const char* file, float directionY) {
	//TODO: Hacer que esto funcione solo con char *

	std::string fileName(file);
	int posicionPunto = fileName.rfind('.');
	if (posicionPunto > 0) {
		std::string extension = fileName.substr(posicionPunto + 1); //TODO: Convertir a minusculas para asegurarnos de que la extensión exista
		if (extension == "obj") {
			return ::imports::Obj::load(file, directionY);
		} else if (extension == "fbx") {
			return ::imports::Fbx::load(file, directionY);
		}
	}/**/
	return {};// std::vector<Entity*>();
}
