#include "cube.h"
#include "../renderableComponent.h"
#include "../../../utilidades/project/genericFile.h"
void renderable::Cube::crearCubo(float l, float r, float g, float b, float a) {
   borrarMesh();
   modoColor = COLOR;
   numeroVertices = 36; //12 triangulos por 3 vertices
   numCoordenadas = numeroVertices * 13; //3+3+4+2+1 (3 coordenadas + 3 normales + 4 color + 2 uv + 1 idTextura
   int numComponentes = numeroVertices * 3;
   vertices = new float[numComponentes];
   normales = new float[numComponentes];
   colores = new float[numeroVertices * 4];
   uvs = new float[numeroVertices * 2];
   numeroModosColor = 1;
   

   modosColor = new MODE_COLOR[numeroModosColor];
   
   
   
   float mL = l / 2.0f; //Cogemos la mitad del cubo
   //Tiene 6 caras, 2 triangulos por cara y 3 vertices por triangulo y 3 coordenadas =6*2*3*3 = 108
   //vertices = new float[];//108
   //normales = new float[108];
   
   //FRENTE (Mirando a nosotros)
   vertices[0] = +mL; vertices[1] = mL; vertices[2] = -mL;
   normales[0] = 0.0f; normales[1] = 0.0f; normales[2] = -1.f;
   vertices[3] = -mL; vertices[4] = mL; vertices[5] = -mL;
   normales[3] = 0.0f; normales[4] = 0.0f; normales[5] = -1.f;
   vertices[6] = -mL; vertices[7] = -mL; vertices[8] = -mL;
   normales[6] = 0.0f; normales[7] = 0.0f; normales[8] = -1.f;
   vertices[9] = mL; vertices[10] = mL; vertices[11] = -mL;
   normales[9] = 0.0f; normales[10] = 0.0f; normales[11] = -1.f;
   vertices[12] = -mL; vertices[13] = -mL; vertices[14] = -mL; 
   normales[12] = 0.0f; normales[13] = 0.0f; normales[14] = -1.f;
   vertices[15] = mL; vertices[16] = -mL; vertices[17] = -mL; 
   normales[15] = 0.0f; normales[16] = 0.0f; normales[17] = -1.f;

   //TRASERA
   vertices[18] = mL; vertices[19] = mL; vertices[20] = mL;
   normales[18] = 0.f; normales[19] = 0.0f; normales[20] = 1.0f;
   vertices[21] = mL; vertices[22] = -mL; vertices[23] = mL;
   normales[21] = 0.f; normales[22] = 0.0f; normales[23] = 1.0f;
   vertices[24] = -mL; vertices[25] = -mL; vertices[26] = mL;
   normales[24] = 0.f; normales[25] = 0.0f; normales[26] = 1.0f;

   vertices[27] = mL; vertices[28] = mL; vertices[29] = mL;
   normales[27] = 0.f; normales[28] = 0.0f; normales[29] = 1.0f;
   vertices[30] = -mL; vertices[31] = -mL; vertices[32] = mL;
   normales[30] = 0.f; normales[31] = 0.0f; normales[32] = 1.0f;
   vertices[33] = -mL; vertices[34] = mL; vertices[35] = mL;
   normales[33] = 0.f; normales[34] = 0.0f; normales[35] = 1.0f;

   //ARRIBA
   vertices[36] = -mL; vertices[37] = mL; vertices[38] = -mL;
   normales[36] = 0.0f; normales[37] = 1.f; normales[38] = 0.0f;
   vertices[39] = mL; vertices[40] = mL; vertices[41] = -mL;
   normales[39] = 0.0f; normales[40] = 1.f; normales[41] = 0.0f;
   vertices[42] = mL; vertices[43] = mL; vertices[44] = mL;
   normales[42] = 0.0f; normales[43] = 1.f; normales[44] = 0.0f;
   vertices[45] = -mL; vertices[46] = mL; vertices[47] = -mL;
   normales[45] = 0.0f; normales[46] = 1.f; normales[47] = 0.0f;
   vertices[48] = mL; vertices[49] = mL; vertices[50] = mL;
   normales[48] = 0.0f; normales[49] = 1.f; normales[50] = 0.0f;
   vertices[51] = -mL; vertices[52] = mL; vertices[53] = mL;
   normales[51] = 0.0f; normales[52] = 1.f; normales[53] = 0.0f;

   //IZQUIERDA
   vertices[54] = -mL; vertices[55] = mL; vertices[56] = mL;
   normales[54] = -1.f; normales[55] = 0.0f; normales[56] = 0.0f;
   vertices[57] = -mL; vertices[58] = -mL; vertices[59] = mL;
   normales[57] = -1.f; normales[58] = 0.0f; normales[59] = 0.0f;
   vertices[60] = -mL; vertices[61] = -mL; vertices[62] = -mL;
   normales[60] = -1.f; normales[61] = 0.0f; normales[62] = 0.0f;
   vertices[63] = -mL; vertices[64] = mL; vertices[65] = mL;
   normales[63] = -1.f; normales[64] = 0.0f; normales[65] = 0.0f;
   vertices[66] = -mL; vertices[67] = -mL; vertices[68] = -mL;
   normales[66] = -1.f; normales[67] = 0.0f; normales[68] = 0.0f;
   vertices[69] = -mL; vertices[70] = mL; vertices[71] = -mL;
   normales[69] = -1.f; normales[70] = 0.0f; normales[71] = 0.0f;

   //ABAJO
   vertices[72] = mL; vertices[73] = -mL; vertices[74] = -mL;
   normales[72] = 0.0f; normales[73] = -1.f; normales[74] = 0.0f;
   vertices[75] = -mL; vertices[76] = -mL; vertices[77] = -mL;
   normales[75] = 0.0f; normales[76] = -1.f; normales[77] = 0.0f;
   vertices[78] = -mL; vertices[79] = -mL; vertices[80] = mL;
   normales[78] = 0.0f; normales[79] = -1.f; normales[80] = 0.0f;
   vertices[81] = mL; vertices[82] = -mL; vertices[83] = -mL;
   normales[81] = 0.0f; normales[82] = -1.f; normales[83] = 0.0f;
   vertices[84] = -mL; vertices[85] = -mL; vertices[86] = mL;
   normales[84] = 0.0f; normales[85] = -1.f; normales[86] = 0.0f;
   vertices[87] = mL; vertices[88] = -mL; vertices[89] = mL;
   normales[87] = 0.0f; normales[88] = -1.f; normales[89] = 0.0f;

   //DERECHA
   vertices[90] = mL; vertices[91] = mL; vertices[92] = -mL;
   normales[90] = 1.0f; normales[91] = 0.0f; normales[92] = 0.f;
   vertices[93] = mL; vertices[94] = -mL; vertices[95] = -mL;
   normales[93] = 1.0f; normales[94] = 0.0f; normales[95] = 0.f;
   vertices[96] = mL; vertices[97] = -mL; vertices[98] = mL;
   normales[96] = 1.0f; normales[97] = 0.0f; normales[98] = 0.f;
   vertices[99] = mL; vertices[100] = mL; vertices[101] = -mL;
   normales[99] = 1.0f; normales[100] = 0.0f; normales[101] = 0.f;
   vertices[102] = mL; vertices[103] = -mL; vertices[104] = mL;
   normales[102] = 1.0f; normales[103] = 0.0f; normales[104] = 0.f;
   vertices[105] = mL; vertices[106] = mL; vertices[107] = mL;
   normales[105] = 1.0f; normales[106] = 0.0f; normales[107] = 0.f;/**/
   
   
   

   //Ponemos colores para cada cara
   int iColor = 0;
   int iUV = 0;
   
   for (int i = 0; i < 6; i++) {
      colores[iColor++] = 1.0f; colores[iColor++] = 1.0f; colores[iColor++] = 1.0f; colores[iColor++] = 1.0f;
   }
   for (int i = 0; i < 6; i++) {
      colores[iColor++] = 1.0f; colores[iColor++] = 0.0f; colores[iColor++] = 0.0f; colores[iColor++] = 1.0f;
   }
   for (int i = 0; i < 6; i++) {
      colores[iColor++] = 1.0f; colores[iColor++] = 1.0f; colores[iColor++] = 1.0f; colores[iColor++] = 1.0f;
   }
   for (int i = 0; i < 6; i++) {
      colores[iColor++] = 1.0f; colores[iColor++] = 1.0f; colores[iColor++] = 1.0f; colores[iColor++] = 1.0f;
   }
   for (int i = 0; i < 6; i++) {
      colores[iColor++] = 1.0f; colores[iColor++] = 1.0f; colores[iColor++] = 1.0f; colores[iColor++] = 1.0f;
   }
   for (int i = 0; i < 3; i++) {
      colores[iColor++] = 0.0f; colores[iColor++] = 0.5f; colores[iColor++] = 0.0f; colores[iColor++] = 1.0f;
   }
   for (int i = 0; i < 3; i++) {
      colores[iColor++] = 0.0f; colores[iColor++] = 1.0f; colores[iColor++] = 0.0f; colores[iColor++] = 1.0f;
   }/**/
   /*for (int i = 0; i < numeroVertices; i++) {
      colores[iColor++] = r; colores[iColor++] = g; colores[iColor++] = b; colores[iColor++] = a;
   }*/
   iUV = 0;
   for (int i = 0; i < 6; i++) {
      uvs[iUV++] = 1.0f; uvs[iUV++] = 1.0f;
      uvs[iUV++] = 0.0f; uvs[iUV++] = 1.0f;
      uvs[iUV++] = 0.0f; uvs[iUV++] = 0.0f;
      uvs[iUV++] = 1.0f; uvs[iUV++] = 1.0f;
      uvs[iUV++] = 0.0f; uvs[iUV++] = 0.0f;
      uvs[iUV++] = 1.0f; uvs[iUV++] = 0.0f;
   }
   //modosColor[0] = MODE_COLOR::TEXTURE;

   //Cargamos los materiales;
   if (idsMateriales == NULL) {
       idsMateriales = new float[numeroVertices];
   }
   recargarIdsCara();
   cambio = true;
   
   /*RenderableComponent* renderizador = getRenderable();
   if (renderizador) {
      renderizador->setUpdated(true);
   }/**/
   
}

renderable::Cube::Cube(RenderableComponent* r) {
    crearCubo(l);
    //malla = new float[32];
    renderizador = r;
}


void renderable::Cube::setSize(float length) {
    l = length;
}

float renderable::Cube::getSize() {
    return l;
}
void renderable::Cube::recargarIdsCara() {
    int idMaterial = -1;
    for (int i = 0; i < numeroVertices; i++) {
        if (i % 6 == 0) {
            idMaterial++;
        }
        idsMateriales[i] = (float)idMaterilesCara[idMaterial];
    }
    cambio = true;
    

}

std::string renderable::Cube::serializar() {
   std::string resultado="{\r\n";
   resultado += GenericFile::serializate("tipo", (int)Object::TYPE::CUBE);
   resultado += GenericFile::serializate("color", color, false);
   return resultado+"}\r\n";
};
int renderable::Cube::desserializar(std::string s, int pos) {
   while (pos < s.length()) {
      auto [posT, clave, valor] = GenericFile::unserializate(s, pos + 1);
      pos = posT;
      if (clave == "color") {
         
         this->color= GenericFile::unserializate4f(valor);
      }
   }
   return pos;
}
bool renderable::Cube::interfazImGUI_C(ImGuiContext* imgui) {
    ImGui::TableNextRow();
    ImGui::TableNextColumn();
    ImGui::Text("Caras");
    ImGui::TableNextColumn();
    bool abierto = ImGui::CollapsingHeader("Materiales");
    char* nombreInput = new char[6] {'#', '#', 'I', 'I', '0', '\0'};
    if (abierto) {
        ImGui::BeginTable("##MCaras", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable);
        for (int i = 0; i < 6; i++) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text("Id Material");
            ImGui::TableNextColumn();
            nombreInput[4] = (char)(48 + i);
            if (ImGui::InputInt(nombreInput, &(idMaterilesCara[i]))) {
                recargarIdsCara();
            }
        }
        ImGui::EndTable();
    }
    return true;
   //Pintamos el color del cubo
   /*ImGui::SetCurrentContext(imgui);
   ImGui::TableNextRow();
   ImGui::TableNextColumn();
   ImGui::Text("Color");
   ImGui::TableNextColumn();
   float elColor[4] = {std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color)};
   if (ImGui::ColorEdit4("##colorCubo", elColor)) {
      std::get<0>(color) = elColor[0];
      std::get<1>(color) = elColor[1]; 
      std::get<2>(color) = elColor[2]; 
      std::get<3>(color) = elColor[3];
      int idColor = 0;
      for (int i = 0; i < numeroVertices; i++) {
         colores[idColor++] = elColor[0];
         colores[idColor++] = elColor[1];
         colores[idColor++] = elColor[2];
         colores[idColor++] = elColor[3];
         if (renderizador) {
            renderizador->update();
         }
      }
   }/**/
   return true;
}
int renderable::Cube::saveState_interno(std::vector<unsigned char>* data, bool withID) {
   int longitud = 0;
   longitud += Serializer::serialize(data, (int)Object::TYPE::CUBE);
   longitud += Serializer::serialize(data, std::get<0>(color), std::get<1>(color), std::get<2>(color), std::get<3>(color));
   return longitud;
};
void renderable::Cube::restoreState_interno(std::vector<unsigned char>* data, bool withID) {
   Deserializer::deserialize(&std::get<0>(color));
   Deserializer::deserialize(&std::get<1>(color));
   Deserializer::deserialize(&std::get<2>(color));
   Deserializer::deserialize(&std::get<3>(color));
};

void renderable::Cube::materialUpdated_I(Texture* texture, Material* material) {
    if (texture) {
        int iUV = 0;
        auto [u1, v1, u2, v2]=texture->getUV();
        for (int i = 0; i < 6; i++) {
            uvs[iUV++] = u2; uvs[iUV++] = v1;
            uvs[iUV++] = u1; uvs[iUV++] = v1;
            uvs[iUV++] = u1; uvs[iUV++] = v2;
            uvs[iUV++] = u2; uvs[iUV++] = v1;
            uvs[iUV++] = u1; uvs[iUV++] = v2;
            uvs[iUV++] = u2; uvs[iUV++] = v2;
        }
        modoColor = TEXTURE;
        modosColor[0] = TEXTURE;
    }
    if (material) {
       auto col = material->getAmbient();
       if (col && colores) {
          int k = 0;
          for (int i = 0; i < numeroVertices; i++) {
             colores[k++] = col[0];
             colores[k++] = col[1];
             colores[k++] = col[2];
             colores[k++] = col[3];
          }
       }
       modoColor = material->getTextures()->size() == 0 ? COLOR : TEXTURE;
       modosColor[0] = material->getTextures()->size() == 0 ? COLOR : TEXTURE;
    }

};