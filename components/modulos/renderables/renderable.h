#ifndef _COMP_REND
#define _COMP_REND

#include "../../src/exportar.h"
#include "../../src/component.h"
#include "../../../modules/src/module.h"
#include "../../../graphics/src/renderable/object.h"
#include <vector>
class EXPORTAR_COMPONENTE RenderableComponent : public Component {
public:
	renderable::Object  * objeto; 
	float pX = 0;
	float pY = 0;
	float pZ = 0;
	float rX = 0;
	float rY = 0;
	float rZ = 0;
	float l;
	/*float transformacion[16] = {
		1.0f, 0.0f, 0.0f, 0.25f,
		0.0f, 0.52f, -0.85f, 0.0f,
		0.0f, 0.85f, 0.52f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};/**/
	float transformacion[16] = {
		1.00f, 0.00f, 0.00f, 0.00f,
		0.00f, 1.00f, 0.00f, 0.00f,
		0.00f, 0.00f, 1.00f, 0.00f,
		0.00f, 0.00f, 0.00f, 1.00f
	};/**/
	float* normales = NULL;
	/*[18] = {
		0.0f, 0.0f, 1.0f, //Normal frente 8
		1.0f, 0.0f, 0.0f, //Normal derecha 9
		0.0f, 1.0f, 0.0f, //Normal superior 10
		-1.0f, 0.0f, 0.0f, //Normal izquierda 11
		0.0f, -1.0f, 0.0f, //Normal inferior 12
		0.0f, 0.0f, -1.0f //Normal trasera 13
	};*/
	float *malla=NULL;

	float r;
	float g;
	float b;
	float a;
public:

	RenderableComponent(renderable::Object *obj);
	~RenderableComponent();
	renderable::Object* getRenderable() { return objeto; };
	void rotateX(float radian);
	void rotateY(float radian);
	void rotateZ(float radian);
	virtual void setPosition(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void setRotationGimbal(float uX, float uY, float uZ, float angle);
	float getX();
	float getY();
	float getZ();
	float getRX();
	float getRY();
	float getRZ();
	float* matrixTrans();



};


#endif // !_COMP_REND

