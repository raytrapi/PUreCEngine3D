#ifndef __MODELO_OBJ
#define __MODELO_OBJ
#include "modelo.h"
#include "../components/src/entity.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <log.h>
namespace renderable {
	namespace model {
		class Obj {
		public:
			static std::vector<Entity*>* load(std::string fileName);
		};
	}
};

#endif // !__MODELO_OBJ
