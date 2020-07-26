#ifndef _OBJECT
#define _OBJECT
#include "../motorExport.h"
#include <vector>

namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Object {
		/*float pX;
		float pY;
		float pZ;
		float rX;
		float rY;
		float rZ;/**/
	protected:
		float pX = 0;
		float pY = 0;
		float pZ = 0;
		float rX = 0;
		float rY = 0;
		float rZ = 0;
		float l;
		

	public:
		enum class EXPORTAR_MODULO_GRAFICO TYPE {
			IMG,
			CUBE
		};
		virtual ~Object();
		virtual Object::TYPE getType() = 0;
		virtual void setPosition(float x, float y, float z);
		virtual void setRotation(float x, float y, float z);
		float getX();
		float getY();
		float getZ();
		float getRX();
		float getRY();
		float getRZ();

		
	};
}


#endif // !_OBJECT

