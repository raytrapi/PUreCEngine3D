#include "entity.h"
#include "collider.h"



/*void Collider::whenChargeEntity() {
	if (entidad) {
		RenderableComponent* renderizables = entidad->getComponent<RenderableComponent>();
		setFaces(renderizables->getFaces());
	}
}/**/


std::tuple<float, float> Collider::getNormal2D(float x1, float y1, float x2, float y2) {
	float x = -(y2 - y1);
	float y = x2 - x1;
	//Normalizamos el valor
	float magnitud = sqrtf(x*x+y*y);

	if (magnitud != 0) {
		x /= magnitud;
		y /= magnitud;
	}
	return { x,y };
}

float Collider::dotProduct2D(float x1, float y1, float x2, float y2) {
	return (x1 * x2) + (y1 * y2);
}

std::tuple<float, float> Collider::getMinMax2D(float axisX, float axisY, float* vertex, unsigned numberVertex) {
	if(numberVertex==0){
		return { 0, 0 };
	}
	float min = dotProduct2D(axisX,axisY,vertex[0], vertex[1]);
	float max = min;
	unsigned k = 3;
	for (unsigned i = 1; i < numberVertex; i++) {
		float dot = dotProduct2D(axisX, axisY, vertex[k], vertex[k+1]);
		k += 3;
		if (dot < min) {
			min = dot;
		}
		if (dot > max) {
			max = dot;
		}
	}
	return { min, max };
}



std::tuple<bool, bool> Collider::checkRangesForContainment(float rangeAMin, float rangeAMax, float rangeBMin, float rangeBMax) {
	std::tuple<bool, bool> result(true, true);
	if (rangeAMax > rangeBMax || rangeAMin < rangeBMin) {
		std::get<0>(result) = false;
	}
	if (rangeBMax > rangeAMax || rangeBMin < rangeAMin) {
		std::get<1>(result) = false;
	}
	return result;
}

float Collider::checkPolygons(float aX, float aY, float* pA, unsigned lengthA, float bX, float bY, float* pB, unsigned lengthB) {
	float distancia = std::numeric_limits<float>::infinity();
	float offsetX = aX-bX;
	float offsetY= aY-bY;
	/*float vectorX;
	float vectorY;/**/
	for (unsigned i = 0; i < lengthA; i++) {
		float aX, aY;
		
		std::tie(aX, aY) = getNormal2D(pA[0], pA[1], pA[i*3], pA[(i*3)+1]);
		float minA, maxA;
		float minB, maxB;
		std::tie(minA, maxA) = getMinMax2D(aX, aY, pA, lengthA);
		std::tie(minB, maxB) = getMinMax2D(aX, aY, pB, lengthB);
		
		float offset = dotProduct2D(aX, aY, offsetX,offsetY);
		minA += offset;
		maxA += offset;

		// now check for a gap betwen the relative min's and max's
		if ((minA - maxB > 0) || (minB - maxA > 0)) {
			return -1;
		}

		bool contieneA, contieneB;
		std::tie(contieneA, contieneB) = checkRangesForContainment(minA, maxA, minB, maxB);


		float distMin = (maxB - minA) * -1;

		float distMinAbs = distMin<0?-distMin:distMin;
		if (distMinAbs < distancia) {
			distancia = distMinAbs;
			/*vectorX = aX;
			vectorY = aY;/**/
			//result.vector = axis;
		}
	}

	/*float separacionX = vectorX * distancia;
	float separacionY = vectorY * distancia;/**/
	
	return distancia;
	
}

/*Collider::Collider() {
	
	cargarEntidad();
	
}/**/
void Collider::cargarEntidad() {
	cX = 0;
	cY = 0;
	cZ = 0;
	if (entidad) {
		RenderableComponent* renderizables = entidad->getComponent<RenderableComponent>();
		if (renderizables != NULL) {
			setFaces(renderizables->getFaces());
		}
	}
}

void Collider::iniciarFisicas() {
	if (graphic != NULL && fisicas == NULL) {
		fisicas = graphic->getPhysics();
	}

	if (fisicas != NULL) {
		DBG("Tengo fisicas");
		fisicas->appendCollider(this);
	} else {
		DBG("NOOOO Tengo físicas");
	}/**/
}
Collider::Collider(Entity* entity, modules::graphics::Graphic* g, Component* p) {
	this->entidad = entity;
	graphic = g;
	padre = p;
	fisicas = g->getPhysics();
	cargarEntidad();
	iniciarFisicas();
}

void Collider::setVertices(std::vector<float*>* vertices) {
	cX = cY = cZ = 0;
	longitud = 0;
	/*if (vertices != NULL) {
		borrarVertices();
	}/**/
	/*numeroVertices = vertices->size();
	this->vertices = new float*[numeroVertices];
	for (int i = 0; i < vertices->size(); i++) {
		float* v = vertices->operator[](i);
		this->vertices[i] = new float[3]{
			v[0],v[1],v[2]
		};
		
		float l = sqrtf(powf(cX - v[0],2) + powf(cY - v[1],2) + powf(cZ - v[2],2));
		if (l > longitud) {
			longitud = l;
		}
	}*/

}

void Collider::setFaces(std::vector<std::vector<const float*>>* faces) {
	this->caras.clear();
	cX = cY = cZ = 0;
	longitud = 0;
	float longitudAncho = 0;
	float longitudAlto = 0;
	float longitudFondo = 0;
	float puntoLimite[3][2] = {
		{ 0,0 }, //min - max X
		{ 0,0 }, //min - max Y
		{ 0,0 } //min - max Z
	};
	
	if (faces == NULL) { //TODO: Esto es un error hay que evitar que si no hay maya de colisión de como válido al pasar en el 0,0,0
		this->limites[0] = 0;
		this->limites[1] = 0;
		this->limites[2] = 0;
		this->limites[3] = 0;
		this->limites[4] = 0;
		this->limites[5] = 0;
		return;
	}
	for (int i = 0; i < faces->size(); i++) {
		std::vector<float*> cara;
		//Primero inicializamos el punto mínimo y máximo de cada eje //First initialize the minimum and maximum point of each axis
		if (i == 0) {
			if (faces->operator[](i).size() > 0) {
				puntoLimite[0][0] = faces->operator[](i)[0][0];
				puntoLimite[0][1] = faces->operator[](i)[0][0];
				puntoLimite[1][0] = faces->operator[](i)[0][1];
				puntoLimite[1][1] = faces->operator[](i)[0][1];
				puntoLimite[2][0] = faces->operator[](i)[0][2];
				puntoLimite[2][1] = faces->operator[](i)[0][2];
			}
		}
		
		for (int j = 0; j < faces->operator[](i).size(); j++) {
			float* v = (float*)faces->operator[](i)[j];
			cara.push_back(v);
			float l = sqrtf(powf(cX - v[0], 2) + powf(cY - v[1], 2) + powf(cZ - v[2], 2));
			if (l > longitud) {
				longitud = l;
			}
			l = cX - v[0];
			if (l > longitudAncho) {
				longitudAncho = l;
			}
			l = cY - v[1];
			if (l > longitudAlto) {
				longitudAlto = l;
			}
			l = cZ - v[2];
			if (l > longitudFondo) {
				longitudFondo = l;
			}
			//Comprobamos si cada coordena min max de cada eje es mayor que el punto mínimo y máximo de ese eje 
			//Check if each coordinate min max of each axis is greater than the minimum and maximum point of that axis
			if (v[0] < puntoLimite[0][0]) {
				puntoLimite[0][0] = v[0];
			}
			if (v[0] > puntoLimite[0][1]) {
				puntoLimite[0][1] = v[0];
			}
			if (v[1] < puntoLimite[1][0]) {
				puntoLimite[1][0] = v[1];
			}
			if (v[1] > puntoLimite[1][1]) {
				puntoLimite[1][1] = v[1];
			}
			if (v[2] < puntoLimite[2][0]) {
				puntoLimite[2][0] = v[2];
			}
			if (v[2] > puntoLimite[2][1]) {
				puntoLimite[2][1] = v[2];
			}
		}
		this->caras.push_back(cara);
	}
	//El cubo más grande que contiene nuestro objeto
	this->limites[0] = puntoLimite[0][0]; // Izquierda
	this->limites[1] = puntoLimite[0][1]; // Derecha
	this->limites[2] = puntoLimite[1][0]; // Abajo
	this->limites[3] = puntoLimite[1][1]; // Arriba
	this->limites[4] = puntoLimite[2][1]; // Fondo
	this->limites[5] = puntoLimite[2][0]; // Frente
	

}


bool Collider::isCollisionRay(float xOrigin, float yOrigin, float zOrigin, float xTarget, float yTarget, float zTarget) {
	bool estamosAliniadosDesdeOrigen = false;
	bool estamosAliniadosDesdeFinal = false;
	float** verticesA = new float* [2]{
		new float[3]{xOrigin,yOrigin,zOrigin},
		new float[3]{xTarget,yTarget,zTarget}
	};
	return false;
	//return checkPolygons(0,0,verticesA, 2, 0, 0, vertices, numeroVertices)==0;
	/*//Controlamos si el comienzo del rayo está a la derecha o a la izquierda de nuestro objeto
	if (xOrigin <= limites[0]) {//El rayo comienza a la izquieda
		if (xTarget < limites[0]) { //El rayo termina a la izquierda
			return false;
		}
	} else { //El rayo comienza a la derecha
		if (xOrigin >= limites[1]) { //El rayo comienza a la derecha
			if (xTarget >limites[1]) { //El rayo termina a la derecha
				return false;
			}
		}
	}
	if (yOrigin <= limites[2]) {//El rayo comienza arriba
		if (yTarget < limites[2]) { //El rayo termina arriba
			return false;
		}
	} else { //El rayo comienza abajo
		if (yOrigin >= limites[3]) { //El rayo comienza abajo
			if (yTarget > limites[3]) { //El rayo termina abajo
				return false;
			}
		}
	}
	if (zOrigin <= limites[4]) {//El rayo comienza atras
		if (zTarget < limites[4]) { //El rayo termina atras
			return false;
		}
	} else { //El rayo comienza delante
		if (zOrigin >= limites[5]) { //El rayo comienza delante
			if (zTarget > limites[5]) { //El rayo termina delante
				return false;
			}
		}
	}

	
	return true;/**/
}

void Collider::changePhysics() {
	if (fisicas != NULL) {
		fisicas->changeCollider(this);
	}
}; 