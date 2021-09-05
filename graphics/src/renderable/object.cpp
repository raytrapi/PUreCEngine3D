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
	if (vertices != NULL) {
		delete[] vertices;
		vertices = NULL;
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
	if (uvs) {
		delete[] uvs;
		uvs = NULL;
	}
	cambio = true;

}
void renderable::Object::ponerMesh(float* mesh, float* normals, float * colors, int * indexs) {
	borrar();
	int longitud = sizeof(mesh);
	vertices = new float[longitud];
	for (int i = 0; i < longitud; i++) {
		vertices[i] = mesh[i];
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
/**
* Add material but not delete when remove the mesh
* */
void renderable::Object::setMaterial(modules::graphics::Material* m) {
	materials.push_back(std::make_tuple(m, false));
}
/**
* Add material and delete when remove the mesh
* */
void renderable::Object::setMaterial(modules::graphics::Material m) {
	//TODO: ERROR, hay que crear realmente el objeto, al tener punteros es posible que falle la copia, o mejor dicho el borrado
	materials.push_back(std::make_tuple(new modules::graphics::Material(m), false));
}

std::vector<modules::graphics::Material*> renderable::Object::getMaterials() {
	std::vector<modules::graphics::Material*> materiales;
	for (int i = 0; i < materials.size(); i++) {
		materiales.push_back(std::get<0>(materials[i]));
	}
	return materiales;
}

float* renderable::Object::getUVs() {
	return uvs;
}

unsigned int renderable::Object::getIdTexture() {
	if (materials.size() > 0) {
		return std::get<0>(materials[0])->getIdTexture();
	}
	return 0;
}




