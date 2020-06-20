#ifndef _RENDERIZABLES
#define _RENDERIZABLES

#include <vector>
#include <type_traits>
#include "img.h"
#include "object.h"
#include "../motor.h"


class EXPORTAR_MODULO_GRAFICO Renderable {
	static std::vector<renderable::Object*> renderizables;
public:
	~Renderable();
	template <class T>
	static T* createRenderable();
	static void clearRenderable();
	static void *getRenderable();
};
template <class T>
inline T* Renderable::createRenderable() {
	if (std::is_same<T, renderable::Img>::value) {
		//Devolvemos un imagen
		renderable::Img* img = new renderable::Img();
		renderizables.push_back((renderable::Object*)img);
		return img;
	}
}
inline void* Renderable::getRenderable() { return (void *)&renderizables; };
#endif // !_RENDERIZABLES
