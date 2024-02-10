#ifndef __TRANSFORM
#define __TRANSFORM

#include <vector>
#include "exportar.h"
#include "../../utilidades/global/constantes.h"
#include <imgui.h>
#include "../utiles/pointers.h"
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
	float* _pivot=0;
	float* _pivot2=0;
	float* _rotation2 =0 ;//Rotación del padre
	float* _scale2 = 0;//Rotación del padre
	bool conPivote = true; //TODO: Quitar esto, debería ser siempre falso
	bool conPivotePadre = false;
	Entity* entidad;

	float forward[3]{ 0,0,-1.0f };
	bool updateForward = true;
	bool updateUp = true;

	float up[3]{ 0,1.0f,0 };
	float identidad[16] = {
		1.00f, 0.00f, 0.00f, 0.00f,
		0.00f, 1.00f, 0.00f, 0.00f,
		0.00f, 0.00f, 1.00f, 0.00f,
		0.00f, 0.00f, 0.00f, 1.00f
	};
	float transformacion[16] = {
		1.00f, 0.00f, 0.00f, 0.00f,
		0.00f, 1.00f, 0.00f, 0.00f,
		0.00f, 0.00f, 1.00f, 0.00f,
		0.00f, 0.00f, 0.00f, 1.00f
	};
	float *identity();
	float *matrizTranslacion(bool inverse=false, float x=0, float y=0, float z=0);
	float *matrizRotacion();
	float* matrizRotacionX(float angle);
	float* matrizRotacionY(float angle);
	float* matrizRotacionZ(float angle);
	float* matrizScala(float x, float y, float z);
	float* matrizCompleta(float* m = 0);
	std::vector<Transform*> hijos;
	Transform* padre=NULL;
	void cambiado();
	void change(bool propagate=true);
	void changeChildrens();

protected:
	friend class InterfaceGL;
	bool interfazImGUI_C(ImGuiContext* imgui);
	int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
	void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
public:
	Transform(Entity * entidad) {
		_position = new Vector3(0, 0, 0);
		_rotation = new Vector3(0, 0, 0);
		_scale = new Vector3(1, 1, 1);
		_pivot = new float[3] { 0.f, 0.f, 0.f };
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
		
		DELETE_MULTI(_pivot);
		DELETE_MULTI(_pivot2);
		DELETE_MULTI(_rotation2);
		DELETE_MULTI(_scale2);
	}
	//Vector3* position();
	//Vector3* rotation();
	//Vector3* scale();
	void setX(float x);
	void setY(float y);
	void setZ(float z);
	void setPosition(float x, float y, float z, bool propagate=true);
	void addPosition(float x, float y, float z, bool propagate = true);
	std::tuple<float, float, float> getPosition() { return {_position->x, _position->y, _position->z}; };
	std::tuple<float, float, float> getWorldPosition();
	void setScale(float x, float y, float z, bool propagate = true);
	void addScale(float x, float y, float z, bool propagate = true);
	std::tuple<float, float, float> getScale() { return { _scale->x, _scale->y, _scale->z }; };

	void setRotation(float x, float y, float z, bool propagate = true);
	void addRotation(float x, float y, float z, bool propagate = true);
	std::tuple<float, float, float> getRotation() { return { _rotation->x, _rotation->y, _rotation->z }; };

	float* matrix(bool recalculate = false, bool copy=false);
	float* matrixScale(float scale);
	float* matrixCompleteScale(float scale);
	void update();

	std::tuple<float, float, float>  getFordward();
	std::tuple<float, float, float>  getUp();

	void appendChild(Entity* child);
	void appendChild(Transform* child);
	void removeChild(Entity* child);
	void removeChild(Transform* child);

	float* rotationPivot(float x, float y, float z, float a, float b, float g);

	static void calculateMatrix(float * tranform, float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz, int modo=0);
	
	static void multMatrix(const float* a, int rowsA, int colsA, const float* b, int rowsB, int colsB, float* result);
	static std::tuple<float, float, float> calculateForwardVector(float x, float y, float z, float fx, float fy, float fz);
	static std::tuple<float, float, float, float, float, float>calculateForwardVector2(float x, float y, float z, float fx, float fy, float fz, float f2x, float f2y, float f2z);
	static std::tuple<float, float, float> crossProduct(float x1, float y1, float z1, float x2, float y2, float z2, bool normalize=false);
	//Crea la matriz invesa
	static bool inverseMatrix(float* in, float *out);
	void restoreState(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
	void setParent(Transform* parent);
	std::tuple<float, float, float> getHierarchicalPosition();
};

#endif // !__TRANSFORM
