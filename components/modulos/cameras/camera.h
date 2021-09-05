#ifndef __CAMERA
#define __CAMERA
#include "../../src/component.h"
#include "../../src/transform.h"
#include "../../src/exportar.h"
#include "../../../modules/src/module.h"
#include "../../../modules/graphic/motor.h"

class EXPORTAR_COMPONENTE Camera : public Component {
	friend class modules::graphics::Graphic;
	
protected:
	//Transform * transformada;
	//Transform* mirandoA;
	bool activa=false;
	bool focal = false;
	bool ortogonal=true;
	bool conCambio = false;
	
	//unsigned int ancho=2;
	//unsigned int alto=2;
	float derecha = 1.f;
	float izquierda = -1.f;
	float arriba = 1.f;
	float abajo = -1.f;
	float cerca = 1.f;
	float lejos = 50.f;
	float anguloFocal = 65.f;
	float vista[16] = { 1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f };
	float proyeccion[16] = { 1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f };
	float eye[3] = { 0.0f, 0.f, 1.f };//{ 0.f, 0.f, 2.f };
	float target[3] = { 0.0f, 0.0f, 0.0f };
	float up[3] = { 0.0f, 1.0f, 0.0f };
	float anguloCamara[3] = { 0.f,0.f,0.f };
	float distanciaObjetivo = 1.f;
	void ponerOrto();
	void ponerPerspectiva();
	void ponerVista();
	void ponerVista2();
	void actualizarProyeccion();
private:
	bool isChange();
public:
	Camera();
	~Camera();
	Transform * transform();
	bool isActive();
	void setActive(bool active);
	bool isOrtho();
	void setOrto(bool ortho);
	void setSize( float x,  float y, float width,  float height);
	void setDistance(float _near, float _far);
	void setFocalAngle(float angle);
	void setFocal(float focal);
	void setLookAt(float eyeX, float eyeY, float eyeZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);
	const float* getViewMatrix();
	const float* getProjectionMatrix();
	float getWidth();
	float getHeight();
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	const float getFocalAngle();
	void setPosX(float v);
	void setPosEyeX(float v);
	float getPosX();
	float getPosEyeX();
	void setPosY(float v);
	void setPosEyeY(float v);
	float getPosY();
	float getPosEyeY();
	void setPosZ(float v);
	void setPosEyeZ(float v);
	float getPosZ();
	float getPosEyeZ();

	float getRotX();
	float getRotY();
	float getRotZ();

	std::tuple<float, float> getNormalizeScreenExtra(double x, double y);
	std::tuple<float, float> getNormalizeScreen(double x, double y);

	void setRotate(float x, float y, float z);
	void refresh(int mode=1);
};
#endif // !__CAMERA
