#ifndef __MODELO_FBX
#define __MODELO_FBX


#include <filesystem>
#include <iostream>
#include <fstream>
#include <log.h>
#include "../../utilidades/utiles/string.h"
#include "../../vendors/OpenFBX/src/ofbx.h"


//extern class Entity;
namespace imports {
	extern class ModelData;
	
	class Fbx {
	public:
		static std::vector<ModelData*> load(const char* fileName, float directionY = -1.0f);
			
	};
	
};

#endif // !__MODELO_FBX
