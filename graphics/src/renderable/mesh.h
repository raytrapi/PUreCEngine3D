#ifndef _MESH
#define _MESH
#include <tuple>
#include "object.h"
#include "../../modules/graphic/motor.h"
#include "../motorExport.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Mesh : public Object {
		
		
	public:

		Mesh();

		void setMesh(float* mesh, float* normals = NULL, float* colors=NULL);
		Object::TYPE getType() { return Object::TYPE::MESH; };
		float r = 1;
		float g = 1;
		float b = 1;
		float a = 1;
		void setSize(float length);
		float getSize();
		//int getAllSize();
		//float* getMesh();
		//float* getNormals();
		//float* getColors();
		int* getIndexs();
		
		void setFaces(std::vector<std::vector<int>*>* faces, std::vector<float**>* vectors, std::vector<float*>* color, std::vector<float**>* normals = NULL, float** uvs = NULL, renderable::Object::MODE_COLOR mode = renderable::Object::MODE_COLOR::COLOR);
		void setTriangles(std::vector<float**>* vectors, std::vector<float*>* color, std::vector<float**>* normals=NULL, float** uvs=NULL, renderable::Object::MODE_COLOR mode= renderable::Object::MODE_COLOR::COLOR);
		void setObject(std::vector<float*>* vectors, std::vector<int>* indexes, std::vector<float**>* normals = NULL, float** color = NULL);
		

		void loadOBJ(const char* file);
		//void setTriangles(std::vector<vector3d *>);
	};
}
#endif // !_MESH
