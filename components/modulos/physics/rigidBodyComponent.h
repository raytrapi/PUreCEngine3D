#ifndef __RIGID_BODY
#define __RIGID_BODY

#include "../../modules/physics/physics.h"
#include "../../src/entity.h"
//#include <wchar.h>
namespace physics {
	class EXPORTAR_COMPONENTE RigidBodyComponent : public Component {
	public:
		enum MODE {
			STATIC=0,
			DINAMIC,
			KINEMATIC
		};
	private:
		bool gravedad=false;
		modules::engine::Physics* fisicas=NULL;
		float masa=1;
		float friccion=0;
		float elasticidad=0;
		float angulo=0;
		float angulo_friccion=0;
		float angulo_elasticidad=0;
		//Velocidad
		float velocidad_x=0;
		float velocidad_y=0;
		float velocidad_z=0;
		std::string serializar();
		MODE modo = MODE::STATIC;
		static bool estatico;
		static int modoEstatico;
	protected:
		friend Entity;
		void setPhysics(modules::engine::Physics* physics) { this->fisicas = physics; };
		bool interfazImGUI_C(ImGuiContext* imgui);
		int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
		void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
	public:
		RigidBodyComponent(Entity* entity, modules::graphics::Graphic* g, Component* p = NULL);
		
		//modules::engine::Physics* getPhysics() { return fisicas; };
		bool isStatic() { return !gravedad; };
		bool hasGravity(){ return gravedad; };
		void setGravity(bool gravity) { gravedad = gravity; };
		
		std::tuple<float, float, float> getVelocity() {
			return { velocidad_x, velocidad_y, velocidad_z };
		};
		void setVelocity(float x, float y, float z) {
			velocidad_x = x;
			velocidad_y = y;
			velocidad_z = z;
		};
		void addVelocity(float x, float y, float z) { velocidad_x += x; velocidad_y += y; velocidad_z += z; };
		void transformChanged();
		MODE getMode() {return modo;};
		static bool itemGetterMode(void* data, int n, const char** out_str);
		TYPE_OBJECT_SERIALIZABLES getType() { return TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RIGIDBODY; };
	};
	
};

#endif // !__RIGID_BODY

