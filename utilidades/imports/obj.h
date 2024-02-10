#ifndef __MODELO_OBJ
#define __MODELO_OBJ


#include <filesystem>
#include <iostream>
#include <fstream>
#include <log.h>
#include "../../utilidades/utiles/string.h"

//extern class Entity;
namespace imports {
	extern class ModelData;
	
	class EXPORTAR_UTILIDADES Obj {
	public:
		//static std::vector<std::tuple<renderable::Object*, std::string>> createObjects(const char* fileName, float directionY = -1.0f);
		static std::vector<ModelData*> load(const char* fileName, float directionY = -1.0f);
		//static std::vector<ModelData*> load2(const char* fileName, float directionY = -1.0f);


		static void createThumbnail(const char* path);
	};
	
};

#endif // !__MODELO_OBJ
