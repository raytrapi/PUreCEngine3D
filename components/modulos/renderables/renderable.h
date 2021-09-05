#ifndef _COMP_REND
#define _COMP_REND

#include "../../src/exportar.h"
#include "../../src/component.h"
#include "../../../modules/src/module.h"
#include "../../../graphics/src/renderable/object.h"
#include <vector>
#define M_PI           3.14159265358979323846
#define M_PI2          1.57079632679489661923
#define M_2PI          6.28318530717958647692
class EXPORTAR_COMPONENTE RenderableComponent : public Component {
private:
	renderable::Object  * objeto; 
	float pX = M_PI;
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
	float *vertices=NULL;

	float r;
	float g;
	float b;
	float a;
	bool actualizar = false;
public:

	RenderableComponent(renderable::Object *obj);
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


};


#endif // !_COMP_REND

