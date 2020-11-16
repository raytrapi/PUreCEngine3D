#ifndef __TRANSFORM
#define __TRANSFORM

#include "exportar.h"
struct EXPORTAR_COMPONENTE Vector3 {
	double x;
	double y;
	double z;
	Vector3(double x, double y, double z) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
};
class EXPORTAR_COMPONENTE Transform {
	Vector3* _position;
	Vector3* _rotation;
	Vector3* _scale;
public:
	Transform() {
		_position = new Vector3(0, 0, 0);
		_rotation = new Vector3(0, 0, 0);
		_scale = new Vector3(1, 1, 1);
	}
	~Transform() {
		delete _position;
		delete _rotation;
		delete _scale;
	}
	Vector3* position();
	Vector3* rotation();
	Vector3* scale();

	
};
#endif // !__TRANSFORM
