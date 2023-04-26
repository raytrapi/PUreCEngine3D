#ifndef _COMP_SHADER
#define _COMP_SHADER

#include "../../src/exportar.h"
#include "../../src/component.h"
#include "../../../modules/src/module.h"

#include "types.h"
#include <vector>
//extern enum modules::graphics::Graphic::TYPE_SHADER;
namespace graphics{
	class EXPORTAR_COMPONENTE Shader : public Component {
	public:
	
		std::vector<Shader*> shadersData; //Contiene un vector de código para cada shader
		std::vector<short int> shadersCompiled;
		std::vector<short int> shadersId;
		std::map<const char*, short int> shadersPathId;
		//std::map<int, std::tuple<std::vector<std::tuple<Shader*, Graphics::Shader::TYPE_SHADER>>, unsigned int, std::vector<short int>>> shadersStack;
		std::map<int, std::tuple<std::vector<Graphics::Shader::TYPE_SHADER>, unsigned int, std::vector<short int>>> shadersStack;

	private:
		short int idS;
		Graphics::Shader::TYPE_SHADER tipo;
		byte* codigo = 0;
		int longitudCodigo;
		bool compilado = false;
		void cargar(short int id, Graphics::Shader::TYPE_SHADER type, const byte*& data, int count);
		void stackShader(Shader* s, short int id, Graphics::Shader::TYPE_SHADER type);
	public:
		Shader(Entity* entity, modules::graphics::Graphic* g, Component* p = NULL);
		~Shader();

		template<class T>
		T* getData();

		Graphics::Shader::TYPE_SHADER getType();
		short int getId();

		int getShaderSize();
		const Shader* getShader(int id);
	
		int loadShader(const char* path, Graphics::Shader::TYPE_SHADER type);
		void reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type, int idShader, int idProgram);
		int compileShader();
		std::vector<short>compileShaders();
		int compileShader(int id);
		int addShader(const char * path, unsigned int id, Graphics::Shader::TYPE_SHADER type);
		int addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte* data, int count);
		int addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type, const char* data, int count);
		int addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type);
		int addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte* data, int count);
		int addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const char* data, int count);

		
		/**/
		std::vector<Shader*>* getShaders();
		//Para agilizar mantendremos un vector para los compilados
		std::vector<short int>* getShadersCompiled();
		std::vector<short>* getShadersId(int idStack=0);
		bool isCompiled() { return compilado; }
	};
	template<class T>
	inline T* Shader::getData() {
		return (T*)codigo;
	}
}
inline graphics::Shader::Shader(Entity* entity, modules::graphics::Graphic* g, Component* p) {
	entidad = entity;
	graphic = g;
	idS = -1;
	tipo = Graphics::Shader::NONE;
	codigo = NULL;
	longitudCodigo = 0;
}
#endif // 

