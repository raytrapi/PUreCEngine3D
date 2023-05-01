#include "shader.h"

#include "../../../modules/graphic/motor.h"
namespace graphics {
	Shader::~Shader() {
		//DBG("Borro Shader");
		if (codigo != 0) {
			delete[]codigo;
		}
		unsigned int longitud = shadersData.size();
		for (int i = 0; i < longitud; i++) {
			delete shadersData[i];
		}
		shadersPathId.clear();
	}
	int Shader::getShaderSize() {
		return shadersData.size();
	}

	const Shader* Shader::getShader(unsigned int id) {
		return shadersData[id];
	}

	unsigned int Shader::loadShader(const char* path, Graphics::Shader::TYPE_SHADER type) {
		if (shadersPathId.find(path) == shadersPathId.end()) {
			int id = Module::get<modules::graphics::Graphic>()->loadShader(path, type);
			addShader(path, id, type);
			return id;
		}else{
			return shadersPathId[path];
		}
	}
	void Shader::reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type, unsigned int idShader, unsigned int idProgram) {
		Module::get<modules::graphics::Graphic>()->reloadShader(path, type, idShader, idProgram);
	}

	unsigned int Shader::compileShader() {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		unsigned int id = g->compileShader(getShadersId(0), entidad);
		shadersCompiled.push_back(id); //Guardamos el id ¿Es realemente necesario?
		std::get<1>(shadersStack[0]) = id;
		//Le indicamos al componente gráfico que tenemos una nueva compilación de shaders
		//g.getEntity(this)
		compilado = true;
		return id;
	}
	std::vector<unsigned int> Shader::compileShaders() {
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
	unsigned int Shader::compileShader(unsigned int id) {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		g->compileShader(id, entidad);
		compilado = true;
		return id;
	}

	unsigned int Shader::addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type) {
		int idS = addShader(id, type);
		if (idS > 0) {
			shadersPathId[path] = id;
		}
		return idS;
	}
	unsigned int Shader::addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte* data, int count) {
		int idS = addShader(id, type,data, count);
		if (idS > 0) {
			shadersPathId[path] = id;
		}
		return idS;
	}
	unsigned int Shader::addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type, const char* data, int count) {
		int idS = addShader(id, type, data, count);
		if (idS > 0) {
			shadersPathId[path] = id;
		}
		return idS;
	};

	unsigned int Shader::addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type) {
		shadersId.push_back(id);
		stackShader(NULL, id, type);
		return shadersId.size();
	}

	unsigned int Shader::addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte* data, int count) {
		if (type != Graphics::Shader::TYPE_SHADER::COMPILE) {
			Shader* s = new Shader(entidad, graphic);
			s->cargar(id, type, data, count);
			shadersData.push_back(s);
			shadersId.push_back(id);

			stackShader(s, id, type);


			return shadersData.size();
		}
		return 0;
	}

	unsigned int Shader::addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const char* data, int count) {
		return addShader(id, type, (const byte*)data, count);
	}/**/
	void Shader::stackShader(Shader* s, unsigned int id, Graphics::Shader::TYPE_SHADER type) {
		//Organizamos los shaders para que se agrupen en vertex, fragment y geometry
			//TODO: Esto puede ser lento, habría que revisarlo en el futuro
		if (shadersStack.size() == 0) {
			shadersStack[0] = { {type},0,{(unsigned int)id } };
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
				shadersStack[shadersStack.size()] = { {type},0,{(unsigned int)id } };
			}
		}
	}
	std::vector<Shader*>* Shader::getShaders() {
		return &shadersData;
	}
	std::vector<unsigned int>* Shader::getShadersId(int idStack) {
		//return &shadersId;
		//TODO: Lo idel sería que el sistema compruebe que no estemos accediendo fuera de los elementos del array. Por eficiencia lo dejamos en manos del desarrollador.
		return &(std::get<2>(shadersStack[idStack]));
	}
	std::vector<unsigned int>* Shader::getShadersCompiled() {
		return &shadersCompiled;
	}
	
	void Shader::cargar(unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte*& data, int count) {
		idS = id;
		tipo = type;
		codigo = new byte[count];
		for (int i = 0; i < count; i++) {
			codigo[i] = data[i];
		}
		longitudCodigo = count;
	}/**/


	Graphics::Shader::TYPE_SHADER Shader::getType() {
		return tipo;
	}/**/

	unsigned int Shader::getId() {
		return idS;
	}
//std::map<const char*, short int> Shader::shadersPathId;
}