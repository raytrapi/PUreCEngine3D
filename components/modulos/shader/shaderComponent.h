#ifndef _COMP_SHADER
#define _COMP_SHADER

#include "../../src/exportar.h"
#include "../../src/component.h"
#include "../../../modules/src/module.h"
#include "../../../utilidades/global/config.h"
#include "types.h"
#include <vector>
extern class Shader;
//extern enum modules::graphics::Graphic::TYPE_SHADER;
namespace graphics{
	class EXPORTAR_COMPONENTE ShaderComponent : public Component {
	public:
	
		std::vector<ShaderComponent*> shadersData; //Contiene un vector de código para cada shader
		std::vector<unsigned int> shadersCompiled;
		std::vector<unsigned int> shadersId;
		std::map<std::string, unsigned int> shadersPathId;
		//std::map<int, std::tuple<std::vector<std::tuple<Shader*, Graphics::Shader::TYPE_SHADER>>, unsigned int, std::vector<short int>>> shadersStack;
		std::map<int, std::tuple<std::vector<Graphics::Shader::TYPE_SHADER>, unsigned int, std::vector<unsigned int>>> shadersStack;

		std::vector<std::tuple<Graphics::Shader::TYPE_SHADER, std::string, int>> shadersGuardados;

	private:
		unsigned int idS;
		int idActual = 0;
		int idPares = 0;
		Graphics::Shader::TYPE_SHADER tipo;
		byte* codigo = 0;
		int longitudCodigo;
		bool compilado = false;
		void cargar(unsigned int id, Graphics::Shader::TYPE_SHADER type, const byte*& data, int count);
		void stackShader(ShaderComponent* s, unsigned int id, Graphics::Shader::TYPE_SHADER type);


		//Guardamos los shaders
		Shader* shaderMaterial=0;
		char* nombreMaterial = 0;
		Shader* shaderSombras=0;
		Shader* shaderOutline=0;
		Shader* shaderClicking=0;
		//friend class Entity;
		
		
	protected:
		bool interfazImGUI_C(ImGuiContext* imgui);
		int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
		void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
	public:
		ShaderComponent(Entity* entity, modules::graphics::Graphic* g, Component* p = NULL);
		~ShaderComponent();

		template<class T>
		T* getData();

		Graphics::Shader::TYPE_SHADER getTypeShader();
		unsigned int getId();

		int getShaderSize();
		const ShaderComponent* getShader(unsigned int id);
	
		unsigned int loadShader(const char* path, Graphics::Shader::TYPE_SHADER type,int pos=-1);
		
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
		std::vector<ShaderComponent*>* getShaders();
		//Para agilizar mantendremos un vector para los compilados
		std::vector<unsigned int>* getShadersCompiled();
		std::vector<unsigned int>* getShadersId(int idStack=0);
		bool isCompiled() { return compilado; }
		void setIdCurrent(int id) { idActual = id; idPares = 0; }
		TYPE_OBJECT_SERIALIZABLES getType() { return TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_SHADER; };


		//Carga de materiales
		std::vector<Shader* > getMaterials() { return {}; };
		void setMaterial(const char* name);
		void setShadow(const char * nombre="Shadow");
		void setOutline(const char* nombre = "Outline");
		void setClicking(const char* nombre = "Clicing");
		unsigned int getMaterial();
		unsigned int getShadow();
		unsigned int getOutline();
		unsigned int getClicking();

	};
	template<class T>
	inline T* ShaderComponent::getData() {
		return (T*)codigo;
	}
}
inline graphics::ShaderComponent::ShaderComponent(Entity* entity, modules::graphics::Graphic* g, Component* p):Component(entity,g,p) {
	idS = 0;
	tipo = Graphics::Shader::NONE;
	codigo = NULL;
	longitudCodigo = 0;
	setName("Shader");
	//DBG("Creo SHADER");
}/***/


class Shader {
	std::string nombre;
	friend class graphics::ShaderComponent;
	//TODO: Pensar en 
	std::string vertex="";
	std::string fragment="";
	std::string geometry="";
	unsigned int idVertex=0;
	unsigned int idFragment=0;
	unsigned int idGeometry=0;
	unsigned int idProgram=0;
	bool correcto = false;
	
public:
	Shader(const char* name, const char* vertex, const char* fragment, const char* geometry = 0);
	~Shader();
	std::string getName() { return nombre; };
	bool isCorrect() { return correcto; }
};

#endif // 

