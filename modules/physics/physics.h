/**
* Clase para la gestión de físicas en el motor
* Class to handle the physics in the engine
* */
#ifndef _PHYSICS
#define _PHYSICS
#include "../src/module.h"
#include "../../utilidades/global/global.h"

//#include "../../components/src/entity.h"
//#include "../graphic/motor.h"
namespace graphics {
	extern class Graphic;

}

extern class Entity;
extern class Collider;
namespace physics {
	extern class RigidBodyComponent;
}
namespace modules {
	namespace engine {
		class EXPORTAR_MODULO Physics : public Module {
			bool conGravedad = true;

		protected:
			float gravedad = -9.80665f;
			float densidad = 0.01f; //Densidad Aire
			Entity* entidades = NULL;
			friend graphics::Graphic;
			void setEntities(Entity* e) { entidades = e; };
			Global *global;
			void setGlobal(Global * g) { global = g; };
		public:
			Module::MODULES_TYPE tipo() { return Module::MODULES_TYPE::PHYSICS; };
			void setHaveGravity(bool g) { conGravedad = g; };
			bool haveGravity() { return conGravedad; };
			bool isStatic() { return !conGravedad; };

			void setGravity(float g) { gravedad = g; };
			float getGravity() { return gravedad; };

			static std::tuple<float, float, float> getNormal(float x, float y, float z);
			static float getMagnitude(float x, float y, float z);

			//Se encarga de lanzar las físicas de todos los objetos //Launch the physics of all objects
			virtual void pause() {};
			virtual void resume() {};
			virtual void update() = 0;
			virtual void appendRigidBody(physics::RigidBodyComponent*) {};
			virtual void appendCollider(Collider*) {};
			virtual void changeCollider(Collider*) {};
			virtual void changeRigidBody(physics::RigidBodyComponent*) {};
			virtual void transformChanged(physics::RigidBodyComponent*) {};
			static void TraceImpl(const char* inFMT, ...);
			static bool AssertFailedImpl(const char* inExpression, const char* inMessage, const char* inFile, unsigned int inLine);
			
		};

	}
}



#endif // !_PHYSICS