#include "object.h"

renderable::Object::~Object() {
	utiles::Log::debug("borro obj");
	if (malla != NULL) {
		delete[] malla;
		malla = NULL;
	}
	if (normales) {
		delete[] normales;
		normales = NULL;
	}
}

void renderable::Object::setMesh(float* mesh, float* normals) {
	if (malla != NULL) {
		delete[] malla;
		malla = NULL;
	}
	if (normales) {
		delete[] normales;
		normales = NULL;
	}
	
	malla = new float[sizeof(mesh)];
	for (int i = 0; i < sizeof(mesh); i++) {
		malla[i] = mesh[i];
	}
	if (normals) {

	}
}


