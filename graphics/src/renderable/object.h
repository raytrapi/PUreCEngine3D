#ifndef _OBJECT
#define _OBJECT
#include "../motorExport.h"
#include <vector>
#include <log.h>
#include <string>

namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Object {
		/*float pX;
		float pY;
		float pZ;
		float rX;
		float rY;
		float rZ;/**/
	private:
	protected:
		std::string nombre;
		float* normales = NULL;
		float* malla = NULL;
		float* colores = NULL;
		int* indices = NULL;
		int numeroVertices = 0;
		void ponerMesh(float* mesh, float* normals = NULL, float* colores=NULL, int* indexs=NULL);
		void borrar();
	public:
		enum class EXPORTAR_MODULO_GRAFICO TYPE {
			IMG,
			CUBE,
			MESH
		};
		virtual ~Object();
		virtual Object::TYPE getType() = 0;
		
		void setName(std::string name);
		
	};
	
}



#endif // !_OBJECT

