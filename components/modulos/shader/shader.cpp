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

int Shader::loadShader(const char* path, Shader::TYPE type) {
	//return Module::getModule<modules::graphics::Graphic>()->loadShader(path, type, this);
	return 0;
}

void Shader::compileShader() {
	//Module::getModule<modules::graphics::Graphic>()->compileShader(this);
}

int Shader::addShader(unsigned int id, Shader::TYPE type) {
	shadersCompiled.push_back(id);
	return shadersCompiled.size();
}

int Shader::addShader(unsigned int id, Shader::TYPE type, const byte* data, int count) {
	if (type != Shader::TYPE::COMPILE) {
		shadersData.push_back(new Shader(id, type, data, count));
		return shadersData.size();
	}
	return 0;
}

int Shader::addShader(unsigned int id, Shader::TYPE type, const char* data, int count) {
	return addShader(id, type, (const byte*)data, count);
}

std::vector<Shader *>* Shader::getShaders() {
	return &shadersData;
}

std::vector<short int>* Shader::getShadersCompiled() {
	return &shadersCompiled;
}

Shader::Shader(short int id, Shader::TYPE type, const byte*& data, int count) {
	idS = id;
	tipo = type;
	codigo = new byte[count];
	for (int i = 0; i < count; i++) {
		codigo[i] = data[i];
	}
	longitudCodigo = count;
}


Shader::TYPE Shader::getType() {
	return tipo;
}

short int Shader::getId() {
	return idS;
}