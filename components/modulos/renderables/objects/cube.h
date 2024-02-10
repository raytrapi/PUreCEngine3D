#ifndef _CUBE
#define _CUBE

#include "object.h"
#include "../../../src/exportar.h"
extern class LoadLevel;
namespace renderable {
	class EXPORTAR_COMPONENTE Cube : public Object {
		float l=1;
		
		/*float transformacion[16] = {
			1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f,
		};/**/
		std::tuple<float, float, float, float> color = { 1.0f,1.0f,1.0f,1.0f };
		void crearCubo(float l = 1.0f, float r = 1.0f, float g = 1.0f, float b = 1.0f, float a = 1.0f);
		std::string serializar();
		friend class Object;
		friend class Entity;
		friend class RenderableComponent;
		friend class LoadLevel;
		int desserializar(std::string s, int pos=0);
		int idMaterilesCara[6] = { 0,0,0,0,0,0 };
		void recargarIdsCara();
	protected:
		friend class RenderableComponent;
		bool interfazImGUI_C(ImGuiContext* imgui);
		int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
		void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false);
		void  materialUpdated_I(Texture* texture, Material* material);
	public:
		
		Cube(RenderableComponent * parent=0);
		Object::TYPE getType() { return Object::TYPE::CUBE; };
		/*float r = 1;
		float g = 1;
		float b = 1;
		float a = 1;/**/
		void setSize(float length);
		float getSize();
		
	};
}
#endif // !_CUBE
