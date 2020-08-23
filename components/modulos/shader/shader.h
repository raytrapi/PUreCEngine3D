#ifndef _COMP_SHADER
#define _COMP_SHADER

#include "../../src/exportar.h"
#include "../../src/component.h"
#include "../../modules/src/module.h"
//#include "../../modules/graphic/motor.h"
#include <vector>
class EXPORTAR_COMPONENTE Shader : public Component {
public:
	enum class EXPORTAR_COMPONENTE TYPE {
		COMPILE,
		VERTEX,
		FRAGMENT
	};
	std::vector<Shader*> shadersData; //Contiene un vector de código para cada shader
	std::vector<short int> shadersCompiled;
private:
	short int idS;
	TYPE tipo;
	byte* codigo = 0;
	int longitudCodigo;
public:

	Shader(short int id, TYPE type, const byte*& data, int count);
	~Shader();

	template<class T>
	T* getData();

	TYPE getType();
	short int getId();

	int getShaderSize();
	const Shader* getShader(int id);
	int loadShader(const char* path, Shader::TYPE type);
	void compileShader();
	int addShader(unsigned int id, Shader::TYPE type);
	int addShader(unsigned int id, Shader::TYPE type, const byte* data, int count);
	int addShader(unsigned int id, Shader::TYPE type, const char* data, int count);
	std::vector<Shader*>* getShaders();
	//Para agilizar mantendremos un vector para los compilados
	std::vector<short int>* getShadersCompiled();
};


#endif // !_COMP_SHADER

template<class T>
inline T* Shader::getData() {
	return (T*)codigo;
}
