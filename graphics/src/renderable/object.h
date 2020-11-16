#ifndef _OBJECT
#define _OBJECT
#include "../motorExport.h"
#include <vector>
#include <log.h>

namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Object {
		/*float pX;
		float pY;
		float pZ;
		float rX;
		float rY;
		float rZ;/**/
	protected:
		
		float* normales = NULL;
		float* malla = NULL;
	public:
		enum class EXPORTAR_MODULO_GRAFICO TYPE {
			IMG,
			CUBE
		};
		virtual ~Object();
		virtual Object::TYPE getType() = 0;
		void setMesh(float* mesh, float* normals = NULL); 
		
	};
}


#endif // !_OBJECT

