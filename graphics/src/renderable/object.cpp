#include "object.h"

renderable::Object::~Object() {
	//utiles::Log::debug("borro obj");
	borrar();
}
void renderable::Object::setName(std::string name) {
	nombre = name;
}
void renderable::Object::borrar() {
	numeroVertices = 0;
	if (malla != NULL) {
		delete[] malla;
		malla = NULL;
	}
	if (normales) {
		delete[] normales;
		normales = NULL;
	}
	if (colores) {
		delete[] colores;
		colores = NULL;
	}
	if (indices) {
		delete[] indices;
		indices = NULL;
	}
}
void renderable::Object::ponerMesh(float* mesh, float* normals, float * colors, int * indexs) {
	borrar();
	int longitud = sizeof(mesh);
	malla = new float[longitud];
	for (int i = 0; i < longitud; i++) {
		malla[i] = mesh[i];
	}
	numeroVertices = longitud / 3;
	//TODO: Controlar que el número de normales y los colores sea igual a los vertices
	if (normals) {
		int longitud = sizeof(normals);
		normales = new float[longitud];
		for (int i = 0; i < longitud; i++) {
			normales[i] = normals[i];
		}
	}
	if (colors) {
		int longitud = sizeof(colors);
		colores = new float[longitud];
		for (int i = 0; i < longitud; i++) {
			colores[i] = colors[i];
		}
	}
	if (indexs) {
		int longitud = sizeof(indexs);
		indices = new int[longitud];
		for (int i = 0; i < longitud; i++) {
			indices[i] = indexs[i];
		}
	}
}




