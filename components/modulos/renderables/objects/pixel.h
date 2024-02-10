#ifndef _PIXEL
#define _PIXEL
#include "../../../src/exportar.h"
namespace renderable {
	class EXPORTAR_COMPONENTE Pixel {
		int nPixel=4;
		float* p;
	public:
		Pixel();
		~Pixel();
		float R() { return *p; };
		float G() { return *(p + 1); };
		float B() { return *(p + 2); };
		float A() { return *(p + 3); };
		void setColor(float r, float g, float b, float a);
	};
}
#endif // !_PIXEL
