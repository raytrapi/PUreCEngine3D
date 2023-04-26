#include "obj.h"
#include "model.h"



std::vector<Entity*> renderable::model::Obj::load2(const char* fileName, float directionY) {
	std::vector<Entity*> entidades;
	if (std::filesystem::exists(std::filesystem::path(fileName))) {
		std::ifstream file(fileName);
		
		std::vector<std::tuple<std::tuple<float, float, float>, std::tuple<float, float, float>>> vertices;
		std::vector<std::tuple<float,float,float>> positions;
		std::vector< std::tuple<float, float, float>> normals;
		std::string line;
		while (std::getline(file, line)) {
			std::stringstream ss(line);
			std::string command;
			ss >> command;
			if (command == "v") {
				float x, y, z;
				ss >> x >> y >> z;
				positions.push_back({ x, y, z });
			} else if (command == "vn") {
				float x, y, z;
				ss >> x >> y >> z;
				normals.push_back({ x, -y, z });
			} else if (command == "f") {
				std::string vertexString;
				while (ss >> vertexString) {
					std::stringstream vertexSS(vertexString);
					std::string indexString;
					std::getline(vertexSS, indexString, '/');
					int positionIndex = std::stoi(indexString) - 1;
					std::getline(vertexSS, indexString, '/');
					int normalIndex = std::stoi(indexString) - 1;
					vertices.push_back({ positions[positionIndex], normals[normalIndex] });
				}
			}
		}

		//return true;
	}
	return entidades;
}

std::vector<Entity*> renderable::model::Obj::load(const char* fileName, float directionY) {
	std::vector<Entity*> entidades;
	if (std::filesystem::exists(std::filesystem::path(fileName))) {
		//Abrimos el fichero
		std::ifstream fichero;
		fichero.open(fileName, std::ios::in);
		std::string linea;

		Entity* entidadActual = NULL;
		renderable::Mesh* objeto = NULL;// entidad->addComponent<renderable::Mesh>();
		//objeto->setChange(true);
		std::vector<std::vector<float>> vertices;
		std::vector<float*> normales;
		std::vector<std::vector<float>> uv;
		std::vector<float**> triangulos;
		std::vector<float**> normalesTriangulos;

		//utiles::Log::debug("Cargo objeto " + std::string(fileName));
		if (fichero.is_open()) {
			while (std::getline(fichero, linea)) { 
				linea = utils::String::trim(linea);
				if (linea[0] != '#' && linea.length() > 0) {
					std::vector<std::string> parametros = utils::String::split(linea);
					if (parametros[0] == "o") {

						//entidadActual = Entity::create<Entity::TYPE::MESH>();
						//entidadActual->setParent(entidad);
						//Tenemos un objeto
						if (objeto != NULL) {
							//Le cargamos los triangulos
							std::vector<float*>* colorTriangulo = new std::vector<float*>();

							for (int i = 0; i < triangulos.size(); i++) {
								colorTriangulo->push_back(new float[4]);
								for (int j = 0; j < 4; j++) {
									colorTriangulo->operator[](i)[j] = 1.f;
								}
							}
							//utiles::Log::debug("Cargo  " + std::string(parametros[1]) + " con " + std::to_string(triangulos.size()) + " triangulos");
							objeto->setTriangles(&triangulos, colorTriangulo, &normalesTriangulos); //TODO: AÑADIR LAS UV
							//objeto->setTriangles(&triangulos, colorTriangulo, NULL); //TODO: AÑADIR LAS UV
							
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

						}

						//objeto = ((renderable::Mesh*)((entidad->getComponents<RenderableComponent, renderable::Mesh>())->operator[](0)->getRenderable()));

						//entidad->setName(parametros[1]);

						/*if (entidadActual != NULL) {
							objeto = entidadActual->getComponent<renderable::Mesh>();
							if (objeto == NULL) {
								objeto = entidadActual->addComponent<renderable::Mesh>();
							}
						} else {*/
							entidadActual = Entity::create<Entity::EMPTY>();
							entidades.push_back(entidadActual);
							entidadActual->setName(parametros[1]);
							RenderableComponent* rend = entidadActual->addComponent<RenderableComponent>();
							objeto = rend->add<renderable::Mesh>();
						/* }*/
						
						//objeto->setChange(true);

					} else if (parametros[0] == "v") { //Cargamos los vertices
						std::vector<float> v;
						v.push_back(std::stof(parametros[1]));
						v.push_back(directionY * std::stof(parametros[2]));
						v.push_back(std::stof(parametros[3]));
						vertices.push_back(v);
					} else if (parametros[0] == "vn") { //Cargamos las normales
						float* n = new float[3];
						n[0] = std::stof(parametros[1]);
						n[1] = -std::stof(parametros[2]);
						n[2] = std::stof(parametros[3]);
						normales.push_back(n);
					} else if (parametros[0] == "vt") { //Cargamos las posiciones de las texturas UV
						std::vector<float> u;
						u.push_back(std::stof(parametros[1]));
						u.push_back(std::stof(parametros[2]));
						uv.push_back(u);
					} else if (parametros[0] == "f") { //Cargamos las caras
						int numTriangulos = (parametros.size()-1);
						numTriangulos-=2;
						int iT = 0;
						for (int i = 0; i < numTriangulos; i++) {
							triangulos.push_back(new float* [3]);
							normalesTriangulos.push_back(new float* [3]);
							float** tri = triangulos[triangulos.size() - 1];
							float** norm = normalesTriangulos[normalesTriangulos.size()-1];

							std::vector<std::string> trozos[3] = {
								utils::String::split(parametros[iT + 1], '/'),
								utils::String::split(parametros[((iT + 1) % (parametros.size() - 1)) + 1], '/'),
								utils::String::split(parametros[((iT + 2) % (parametros.size() - 1)) + 1], '/')
							};
							for (int j = 0; j < 3; j++) {
								tri[j] = new float[3];
								tri[j][0] = vertices[std::stoi(trozos[j][0]) - 1][0];
								tri[j][1] = vertices[std::stoi(trozos[j][0]) - 1][1];
								tri[j][2] = vertices[std::stoi(trozos[j][0]) - 1][2];

								norm[j] = new float[3];
								int idNormal = std::stoi(trozos[j][2]) - 1;
								norm[j][0] = normales[idNormal][0];
								norm[j][1] = normales[idNormal][1];
								norm[j][2] = normales[idNormal][2];
							}
							iT = (iT == 0) ? 2 : iT + 1;
						}

						
					}
				}
			}
			if (objeto != NULL) {
				//Le cargamos los triangulos
				//utiles::Log::debug("Cargo con " + std::to_string(triangulos.size()) + " triangulos");
				std::vector<float*>* colorTriangulo = new std::vector<float*>();
				for (int i = 0; i < triangulos.size(); i++) {
					colorTriangulo->push_back(new float[4]);
					for (int j = 0; j < 4; j++) {
						colorTriangulo->operator[](i)[j] = 1.f;
					}
				}
				objeto->setTriangles(&triangulos, colorTriangulo, &normalesTriangulos);
				//objeto->setTriangles(&triangulos, colorTriangulo, NULL);
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


			}
			/*if (entidad == NULL) {
				entidad = Entity::create<Entity::TYPE::MESH>();
			}*/
			vertices.clear();
			//objeto = ((renderable::Mesh*)((entidad->getComponents<RenderableComponent, renderable::Mesh>())->operator[](0)->getRenderable()));
			fichero.close();
			return entidades;
		} else {
			DBG("Not is possible open file %", fileName);
		}

	}
	return entidades;
}





/*void Entity::loadOBJ(const char* file, float directioY) {
	renderable::model::Model::load(file, directioY);
	actualizarRender=true;
	DBG("He cargado el objeto");
}*/