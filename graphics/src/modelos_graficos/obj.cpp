#include "obj.h"

std::vector<Entity*>* renderable::model::Obj::load(std::string fileName, float directionY) {
	if (std::filesystem::exists(std::filesystem::path(fileName))) {
		//Abrimos el fichero
		std::ifstream fichero;
		fichero.open(fileName, std::ios::in);
		std::string linea;
		 
		renderable::Mesh* objeto=NULL;
		Entity* entidad = NULL;
		std::vector<Entity*>* objetos = NULL;
		std::vector<std::vector<float>> vertices;
		std::vector<float*> normales;
		std::vector<std::vector<float>> uv;
		std::vector<float**> triangulos;
		std::vector<float**> normalesTriangulos;
		utiles::Log::debug("Cargo objeto " + std::string(fileName));
		if (fichero.is_open()) {
			while (std::getline(fichero, linea)) {
				linea = Model::trim(linea);
				if (linea[0] != '#' && linea.length()>0) {
					std::vector<std::string> parametros = Model::split(linea);
					if (parametros[0] == "o") {
						//Tenemos un objeto
						if (objeto != NULL) {
							//Le cargamos los triangulos
							std::vector<float*>* colorTriangulo = new std::vector<float*>();

							for (int i = 0; i < triangulos.size(); i++) {
								colorTriangulo->push_back( new float[3]);
								for (int j = 0; j < 3; j++) {
									colorTriangulo->operator[](i)[j] = 1.f;
								}
							}
							utiles::Log::debug("Cargo  " + std::string(parametros[1]) + " con " + std::to_string(triangulos.size())+" triangulos");
							objeto->setTriangles(&triangulos, colorTriangulo,&normalesTriangulos); //TODO: AÑADIR LAS UV
							for (int i = 0; i < triangulos.size(); i++) {
								delete[]colorTriangulo->operator[](i);
								delete[]triangulos[i][0];
								delete[]triangulos[i][1];
								delete[]triangulos[i][2];
								delete[]triangulos[i];
								delete[]normalesTriangulos[i][0];
								delete[]normalesTriangulos[i][1];
								delete[]normalesTriangulos[i][2];
								delete[]normalesTriangulos[i];
							}
							delete colorTriangulo;
							triangulos.clear();
							normalesTriangulos.clear();
							
							if (objetos == NULL) {
								objetos = new std::vector<Entity*>;
							}
							objetos->push_back(entidad);
						}
						entidad= Entity::create<Entity::TYPE::MESH>();
						objeto = ((renderable::Mesh*)((entidad->getComponents<RenderableComponent, renderable::Mesh>())->operator[](0)->getRenderable()));
						
						entidad->setName(parametros[1]);
						

					} else if (parametros[0] == "v") { //Cargamos los vertices
						std::vector<float> v;
						v.push_back(std::stof(parametros[1]));
						v.push_back(directionY * std::stof(parametros[2]));
						v.push_back(std::stof(parametros[3]));
						vertices.push_back(v);
					}else if (parametros[0] == "vn") { //Cargamos las normales
						float *n=new float[3];
						n[0]=std::stof(parametros[1]);
						n[1]=std::stof(parametros[2]);
						n[2]=std::stof(parametros[3]);
						normales.push_back(n);
					} else if (parametros[0] == "vt") { //Cargamos las posiciones de las texturas UV
						std::vector<float> u;
						u.push_back(std::stof(parametros[1]));
						u.push_back(std::stof(parametros[2]));
						uv.push_back(u);
					} else if (parametros[0] == "f") { //Cargamos las caras
						int numTriangulos = parametros.size() - 3;
						int iT = 0; 
						for (int i = 0; i < numTriangulos; i++) {
							triangulos.push_back(new float* [3]);
							normalesTriangulos.push_back(new float* [3]);
							float** tri = triangulos[triangulos.size() - 1];
							float** norm = normalesTriangulos[normalesTriangulos.size() - 1];

							std::vector<std::string> trozos[3] = { 
								Model::split(parametros[iT+1], '/'),
								Model::split(parametros[((iT+1) % (parametros.size()-1)) + 1], '/'),
								Model::split(parametros[((iT+2) % (parametros.size()-1)) + 1], '/')
							};
							for (int j = 0; j < 3; j++) {
								tri[j] = new float[3];
								tri[j][0] = vertices[std::stoi(trozos[j][0]) - 1][0]; 
								tri[j][1] = vertices[std::stoi(trozos[j][0]) - 1][1];
								tri[j][2] = vertices[std::stoi(trozos[j][0]) - 1][2];

								norm[j] = new float[3];
								norm[j][0] = normales[std::stoi(trozos[j][2]) - 1][0];
								norm[j][1] = normales[std::stoi(trozos[j][2]) - 1][1];
								norm[j][2] = normales[std::stoi(trozos[j][2]) - 1][2];
							}
							iT = (iT == 0) ? 2 : iT + 1;
						}
					}
				}
			}
			if (objeto != NULL) {
				//Le cargamos los triangulos
				std::vector<float*>* colorTriangulo = new std::vector<float*>();
				for (int i = 0; i < triangulos.size(); i++) {
					colorTriangulo->push_back(new float[3]);
					for (int j = 0; j < 3; j++) {
						colorTriangulo->operator[](i)[j] = 1.f;
					}
				}
				objeto->setTriangles(&triangulos, colorTriangulo, &normalesTriangulos);
				for (int i = 0; i < triangulos.size(); i++) {
					delete[]colorTriangulo->operator[](i);
					delete[]triangulos[i][0];
					delete[]triangulos[i][1];
					delete[]triangulos[i][2];
					delete[]triangulos[i];
					delete[]normalesTriangulos[i][0];
					delete[]normalesTriangulos[i][1];
					delete[]normalesTriangulos[i][2];
					delete[]normalesTriangulos[i];
				}
				delete colorTriangulo;
				triangulos.clear();
				normalesTriangulos.clear();

				if (objetos == NULL) {
					objetos = new std::vector<Entity*>;
				}
				objetos->push_back(entidad);
			}
			entidad = Entity::create<Entity::TYPE::MESH>();
			objeto = ((renderable::Mesh*)((entidad->getComponents<RenderableComponent, renderable::Mesh>())->operator[](0)->getRenderable()));
			fichero.close();
			return objetos;
		} else {
			utiles::Log::error("Not is possible open file " + fileName);
		}

	}
	return nullptr;
}

