#ifndef __MODELO_G
#define __MODELO_G
#include "../utiles/utilidades.h"
#include <mesh.h>
#include <string>
#include <vector>
namespace utiles {
	namespace model {
		class EXPORTAR_UTILIDADES Model {
		
		public:
			//virtual renderable::Mesh* load(std::string fileName) = 0;
			static std::string trim(std::string cadena);
			static std::vector<std::string>  split(std::string cadena, char c=' ');
		};
	}
};

#endif // !__MODELO_G
