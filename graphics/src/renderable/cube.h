#ifndef _CUBE
#define _CUBE

#include "object.h"
#include "../motor.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Cube : public Object {
	public:
		Object::TYPE getType() { return Object::TYPE::CUBE; };
	};
}
#endif // !_CUBE
