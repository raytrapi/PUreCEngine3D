#include "entity.h"
#include "collider.h"

void Collider::setVertices(std::vector<float*>* vertices) {
	cX = cY = cZ = 0;
	longitud = 0;
	for (int i = 0; i < vertices->size(); i++) {
		float* v = vertices->operator[](i);
		this->vertices.push_back(v);
		float l = sqrtf(powf(cX - v[0],2) + powf(cY - v[1],2) + powf(cZ - v[2],2));
		if (l > longitud) {
			longitud = l;
		}
	}

}

void Collider::setFaces(std::vector<std::vector<float*>>* faces) {
	cX = cY = cZ = 0;
	longitud = 0;
	for (int i = 0; i < faces->size(); i++) {
		std::vector<float*> cara;
		for (int j = 0; j < faces->operator[](i).size(); j++) {
			float* v = faces->operator[](i)[j];
			cara.push_back(v);
			float l = sqrtf(powf(cX - v[0], 2) + powf(cY - v[1], 2) + powf(cZ - v[2], 2));
			if (l > longitud) {
				longitud = l;
			}
		}
		this->caras.push_back(cara);
	}
}
