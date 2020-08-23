#include "shader.h"

Shader::~Shader() {
	if (codigo != 0) {
		delete[]codigo;
	}
	unsigned int longitud = shadersData.size();
	for (int i = 0; i < longitud; i++) {
		delete shadersData[i];
	}
}
int Shader::getShaderSize() {
	return shadersData.size();
}

const Shader* Shader::getShader(int id) {
	return shadersData[id];
}

int Shader::loadShader(const char* path, Graphics::Shader::TYPE_SHADER type) {
	int id = Module::get<modules::graphics::Graphic>()->loadShader(path, type);
	addShader(id, type);
	return id;
}
void Shader::reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type, int idShader, int idProgram) {
	Module::get<modules::graphics::Graphic>()->reloadShader(path, type,idShader, idProgram);
}

int Shader::compileShader() {
	modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
	int id = g->compileShader(getShadersId(),entidad);
	shadersCompiled.push_back(id); //Guardamos el id ¿Es realemente necesario?
	//Le indicamos al componente gráfico que tenemos una nueva compilación de shaders
	//g.getEntity(this)
	return id;
}
int Shader::compileShader(int id) {
	modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
	g->compileShader(id,entidad);
	return id;
}
int Shader::addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type) {
	shadersId.push_back(id);
	return shadersId.size();
}

int Shader::addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte* data, int count) {
	if (type != Graphics::Shader::TYPE_SHADER::COMPILE) {
		shadersData.push_back(new Shader(id, type, data, count));
		shadersId.push_back(id);



		return shadersData.size(); 
	}
	return 0;
}

int Shader::addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const char* data, int count) {
	return addShader(id, type, (const byte*)data, count);
}/**/

std::vector<Shader *>* Shader::getShaders() {
	return &shadersData;
}
std::vector<short>* Shader::getShadersId() {
	return &shadersId;
}
std::vector<short int>* Shader::getShadersCompiled() {
	return &shadersCompiled;
}
Shader::Shader() {
	idS = -1;
	tipo = Graphics::Shader::NONE;
	codigo = NULL;
	longitudCodigo = 0;
}
Shader::Shader(short int id, Graphics::Shader::TYPE_SHADER type, const byte*& data, int count) {
	idS = id;
	tipo = type;
	codigo = new byte[count];
	for (int i = 0; i < count; i++) {
		codigo[i] = data[i];
	}
	longitudCodigo = count;
}


Graphics::Shader::TYPE_SHADER Shader::getType() {
	return tipo;
}/**/

short int Shader::getId() {
	return idS;
}