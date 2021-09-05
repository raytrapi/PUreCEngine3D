#ifndef __TRANSFORM
#define __TRANSFORM

#include "exportar.h"
extern class Entity;
struct EXPORTAR_COMPONENTE Vector3 {
	float x;
	float y;
	float z;
	Vector3(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
class EXPORTAR_COMPONENTE Transform {
	Vector3* _position;
	Vector3* _rotation;
	Vector3* _scale;
	Entity* entidad;
public:
	Transform(Entity * entidad) {
		_position = new Vector3(0, 0, 0);
		_rotation = new Vector3(0, 0, 0);
		_scale = new Vector3(1, 1, 1);
		this->entidad=entidad;
	}
	~Transform() {
		delete _position;
		delete _rotation;
		delete _scale;
	}
	Vector3* position();
	Vector3* rotation();
	Vector3* scale();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setPosition(float x, float y, float z);
	
};
#endif // !__TRANSFORM
