#ifndef _OBJECT
#define _OBJECT
#include "../motorExport.h"
#include "../../modules/graphic/motor.h"
#include <vector>
#include <log.h>
#include <string>

namespace renderable {

	class EXPORTAR_MODULO_GRAFICO Object {
	public:
		enum class EXPORTAR_MODULO_GRAFICO TYPE {
			IMG,
			CUBE,
			MESH
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
	protected:
		std::string nombre;
		float* normales = NULL; //Contiene el array de Normales
		float* vertices = NULL; //Contiene los vertices
		float* colores = NULL;
		float* uvs = NULL;//Array de posiciones UV para texturas
		int* indices = NULL;
		int numeroVertices = 0;

		boolean cambio = false;
		void ponerMesh(float* mesh, float* normals = NULL, float* colores=NULL, int* indexs=NULL);
		void borrar();
		/// <summary>
		/// keep the material and a boolean that say if the material is delete when delete the mesh
		/// Guardamos el materila y un booleano indicando si hay que borrar el material si borramos la malla
		/// </summary>
		std::vector<std::tuple<modules::graphics::Material*, bool>> materials;
		
		MODE_COLOR modoColor = COLOR;
	public:
		
		virtual ~Object();
		virtual Object::TYPE getType() = 0;
		Object::MODE_COLOR getTypeColor() { return modoColor; }
		void setName(std::string name);
		bool hasChange() {
			if (cambio) { cambio = false; return true; }
		}
		void setMaterial(modules::graphics::Material* m);
		void setMaterial(modules::graphics::Material m);
		std::vector<modules::graphics::Material*> getMaterials();
		float* getUVs();
		unsigned int getIdTexture();
	};
	
}



#endif // !_OBJECT

