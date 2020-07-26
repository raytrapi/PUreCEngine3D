#ifndef _CUBE
#define _CUBE

#include "object.h"
#include "../motorExport.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Cube : public Object {
		float l=1;
	public:
		Object::TYPE getType() { return Object::TYPE::CUBE; };
		float r = 1;
		float g = 1;
		float b = 1;
		float a = 1;
		void setSize(float length);
		float getSize();
	};
}
#endif // !_CUBE
