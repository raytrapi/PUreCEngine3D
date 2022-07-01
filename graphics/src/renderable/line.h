#ifndef _LINE
#define _LINE

#include "object.h"
#include "../motorExport.h"
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Line : public Object {
		//float* puntos=NULL;
		
		//float* color=NULL;
		float ancho;
		void borrar();
		
		static int idShaderVertex;
		static int idShaderFragment;
		static int idShaderCompiled;
		unsigned tipo = 1;
		
	public:
		Line(std::vector<float*> points, float* color, float width = 1.f, unsigned style=1);
		Line(float* points, unsigned countPoints, float* color, float width = 1.f, unsigned style = 1);
		~Line();
		Object::TYPE getType() { return Object::TYPE::LINE; };
		
		int getNumberPoints() { return numeroVertices; };
		float* getPoints() { return vertices; };
		//float* getColours() { return color; };
		
		unsigned getStyle() { return tipo; }
		/**
		* 
		* crea una línea en pantalla - new line
		* 
		* @param points vector[float[3]] coord 3d the points
		* @param color float[3] r,g,b
		*/
		static Line* create(std::vector<float*> points, float* color, float width=1.f);
		static void destroy(Line* line);
		static int getShaderId();
		void setVertex(float* vertex, unsigned countVertex);



	};
}
#endif // !_LINE
