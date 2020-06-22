#ifndef _OBJECT
#define _OBJECT
#include "../motor.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Object {
		/*float pX;
		float pY;
		float pZ;
		float rX;
		float rY;
		float rZ;/**/
	public:
		enum class EXPORTAR_MODULO_GRAFICO TYPE {
			IMG,
			CUBE
		};

		virtual Object::TYPE getType() = 0;
		float pX;
		float pY;
		float pZ;
		float rX;
		float rY;
		float rZ;
		float l;
	};
}


#endif // !_OBJECT

