#ifndef _TYPE_SHADER
#define _TYPE_SHADER
#include "../../src/exportar.h"
namespace Graphics {
	namespace Shader {
		EXPORTAR_COMPONENTE enum TYPE_SHADER {
			NONE,
			COMPILE,
			VERTEX,
			FRAGMENT
		};
	}
}
#endif