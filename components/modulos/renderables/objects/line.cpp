#include "line.h"

renderable::Line::Line(std::vector<float*> points, float* color, float width, unsigned type) {
   ancho = width;
   //borrar();
   this->colores = new float[4]; //Guardamos alfa
   for (int i = 0; i < 4; i++) {
      this->colores[i] = color[i];
   }
   vertices = new float[points.size()*3];
   numeroVertices = points.size();
   int iComponente = 0;
   for (auto p = points.begin(); p != points.end(); p++) {
      
      for (int i = 0; i < 3; i++) {
         vertices[iComponente++]=(*p)[i];
      }
   }
   tipo = type;
   /*DBG("creamos línea");
   DBG("Cargamos shader");
   if (idShaderCompiled == -1) {
      modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
      idShaderVertex = g->loadShader("shaders/vertex_line.glsl", Graphics::Shader::TYPE_SHADER::VERTEX);
      idShaderFragment = g->loadShader("shaders/fragment_line.glsl", Graphics::Shader::TYPE_SHADER::FRAGMENT);
      std::vector<short> ids;
      ids.push_back(idShaderVertex);
      ids.push_back(idShaderFragment);
      idShaderCompiled=g->compileShader(&ids);
      
   }*/
   //shaders.compileShader();
}

renderable::Line::Line(float* points, unsigned countPoints, float* color, float width, unsigned type) {
    if (points == NULL) {
        return;
   }
   ancho = width;
   this->colores = new float[4]; //Guardamos alfa
   for (int i = 0; i < 4; i++) {
      this->colores[i] = color[i];
   }
   vertices = new float[countPoints *3];
   numeroVertices = countPoints;
   int iComponente = 0;
   for (int i = 0; i < numeroVertices; i++) {
      
      for (int j = 0; j < 3; j++) {
         vertices[iComponente]=points[iComponente];
         iComponente++;
      }
   }
   tipo = type;
}

renderable::Line::~Line() {
   borrar();
   DBG("destruimos línea");
}

void renderable::Line::borrar() {
   if (colores != NULL) {
      delete[]colores;
      
   }
   colores = NULL;
   
   borrarVertex();
}



renderable::Line* renderable::Line::create(std::vector<float*> points, float* color, float width) {
   Line* o = new Line(points, color, width);
   almacenar(o);
   return o;
}

int renderable::Line::getShaderId() {
   return idShaderCompiled;
}

void renderable::Line::setVertex(float* vertex, unsigned countVertex) {
   
   
   unsigned longitud = countVertex * 3;
   if (countVertex != numeroVertices) {
      borrarVertex();
      vertices = new float[longitud];
      numeroVertices = countVertex;
   }
   for(int i=0;i<longitud;i++){
      vertices[i] = vertex[i];
   }

}

int renderable::Line::idShaderVertex=-1;
int renderable::Line::idShaderFragment=-1;
int renderable::Line::idShaderCompiled = -1;