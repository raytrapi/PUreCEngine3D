#ifndef _OBJECT
#define _OBJECT
#include "../motor.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Object {

	public:
		enum class EXPORTAR_MODULO_GRAFICO TYPE {
			IMG
		};

		virtual Object::TYPE getType() = 0;
	};
}


#endif // !_OBJECT

