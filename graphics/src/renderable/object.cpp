#include "object.h"
#include "../../../components/modulos/renderables/renderable.h"
renderable::Object::~Object() {
	//utiles::Log::debug("borro obj");
	borrar();
	
}
void renderable::Object::setName(std::string name) {
	nombre = name;
}
void renderable::Object::borrar() {
	borrarMesh();
	borrarMaterial();
	cambio = true;
	
}
void renderable::Object::borrarVertex() {
	numeroVertices = 0;
	if (vertices != NULL) {
		delete[] vertices;
		vertices = NULL;
	}
}
void renderable::Object::borrarMesh() {
	borrarVertex();
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
	if (caras) {
		delete caras;
		caras = NULL;
	}
}
void renderable::Object::borrarMaterial() {
	for (auto itr = materials.begin(); itr != materials.end(); itr++) {
		if (std::get<1>(*itr)) {
			
			delete std::get<0>(*itr);
		}
	}
	materials.clear();
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
unsigned renderable::Object::setMaterial(modules::graphics::Material* m, int pos, bool del) {
	if (pos > -1 && pos<materials.size()) {
		delete std::get<0>(materials[pos]);
		if (del) {
			std::get<0>(materials[pos]) = new modules::graphics::Material(*m);
		} else {
			std::get<0>(materials[pos]) = m;
		}
		std::get<1>(materials[pos]) = del;
		return pos;
	} else {
		materials.push_back(std::make_tuple(m, del));
		return materials.size() - 1;
	}
}
/**
* Add material and delete when remove the mesh
* */
unsigned renderable::Object::setMaterial(modules::graphics::Material m, int pos, bool del) {
	modules::graphics::Material* m2 = new modules::graphics::Material(m);
	return setMaterial(m2, pos, del);
	
}



RenderableComponent* renderable::Object::getRenderable() {
	return renderizador;
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

int renderable::Object::getNormalsNumber() {
	return numeroNormales;
}

int renderable::Object::getVertexNumber() {
	return numeroVertices;
}

int renderable::Object::getFacesNumber() {
	return caras->size();
}
void renderable::Object::setUV(float** uv) {
	/*if (uvs) {
		delete[] uvs;
		uvs = NULL;
	}*/
	if (this->uvs != NULL) {
		for (int i = 0; i < numeroVertices; i++) {
			for (int jC = 0; jC < 2; jC++) {
				this->uvs[(i * 2) + jC] = uv[i][jC];
			}
		}
	}
	
	cambio = true;
	actualizarVertices = true;
	setToRender(true);
}
void renderable::Object::setToRender(bool toRender) {
	RenderableComponent* renderizador = getRenderable();
	if (renderizador!=NULL) {
		renderizador->setUpdated(toRender);
	}
}


std::vector<renderable::Object*> renderable::Object::objetos;