#ifndef __MODELO_OBJ
#define __MODELO_OBJ
#include "modelo.h"
#include <filesystem>
#include <iostream>
#include <fstream>
#include <array>
#include "../log/log.h"
namespace utiles {
	namespace model {
		class EXPORTAR_UTILIDADES Obj:public Model {
		public:
			static std::vector<Entity*>* load(std::string fileName);
		};
	}
};

#endif // !__MODELO_OBJ
