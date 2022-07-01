#ifndef __MODELO_FBX
#define __MODELO_FBX


#include <filesystem>
#include <iostream>
#include <fstream>
#include <log.h>
#include "../../components/src/entity.h"
#include "../../utilidades/utiles/string.h"
#include "../../../vendors/OpenFBX/src/ofbx.h"

//extern class Entity;
extern class Model;
namespace renderable {
	namespace model {
		class Fbx {
		public:
			static std::vector<Entity*> load(const char* fileName, float directionY = -1.0f);
			
		};
	}
};

#endif // !__MODELO_FBX
