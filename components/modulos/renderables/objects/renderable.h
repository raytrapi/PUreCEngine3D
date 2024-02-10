#ifndef _RENDERIZABLES
#define _RENDERIZABLES

#include <vector>
#include <type_traits>
#include "img.h"
#include "cube.h"
#include "object.h"
#include "../../../src/exportar.h"
#include "../../modules/graphic/motor.h"

class EXPORTAR_COMPONENTE Renderable {
	static std::vector<renderable::Object*> renderizables;
	static modules::graphics::Graphic *motorGrafico;
	bool activo=true;
public:
	~Renderable();
	template <class T>
	static T* createRenderable();
	static void clearRenderable();
	static void *getRenderable();
	static void setGraphicEngine(modules::graphics::Graphic* motorGrafico) { Renderable::motorGrafico = motorGrafico; };
	void setActive(bool active) { activo = active; };
	bool isActive() { return activo; };

};
template <class T>
inline T* Renderable::createRenderable() {
	modules::graphics::Graphic::TYPE_ENTITY tipo = modules::graphics::Graphic::TYPE_ENTITY::NONE;
	renderable::Object* obj = 0;
	if (std::is_same<T, renderable::Img>::value) {
		//Devolvemos un imagen
		renderable::Img* img = new renderable::Img();
		renderizables.push_back((renderable::Object*)img);
		obj = (renderable::Object*)img;
		tipo = modules::graphics::Graphic::TYPE_ENTITY::IMG;
		
	}
	if (std::is_same<T, renderable::Cube>::value) {
		//Devolvemos un cubo
		renderable::Cube* cubo = new renderable::Cube(0);
		renderizables.push_back((renderable::Object*)cubo);
		obj = (renderable::Object*)cubo;
		tipo = modules::graphics::Graphic::TYPE_ENTITY::MESH;
	}

	if (motorGrafico) {
		//motorGrafico->newEntity(tipo, obj);
	}
	return (T*)obj;
}
inline void* Renderable::getRenderable() { return (void *)&renderizables; };
#endif // !_RENDERIZABLES
