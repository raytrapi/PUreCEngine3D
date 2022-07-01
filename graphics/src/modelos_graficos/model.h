#ifndef __MODELO_G
#define __MODELO_G
#include <log.h>
#include "../renderable/mesh.h"
#include "../motorExport.h"
#include "obj.h"
#include "fbx.h"
#include <string>
#include <vector>
//extern class Entity;
namespace renderable {
	//
	class EXPORTAR_MODULO_GRAFICO Model {
		//friend class renderable::model::Obj;
		private:
			/*static std::string trim(std::string cadena);
			static std::vector<std::string>  split(std::string cadena, char c = ' ');*/
		public:
			//virtual renderable::Mesh* load(std::string fileName) = 0;

			static std::vector<Entity *> load(const char* fileName);
			static std::vector<Entity*> load(const char * fileName,float directionY);
				
	};
};



#endif // !__MODELO_G
