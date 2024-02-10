#ifndef _COMP_LUZ
#define _COMP_LUZ

#include <vector>
#include <cmath>
#include <iostream>
#include <limits>
#include "../renderables/renderableComponent.h"

	//namespace compon {
	namespace modules {
		namespace engine {
			extern class Physics;
		}
	}

	class EXPORTAR_COMPONENTE LightComponent : public Component {
	public:
		std::string serializar();
	private:
		bool cargarTextura = true;
		float matrizGizmo[16];

		float r = 1.0;
		float g = 1.0;
		float b = 1.0;
		float a = 1.0;
		

		float derecha = 10.f;
		float izquierda = -10.f;
		float arriba = 10.f;
		float abajo = -10.f;
		float cerca = 0.001f;
		float lejos = 350.f;
		float vista[16] = { 1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f }; 
		float proyeccion[16] = { 1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f };
		float vista_proyeccion[16] = { 1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f,0.f,0.f,0.f,0.f,1.f };
		float eye[3] = { 0.0f, 0.f, 0.f };//{ 0.f, 0.f, 2.f };
		float target[3] = { 0.0f, 0.0f, 0.0f };
		float up[3] = { 0.0f, 1.0f, 0.0f };
		float anguloCamara[3] = { 0.f,0.f,0.f };
		float distanciaObjetivo = 100.f;

		unsigned int profundidadFBO = 0;
		unsigned int profundidadTextura2D = 0;
		const unsigned int anchoTextura2D = 1024;
		const unsigned int altoTextura2D = 1024;
		void calcularVistaProyeccion();
	protected:
		int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
		void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
	public:
		LightComponent(Entity* entity, modules::graphics::Graphic* g, Component * p=NULL);
		
		~LightComponent() {
			
		}
		bool loadTexture() { if (cargarTextura) { cargarTextura = false; return true; }; return false; };

		float* getMatrixGizmo() {return matrizGizmo;};
		void updateGizmo();
		void transformChanged();
		std::tuple<float, float, float, float> getColor() { return { r,g,b,a }; };

		unsigned int getFBO() {
			return profundidadFBO;
		}
		unsigned int getTexture(){
			return profundidadTextura2D;
		}
		unsigned int profundidadFBO_DBG = 0;
		unsigned int profundidadTextura2D_DBG = 0;
		unsigned int VAO_DBG = 0;
		unsigned int VBO_DBG = 0;
		const float* getViewProjectMatrix(int view=0);
		const float* getViewMatrix(int view = 0);
		const float* getProjectMatrix();
		std::string getName()override { return "luz"; } ;
		TYPE_OBJECT_SERIALIZABLES getType() { return TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_LUZ; };
	};

#endif // !_COMP_LUZ

