#ifndef __MODELO_G
#define __MODELO_G
#include <log.h>
//#include "../renderable/mesh.h"
#include "../utiles/utilidades.h"
#include "obj.h"
#include "fbx.h"
#include <string>
#include <vector>
#include "../utiles/pointers.h"
//#include "../../components/modulos/renderables/objects/object.h"
//extern class Entity;



namespace imports {
	struct ModelData {
		char* name = 0;
		std::vector<float**>* triangles=0;
		std::vector<float**>* colors = 0;
		std::vector<float**>* normals = 0;
		std::vector<float**>* uvs=0;
		//renderable::Object::MODE_COLOR mode;
		int mode=0;
		void setName(const char* n) {
			COPY_CHAR(n, name);
		}
		~ModelData() {
			deleteMulti(triangles);
			triangles = NULL;
			
			deleteMulti(colors);
			colors = NULL;
			deleteMulti(normals);
			normals = NULL;
			deleteMulti(uvs);
			uvs = NULL;
			
			DELETE_MULTI(name);
		}
	private: 
		void deleteMulti(std::vector<float**>* p) {
			if (p) {
				auto l = p->size();
				for (int i = 0; i < l; i++) {
					delete[] p->operator[](i);
				}
				delete p;
			};
		}
	};
	//
	class EXPORTAR_UTILIDADES Model {
		//friend class renderable::model::Obj;
		private:
			/*static std::string trim(std::string cadena);
			static std::vector<std::string>  split(std::string cadena, char c = ' ');*/
		public:
			//virtual renderable::Mesh* load(std::string fileName) = 0;

			static std::vector<ModelData *> load(const char* fileName);
			static std::vector<ModelData *> load(const char * fileName,float directionY);
				
	};
};



#endif // !__MODELO_G
