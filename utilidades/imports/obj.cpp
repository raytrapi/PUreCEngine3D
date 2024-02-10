#include "obj.h"
#include "model.h"
#include "../global/global.h"
#include "../files/filesControl.h"

std::vector<imports::ModelData*> imports::Obj::load(const char* fileName, float directionY) {
	std::vector<imports::ModelData*> objetos;

	if (std::filesystem::exists(std::filesystem::path(fileName))) {
		//Abrimos el fichero
		std::ifstream fichero;
		fichero.open(fileName, std::ios::in);
		std::string linea;

		//Entity* entidadActual = NULL;
		//renderable::Mesh* objeto = NULL;// entidad->addComponent<renderable::Mesh>();
		ModelData* objeto=NULL;
		//objeto->setChange(true);
		std::vector<std::vector<float>> vertices;
		std::vector<float*> normales;
		std::vector<std::vector<float>> uv;
		std::vector<float**>* triangulos;
		std::vector<float**>* normalesTriangulos;
		std::vector<float**>* uvTriangulos;

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
							std::vector<float**>* colorTriangulo = new std::vector<float**>();

							for (int i = 0; i < triangulos->size(); i++) {
								colorTriangulo->push_back(new float*[3]);
								for (int k = 0; k < 3; k++) {
									auto color = new float[4];
									colorTriangulo->operator[](i)[k] = color;
									for (int j = 0; j < 4; j++) {
										color[j] = 1.f;
									}
								}
							}
							//utiles::Log::debug("Cargo  " + std::string(parametros[1]) + " con " + std::to_string(triangulos.size()) + " triangulos");
							objeto->triangles = triangulos;
							objeto->colors = colorTriangulo;
							objeto->normals = normalesTriangulos;
							objeto->uvs = uvTriangulos;
							vertices.clear();
	
							//triangulos.clear();
							//normalesTriangulos.clear();
							//uvTriangulos.clear();
						}

						//objeto = ((renderable::Mesh*)((entidad->getComponents<RenderableComponent, renderable::Mesh>())->operator[](0)->getRenderable()));

						//entidad->setName(parametros[1]);

						/*if (entidadActual != NULL) {
							objeto = entidadActual->getComponent<renderable::Mesh>();
							if (objeto == NULL) {
								objeto = entidadActual->addComponent<renderable::Mesh>();
							}
						} else {*/

						//objeto = new renderable::Mesh();
						//objetos.push_back({ objeto, parametros[1] });

						/* }*/

						//objeto->setChange(true);
						triangulos=new std::vector<float**>;
						normalesTriangulos= new std::vector<float**>;
						uvTriangulos = new std::vector<float**>;
						objeto = new ModelData();
						objeto->setName(parametros[1].c_str());
						objetos.push_back(objeto);
					} else if (parametros[0] == "v") { //Cargamos los vertices
						std::vector<float> v;
						v.push_back(std::stof(parametros[1]));
						v.push_back(directionY * std::stof(parametros[2]));
						v.push_back(std::stof(parametros[3]));
						vertices.push_back(v);
					} else if (parametros[0] == "vn") { //Cargamos las normales
						float* n = new float[3];
						n[0] = -std::stof(parametros[1]);
						n[1] = std::stof(parametros[2])* directionY;
						n[2] = std::stof(parametros[3]);
						normales.push_back(n);
					} else if (parametros[0] == "vt") { //Cargamos las posiciones de las texturas UV
						std::vector<float> u;
						u.push_back(std::stof(parametros[1]));
						u.push_back(std::stof(parametros[2]));
						uv.push_back(u);
					} else if (parametros[0] == "f") { //Cargamos las caras
						int numTriangulos = (parametros.size() - 1);
						numTriangulos -= 2;
						int iT = 0;
						for (int i = 0; i < numTriangulos; i++) {
							/*triangulos->push_back(new float* [3]);
							normalesTriangulos->push_back(new float* [3]);
							uvTriangulos->push_back(new float* [2]);
							float** tri = triangulos->operator[](triangulos->size() - 1);
							float** norm = normalesTriangulos->operator[](normalesTriangulos->size() - 1);
							float** uvs = uvTriangulos->operator[](uvTriangulos->size() - 1);/**/
							float** tri = new float* [3];
							float** norm = new float* [3];
							float** uvs = new float* [3];
							triangulos->push_back(tri);
							normalesTriangulos->push_back(norm);
							uvTriangulos->push_back(uvs);

							std::vector<std::string> trozos[3] = {
								utils::String::split(parametros[iT + 1], '/'),
								utils::String::split(parametros[((iT + 1) % (parametros.size() - 1)) + 1], '/'),
								utils::String::split(parametros[((iT + 2) % (parametros.size() - 1)) + 1], '/')
							};
							for (int j = 0; j <3; j++) {
								/*tri[j][0] = vertices[std::stoi(trozos[j][0]) - 1][0];
								tri[j][1] = vertices[std::stoi(trozos[j][0]) - 1][1];
								tri[j][2] = vertices[std::stoi(trozos[j][0]) - 1][2];/**/
								auto posI = std::stoi(trozos[j][0]) - 1;
								if (posI < vertices.size()) {
									tri[j] = new float[3];
									tri[j][0] = vertices[posI][2];
									tri[j][1] = vertices[posI][1];
									tri[j][2] = vertices[posI][0];
									norm[j] = new float[3];
									int idNormal = std::stoi(trozos[j][2]) - 1;
									norm[j][0] = normales[idNormal][2];
									norm[j][1] = normales[idNormal][1];
									norm[j][2] = normales[idNormal][0];
									uvs[j] = new float[2];
									if (trozos[j][1] != "") {
										int idUV = std::stoi(trozos[j][1]) - 1;
										uvs[j][0] = uv[idUV][0];
										uvs[j][1] = uv[idUV][1];
									} else {
										uvs[j][0] = 0;
										uvs[j][1] = 0;
									}
								} else {
									tri[j] = 0;
									norm[j] = 0;
									uvs[j] = 0;
								}
							}
							iT = (iT == 0) ? 2 : iT + 1;
						}


					}
				}
			}
			if (objeto != NULL) {
				std::vector<float**>* colorTriangulo = new std::vector<float**>();

				for (int i = 0; i < triangulos->size(); i++) {
					colorTriangulo->push_back(new float* [3]);
					for (int k = 0; k < 3; k++) {
						auto color = new float[4];
						colorTriangulo->operator[](i)[k] = color;
						for (int j = 0; j < 4; j++) {
							color[j] = 1.f;
						}
					}
				}
				//utiles::Log::debug("Cargo  " + std::string(parametros[1]) + " con " + std::to_string(triangulos.size()) + " triangulos");
				objeto->triangles = triangulos;
				objeto->colors = colorTriangulo;
				objeto->normals = normalesTriangulos;
				objeto->uvs = uvTriangulos;
	
				//triangulos.clear();
				//normalesTriangulos.clear();
				//uvTriangulos.clear();


			}
			/*if (entidad == NULL) {
				entidad = Entity::create<Entity::TYPE::MESH>();
			}*/
			vertices.clear();
			//objeto = ((renderable::Mesh*)((entidad->getComponents<RenderableComponent, renderable::Mesh>())->operator[](0)->getRenderable()));
			fichero.close();
		} else {
			DBG("No es posible abrir el fichero %", fileName);
		}
		return objetos;

	}








	return objetos;
}

void imports::Obj::createThumbnail(const char* path){
	std::filesystem::path rutaOBJ(path);
	std::filesystem::path ruta ((rutaOBJ.parent_path() / rutaOBJ.stem()).string() + Global::getInstance()->getExt());

	if (std::filesystem::exists(ruta)) {
		//return std::unexpected(Error(-1, "El fichero ya existe"));
		ERR("No se puede crear el Thumbnail");
		return;
	}
	std::ofstream fs(ruta, std::ios::binary);
	unsigned int longitud = strlen(UID_OBJ) + 1;
	fs.write((char*)&longitud, sizeof(unsigned int));
	fs.write(UID_OBJ, longitud);

	unsigned long long uid = FileControl::generateUID<unsigned long long>();

	fs.write((char*)&uid, sizeof(unsigned long long));

	longitud = 0; //Longitud
	auto rutaFicheroOBJ = rutaOBJ.string().substr(Global::getInstance()->getPathRoot().size() + 1);
	longitud = rutaFicheroOBJ.length();
	char* rutaFicheroOBJCorregido= new char[longitud + 1];
	for (int i = 0; i < longitud; i++) {
		rutaFicheroOBJCorregido[i] = rutaFicheroOBJ[i];
	}
	rutaFicheroOBJCorregido[longitud] = '\0';
	longitud++;
	fs.write((char*)&longitud, sizeof(unsigned int));
	fs.write(rutaFicheroOBJCorregido, sizeof(char)*longitud);
	delete[]rutaFicheroOBJCorregido;




	float* imagen = 0;
	
	fs.write((char*)&longitud, sizeof(unsigned int));
	if (longitud > 0) {
		//TODO: Guardar información de la imagen
	}

	fs.close();

}

/*std::vector<ModelData*> renderable::model::Obj::load2(const char* fileName, float directionY) {
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
}/**/

/*std::vector<std::tuple<renderable::Object*, std::string>> renderable::model::Obj::createObjects(const char* fileName, float directionY) {
	std::vector<std::tuple<renderable::Object*, std::string>> objetos;
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

		if (fichero.is_open()) {
			while (std::getline(fichero, linea)) {
				linea = utils::String::trim(linea);
				if (linea[0] != '#' && linea.length() > 0) {
					std::vector<std::string> parametros = utils::String::split(linea);
					if (parametros[0] == "o") {

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
							objeto->setTriangles(&triangulos, colorTriangulo, &normalesTriangulos); //TODO: AÑADIR LAS UV

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

						
						objeto = new renderable::Mesh();
						objetos.push_back({ objeto, parametros[1] });
						

					}
					else if (parametros[0] == "v") { //Cargamos los vertices
						std::vector<float> v;
						v.push_back(std::stof(parametros[1]));
						v.push_back(directionY * std::stof(parametros[2]));
						v.push_back(std::stof(parametros[3]));
						vertices.push_back(v);
					}
					else if (parametros[0] == "vn") { //Cargamos las normales
						float* n = new float[3];
						n[0] = std::stof(parametros[1]);
						n[1] = -std::stof(parametros[2]);
						n[2] = std::stof(parametros[3]);
						normales.push_back(n);
					}
					else if (parametros[0] == "vt") { //Cargamos las posiciones de las texturas UV
						std::vector<float> u;
						u.push_back(std::stof(parametros[1]));
						u.push_back(std::stof(parametros[2]));
						uv.push_back(u);
					}
					else if (parametros[0] == "f") { //Cargamos las caras
						int numTriangulos = (parametros.size() - 1);
						numTriangulos -= 2;
						int iT = 0;
						for (int i = 0; i < numTriangulos; i++) {
							triangulos.push_back(new float* [3]);
							normalesTriangulos.push_back(new float* [3]);
							float** tri = triangulos[triangulos.size() - 1];
							float** norm = normalesTriangulos[normalesTriangulos.size() - 1];

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
			vertices.clear();
			fichero.close();
			return objetos;
		}
		else {
			DBG("Not is possible open file %", fileName);
		}

	}
	return objetos;
}/**/

/*std::vector<ModelData*> renderable::model::Obj::load(const char* fileName, float directionY) {
	std::vector<Entity*> entidades;
	auto objetos = createObjects(fileName, directionY);
	for (auto objeto : objetos) {
		auto entidadActual = Entity::create<Entity::EMPTY>();
		entidades.push_back(entidadActual);
		entidadActual->setName(std::get<1>(objeto));
		RenderableComponent* rend = entidadActual->addComponent<RenderableComponent>();
		
		rend->add<renderable::Mesh>(std::get<0>(objeto));
	}
	return entidades;
}/**/





/*void Entity::loadOBJ(const char* file, float directioY) {
	renderable::model::Model::load(file, directioY);
	actualizarRender=true;
	DBG("He cargado el objeto");
}*/