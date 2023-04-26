#ifndef _COMP_REND
#define _COMP_REND

#include "../../src/exportar.h"
#include "../../src/component.h"
//#include "../../../modules/src/module.h"
#include "../shader/shader.h"
#include "../../../graphics/src/renderable/object.h"
#include "../../../graphics/src/renderable/img.h"
#include <vector>
#include <type_traits>
//#include "../../../utilidades/utiles/mathConsts.h"


class EXPORTAR_COMPONENTE RenderableComponent : public Component {
private:
	renderable::Object  * objeto; 
	float pX = 0;// M_PI;
	float pY = 0;
	float pZ = 0;
	float rX = 0;
	float rY = 0;
	float rZ = 0;
	float l;
	/*float transformacion[16] = {
		1.00f, 0.00f, 0.00f, 0.00f,
		0.00f, 1.00f, 0.00f, 0.00f,
		0.00f, 0.00f, 1.00f, 0.00f,
		0.00f, 0.00f, 0.00f, 1.00f
	};/**/
	/*int numeroNormales;
	float* normales = NULL;
	int numeroVertices;
	float *vertices=NULL;
	int numeroCaras;
	Face* caras = NULL;/**/
	

	float r;
	float g;
	float b;
	float a;
	bool actualizar = false;
	bool objetoPropio = false;
public:

	RenderableComponent(Entity* entity, modules::graphics::Graphic* g,Component*p=NULL);
	~RenderableComponent();
	renderable::Object* getRenderable() { return objeto; };
	void rotateX(float radian);
	void rotateY(float radian);
	void rotateZ(float radian);
	virtual void setPosition(float x, float y, float z);
	virtual void moveX(float x);
	void setRotation(float x, float y, float z);
	void setRotationGimbal(float uX, float uY, float uZ, float angle);
	float getX();
	float getY();
	float getZ();
	float getRX();
	float getRY();
	float getRZ();
	float* matrixTrans();
	bool isUpdatable();
	void update();
	void setUpdated(bool update);
	std::vector<std::vector<const float*>>* getFaces();
	
	template<class T>
	T* add(renderable::Object* o=NULL);
};



#endif // !_COMP_REND

