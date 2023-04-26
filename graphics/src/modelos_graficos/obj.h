#ifndef __MODELO_OBJ
#define __MODELO_OBJ


#include <filesystem>
#include <iostream>
#include <fstream>
#include <log.h>
#include "../../components/src/entity.h"
#include "../../utilidades/utiles/string.h"

//extern class Entity;
extern class Model;
namespace renderable {
	namespace model {
		class Obj {
		public:
			static std::vector<Entity*> load(const char* fileName, float directionY = -1.0f);
			static std::vector<Entity*> load2(const char* fileName, float directionY = -1.0f);
		};
	}
};

#endif // !__MODELO_OBJ
