#include "mesh.h"

renderable::Mesh::Mesh(){
}

void renderable::Mesh::setMesh(float* mesh, float* normals, float *colors) {
	ponerMesh(mesh, normals,colors);
}

void renderable::Mesh::setSize(float length) {}

float renderable::Mesh::getSize() {
	return 0.0f;
}
int renderable::Mesh::getAllSize() {
	return numCoordenadas;
}

float* renderable::Mesh::getMesh() {
	return malla;
}
float* renderable::Mesh::getNormals() {
	return normales;
}
float* renderable::Mesh::getColors() {
	return colores;
}
int* renderable::Mesh::getIndexs() {
	return indices;
}
int renderable::Mesh::getVertexNumber() {
	return numeroVertices;
}


void renderable::Mesh::setTriangles(std::vector<float **>*triangulos,float ** color, std::vector<float**>* normals) {
	borrar();
	numeroVertices = triangulos->size()*3;
	numCoordenadas = numeroVertices * 9;
	int numComponentes = numeroVertices * 3;
	malla = new float[numComponentes];
	normales= new float[numComponentes];
	colores= new float[numComponentes];
	int iMalla = 0;
	int iNormales = 0;
	int iColores = 0;
	for (int i = 0; i < triangulos->size(); i++) {
		//No comprobamos que efectivamente existan al menos 3 coordenadas para acelerar el proceso de carga.
		float** vertice = triangulos->operator[](i);
		malla[iMalla++] = vertice[0][0];
		malla[iMalla++] = vertice[0][1];
		malla[iMalla++] = vertice[0][2];
		malla[iMalla++] = vertice[1][0];
		malla[iMalla++] = vertice[1][1];
		malla[iMalla++] = vertice[1][2];
		malla[iMalla++] = vertice[2][0];
		malla[iMalla++] = vertice[2][1];
		malla[iMalla++] = vertice[2][2];

		float normal[3] = { 0.f,0.f,1.f };
		if (normals) {
			for (int iN = 0; iN < 3; iN++) {
				for (int jN = 0; jN < 3; jN++) {
					normales[iNormales++] = normals->operator[](i)[iN][jN];
				}
			}
		} else {

			normal[0] = (vertice[0][1] - vertice[1][1]) * (vertice[0][2] + vertice[1][2]) +
				(vertice[1][1] - vertice[2][1]) * (vertice[1][2] + vertice[2][2]) +
				(vertice[2][1] - vertice[0][1]) * (vertice[2][2] + vertice[0][2]);
			normal[1] = (vertice[0][2] - vertice[1][2]) * (vertice[0][0] + vertice[1][0]) +
				(vertice[1][2] - vertice[2][2]) * (vertice[1][0] + vertice[2][0]) +
				(vertice[2][2] - vertice[0][2]) * (vertice[2][0] + vertice[0][0]);
			normal[2] = (vertice[0][0] - vertice[1][0]) * (vertice[0][1] + vertice[1][1]) +
				(vertice[1][0] - vertice[2][0]) * (vertice[1][1] + vertice[2][1]) +
				(vertice[2][0] - vertice[0][0]) * (vertice[2][1] + vertice[0][1]);
			normales[iNormales++] = normal[0];
			normales[iNormales++] = normal[1];
			normales[iNormales++] = normal[2];
			normales[iNormales++] = normal[0];
			normales[iNormales++] = normal[1];
			normales[iNormales++] = normal[2];
			normales[iNormales++] = normal[0];
			normales[iNormales++] = normal[1];
			normales[iNormales++] = normal[2];
		}
		/**/
		/* Calculo obtenido de https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal */

		//Se repite 3 veces porque cada vertice del mismo triangulo tiene la misma normal
		

		//De momento el color será blanco
		colores[iColores++] = color[i][0];
		colores[iColores++] = color[i][1];
		colores[iColores++] = color[i][2];
		colores[iColores++] = color[i][0];
		colores[iColores++] = color[i][1];
		colores[iColores++] = color[i][2];
		colores[iColores++] = color[i][0];
		colores[iColores++] = color[i][1];
		colores[iColores++] = color[i][2];
	}
}