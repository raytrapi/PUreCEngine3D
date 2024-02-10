#include "objects/object.h"
#include "../../../utilidades/project/genericFile.h"
#include "renderableComponent.h"
#include "entity.h"
//TODO: Esto cambiará en el futuro para que sea genérico
#include "../../../graphics/terceros/opengl4/src/imgui/controles/imgui_objetos.h"
void renderable::Object::setRenderable(RenderableComponent* render) {
	renderizador = render;
}
RenderableComponent::RenderableComponent(Entity* entity, modules::graphics::Graphic* g, Component* p) {
	this->entidad = entity;
	this->graphic = g;
	setName("RenderableComponent");
	//nombre = (char*)"RenderableComponent";
	
};
	
RenderableComponent::~RenderableComponent() {
	if (objeto) {
		delete objeto;
		objeto = NULL; 
	}
	//DBG("Borro Render");
	
}
 
void RenderableComponent::rotateX(float radian) {

	setRotation(radian, rY, rZ);
}
void RenderableComponent::rotateY(float radian) {
	setRotation(rX, radian, rZ);
}
void RenderableComponent::rotateZ(float radian) {
	setRotation(rX, rY, radian);
}
void RenderableComponent::setPosition(float x, float y, float z) {
	Transform* global = entidad->transform();
	/*actualizar = true;
	pX = x;
	pY = y;
	pZ = z;
	transformacion[3] = pX + global->position()->x;
	transformacion[7] = pY + global->position()->y;
	transformacion[11] =  pZ + global->position()->z;/**/
}

void RenderableComponent::moveX(float x) {
	pX += x;
	//transformacion[3] = pX;
}

void RenderableComponent::setRotation(float x, float y, float z) {
	entidad->setRenderUpdatable();
	/*rX = x;
	if (rX > M_2PI) {
		rX = rX-M_2PI ;
	} else if (rX < 0) {
		rX = M_2PI + rX;
	}
	rY = y;
	
	rZ = z;
	if (rZ > M_2PI) {
		rZ = rZ - M_2PI;
	} else if (rZ < 0) {
		rZ = M_2PI + rZ;
	}
	double cX = cos(rX);
	double sX = sin(rX);
	double cY = cos(rY);
	double sY = sin(rY);
	double cZ = cos(rZ);
	double sZ = sin(rZ);
	
	transformacion[0] = cZ*cY;
	transformacion[1] = -cX*sZ+sY*cZ*sX;
	transformacion[2] = sX* sZ + sY * cX * cZ;

	transformacion[4] = cY * sZ;
	transformacion[5] = cX*cZ + sY*sZ*sX;
	transformacion[6] = -sX * cZ + sY * cX * sZ;

	transformacion[8] = sX;
	transformacion[9] = cY*sX;
	transformacion[10] = cX*cY;/**/
	//transformacion[3] = 0.25f;
	//this->entidad->
	//updateEntityCUBE
	
}

void RenderableComponent::setRotationGimbal(float uX, float uY, float uZ, float angle) {
	float cA = cosf(angle);
	float cA_1 = 1 - cA;
	float sA = sinf(angle);
	//float SA_1 = 1 - sA;
	

	/*transformacion[0] = cA + (uX * uX) * cA_1;
	transformacion[1] = uX*uY*cA_1-uZ*sA;
	transformacion[2] = uX*uZ*cA_1+uY*sA;
	transformacion[3] = 0;
	transformacion[4] = uY*uX*cA_1+uZ*sA;
	transformacion[5] = cA+ (uY*uY)*cA_1;
	transformacion[6] = uY*uZ*cA_1-uX*sA;
	transformacion[7] = 0;
	transformacion[8] = uZ*uX*cA_1-uY*sA;
	transformacion[9] = uZ*uY*cA_1+uX*sA;
	transformacion[10] = cA+(uZ*uZ)*cA_1;
	transformacion[11] = 0;
	transformacion[12] = 0;
	transformacion[13] = 0;
	transformacion[14] = 0;
	transformacion[15] = 1;/**/
}

float RenderableComponent::getX() {
	actualizar = true;
	return pX;
}

float RenderableComponent::getY() {
	actualizar = true;
	return pY;
}

float RenderableComponent::getZ() {
	actualizar = true;
	return pZ;
}

float RenderableComponent::getRX() {
	return rX;
}
float RenderableComponent::getRY() {
	return rY;
}
float RenderableComponent::getRZ() {
	return rZ;
}

float* RenderableComponent::matrixTrans() {
	return entidad->transform()->matrix();
}

bool RenderableComponent::isUpdatable() {
	if (actualizar) {
		actualizar = false;
		return true;
	}
	return false;
}
/**
* Este método forzará la actualización del objeto 
*/
void RenderableComponent::update() {
	actualizar = true;
	if (entidad) {
		entidad->transform()->update();
		entidad->setRenderUpdatable();
	}
	/*Transform* transform = entidad->transform();
	auto [posX, posY, posZ] = transform->getPosition();
	auto [escX, escY, escZ] = transform->getScale();
	auto [rotX, rotY, rotZ] = transform->getRotator();
	rotX *= GRAD_RAD;
	rotY *= GRAD_RAD;
	rotZ *= GRAD_RAD;
	double cX = cos(rotX);
	double sX = sin(rotX);
	double cY = cos(rotY);
	double sY = sin(rotY);
	double cZ = cos(rotZ);
	double sZ = sin(rotZ);

	transformacion[0] = cZ * cY * escX;
	transformacion[1] = -cX * sZ + sY * cZ * sX;
	transformacion[2] = sX * sZ + sY * cX * cZ;
	transformacion[3] = posX;

	transformacion[4] = cY * sZ;
	transformacion[5] = cX * cZ + sY * sZ * sX * escY;
	transformacion[6] = -sX * cZ + sY * cX * sZ;
	transformacion[7] = posY;

	transformacion[8] = -sY;
	transformacion[9] = cY * sX;
	transformacion[10] = cX * cY * escZ;
	transformacion[11] = posZ;
	/**/


}

void RenderableComponent::setUpdated(bool update) {
	actualizar = update;
	if (actualizar) {
		entidad->setRenderUpdatable();
	}
}

std::vector<std::vector<const float*>>* RenderableComponent::getFaces() {
	return objeto->getFaces();
}


std::vector<std::vector<const float*>>* renderable::Object::getFaces() {
	return caras;
}


std::string RenderableComponent::serializar() {
	std::string objetoSerializado = "";
	if (objeto) {
		objetoSerializado = GenericFile::serializate("objeto", objeto->serializar(),false,false);
	}
	std::string resultado = GenericFile::serializate("componente", "{\r\n"+ GenericFile::serializate("tipo",TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RENDERABLE)+objetoSerializado+"}\r\n", false,false);
	return resultado;
	
};
int RenderableComponent::desserializar(std::string s, int pos) {
	return 0;
}
bool RenderableComponent::interfazImGUI_C(ImGuiContext* imgui) {
	//ImGui::SetCurrentContext(imgui);
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
		
		ImGui::Text("Objeto");
		ImGui::TableNextColumn();
		ImGui::Image(0, ImVec2(50, 50));
		/*auto m = ImGui::selectionObject("DRAG_OBJ", 0, ImVec2(50, 50));
		if (m) {
			auto datos = *m;
			if (objeto) {
				delete objeto;
				objeto = NULL;
			}
			objeto = new renderable::Mesh();
			objeto->setRenderable(this);
			((renderable::Mesh*)objeto)->loadOBJ((Global::getPathRoot() + "/" + datos.path + "/" + datos.name + ".obj").c_str());
			((renderable::Mesh*)objeto)->setUID(datos.UID);
		}
		ImGui::Text("Cubo");/**/
	if (objeto) {
		ImGui::SameLine();
		if (ImGui::Button("Borrar")) {
			delete objeto;
			objeto = NULL;
		}else{
			objeto->interfazImGUI(imgui);
		}
	} 
	if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::BeginDragDropTarget()) {
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_OBJ")) {
			if (payload->DataSize == sizeof(DragFile)) {
				auto datos = *(DragFile*)payload->Data;
				if (objeto) {
					delete objeto;
					objeto = NULL;
				}
				objeto = new renderable::Mesh();
				objeto->setRenderable(this);
				((renderable::Mesh*)objeto)->loadOBJ((Global::getPathRoot() + "/" + datos.path + "/" + datos.name + ".obj").c_str());
				((renderable::Mesh*)objeto)->setUID(datos.UID);

			}
		}

		ImGui::EndDragDropTarget();
	}/**/
	return true;
}

Material* RenderableComponent::setMaterial(UID uid, unsigned int pos) {
	if (objeto) {
		auto m = new Material(uid);
		if (m) {
			auto id = objeto->setMaterial(m, pos);
			return objeto->getMaterial(pos);
		}else {
			return NULL;
		}
	}
	return NULL;
}
std::vector<Material*> RenderableComponent::getMaterials() {
	if (objeto) {
		
		return objeto->getMaterials();
		
	}
	std::vector<Material*> ms;
	return ms;
};
int RenderableComponent::saveState_interno(std::vector<unsigned char>* data, bool withID) {
	int longitud = Serializer::serialize(data, (int)TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RENDERABLE);
	if (objeto) {
		longitud += objeto->saveState(data, withID);
	}
	return longitud;
};
void RenderableComponent::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
	void* objetoTemp = objeto;
	if (withID) {
		Deserializer::deserialize(&objetoTemp);
		if (objeto != objetoTemp && objeto) {
			delete objeto;
			objeto = NULL;
		}
	}
	int tipo = -1;
	Deserializer::deserialize(&tipo);
	if (objeto==NULL) {
		//Creamos el objeto
		switch ((renderable::Object::TYPE)tipo){
			case renderable::Object::TYPE::CUBE:
				objeto = new renderable::Cube(this);
				objetoPropio = true;
				break;
			case renderable::Object::TYPE::MESH:
				objeto = new renderable::Mesh();
				objetoPropio = true;
				break;
			default:
				break;
		}
	}
	if (objeto) {
		objeto->setRenderable(this);
		objeto->restoreState(0, withID);
	}/**/
	setUpdated(true);
};

void RenderableComponent::setUV(int pos, float u, float v) {
	if (objeto) {
		objeto->setUV(pos, u, v);
	}
}

/*//TODO: ESTO ESTA MUYYYYY MAL

std::vector<std::tuple<renderable::Object*, std::string>> RenderableComponent::createObjects(const char* fileName, float directionY) {
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
		std::vector<float**> uvTriangulos;

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

							for (int i = 0; i < triangulos.size(); i++) {
								colorTriangulo->push_back(new float*[3]);
								for (int k = 0; k < 3; k++) {
									colorTriangulo->operator[](i)[k] = new float[4];
									for (int j = 0; j < 4; j++) {

										colorTriangulo->operator[](i)[k][j] = 1.f;
									}
								}
							}
							//utiles::Log::debug("Cargo  " + std::string(parametros[1]) + " con " + std::to_string(triangulos.size()) + " triangulos");
							objeto->setTriangles(&triangulos, colorTriangulo, &normalesTriangulos); //TODO: AÑADIR LAS UV
							//objeto->setTriangles(&triangulos, colorTriangulo, NULL); //TODO: AÑADIR LAS UV

							for (int i = 0; i < triangulos.size(); i++) {
								delete[]colorTriangulo->operator[](i)[0];
								delete[]colorTriangulo->operator[](i)[1];
								delete[]colorTriangulo->operator[](i)[2];
								delete[]colorTriangulo->operator[](i);
								delete[]triangulos[i][0];
								delete[]triangulos[i][1];
								delete[]triangulos[i][2];
								delete[]triangulos[i];
								delete[]normalesTriangulos[i][0];
								delete[]normalesTriangulos[i][1];
								delete[]normalesTriangulos[i][2];
								delete[]normalesTriangulos[i];
								//delete[]uvTriangulos[i][0];
								//delete[]uvTriangulos[i][1];
								//delete[]uvTriangulos[i];
							}
							delete colorTriangulo;
							triangulos.clear();
							normalesTriangulos.clear();

						}

						//objeto = ((renderable::Mesh*)((entidad->getComponents<RenderableComponent, renderable::Mesh>())->operator[](0)->getRenderable()));

						//entidad->setName(parametros[1]);

						objeto = new renderable::Mesh();
						objetos.push_back({ objeto, parametros[1] });


						//objeto->setChange(true);

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
						n[0] = -std::stof(parametros[1]);
						n[1] = std::stof(parametros[2]);
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
								tri[j][2] = vertices[std::stoi(trozos[j][0]) - 1][0];
								tri[j][1] = vertices[std::stoi(trozos[j][0]) - 1][1];
								tri[j][0] = vertices[std::stoi(trozos[j][0]) - 1][2];
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
				std::vector<float**>* colorTriangulo = new std::vector<float**>();
				for (int i = 0; i < triangulos.size(); i++) {
					colorTriangulo->push_back(new float*[3]);
					for (int k = 0; k < 3; k++) {
						colorTriangulo->operator[](i)[k] = new float[4];
						for (int j = 0; j < 4; j++) {
							colorTriangulo->operator[](i)[k][j] = 1.f;
						}
					}
				}
				objeto->setTriangles(&triangulos, colorTriangulo, &normalesTriangulos);
				//objeto->setTriangles(&triangulos, colorTriangulo, NULL);
				for (int i = 0; i < triangulos.size(); i++) {

					delete[]colorTriangulo->operator[](i)[0];
					delete[]colorTriangulo->operator[](i)[1];
					delete[]colorTriangulo->operator[](i)[2];
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
			//objeto = ((renderable::Mesh*)((entidad->getComponents<RenderableComponent, renderable::Mesh>())->operator[](0)->getRenderable()));
			fichero.close();
			return objetos;
		}
		else {
			DBG("Not is possible open file %", fileName);
		}

	}
	return objetos;
}/**/