#ifndef _MESH
#define _MESH
#include <tuple>
#include "object.h"
#include "../../modules/graphic/motor.h"
#include "../../../src/exportar.h"
#include "../../../../utilidades/files/filesControl.h"
#include "../../../../utilidades/project/serializer/serializer.h"
#include "../../../../utilidades/project/serializer/deserializer.h"
#include "../../../../utilidades/imports/model.h"
namespace renderable {
	class EXPORTAR_COMPONENTE Mesh : public Object {
		void borrarCaras();
		
	private:
		void materialUpdated_I(Texture* texture, Material* material);
		UID uidObject = 0;
		bool interfazImGUI_C(ImGuiContext* imgui);
		int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
		void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false);
	public:

		Mesh();
		~Mesh();

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
		
		void setFaces(std::vector<std::vector<int>*>* faces, std::vector<float**>* vectors, std::vector<float**>* color, std::vector<float**>* normals = NULL, std::vector<float**>* uvs = NULL, renderable::Object::MODE_COLOR mode = renderable::Object::MODE_COLOR::COLOR);
		void setTriangles(std::vector<float**>* vectors, std::vector<float**>* color, std::vector<float**>* normals=NULL, std::vector<float**>* uvs=NULL, renderable::Object::MODE_COLOR mode= renderable::Object::MODE_COLOR::COLOR);
		void setTriangles(int triangles, float* vertex, float* colors = 0, float* normals = NULL, float* uvs = NULL, renderable::Object::MODE_COLOR mode = renderable::Object::MODE_COLOR::COLOR);
		void setObject(std::vector<float*>* vectors, std::vector<int>* indexes, std::vector<float**>* normals = NULL, float** color = NULL);
		

		void loadOBJ(const char* file);
		void setUID(UID uid) {uidObject = uid;};
		UID getUID() { return uidObject; };
		//void setTriangles(std::vector<vector3d *>);
	};
}
#endif // !_MESH
