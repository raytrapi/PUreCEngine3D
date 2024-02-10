#ifndef _OBJECT
#define _OBJECT
#include "../../../src/exportar.h"

#include "../../../modules/graphic/motor.h"
#include "../../utilidades/project/serializer/serializer.h"
#include "../../utilidades/project/serializer/deserializer.h"
#include "../resources/material.h"
#include <vector>
#include <list>
#include <log.h>
#include <string>
#include <imgui.h>

extern class RenderableComponent;
namespace renderable {

	class EXPORTAR_COMPONENTE Object {
	protected:
		friend class RenderableComponent;
		virtual bool interfazImGUI_C(ImGuiContext* imgui) {return true;};
		virtual int saveState_interno(std::vector<unsigned char>* data, bool withID = false) { return 0; }
		virtual void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false) { }

		
	public:
		enum class EXPORTAR_COMPONENTE TYPE {
			LINE,
			IMG,
			CUBE,
			MESH,
			TEXT
		};
		enum MODE_COLOR {
			COLOR=0,
			TEXTURE=1
		};
		/*float pX;
		float pY;
		float pZ;
		float rX;
		float rY;
		float rZ;/**/
		friend class Entity;
		virtual std::string serializar() { return ""; };
		//static int desserializar(std::string s, int pos, Component* e);
		static int desserializar(std::string s, int pos, RenderableComponent* e);
		virtual int desserializar(std::string s, int pos=0) { return pos; };

		int saveState(std::vector<unsigned char>* data, bool withID = false);
		void restoreState(std::vector<unsigned char>* data = 0, bool withID = false);
		bool interfazImGUI(ImGuiContext* imgui);
	private:
		static std::vector<Object*> objetos;

	protected:
		int numCoordenadas = 0; //Suponemos que normales y colores son por vertice.
		std::string nombre="";
		int numeroNormales=0;
		float* normales = NULL; //Contiene el array de Normales
		int numeroVertices=0;
		float* vertices = NULL; //Contiene los vertices en bloques de 3 en 3 (x,y,z)
		float* colores = NULL;
		float* uvs = NULL;//Array de posiciones UV para texturas
		int* indices = NULL;
		int numeroModosColor = 0;
		float* idsMateriales = NULL;
		MODE_COLOR* modosColor = NULL;
		std::vector<std::vector<const float*>>* caras = NULL;

		boolean cambio = false;
		void ponerMesh(float* mesh, float* normals = NULL, float* colores=NULL, int* indexs=NULL);
		void borrar();
		void borrarVertex();
		void borrarMesh();
		void borrarMaterial();
		void borrarIdsMaterial();
		/// <summary>
		/// keep the material and a boolean that say if the material is delete when delete the mesh
		/// Guardamos el material y un booleano indicando si hay que borrar el material si borramos la malla
		/// </summary>
		std::vector<std::tuple<Material*, bool>> materials;
		RenderableComponent* renderizador=NULL;
		MODE_COLOR modoColor = COLOR;
		static void almacenar(Object* objeto) { objetos.push_back(objeto); };
		static void liberar(Object* objeto) { delete objeto; };
		bool actualizarRender = false;

		bool actualizarVertices = true;
		bool actualizarTextura = true;
		
		virtual void materialUpdated_I(Texture* texture, Material* material) {};

	public:
		void materialUpdated(Texture* texture, Material* material);
		virtual ~Object();
		virtual Object::TYPE getType() = 0;
		Object::MODE_COLOR getTypeColor() { return modoColor; }
		void setName(std::string name);
		bool hasChange() {
			if (cambio) { cambio = false; return true; }
			return false;
		}
		void setChange(bool changed) {
			cambio = changed;
			setToRender(changed);
		}
		unsigned setMaterial(Material* m, int pos=-1, bool del=true);
		unsigned setMaterial(Material m, int pos=-1, bool del = true);
		void setRenderable(RenderableComponent*);
		RenderableComponent* getRenderable();
		std::vector<Material*> getMaterials();
		void setToRender(bool toRender);
		float* getUVs();
		unsigned int getIdTexture();
		int getNormalsNumber();
		int getVertexNumber();
		int getFacesNumber();

		std::vector<std::vector<const float*>>* getFaces();
		static void freeAll() {
			int limite = 1000;
			while (objetos.size()>0 && limite-->0) {
				renderable::Object* o = objetos.back();
				liberar(o);
				objetos.pop_back();
			}
		}
		void setUV(float** uv);
		void setUV(int pos, float u, float v);
		int getAllSize() { return numCoordenadas; };
		float* getMesh() { return vertices; };
		float* getNormals() { return normales;};
		float* getColors() { return colores; }; 
		float* getIdMaterials() { return idsMateriales; };
		MODE_COLOR* getColorModes() { return modosColor; }
		int getMaterialsNumber() { return numeroModosColor; }
		void setUpdatingRender(bool updating) {
			actualizarRender = updating;
		}
		bool isUpdatingRender() {
			if (actualizarRender) {
				actualizarRender = false;
				return true;
			}
			return false;
		}
		bool isUpdatingVertex() {
			if (actualizarVertices) {
				actualizarVertices = false;
				return true;
			}
			return false;
		}
		void setUpdatingVertex(bool updating) {
			actualizarVertices = updating;
		}
		bool isUpdatingTexture() {
			if (actualizarTextura) {
				actualizarTextura = false;
				return true;
			}
			return false;
		}
		void setUpdatingTexture(bool updating) {
			actualizarTextura = updating;
		}
		Material* getMaterial(unsigned int ix);
	};
	
}



#endif // !_OBJECT

