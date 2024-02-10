#ifndef __BOX_COLLIDER
#define __BOX_COLLIDER
#include "../../../components/modulos/collider/collider.h"
#include "../../../components/src/entity.h"
//namespace collider {
class EXPORTAR_COMPONENTE BoxColliderComponent : public Collider {
	private:
		float w = 1.0f;
		float h = 1.0f;
		float d = 1.0f;
		std::string serializar();
	protected:
		bool interfazImGUI_C(ImGuiContext* imgui);
		int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
		void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
	public:

		BoxColliderComponent(Entity * entity, modules::graphics::Graphic* g, Component* p=NULL);
		~BoxColliderComponent();
		void setSize(float width, float height, float deph, bool withChangePhisics=true);
		std::tuple<float, float, float> getSize() { return { w,h,d }; };
		
		bool haveCollision(Collider* object);
		void refresh();
		std::vector<collider::Hit> getCollisions();
		std::vector<collider::Hit> getCollisionsExpanding(float x, float y, float z);
		std::vector<collider::Hit> getCollisions(float x, float y, float z);
		TYPE_OBJECT_SERIALIZABLES getType() { return TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_BOXCOLLIDER; };
};
//};
#endif // !__BOX_COLLIDER
