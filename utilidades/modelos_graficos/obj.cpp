#include "obj.h"

std::vector<renderable::Mesh*>* utiles::model::Obj::load(std::string fileName) {
	if (std::filesystem::exists(std::filesystem::path(fileName))) {
		//Abrimos el fichero
		std::ifstream fichero;
		fichero.open(fileName, std::ios::in);
		std::string linea;
		
		renderable::Mesh* objeto=NULL;
		std::vector<renderable::Mesh*>* objetos = NULL;
		
		if (fichero.is_open()) {
			while (std::getline(fichero, linea)) {
				linea = trim(linea);
				if (linea[0] != '#' && linea.length()>0) {
					std::vector<std::string> parametros = split(linea); 
					if (parametros[0] == "o") {
						//Tenemos un objeto
						if (objeto != NULL) {
							if (objetos == NULL) {
								objetos = new std::vector<renderable::Mesh*>;
							}
							objetos->push_back(objeto);
						}
						objeto = new renderable::Mesh;
						//objeto->setName(parametros[1]);
					}/* else(parametros[0] == "v") {

					}*/
				}
			}

			fichero.close();
			return objetos;
		} else {
			Log::error("Not is possible open file " + fileName);
		}

	}
	return nullptr;
}
