#ifndef _TEXT
#define _TEXT

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../utilidades/global/screen.h"

#include <tuple>
#include "object.h"
#include "../../modules/graphic/motor.h"
#include "../motorExport.h"
#define LENGTH_TEXT_MAX 500
#include<map>
namespace renderable {
	class EXPORTAR_MODULO_GRAFICO Text : public Object {
		//int numCoordenadas =0; //Suponemos que normales y colores son por vertice.
		static std::map<const char*, std::tuple< FT_Library, FT_Face>> fuentesLetra;
		static unsigned numeroInstancias;
		FT_Library  libreriaParticular=0;
		FT_Face faceParticular=0;
		char* texto=new char[LENGTH_TEXT_MAX+1];
		int longitudTexto = 0;
		int tamañoLetra = 24;// 16;
		//unsigned anchoTexto = 0;
		//unsigned altoTexto = 0;
		float anchoTexto=0;
		float altoTexto = 0;

		FT_Library libreria;
		FT_Face face;

		float ancho = 300;
		float alto = 100;
		
		float rColor = 1.f;
		float gColor = 1.f;
		float bColor = 1.f;
		float aColor = 1.f;
		unsigned idMaterial = -1;
		std::tuple<unsigned, unsigned> pintarTexto();
		void setTriangles(std::vector<float**>* vectors, std::vector<float*>* color, std::vector<float**>* normals = NULL, float** uvs = NULL, renderable::Object::MODE_COLOR mode = renderable::Object::MODE_COLOR::COLOR);
		void borrarCaras();
	public:
		Object::TYPE getType() { return Object::TYPE::TEXT; };
		Text();
		/*Text(Entity* entity, modules::graphics::Graphic* g, Component* p)
		//RenderableComponent::RenderableComponent(Entity* entity, modules::graphics::Graphic* g, Component* p) {
			this->entidad = entity;
			this->graphic = g;

		};/**/
		~Text();
		std::tuple<unsigned, unsigned> setText(const char* text);
		void setColor(float r, float g, float b, float a);
		void setTextSize(int s);
		float getWidth() { return anchoTexto; };
		float getHeight() { return altoTexto; };

	};
}
#endif // !_TEXT
