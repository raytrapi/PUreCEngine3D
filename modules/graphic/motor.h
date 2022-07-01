#pragma once
#ifndef _MOTORGRAFICO
#define _MOTORGRAFICO


#include "../src/module.h"
#include "../../components/modulos/shader/types.h"
#include "../../utilidades/log/log.h"
#include "../../utilidades/global/screen.h"
#include "../../utilidades/global/global.h"
#include "../../utilidades/global/input.h"
#include "../../utilidades/global/mouse.h"
#include "interface.h"
//#include "../../components/src/entity.h"
#include <list>
#include <vector>
#include <map>
#include <tuple>
#include <string>
//#include "../../graphics/src/renderable/object.h"





extern class Camera;
extern class Entity;
namespace modules {
	namespace graphics {
		struct EXPORTAR_MODULO TextureImg {
			enum TYPE {
				COLOR,
				SCALAR,
				BUMP
			};
			enum FORMAT_COLOR {
				DEPTH,
				DEPTH_STENCIL,
				RED,
				RG,
				RGB,
				RGBA
			};
			TextureImg() {};
			TextureImg(const TextureImg&);
			TextureImg(float* image, unsigned int length, TYPE tipo, int width=0, int height=0, FORMAT_COLOR formatColor=RGB);
			~TextureImg() { 
				if (image!=NULL) { 
					delete[]image; 
					image = NULL; 
				}; 
			};
			void setImage(float* image, unsigned int length, TYPE tipo, int width=0, int height=0, FORMAT_COLOR formatColor=RGB);
		private:
			TYPE type;
			float* image=NULL;
			unsigned int length = 0;
			int width;
			int height;
			FORMAT_COLOR formatColor;
			void chargeImage(float* image, unsigned int lenght);
		};
		struct EXPORTAR_MODULO Texture {
			Texture() {};
			Texture(const Texture&);
			~Texture() { 
				if (texture!=NULL) { 
					delete texture; 
					texture = NULL; 
				}; 
			};
			void setImage(float* image, unsigned int length, int width, int height, unsigned  idTexture, TextureImg::FORMAT_COLOR formatColor = TextureImg::FORMAT_COLOR::RGBA);
			void setTexture(float*, unsigned int, int width, int height, TextureImg::FORMAT_COLOR formatColor = TextureImg::FORMAT_COLOR::RGBA);
			void setTexture(unsigned  idTexture);
			unsigned int getIdTexture() { return idTexture; };
		private:
			TextureImg* texture=NULL;
			int idTexture =-1;
		};
		struct EXPORTAR_MODULO Material {
			enum TYPE {
				RGB,
				FILE
			};
			Material();
			Material(const Material &);
			~Material();
			void setTexture(Texture* t);
			void setTexture(unsigned int idTexture);
			void setTexture(float*, unsigned int, int width, int height, TextureImg::FORMAT_COLOR formatColor = TextureImg::FORMAT_COLOR::RGBA);
			unsigned int getIdTexture() { if (textures.size() > 0) { return textures[0]->getIdTexture(); } else { return 0; } };
			std::vector<Texture*>* getTextures() { return &textures; };
			boolean haveTextures() { return textures.size() > 0; };
		private:
			float *ambient=NULL; //Ka Color
			int lenA = 0;
			TYPE typeAmbient;
			float *difuse = NULL; //Kd Color
			int lenD = 0;
			TYPE typeDifuse;
			float *specular = NULL; //Ks Color
			int lenS = 0;
			TYPE typeSpecular;
			float *emission = NULL;
			int lenE = 0;
			TYPE typeEmission;
			int ilumination;
			float opacity; //d escalar
			float exponenteSpecular; //Ns escalar
			int sharpness = 60; //0 a 1000
			float densityOptical; //Ni
			//.mpc textura color
			//.mps textura escalar
			//.mpb textura de bump
			std::vector<TextureImg*> imgTextures;
			std::vector<Texture*> textures;
			
		};




		
		class EXPORTAR_MODULO Graphic:public Module {
			//std::list<void*>elementosRenderizar;
			//TODO: Ver si aceleramos el pintado si procesamos nosotros la capa.
			//byte* lienzo = null;
			bool end = false;
			std::map<std::string, Material*>materiales;
			
		protected:
			void setEnd() { end = true; };
			//std::vector<void *> entities;
			static bool open;
			bool stopping = false;
			//double ancho=1;
			//double alto=1;
			virtual void iniciar() {};
			virtual void destruir() {};
			//bool mostrarGizmo = false;
			utiles::Log* gestorLog=NULL;
			int idInstanciaLog = 0;
			Global *global=NULL;
			Interface *interfaz=NULL;
			Input *input;
			Mouse *mouse;
		public:
			
			Input *getInput() { return input; };
			static std::vector<void(*)(bool)> onFocus;
			
			static std::vector<Tape*> onFocusTapes;
			enum TYPE_ENTITY {
				NONE,
				IMG,
				MESH
			};
			enum TYPE_TEXTURE {
				T_NONE,
				T_IMG
			};
			enum TYPE_OPERATION {
				ALL,
				MOVE
			};
			void init() final {
				iniciar();
			}
			void destroy() final {
				destruir();
			}
			void setInput(Input& i) {
				input = &i;
			}
			void setMouse(Mouse& m) {
				mouse = &m;
			}/**/
			void setInterface(Interface* i) { interfaz = i; if (global != NULL) { interfaz->setGlobal(global); } };
			void setGlobal(Global* g) {
				global = g; 
				if (interfaz != NULL) { interfaz->setGlobal(g); } 
			};
			Global* getGlobal() {
				return global;
			}

			utiles::Log* getLog() { return gestorLog; };
			void setLog(utiles::Log* log) {
				gestorLog = log; idInstanciaLog = utiles::Log::getNumberInstances()-1;
			};
			int getIdInstanceLog() {
				return idInstanciaLog;
			}
			
			/*~Grafico() {
				//Renderable::clearRenderable();
			};/**/
			virtual void preRender() = 0;
			virtual void render() = 0;
			virtual void render(void *) = 0;
			virtual void renderInterface() = 0;
			virtual void postRender() = 0;
			//virtual void renderNewViewPort(std::vector<Entity*> entidades, float x = -1.f, float y = 1.f, float width = 2.f, float height = 2.f) {};
			//virtual void insertarMapaBits(byte*, double ancho, double alto, double x, double y, double z)=0;
			virtual bool inicializar(void*, double, double) = 0;
			Module::MODULES_TYPE tipo() { return Module::MODULES_TYPE::GRAPHIC; };
			bool isEnd() { return end; };
			virtual void updateEntity(void* entity, TYPE_OPERATION type=ALL) {};
			void updateEntities(unsigned stack=0,TYPE_OPERATION type = MOVE);
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
			bool isChangeCamera(Camera* camera);
			//virtual void* 
			void loadTexture(std::string name, std::string path, TYPE_TEXTURE type = TYPE_TEXTURE::T_NONE);
			/// <summary>
			/// Add a texture in GPU 
			/// Añade una textura a la tajeta gráfica
			/// </summary>
			/// <param name="image">vector to floats</param>
			/// <param name="length">number of floats</param>
			/// <param name="idTexture">set the value of texture in the GPU</param>
			/// <returns>true if the textura load in memory</returns>
			virtual bool addTexture(float* image, unsigned int length, int width, int height, int& idTexture, TextureImg::FORMAT_COLOR typeColor= TextureImg::FORMAT_COLOR::RGBA)=0;
			std::tuple<double, double> getScreenSize() {

				return { Screen::getWidth(), Screen::getHeight() };
			}
			virtual Entity * drawLine(float* vertex, unsigned countVertex, float r, float g, float b, float a,unsigned width =1) = 0;
			virtual Entity * drawLineLoop(float* vertex, unsigned countVertex, float r, float g, float b, float a, unsigned width = 1) {
				return drawLine(vertex, countVertex, r, g, b, a, width);
			};
			
		};


	}
}

/*inline virtual modulos::graficos::Grafico::~Grafico() {
	Renderable::clearRenderable();
}
/**/
//std::vector<std::tuple<Key, std::function<void(Key)>, bool>>  Input::controlTeclasPulsadas;
#endif // 