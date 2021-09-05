#ifndef __MODELO_G
#define __MODELO_G
#include <log.h>
#include "../renderable/mesh.h"
#include "../components/src/entity.h"
#include "obj.h"
#include <string>
#include <vector>
namespace renderable {
	namespace model {
		class EXPORTAR_UTILIDADES Model {
			friend class Obj;
			private:
				static std::string trim(std::string cadena);
				static std::vector<std::string>  split(std::string cadena, char c = ' ');
			public:
				//virtual renderable::Mesh* load(std::string fileName) = 0;
				static std::vector<Entity*>* load(std::string fileName,float directionY=-1.0f);
		};
	}
};

#endif // !__MODELO_G
