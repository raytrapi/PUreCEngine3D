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
	Transform * transformada;
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
	float anguloFocal = 1.04719758f;
	float vista[16] = { 1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f };
	float vistaGuizmo[16] = { 1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f };
	float proyeccion[16] = { 1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f };
	float inverseVista[16];
	bool mirandoPuntoFijo = false;
	float eye[3] = { 0.0f, 0.f, 1.f };//{ 0.f, 0.f, 2.f };
	float target[3] = { 0.0f, 0.0f, 0.0f };
	float up[3] = { 0.0f, 1.0f, 0.0f };
	
	float anguloCamara[3] = { 0.f,0.f,0.f };
	float distanciaObjetivo = 1.f;
	void ponerOrto();
	void ponerPerspectiva();
	void ponerVista();
	void ponerVistaGuizmo();
	void ponerVista2();
	void actualizarProyeccion();
	void recalcularObjetivo(); //Se encargará de calcular nuevamente el objetivo
private:
	bool isChange(bool reset=true);
protected:
	bool interfazImGUI_C(ImGuiContext* imgui);
	int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
	void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
public:
	Camera(Entity* e, modules::graphics::Graphic* g, Component* p = NULL) :Component(e, g, p) { if (e == NULL) { transformada = new Transform(e); } };
	virtual ~Camera();
	Transform * transform();
	const float* getViewMatrix();
	float* getViewMatrixGuizmo();
	const float* getProjectionMatrix();
	const float* getInverseViewMatrix();
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
	std::tuple<float,float,float> getPositionTarget();
	float getPosY();
	float getPosEyeY();
	float getPosZ();
	float getPosEyeZ();

	float getRotX();
	float getRotY();
	float getRotZ();

	bool isActive();
	bool isOrtho();
	bool isFixedTarget() { return mirandoPuntoFijo; };



	void setActive(bool active);
	void setOrto(bool ortho);
	void setSize( float x,  float y, float width,  float height);
	void setDistance(float _near, float _far);
	void setFocalAngle(float angle);
	void setFocal(float focal);
	void setLookAt(float eyeX, float eyeY, float eyeZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ);
	void setFixedTarget(bool fixed) { mirandoPuntoFijo = fixed; };
	void setPositionTarget(float x, float y, float z);
	void setPosY(float v);
	void setPosEyeY(float v);
	void setPosZ(float v);
	void setPosEyeZ(float v);
	void setChange(bool change) { this->conCambio = change; };

	std::tuple<float, float, float> getPosition() {
		if (transform()) { return { eye[0], eye[1], eye[2] }; } else { return { 0,0,0 }; }
	
	}
	std::tuple<float, float, float> getScale() {
		if (transform()) { return transform()->getScale(); } else { return { 0,0,0 }; }
	}
	std::tuple<float, float, float> getRotation() {
		if (transform()) { return transform()->getRotation(); } else { return { 0,0,0 }; }
	}

	std::tuple<float, float> getNormalizeScreenExtra(double x, double y);
	std::tuple<float, float> getNormalizeScreen(double x, double y);
	
	void move(float incX, float incY, float incZ, float complete = true);

	void setRotate(float x, float y, float z);
	void refresh(int mode=1);

	void transformChanged();
	TYPE_OBJECT_SERIALIZABLES getType() { return TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_CAMERA; };
};
#endif // !__CAMERA
