#ifndef __RIGID_BODY
#define __RIGID_BODY

#include "../../modules/physics/physics.h"
#include "../../src/entity.h"
namespace physics {
	class EXPORTAR_COMPONENTE RigidBody : public Component {
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
	protected:
		friend Entity;
		void setPhysics(modules::engine::Physics* physics) { this->fisicas = physics; };
		
	public:
		RigidBody(Entity* entity, modules::graphics::Graphic* g, Component* p = NULL);
		
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
	};
	
};

#endif // !__RIGID_BODY

