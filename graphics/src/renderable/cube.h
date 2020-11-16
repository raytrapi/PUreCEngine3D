#ifndef _CUBE
#define _CUBE

#include "object.h"
#include "../motorExport.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Cube : public Object {
		float l=1;
		
		/*float transformacion[16] = {
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
		};/**/
		void crearCubo(float l);
	public:
		Cube();
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
