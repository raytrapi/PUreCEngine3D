#include "shaderComponent.h"

#include "../../../modules/graphic/motor.h"
#include "../../src/entity.h"
namespace graphics {
	/*graphics::ShaderComponent::ShaderComponent(Entity* entity, modules::graphics::Graphic* g, Component* p) {
		entidad = entity;
		graphic = g;
		idS = -1;
		tipo = Graphics::Shader::NONE;
		codigo = NULL;
		longitudCodigo = 0;
		setName("Shader");
	}/**/
	ShaderComponent::~ShaderComponent() {
		//DBG("Borro Shader");
		if (codigo != 0) {
			delete[]codigo;
		}
		unsigned int longitud = shadersData.size();
		for (int i = 0; i < longitud; i++) {
			delete shadersData[i];
		}
		shadersPathId.clear();

		if (shaderSombras) {
			delete shaderSombras;
			shaderSombras = 0;
		}
		if (shaderOutline) {
			delete shaderOutline;
			shaderOutline = 0;
		}
		if (shaderClicking) {
			delete shaderClicking;
			shaderClicking = 0;
		}
		if (shaderMaterial) {
			delete shaderMaterial;
			shaderMaterial = 0;
		}
		if (nombreMaterial) {
			delete[] nombreMaterial;
			nombreMaterial = 0;
		}
	}
	int ShaderComponent::getShaderSize() {
		return shadersData.size();
	}

	const ShaderComponent* ShaderComponent::getShader(unsigned int id) {
		return shadersData[id];
	}

	unsigned int ShaderComponent::loadShader(const char* path, Graphics::Shader::TYPE_SHADER type, int pos) {
		//Buscamos el shader
		bool encuentro = false;
		std::string pathS = std::string(path);
		for (auto k_v : shadersPathId) {
			if (k_v.first== pathS) {
				encuentro = true;
				break;
			}
		}
		if (encuentro) {
			int id = shadersPathId[pathS];
				shadersGuardados.push_back({ type, pathS,id });
			return id;
		}else{
			int id = Module::get<modules::graphics::Graphic>()->loadShader(path, type);
			//if (pos > -1) {
			//	id = pos;
			//}
			shadersGuardados.push_back({ type, pathS,id });

			addShader(path, id, type);
			return id;
		}
	}
	void ShaderComponent::reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type, unsigned int idShader, unsigned int idProgram) {
		Module::get<modules::graphics::Graphic>()->reloadShader(path, type, idShader, idProgram);
	}

	unsigned int ShaderComponent::compileShader() {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		unsigned int id = g->compileShader(getShadersId(0), entidad);
		shadersCompiled.push_back(id); //Guardamos el id ¿Es realemente necesario?
		std::get<1>(shadersStack[0]) = id;
		//Le indicamos al componente gráfico que tenemos una nueva compilación de shaders
		//g.getEntity(this)
		compilado = true;
		return id;
	}
	std::vector<unsigned int> ShaderComponent::compileShaders() {
		//std::vector<int> ids;
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		int id = g->compileShader(getShadersId(0), entidad);
		std::get<1>(shadersStack[0]) = id;
		shadersCompiled.push_back(id);
		for (int i = 1; i < shadersStack.size(); i++) {
			id = g->compileShader(getShadersId(i), entidad);
			std::get<1>(shadersStack[i]) = id;
			shadersCompiled.push_back(id);
			
		}

		compilado = true;
		return shadersCompiled;
	}
	unsigned int ShaderComponent::compileShader(unsigned int id) {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		g->compileShader(id, entidad);
		compilado = true;
		return id;
	}

	unsigned int ShaderComponent::addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type) {
		int idS = addShader(id, type);
		if (idS > 0) {
			shadersPathId[std::string(path)] = id;
		}
		return idS;
	}
	unsigned int ShaderComponent::addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte* data, int count) {
		int idS = addShader(id, type,data, count);
		if (idS > 0) {
			shadersPathId[std::string(path)] = id;
		}
		return idS;
	}
	unsigned int ShaderComponent::addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type, const char* data, int count) {
		int idS = addShader(id, type, data, count);
		if (idS > 0) {
			shadersPathId[std::string(path)] = id;
		}
		return idS;
	};

	unsigned int ShaderComponent::addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type) {
		shadersId.push_back(id);
		stackShader(NULL, id, type);
		return shadersId.size();
	}

	unsigned int ShaderComponent::addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte* data, int count) {
		if (type != Graphics::Shader::TYPE_SHADER::COMPILE) {
			ShaderComponent* s = new ShaderComponent(entidad, graphic);
			s->cargar(id, type, data, count);
			shadersData.push_back(s);
			shadersId.push_back(id);

			stackShader(s, id, type);


			return shadersData.size();
		}
		return 0;
	}

	unsigned int ShaderComponent::addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const char* data, int count) {
		return addShader(id, type, (const byte*)data, count);
	}/**/
	void ShaderComponent::stackShader(ShaderComponent* s, unsigned int id, Graphics::Shader::TYPE_SHADER type) {
		//Organizamos los shaders para que se agrupen en vertex, fragment y geometry
			//TODO: Esto puede ser lento, habría que revisarlo en el futuro
		if (shadersStack.size() == 0) {
			shadersStack[idActual] = { {type},0,{(unsigned int)id } };
		} else {
			bool existe=false;
			for (auto shaders : shadersStack) {
				//Ahora comprobamos si ya contiene el shader del tipo indicado
				
				for (auto sType : std::get<0>(shaders.second)) {
					if (sType == type) {
						existe = true;
						break;
					}
				}
				if (!existe) {
					std::get<0>(shadersStack[shaders.first]).push_back(type);
					std::get<2>(shadersStack[shaders.first]).push_back(id);
					existe = true;
					break;
				}
				existe = false;
			}
			if (!existe) {
				idActual++;
				shadersStack[idActual] = { {type},0,{(unsigned int)id } };
				/*idPares++;
				if (idPares > 1) {
					idPares = 0;
					idActual++;
				}/**/
			}
		}
	}
	std::vector<ShaderComponent*>* ShaderComponent::getShaders() {
		return &shadersData;
	}
	std::vector<unsigned int>* ShaderComponent::getShadersId(int idStack) {
		//return &shadersId;
		//TODO: Lo idel sería que el sistema compruebe que no estemos accediendo fuera de los elementos del array. Por eficiencia lo dejamos en manos del desarrollador.
		return &(std::get<2>(shadersStack[idStack]));
	}
	std::vector<unsigned int>* ShaderComponent::getShadersCompiled() {
		return &shadersCompiled;
	}
	
	void ShaderComponent::cargar(unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte*& data, int count) {
		idS = id;
		tipo = type;
		codigo = new byte[count];
		for (int i = 0; i < count; i++) {
			codigo[i] = data[i];
		}
		longitudCodigo = count;
	}/**/


	Graphics::Shader::TYPE_SHADER ShaderComponent::getTypeShader() {
		return tipo;
	}/**/

	unsigned int ShaderComponent::getId() {
		return idS;
	}

	bool ShaderComponent::interfazImGUI_C(ImGuiContext* imgui) {
		auto numShaders = shadersGuardados.size();
		auto numShaders_ =(int)ceil(numShaders / 2);
		ImGui::SetCurrentContext(imgui);
		ImGui::TableNextColumn();
		ImGui::Text((const char*)u8"Material");
		ImGui::TableNextColumn();
		char* shaderEditable = new char[200];
		if (nombreMaterial == 0) {
			shaderEditable[0] = '\0';
		} else {
			strcpy(shaderEditable, nombreMaterial);
		}
		
		if (ImGui::InputTextWithHint("##Shader", "Color", shaderEditable, 200)) {
			setMaterial(shaderEditable);
			if (shaderMaterial && shaderMaterial->isCorrect() && entidad) {
				entidad->setUpdatingRender(true);
			}
		};
		delete[]shaderEditable;
		/*int iActual = 0;
		//char** shadersEditables = new char* [numShaders_*2];
		for (int i = 0; i < numShaders_; i++) {
			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text((const char*)u8"Vertex");
			ImGui::TableNextColumn();
			if (!(numShaders > iActual && std::get<0>(shadersGuardados[iActual]) == Graphics::Shader::VERTEX)) {
				shadersGuardados.insert(shadersGuardados.begin() + iActual + 1, { Graphics::Shader::VERTEX, std::string(""),0 });
				//iActual--;
			}
			if (std::get<1>(shadersGuardados[iActual]).length() < 200) {
				char* shaderEditable = new char[200];
				strcpy(shaderEditable, std::get<1>(shadersGuardados[iActual]).c_str());
				std::string nombre = "##shader_" + std::to_string(iActual);
				if (ImGui::InputTextWithHint(nombre.c_str(), "src/xxx.glsl", shaderEditable, 200)) {
					std::get<1>(shadersGuardados[iActual]) = std::string(shaderEditable);
				};
				delete[]shaderEditable;
				
			} else {
				ImGui::Text(std::get<1>(shadersGuardados[iActual]).c_str());
			}
			
			iActual++;

			ImGui::TableNextRow();
			ImGui::TableNextColumn();
			ImGui::Text((const char*)u8"Fragment");
			ImGui::TableNextColumn();
			if (!(numShaders > iActual && std::get<0>(shadersGuardados[iActual]) == Graphics::Shader::FRAGMENT)) {
				shadersGuardados.insert(shadersGuardados.begin() + iActual + 1, { Graphics::Shader::FRAGMENT, std::string(""),0 });
			}
			if (std::get<1>(shadersGuardados[iActual]).length() < 200) {
				char* shaderEditable = new char[200];
				strcpy(shaderEditable, std::get<1>(shadersGuardados[iActual]).c_str());
				std::string nombre = "##shader_" + std::to_string(iActual);
				if (ImGui::InputTextWithHint(nombre.c_str(), "src/xxx.glsl", shaderEditable, 200)) {
					std::get<1>(shadersGuardados[iActual]) = std::string(shaderEditable);
				};
				delete[]shaderEditable;
			} else {
				ImGui::Text(std::get<1>(shadersGuardados[iActual]).c_str());
			}
			
			iActual++;
		}/**/
		ImGui::EndTable();
		if (ImGui::Button("Nuevo Shader")) {

			/*if ((numShaders_ & 1) == 1) {
				//Tenemos un elemento desparejado, lo arreglamos
				int tipo =0;
				Graphics::Shader::TYPE_SHADER tipoACrear;
				for (int i = 0; i < shadersGuardados.size(); i++) {
					bool crear = false;
					switch (tipo){
						case 0: //Vertex
							if (std::get<0>(shadersGuardados[i]) != Graphics::Shader::VERTEX) {
								//Creamos un vertex
								crear = true;
								tipoACrear = Graphics::Shader::VERTEX;
							}
						case 1: //Fragment
							if (std::get<0>(shadersGuardados[i]) != Graphics::Shader::FRAGMENT) {
								//Creamos un vertex
								crear = true;
								tipoACrear = Graphics::Shader::FRAGMENT;
							}
						default:
							break;
					}
					if (crear) {
						shadersGuardados.insert(shadersGuardados.begin() + i + 1, {tipoACrear,"",0});
						i++;
					}
					tipo = (tipo + 1) % 2;
				}

				//shadersGuardados.push_back({()})
			}/**/
			shadersGuardados.push_back({ Graphics::Shader::VERTEX,"",0 });
			shadersGuardados.push_back({ Graphics::Shader::FRAGMENT,"",0 });
		};
		return false;
	}
//std::map<const char*, short int> Shader::shadersPathId;
	int ShaderComponent::saveState_interno(std::vector<unsigned char>* data, bool withID) {
		int longitud = Serializer::serialize(data, (int)TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_SHADER);
		//Guardamos el nombre del material
		Serializer::serialize(data, nombreMaterial);
		//Guardamos el número de shaders
		/*int numShaders = 0;
		for (auto s : shadersGuardados) {
			if (std::get<1>(s).size() > 0) {
				numShaders++;
			}
		}
		longitud += Serializer::serialize(data, (int)numShaders);
		for (auto s : shadersGuardados) {
			if (std::get<1>(s).size() > 0) {
				longitud += Serializer::serialize(data, (int)std::get<0>(s), std::get<1>(s).c_str());
			}
		}/**/
		return longitud;
	};
	void ShaderComponent::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
		if (data != 0) {
			Deserializer::setBytes(data);
		}

		//Nombre 
		int longitudCadena = Deserializer::getLengthString();

		if (longitudCadena > 0) {
			char * nombreMaterial= new char[longitudCadena];
			Deserializer::deserialize(&nombreMaterial);
			setMaterial(nombreMaterial);
			delete [] nombreMaterial;
		}
		setShadow();
		setOutline();
		setClicking();
		/*int numShaders = 0;
		Deserializer::deserialize(&numShaders);
		if (numShaders > 64) {
			DBG("error al copiar Shaders...");
			return;
		}
		int idShaderActual = 0;
		for (int i = 0; i < numShaders; i++) {
			int tipoS = -1;
			int lengthNombre = 0;
			char* nombreS;
			//int posS = 0;
			Deserializer::deserialize(&tipoS);
			lengthNombre=Deserializer::getLengthString();
			nombreS = new char[lengthNombre];
			Deserializer::deserialize(&nombreS);
			//Deserializer::deserialize(&posS);

			//Aquí tenemos la información del shader
			//if(idShaderActual<)
			auto id=loadShader(nombreS, (Graphics::Shader::TYPE_SHADER)tipoS);
			//if (id != posS) {
			//	DBG("ERROR...");
			//}
			delete[] nombreS;
		}/**/
	};

	void ShaderComponent::setMaterial(const char* name) {
		if (shaderMaterial) {
			delete shaderMaterial;
		}
		if (nombreMaterial) {
			delete[] nombreMaterial;
		}
		nombreMaterial = new char[strlen(name) + 1];
		strcpy(nombreMaterial, name);
		//TODO Corregir el tema de las cadenas de texto
		shaderMaterial=new Shader(name, (std::string("shaders/")+std::string(name) + "/vertex.glsl").c_str(), (std::string("shaders/") + std::string(name) + "/fragment.glsl").c_str(), 0);
	};
	void ShaderComponent::setShadow(const char* nombre) {
		if (shaderSombras) {
			delete shaderSombras;
		}
		shaderSombras=new Shader(nombre, "shaders/shadow_map_vertex.glsl", "shaders/shadow_map_fragment.glsl",0);
	};
	void ShaderComponent::setOutline(const char* nombre) {
		if (shaderOutline) {
			delete shaderOutline;
		}
		shaderOutline=new Shader(nombre, "shaders/editor/outline_vertex.glsl", "shaders/editor/outline_fragment.glsl",0);
	};
	void ShaderComponent::setClicking(const char* nombre) {
		if (shaderClicking) {
			delete shaderClicking;
		}
		shaderClicking=new Shader(nombre, "shaders/editor/entidadID_vertex.glsl", "shaders/editor/entidadID_fragment.glsl", 0);
	};
	unsigned int ShaderComponent::getMaterial() {
		if(shaderMaterial){
			return shaderMaterial->idProgram;
		}
		return 0;
	};
	unsigned int ShaderComponent::getShadow() {
		if (shaderSombras){
			return shaderSombras->idProgram;
		}
		return 0;
	};
	unsigned int ShaderComponent::getOutline() {
		if (shaderOutline) {
			return shaderOutline->idProgram;
		}
		return 0;
	};
	unsigned int ShaderComponent::getClicking() {
		if (shaderClicking) {
			return shaderClicking->idProgram;
		}
		return 0;
	};
}//namespace

/*** MATERIAL ***/
Shader::Shader(const char* name, const char* vertex, const char* fragment, const char* geometry) {
	auto g = Module::get<modules::graphics::Graphic>();
	nombre = std::string(name);
	this->vertex = std::string(vertex);
	this->fragment = std::string(fragment);
	correcto = true;
	idVertex = g->loadShader(vertex, Graphics::Shader::VERTEX);
	if (idVertex == 0) {
		correcto = false;
		return;
	}
	idFragment = g->loadShader(fragment, Graphics::Shader::FRAGMENT);
	if (idFragment == 0) {
		correcto = false;
		return;
	}
	//
	if (geometry != 0) {
		this->geometry = std::string(geometry);
		idGeometry = g->loadShader(geometry, Graphics::Shader::GEOMETRY);
		if (idGeometry == 0) {
			correcto = false;
			return;
		}
	}
	//Compilar el programa
	std::vector<unsigned int> ids;
	ids.push_back(idVertex);
	ids.push_back(idFragment);
	idProgram = g->compileShader(&ids);
	if (idProgram == 0) {
		correcto = false;
		return;
	}
}
Shader::~Shader() {
	auto g = Module::get<modules::graphics::Graphic>();
	std::vector<unsigned int> ids;
	//TODO: Cuando alguno de los id se comparta, por ejemplo el fragment tendremos que tenerlo en cuenta
	ids.push_back(idVertex);
	ids.push_back(idFragment);
	g->removeShader(idProgram, &ids);
}
/*** MATERIAL ***/