#ifndef _OBJECT
#define _OBJECT
#include "../motorExport.h"
#include "../../modules/graphic/motor.h"
#include <vector>
#include <list>
#include <log.h>
#include <string>

extern class RenderableComponent;
namespace renderable {

	class EXPORTAR_MODULO_GRAFICO Object {
	public:
		enum class EXPORTAR_MODULO_GRAFICO TYPE {
			LINE,
			IMG,
			CUBE,
			MESH,
			TEXT
		};
		enum MODE_COLOR {
			COLOR,
			TEXTURE
		};
		/*float pX;
		float pY;
		float pZ;
		float rX;
		float rY;
		float rZ;/**/
	private:
		static std::vector<Object*> objetos;

	protected:
		int numCoordenadas = 0; //Suponemos que normales y colores son por vertice.
		std::string nombre;
		int numeroNormales;
		float* normales = NULL; //Contiene el array de Normales
		int numeroVertices=0;
		float* vertices = NULL; //Contiene los vertices en bloques de 3 en 3 (x,y,z)
		float* colores = NULL;
		float* uvs = NULL;//Array de posiciones UV para texturas
		int* indices = NULL;
		std::vector<std::vector<const float*>>* caras = NULL;

		boolean cambio = false;
		void ponerMesh(float* mesh, float* normals = NULL, float* colores=NULL, int* indexs=NULL);
		void borrar();
		void borrarVertex();
		void borrarMesh();
		void borrarMaterial();
		/// <summary>
		/// keep the material and a boolean that say if the material is delete when delete the mesh
		/// Guardamos el material y un booleano indicando si hay que borrar el material si borramos la malla
		/// </summary>
		std::vector<std::tuple<modules::graphics::Material*, bool>> materials;
		RenderableComponent* renderizador=NULL;
		MODE_COLOR modoColor = COLOR;
		static void almacenar(Object* objeto) { objetos.push_back(objeto); };
		static void liberar(Object* objeto) { delete objeto; };
		bool actualizarRender = false;

		bool actualizarVertices = true;
		bool actualizarTextura = true;
	public:
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
		unsigned setMaterial(modules::graphics::Material* m, int pos=-1, bool del=true);
		unsigned setMaterial(modules::graphics::Material m, int pos=-1, bool del = true);
		void setRenderable(RenderableComponent*);
		RenderableComponent* getRenderable();
		std::vector<modules::graphics::Material*> getMaterials();
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
		int getAllSize() { return numCoordenadas; };
		float* getMesh() { return vertices; };
		float* getNormals() { return normales;};
		float* getColors() { return colores; }; 
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

	};
	
}



#endif // !_OBJECT

