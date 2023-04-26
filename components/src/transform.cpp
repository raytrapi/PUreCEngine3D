#include "transform.h"
#include "entity.h"

void Transform::cambiado() {
	//Cogemos todos los que haya que notificar y notificamos
	//Por ejemplo los colliders
	if (entidad) {
		std::vector<Collider*> *colliders = entidad->getComponents<Collider>();
		for (auto coll : *colliders) {
			coll->recalcular();
		}
	}
}

Vector3* Transform::position() { return _position; };
Vector3* Transform::rotation() { return _rotation; };
Vector3* Transform::scale() { return _scale; };
void Transform::setX(float x) {
	_position->x = x;
	//std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
  	/*for (auto it = renderables->begin(); it != renderables->end(); it++) {
		(*it)->update();
	}/**/
	/*for (auto hijo : hijos) {
		hijo->setX(x);
	}*/
	changeChildrens();
	cambiado();
	update();
};
void Transform::setY(float y) {
	_position->y = y;
	//std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
	/*for (auto it = renderables->begin(); it != renderables->end(); it++) {
		(*it)->update();
	}/**/
	changeChildrens();
	for (auto hijo : hijos) {
		hijo->setY(y);
	}
	cambiado();
	update();
};
void Transform::setZ(float z) {
	_position->z = z;
	//std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
	/*for (auto it = renderables->begin(); it != renderables->end(); it++) {
		(*it)->update();
	}/**/
	changeChildrens();
	for (auto hijo : hijos) {
		hijo->setZ(z);
	}
	cambiado();
	update();
};
void Transform::setPosition(float x, float y, float z) {
	if (_position->x != x || _position->y != y || _position->z != z) {
		
		entidad->setRenderUpdatable();
		_position->x = x;
		_position->y = y;
		_position->z = z;

		changeChildrens();

		//std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
		/*for (auto it = renderables->begin(); it != renderables->end(); it++) {
			(*it)->update();
		}/**/
		for (auto hijo : hijos) {
			hijo->setPosition(x, y, z);
		}
		cambiado();
		update();
	}
}
void Transform::setScale(float x, float y, float z) {
	if (_scale->x != x || _scale->y != y || _scale->z != z) {
		entidad->setRenderUpdatable();
		_scale->x = x;
		_scale->y = y;
		_scale->z = z;
		//std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
		/*for (auto it = renderables->begin(); it != renderables->end(); it++) {
			(*it)->update();
		}/**/
		/*for (auto hijo : hijos) {
			hijo->setPosition(x, y, z);
		}/**/
		changeChildrens();
		update();
		cambiado();
	}
}
void Transform::setRotator(float x, float y, float z) {
	if (_rotation->x != x || _rotation->y != y || _rotation->z != z) {
		entidad->setRenderUpdatable();
		_rotation->x = x;
		_rotation->y = y;
		_rotation->z = z;
		//std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
		/*for (auto it = renderables->begin(); it != renderables->end(); it++) {
			(*it)->update();
		}/**/
		/*for (auto hijo : hijos) {
			hijo->setPosition(x, y, z);
		}/**/
		changeChildrens();
		update();
		cambiado();
	}
}
void Transform::appendChild(Entity* child) {
	hijos.push_back(child->transform());
}

void Transform::appendChild(Transform* child) {
	hijos.push_back(child);
}

void Transform::removeChild(Entity* child) {
	removeChild(child->transform());
}

void Transform::removeChild(Transform* child) {
	auto itr = hijos.begin();
	bool seguir = true;
	while (seguir && itr != hijos.end()) {
		if ((*itr) == child) {
			hijos.erase(itr);
			seguir = true;
		} else {
			itr++;
		}
	}
}

float* Transform::matrix() {
	return transformacion;
};
void Transform::update() {
	
	calculateMatrix(transformacion, _position->x, _position->y, _position->z, _rotation->x, _rotation->y, _rotation->z, _scale->x, _scale->y,_scale->z);
	
	
}
void Transform::calculateMatrix(float *transform,float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz) {
	
	float rotX = rx;
	float rotY = ry;
	float rotZ = rz;
	rotX *= M_GRAD_RAD;
	rotY *= M_GRAD_RAD;
	rotZ *= M_GRAD_RAD;
	double cX = cos(rotX);
	double sX = sin(rotX);
	double cY = cos(rotY);
	double sY = sin(rotY);
	double cZ = cos(rotZ);
	double sZ = sin(rotZ);

	transform[0] = cZ * cY * sx;
	transform[1] = -cX * sZ + sY * cZ * sX;
	transform[2] = sX * sZ + sY * cX * cZ;
	transform[3] = px;

	transform[4] = cY * sZ;
	transform[5] = (cX * cZ + sY * sZ * sX) * sy;
	transform[6] = -sX * cZ + sY * cX * sZ;
	transform[7] = py;

	transform[8] = -sY;
	transform[9] = cY * sX;
	transform[10] = cX * cY * sz;
	transform[11] = pz;


	transform[12] = 0.00f;
	transform[13] = 0.00f;
	transform[14] = 0.00f;
	transform[15] = 1.00f;
	//return std::move(&transform[0]);
}

/**
* Se encarga de informar de la actualización de datos de transformada para los componentes e hijos
*/
void Transform::changeChildrens() {
	auto componentes=entidad->getComponents();
	for (auto componente : *componentes) {
		componente->transformChanged();
	}
	//std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
	/*for (auto it = renderables->begin(); it != renderables->end(); it++) {
		(*it)->update();
	}/**/
	/*for (auto hijo : hijos) {
		hijo->setX(x);
	}*/
};


void Transform::multMatrix(float* a, int rowsA, int colsA, float* b, int rowsB, int colsB, float* result) {
	// Verificar que las dimensiones de las matrices sean compatibles para multiplicación
	if (colsA != rowsB) {
		//std::cerr << "Error: Dimensiones incompatibles para multiplicación de matrices" << std::endl;
		DBG("Error: Dimensiones incompatibles para multiplicación de matrices");
		return;
	}

	// Multiplicar las matrices a y b
	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < colsB; j++) {
			float sum = 0.0;
			for (int k = 0; k < colsA; k++) {
				sum += a[i * colsA + k] * b[k * colsB + j];
			}
			result[i * colsB + j] = sum;
		}
	}
}
std::tuple<float, float, float> Transform::calculateForwardVector(float x, float y, float z, float fx, float fy, float fz) {
	// Convertir los ángulos a radianes
	float thetaX = x * M_GRAD_RAD;
	float thetaY = y * M_GRAD_RAD;
	float thetaZ = z * M_GRAD_RAD;

	// Construir la matriz de rotación
	float cosX = std::cos(thetaX);
	float sinX = std::sin(thetaX);
	float cosY = std::cos(thetaY);
	float sinY = std::sin(thetaY);
	float cosZ = std::cos(thetaZ);
	float sinZ = std::sin(thetaZ);

	float matriz[9] = { 1.0,1.0 ,1.0 ,1.0 ,1.0 ,1.0 ,1.0 ,1.0 ,1.0 };
	/*float m11 = cosY * cosZ;
	float m12 = -cosY * sinZ;
	float m13 = sinY;
	float m21 = cosX * sinZ + sinX * sinY * cosZ;
	float m22 = cosX * cosZ - sinX * sinY * sinZ;
	float m23 = -sinX * cosY;
	float m31 = sinX * sinZ - cosX * sinY * cosZ;
	float m32 = sinX * cosZ + cosX * sinY * sinZ;
	float m33 = cosX * cosY;*/
	matriz[0] = cosZ * cosY;
	matriz[1] = -cosX * sinZ + sinY * cosZ * sinX;
	matriz[2] = sinX * sinZ + sinY * cosX * cosZ;
	
	matriz[3] = cosY * sinZ;
	matriz[4] = (cosX * cosZ + sinY * sinZ * sinX);
	matriz[5] = -sinX * cosZ + sinY * cosX * sinZ;
	
	matriz[6] = -sinY;
	matriz[7] = cosY * sinX;
	matriz[8] = cosX * cosY;

	float matrizInicial[3] = {fx , fy, fz};
	float matrizFinal[3] = { 0,0,0 };

	multMatrix(matriz, 3, 3, matrizInicial, 3 , 1, matrizFinal);

	float sumaFs = sqrtf(matrizFinal[0]* matrizFinal[0] + matrizFinal[1]* matrizFinal[1] + matrizFinal[2]* matrizFinal[2]);
	// Aplicar la matriz de rotación al vector Forward inicial (0, 0, 1)
	if (sumaFs > 0) {
		return { matrizFinal[0] / sumaFs, matrizFinal[1] / sumaFs, matrizFinal[2] / sumaFs };
	} else {
		return { matrizFinal[0], matrizFinal[1], matrizFinal[2] };
	}

}
std::tuple<float, float, float, float, float, float> Transform::calculateForwardVector2(float x, float y, float z, float fx, float fy, float fz, float f2x, float f2y, float f2z) {
	float thetaX = x * M_GRAD_RAD;
	float thetaY = y * M_GRAD_RAD;
	float thetaZ = z * M_GRAD_RAD;

	// Construir la matriz de rotación
	float cosX = std::cos(thetaX);
	float sinX = std::sin(thetaX);
	float cosY = std::cos(thetaY);
	float sinY = std::sin(thetaY);
	float cosZ = std::cos(thetaZ);
	float sinZ = std::sin(thetaZ);

	float matriz[9] = { 1.0,1.0 ,1.0 ,1.0 ,1.0 ,1.0 ,1.0 ,1.0 ,1.0 };
	matriz[0] = cosZ * cosY;
	matriz[1] = -cosX * sinZ + sinY * cosZ * sinX;
	matriz[2] = sinX * sinZ + sinY * cosX * cosZ;

	matriz[3] = cosY * sinZ;
	matriz[4] = (cosX * cosZ + sinY * sinZ * sinX);
	matriz[5] = -sinX * cosZ + sinY * cosX * sinZ;

	matriz[6] = -sinY;
	matriz[7] = cosY * sinX;
	matriz[8] = cosX * cosY;

	float matrizInicial[3] = { fx , fy, fz };
	float matrizInicial2[3] = { f2x , f2y, f2z };
	float matrizFinal[3] = { 0,0,0 };
	float matrizFinal2[3] = { 0,0,0 };

	multMatrix(matriz, 3, 3, matrizInicial, 3, 1, matrizFinal);
	multMatrix(matriz, 3, 3, matrizInicial2, 3, 1, matrizFinal2);

	float sumaFs = sqrtf(matrizFinal[0] * matrizFinal[0] + matrizFinal[1] * matrizFinal[1] + matrizFinal[2] * matrizFinal[2]);
	float sumaFs2 = sqrtf(matrizFinal2[0] * matrizFinal2[0] + matrizFinal2[1] * matrizFinal2[1] + matrizFinal2[2] * matrizFinal2[2]);
	// Aplicar la matriz de rotación al vector Forward inicial (0, 0, 1)
	if (sumaFs > 0) {
		matrizFinal[0] /= sumaFs;
		matrizFinal[1] /= sumaFs;
		matrizFinal[2] /= sumaFs;
	}
	if (sumaFs2 > 0) {
		matrizFinal2[0] /= sumaFs2;
		matrizFinal2[1] /= sumaFs2;
		matrizFinal2[2] /= sumaFs2;
	}
	
	return { matrizFinal[0], matrizFinal[1], matrizFinal[2],matrizFinal2[0], matrizFinal2[1], matrizFinal2[2] };
	

}
/**/