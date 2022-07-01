#ifndef __STRING
#define __STRING
#include <string>
#include <vector>
#include "utilidades.h"
namespace utils {
	class EXPORTAR_UTILIDADES  String {
	public:
		static std::string trim(std::string cadena);
		static std::vector<std::string> split(std::string cadena, char c=' ');
	};
}
#endif // !__STRING
