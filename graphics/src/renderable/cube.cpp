#include "cube.h"

void renderable::Cube::crearCubo(float l) {
   float mL = l * 0.5f; //Cogemos la mitad del cubo
   //Tiene 6 caras, 2 triangulos por cara y 3 vertices por triangulo y 3 coordenadas =6*2*3*3 = 108
   malla = new float[108];
   normales = new float[108];
   //FRENTE
      //Superior izquierda
         //derecha arriba frente 0
   malla[0] = mL; malla[1] = mL; malla[2] = mL;
   normales[0] = 0.0f; normales[1] = 0.0f; normales[2] = 1.f;
         //derecha abajo frente 1
   malla[3] = mL; malla[4] = -mL; malla[5] = mL;
   normales[3] = 0.0f; normales[4] = 0.0f; normales[5] = 1.f;
         //izquiera arriba frente 3
   malla[6] = -mL; malla[7] = mL; malla[8] = mL;
   normales[6] = 0.0f; normales[7] = 0.0f; normales[8] = 1.f;
   //Superior derecho
      //izquiera arriba frente 3
   malla[9] = -mL; malla[10] = mL; malla[11] = mL;
   normales[9] = 0.0f; normales[10] = 0.0f; normales[11] = 1.f;
      //izquierda abajo frente 2
   malla[12] = -mL; malla[13] = -mL; malla[14] = mL; 
   normales[12] = 0.0f; normales[13] = 0.0f; normales[14] = 1.f;
      //derecha abajo frente 1
   malla[15] = mL; malla[16] = -mL; malla[17] = mL; 
   normales[15] = 0.0f; normales[16] = 0.0f; normales[17] = 1.f;

   //DERECHA
      //derecha arriba frente 0
   malla[18] = mL; malla[19] = mL; malla[20] = mL; 
   normales[18] = 1.f; normales[19] = 0.0f; normales[20] = 0.0f;
      //derecha abajo frente 1
   malla[21] = mL; malla[22] = -mL; malla[23] = mL; 
   normales[21] = 1.f; normales[22] = 0.0f; normales[23] = 0.0f;
      //derecha arriba trasara 4
   malla[24] = mL; malla[25] = mL; malla[26] = -mL;
   normales[24] = 1.f; normales[25] = 0.0f; normales[26] = 0.0f;
      //derecha arriba trasara 4
   malla[27] = mL; malla[28] = mL; malla[29] = -mL;
   normales[27] = 1.f; normales[28] = 0.0f; normales[29] = 0.0f;
      //derecha abajo trasara 5
   malla[30] = mL; malla[31] = -mL; malla[32] = -mL;
   normales[30] = 1.f; normales[31] = 0.0f; normales[32] = 0.0f;
      //derecha abajo frente 1
   malla[33] = mL; malla[34] = -mL; malla[35] = mL;
   normales[33] = 1.f; normales[34] = 0.0f; normales[35] = 0.0f;
   //ARRIBA
      //derecha arriba frente 0
   malla[36] = mL; malla[37] = mL; malla[38] = mL;
   normales[36] = 0.0f; normales[37] = 1.f; normales[38] = 0.0f;
      //derecha arriba trasara 4
   malla[39] = mL; malla[40] = mL; malla[41] = -mL;
   normales[39] = 0.0f; normales[40] = 1.f; normales[41] = 0.0f;
      //izquiera arriba trasera 7
   malla[42] = -mL; malla[43] = mL; malla[44] = -mL;
   normales[42] = 0.0f; normales[43] = 1.f; normales[44] = 0.0f;
      //izquiera arriba trasera 7
   malla[45] = -mL; malla[46] = mL; malla[47] = -mL;
   normales[45] = 0.0f; normales[46] = 1.f; normales[47] = 0.0f;
      //izquierda arriba frente 0
   malla[48] = -mL; malla[49] = mL; malla[50] = mL;
   normales[48] = 0.0f; normales[49] = 1.f; normales[50] = 0.0f;
      //derecha arriba frente 0
   malla[51] = mL; malla[52] = mL; malla[53] = mL;
   normales[51] = 0.0f; normales[52] = 1.f; normales[53] = 0.0f;
   //IZQUIERDA
      //izquiera arriba frente 3
   malla[54] = -mL; malla[55] = mL; malla[56] = mL;
   normales[54] = -1.f; normales[55] = 0.0f; normales[56] = 0.0f;
      //izquierda abajo frente 2
   malla[57] = -mL; malla[58] = -mL; malla[59] = mL;
   normales[57] = -1.f; normales[58] = 0.0f; normales[59] = 0.0f;
      //izquiera abajo trasera 7
   malla[60] = -mL; malla[61] = -mL; malla[62] = -mL;
   normales[60] = -1.f; normales[61] = 0.0f; normales[62] = 0.0f;
      //izquiera abajo trasera 7
   malla[63] = -mL; malla[64] = -mL; malla[65] = -mL;
   normales[63] = -1.f; normales[64] = 0.0f; normales[65] = 0.0f;
      //izquierda arriba trasera 6
   malla[66] = -mL; malla[67] = mL; malla[68] = -mL;
   normales[66] = -1.f; normales[67] = 0.0f; normales[68] = 0.0f;
      //izquierda arriba frente 2
   malla[69] = -mL; malla[70] = mL; malla[71] = mL;
   normales[69] = -1.f; normales[70] = 0.0f; normales[71] = 0.0f;
   //ABAJO
      //derecha abajo frente 1
   malla[72] = mL; malla[73] = -mL; malla[74] = mL;
   normales[72] = 0.0f; normales[73] = -1.f; normales[74] = 0.0f;
      //izquierda abajo frente 2
   malla[75] = -mL; malla[76] = -mL; malla[77] = mL;
   normales[75] = 0.0f; normales[76] = -1.f; normales[77] = 0.0f;
      //izquierda abajo trasera 6
   malla[78] = -mL; malla[79] = -mL; malla[80] = -mL;
   normales[78] = 0.0f; normales[79] = -1.f; normales[80] = 0.0f;
      //izquierda abajo trasera 6
   malla[81] = -mL; malla[82] = -mL; malla[83] = -mL;
   normales[81] = 0.0f; normales[82] = -1.f; normales[83] = 0.0f;
      //derecha abajo trasera 6
   malla[84] = mL; malla[85] = -mL; malla[86] = -mL;
   normales[84] = 0.0f; normales[85] = -1.f; normales[86] = 0.0f;
      //derecha abajo frente 1
   malla[87] = mL; malla[88] = -mL; malla[89] = mL;
   normales[87] = 0.0f; normales[88] = -1.f; normales[89] = 0.0f;

   //TRASERA
      //izquierda abajo trasera 6
   malla[90] =-mL; malla[91] = -mL; malla[92] = -mL;
   normales[90] = 0.0f; normales[91] = 0.0f; normales[92] = -1.f;
      //derecha abajo trasera 6
   malla[93] = mL; malla[94] = -mL; malla[95] = -mL;
   normales[93] = 0.0f; normales[94] = 0.0f; normales[95] = -1.f;
      //izquiera arriba trasera 7
   malla[96] = -mL; malla[97] = mL; malla[98] = -mL;
   normales[96] = 0.0f; normales[97] = 0.0f; normales[98] = -1.f;

   //izquiera arriba trasera 7
   malla[99] = -mL; malla[100] = mL; malla[101] = -mL;
   normales[99] = 0.0f; normales[100] = 0.0f; normales[101] = -1.f;

   //derecha arriba trasara 4
   malla[102] = mL; malla[103] = mL; malla[104] = -mL;
   normales[102] = 0.0f; normales[103] = 0.0f; normales[104] = -1.f;

   //derecha abajo trasara 5
   malla[105] = mL; malla[106] = -mL; malla[107] = -mL;
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

