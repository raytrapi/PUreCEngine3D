#ifndef _RECURSOS
#define _RECURSOS


#include "../src/module.h"
#include "../../components/modulos/shader/types.h"
#include "../graphic/motor.h"
//#include "../../components/src/entity.h"
#include "../../components/modulos/renderables/resources/texture.h"
#include <list>
#include <vector>
#include <map>
#include <tuple>
#include <string>
#include <tuple>
//#include "../../graphics/src/renderable/object.h"


extern class Camera;
namespace modules {
	namespace resources {
		
		class EXPORTAR_MODULO Resource:public Module {
			public:
				Module::MODULES_TYPE tipo() { return Module::MODULES_TYPE::RESOURCES; };
				virtual std::tuple<float*, int, int, unsigned int, TextureImg::FORMAT_COLOR> loadImage(const char *,bool inverse=true)=0;
		};

	}
}

#endif // 