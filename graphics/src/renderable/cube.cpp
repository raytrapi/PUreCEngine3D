#include "cube.h"

void renderable::Cube::crearCubo(float l) {
   float mL = l * 0.5f; //Cogemos la mitad del cubo
   //Tiene 6 caras, 2 triangulos por cara y 3 vertices por triangulo y 3 coordenadas =6*2*3*3 = 108
   vertices = new float[108];
   normales = new float[108];
   //FRENTE
      //Superior izquierda
         //derecha arriba frente 0
   vertices[0] = mL; vertices[1] = mL; vertices[2] = mL;
   normales[0] = 0.0f; normales[1] = 0.0f; normales[2] = 1.f;
         //derecha abajo frente 1
   vertices[3] = mL; vertices[4] = -mL; vertices[5] = mL;
   normales[3] = 0.0f; normales[4] = 0.0f; normales[5] = 1.f;
         //izquiera arriba frente 3
   vertices[6] = -mL; vertices[7] = mL; vertices[8] = mL;
   normales[6] = 0.0f; normales[7] = 0.0f; normales[8] = 1.f;
   //Superior derecho
      //izquiera arriba frente 3
   vertices[9] = -mL; vertices[10] = mL; vertices[11] = mL;
   normales[9] = 0.0f; normales[10] = 0.0f; normales[11] = 1.f;
      //izquierda abajo frente 2
   vertices[12] = -mL; vertices[13] = -mL; vertices[14] = mL; 
   normales[12] = 0.0f; normales[13] = 0.0f; normales[14] = 1.f;
      //derecha abajo frente 1
   vertices[15] = mL; vertices[16] = -mL; vertices[17] = mL; 
   normales[15] = 0.0f; normales[16] = 0.0f; normales[17] = 1.f;

   //DERECHA
      //derecha arriba frente 0
   vertices[18] = mL; vertices[19] = mL; vertices[20] = mL; 
   normales[18] = 1.f; normales[19] = 0.0f; normales[20] = 0.0f;
      //derecha abajo frente 1
   vertices[21] = mL; vertices[22] = -mL; vertices[23] = mL; 
   normales[21] = 1.f; normales[22] = 0.0f; normales[23] = 0.0f;
      //derecha arriba trasara 4
   vertices[24] = mL; vertices[25] = mL; vertices[26] = -mL;
   normales[24] = 1.f; normales[25] = 0.0f; normales[26] = 0.0f;
      //derecha arriba trasara 4
   vertices[27] = mL; vertices[28] = mL; vertices[29] = -mL;
   normales[27] = 1.f; normales[28] = 0.0f; normales[29] = 0.0f;
      //derecha abajo trasara 5
   vertices[30] = mL; vertices[31] = -mL; vertices[32] = -mL;
   normales[30] = 1.f; normales[31] = 0.0f; normales[32] = 0.0f;
      //derecha abajo frente 1
   vertices[33] = mL; vertices[34] = -mL; vertices[35] = mL;
   normales[33] = 1.f; normales[34] = 0.0f; normales[35] = 0.0f;
   //ARRIBA
      //derecha arriba frente 0
   vertices[36] = mL; vertices[37] = mL; vertices[38] = mL;
   normales[36] = 0.0f; normales[37] = 1.f; normales[38] = 0.0f;
      //derecha arriba trasara 4
   vertices[39] = mL; vertices[40] = mL; vertices[41] = -mL;
   normales[39] = 0.0f; normales[40] = 1.f; normales[41] = 0.0f;
      //izquiera arriba trasera 7
   vertices[42] = -mL; vertices[43] = mL; vertices[44] = -mL;
   normales[42] = 0.0f; normales[43] = 1.f; normales[44] = 0.0f;
      //izquiera arriba trasera 7
   vertices[45] = -mL; vertices[46] = mL; vertices[47] = -mL;
   normales[45] = 0.0f; normales[46] = 1.f; normales[47] = 0.0f;
      //izquierda arriba frente 0
   vertices[48] = -mL; vertices[49] = mL; vertices[50] = mL;
   normales[48] = 0.0f; normales[49] = 1.f; normales[50] = 0.0f;
      //derecha arriba frente 0
   vertices[51] = mL; vertices[52] = mL; vertices[53] = mL;
   normales[51] = 0.0f; normales[52] = 1.f; normales[53] = 0.0f;
   //IZQUIERDA
      //izquiera arriba frente 3
   vertices[54] = -mL; vertices[55] = mL; vertices[56] = mL;
   normales[54] = -1.f; normales[55] = 0.0f; normales[56] = 0.0f;
      //izquierda abajo frente 2
   vertices[57] = -mL; vertices[58] = -mL; vertices[59] = mL;
   normales[57] = -1.f; normales[58] = 0.0f; normales[59] = 0.0f;
      //izquiera abajo trasera 7
   vertices[60] = -mL; vertices[61] = -mL; vertices[62] = -mL;
   normales[60] = -1.f; normales[61] = 0.0f; normales[62] = 0.0f;
      //izquiera abajo trasera 7
   vertices[63] = -mL; vertices[64] = -mL; vertices[65] = -mL;
   normales[63] = -1.f; normales[64] = 0.0f; normales[65] = 0.0f;
      //izquierda arriba trasera 6
   vertices[66] = -mL; vertices[67] = mL; vertices[68] = -mL;
   normales[66] = -1.f; normales[67] = 0.0f; normales[68] = 0.0f;
      //izquierda arriba frente 2
   vertices[69] = -mL; vertices[70] = mL; vertices[71] = mL;
   normales[69] = -1.f; normales[70] = 0.0f; normales[71] = 0.0f;
   //ABAJO
      //derecha abajo frente 1
   vertices[72] = mL; vertices[73] = -mL; vertices[74] = mL;
   normales[72] = 0.0f; normales[73] = -1.f; normales[74] = 0.0f;
      //izquierda abajo frente 2
   vertices[75] = -mL; vertices[76] = -mL; vertices[77] = mL;
   normales[75] = 0.0f; normales[76] = -1.f; normales[77] = 0.0f;
      //izquierda abajo trasera 6
   vertices[78] = -mL; vertices[79] = -mL; vertices[80] = -mL;
   normales[78] = 0.0f; normales[79] = -1.f; normales[80] = 0.0f;
      //izquierda abajo trasera 6
   vertices[81] = -mL; vertices[82] = -mL; vertices[83] = -mL;
   normales[81] = 0.0f; normales[82] = -1.f; normales[83] = 0.0f;
      //derecha abajo trasera 6
   vertices[84] = mL; vertices[85] = -mL; vertices[86] = -mL;
   normales[84] = 0.0f; normales[85] = -1.f; normales[86] = 0.0f;
      //derecha abajo frente 1
   vertices[87] = mL; vertices[88] = -mL; vertices[89] = mL;
   normales[87] = 0.0f; normales[88] = -1.f; normales[89] = 0.0f;

   //TRASERA
      //izquierda abajo trasera 6
   vertices[90] =-mL; vertices[91] = -mL; vertices[92] = -mL;
   normales[90] = 0.0f; normales[91] = 0.0f; normales[92] = -1.f;
      //derecha abajo trasera 6
   vertices[93] = mL; vertices[94] = -mL; vertices[95] = -mL;
   normales[93] = 0.0f; normales[94] = 0.0f; normales[95] = -1.f;
      //izquiera arriba trasera 7
   vertices[96] = -mL; vertices[97] = mL; vertices[98] = -mL;
   normales[96] = 0.0f; normales[97] = 0.0f; normales[98] = -1.f;

   //izquiera arriba trasera 7
   vertices[99] = -mL; vertices[100] = mL; vertices[101] = -mL;
   normales[99] = 0.0f; normales[100] = 0.0f; normales[101] = -1.f;

   //derecha arriba trasara 4
   vertices[102] = mL; vertices[103] = mL; vertices[104] = -mL;
   normales[102] = 0.0f; normales[103] = 0.0f; normales[104] = -1.f;

   //derecha abajo trasara 5
   vertices[105] = mL; vertices[106] = -mL; vertices[107] = -mL;
   normales[105] = 0.0f; normales[106] = 0.0f; normales[107] = -1.f;
}

renderable::Cube::Cube() {
   crearCubo(l);
   //malla = new float[32];

}

void renderable::Cube::setSize(float length) {
    l = length;
}

float renderable::Cube::getSize() {
    return l;
}

