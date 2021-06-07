#ifndef _MOTORGRAFICO
#define _MOTORGRAFICO


#include "../src/module.h"
#include "../../components/modulos/shader/types.h"
//#include "../../components/src/entity.h"
#include <list>
#include <vector>
#include <map>
#include <string>
//#include "../../graphics/src/renderable/object.h"


extern class Camera;
namespace modules {
	namespace graphics {
		struct EXPORTAR_MODULO Texture {

		};
		class EXPORTAR_MODULO Graphic:public Module {
			//std::list<void*>elementosRenderizar;
			//TODO: Ver si aceleramos el pintado si procesamos nosotros la capa.
			//byte* lienzo = null;
			bool end = false;
			std::map<std::string, Texture *>texturas;
		protected:
			void setEnd() { end = true; };
			std::vector<void*> entities;
			static bool open;
			bool stopping = false;
		public:
			static std::vector<void(*)(bool)> onFocus;
			static std::vector<Tape*> onFocusTapes;
			enum TYPE_ENTITY {
				NONE,
				IMG,
				MESH
			};
			enum TYPE_TEXTURE {
				NONE,
				IMG
			};
			
			/*~Grafico() {
				//Renderable::clearRenderable();
			};/**/
			virtual void destroy() {};
			virtual void renderizar() = 0;
			virtual void renderizar(void *) = 0;
			//virtual void insertarMapaBits(byte*, double ancho, double alto, double x, double y, double z)=0;
			virtual bool inicializar(void*, double, double) = 0;
			Module::MODULES_TYPE tipo() { return Module::MODULES_TYPE::GRAPHIC; };
			bool isEnd() { return end; };
			virtual void updateEntity(void* entity) {};
			virtual void addEntity(void* entity);
			virtual void removeEntity(void* entity);
			virtual void removeEntities();
			virtual void removeAll();
			/*virtual void newEntity(TYPE_ENTITY type, renderable::Object * object) {};*/
			virtual const byte* loadShader(const char* path) { return 0; };
			virtual int loadShader(const char* path, Graphics::Shader::TYPE_SHADER type) { return 0; };
			virtual void reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type,int idShader, int idProgram) { };
			virtual int compileShader(std::vector<short>*) { return 0; };
			virtual int compileShader(int ps) { return 0; };
			virtual int compileShader(std::vector<short>*, void* entity) { return 0; }; 
			virtual int compileShader(int ps, void* entity) { return 0; };

			void addOnFocus(void(*callback)(bool));
			void addOnFocus(Tape * juego);
			void removeOnFocus(Tape* juego);
			void removeAllFocus();

			virtual bool isOpen() { return open;};

			virtual void changeCamera(Camera* camera) {};//Lamentablemente para evitar ciclos hemos de añadir un puntero, pero realmente será un tipo Camera
			virtual void resizeCamera() {};
			//virtual void* 
			void loadTexture(std::string name, std::string path, TYPE_TEXTURE type = TYPE_TEXTURE::NONE);
		};

	}
}

/*inline virtual modulos::graficos::Grafico::~Grafico() {
	Renderable::clearRenderable();
}
/**/


#endif // 