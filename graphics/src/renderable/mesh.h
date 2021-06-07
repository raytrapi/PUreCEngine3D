#ifndef _MESH
#define _MESH

#include "object.h"
#include "../motorExport.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Mesh : public Object {
		int numCoordenadas =0; //Suponemos que normales y colores son por vertice.
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
		int getAllSize();
		float* getMesh();
		float* getNormals();
		float* getColors();
		int* getIndexs();
		int getVertexNumber();
		void setTriangles(std::vector<float**>* vectors, float ** color, std::vector<float**>* normals=NULL);
		//void setTriangles(std::vector<vector3d *>);
	};
}
#endif // !_MESH
