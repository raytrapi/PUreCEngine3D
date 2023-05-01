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
		std::vector<unsigned int> shadersCompiled;
		std::vector<unsigned int> shadersId;
		std::map<const char*, unsigned int> shadersPathId;
		//std::map<int, std::tuple<std::vector<std::tuple<Shader*, Graphics::Shader::TYPE_SHADER>>, unsigned int, std::vector<short int>>> shadersStack;
		std::map<int, std::tuple<std::vector<Graphics::Shader::TYPE_SHADER>, unsigned int, std::vector<unsigned int>>> shadersStack;

	private:
		unsigned int idS;
		Graphics::Shader::TYPE_SHADER tipo;
		byte* codigo = 0;
		int longitudCodigo;
		bool compilado = false;
		void cargar(unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte*& data, int count);
		void stackShader(Shader* s, unsigned int id, Graphics::Shader::TYPE_SHADER type);
	public:
		Shader(Entity* entity, modules::graphics::Graphic* g, Component* p = NULL);
		~Shader();

		template<class T>
		T* getData();

		Graphics::Shader::TYPE_SHADER getType();
		unsigned int getId();

		int getShaderSize();
		const Shader* getShader(unsigned int id);
	
		unsigned int loadShader(const char* path, Graphics::Shader::TYPE_SHADER type);
		void reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type, unsigned int idShader, unsigned int idProgram);
		unsigned int compileShader();
		std::vector<unsigned int>compileShaders();
		unsigned int compileShader(unsigned int id);
		unsigned int addShader(const char * path, unsigned int id, Graphics::Shader::TYPE_SHADER type);
		unsigned int addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte* data, int count);
		unsigned int addShader(const char* path, unsigned int id, Graphics::Shader::TYPE_SHADER type, const char* data, int count);
		unsigned int addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type);
		unsigned int addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte* data, int count);
		unsigned int addShader(unsigned int id, Graphics::Shader::TYPE_SHADER type, const char* data, int count);

		
		/**/
		std::vector<Shader*>* getShaders();
		//Para agilizar mantendremos un vector para los compilados
		std::vector<unsigned int>* getShadersCompiled();
		std::vector<unsigned int>* getShadersId(int idStack=0);
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

