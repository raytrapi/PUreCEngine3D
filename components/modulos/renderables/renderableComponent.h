#ifndef _COMP_REND
#define _COMP_REND

#include "../../src/exportar.h"
#include "../../src/component.h"
//#include "../../../modules/src/module.h"
#include "../shader/shaderComponent.h"
//#include "resources/material.h"
#include "../../../components/modulos/renderables/resources/material.h"

#include "objects/object.h"
#include "objects/img.h"
#include <vector>
#include <type_traits>
#include "../utiles/string.h"

//#include "../../../utilidades/utiles/mathConsts.h"


class EXPORTAR_COMPONENTE RenderableComponent : public Component {
private:
	renderable::Object  * objeto=NULL; 
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
	bool visible = false;
	std::string serializar();
	int desserializar(std::string s, int pos = 0);
protected:
	bool interfazImGUI_C(ImGuiContext* imgui);
	int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
	void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
	//std::vector<std::tuple<renderable::Object*, std::string>> createObjects(const char* fileName, float directionY=1);
public:

	RenderableComponent(Entity* entity, modules::graphics::Graphic* g,Component*p=NULL);
	~RenderableComponent();
	renderable::Object* getRenderable() { return objeto; };
	template <class T>
	T* getRenderable();
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
	bool isVisible() { return visible; };
	void update();
	void setUpdated(bool update);
	void setUV(int pos, float u, float v);
	std::vector<std::vector<const float*>>* getFaces();
	Material * setMaterial(UID uid, unsigned int pos=0);
	template<class T>
	T* add(renderable::Object* o=NULL);

	TYPE_OBJECT_SERIALIZABLES getType() { return TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RENDERABLE; };
	std::vector<Material*> getMaterials();
	

};

template <class T>
inline T* RenderableComponent::getRenderable() {
	if (objeto==0) {
		objeto = new T();
	}
	return (T*)objeto;
};

#endif // !_COMP_REND

