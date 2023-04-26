#ifndef __TRANSFORM
#define __TRANSFORM

#include <vector>
#include "exportar.h"
#include "../../utilidades/global/constantes.h"
//extern class modules::graphics::Interface;
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
	//friend class modules::graphics::Interface;
	Vector3* _position;
	Vector3* _rotation;
	Vector3* _scale;
	Entity* entidad;
	float transformacion[16] = {
		1.00f, 0.00f, 0.00f, 0.00f,
		0.00f, 1.00f, 0.00f, 0.00f,
		0.00f, 0.00f, 1.00f, 0.00f,
		0.00f, 0.00f, 0.00f, 1.00f
	};
	std::vector<Transform*> hijos;
	void cambiado();
	void changeChildrens();
public:
	Transform(Entity * entidad) {
		_position = new Vector3(0, 0, 0);
		_rotation = new Vector3(0, 0, 0);
		_scale = new Vector3(1, 1, 1);
		this->entidad=entidad;
		
	}
	~Transform() {
		if (_position != NULL) {
			delete _position;
		}
		if (_rotation != NULL) {
			delete _rotation;
		}
		if (_scale != NULL) {
			delete _scale;
		}
		_scale = NULL;
		_rotation = NULL;
		_position = NULL;
	}
	Vector3* position();
	Vector3* rotation();
	Vector3* scale();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setPosition(float x, float y, float z);
	std::tuple<float, float, float> getPosition() { return {_position->x, _position->y, _position->z}; };

	void setScale(float x, float y, float z);
	std::tuple<float, float, float> getScale() { return { _scale->x, _scale->y, _scale->z }; };

	void setRotator(float x, float y, float z);
	std::tuple<float, float, float> getRotator() { return { _rotation->x, _rotation->y, _rotation->z }; };

	float* matrix();
	void update();



	void appendChild(Entity* child);
	void appendChild(Transform* child);
	void removeChild(Entity* child);
	void removeChild(Transform* child);

	static void calculateMatrix(float * tranform, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz);
	
	static void multMatrix(float* a, int rowsA, int colsA, float* b, int rowsB, int colsB, float* result);
	static std::tuple<float, float, float> calculateForwardVector(float x, float y, float z, float fx, float fy, float fz);
	static std::tuple<float, float, float, float, float, float>calculateForwardVector2(float x, float y, float z, float fx, float fy, float fz, float f2x, float f2y, float f2z);
};
#endif // !__TRANSFORM
