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
void Transform::change(bool propagate) {
	cambiado();
	update();
	if (propagate) {
		changeChildrens();
		for (auto hijo : hijos) {
			hijo->change();
		}
	}
}
/*Vector3* Transform::position() { return _position; };
Vector3* Transform::rotation() { return _rotation; };
Vector3* Transform::scale() { return _scale; };/**/

std::tuple<float, float, float> Transform::getWorldPosition() {
	float xP = 0;
	float yP = 0;
	float zP = 0;
	if (padre) {
		std::tie(xP, yP, zP) = padre->getWorldPosition();
	}
	return { _position->x + xP, _position->y + yP, _position->z + zP };
}

void Transform::setX(float x) {
	_position->x = x;
	change();
	/*changeChildrens();
	cambiado();
	update();/**/
};
void Transform::setY(float y) {
	_position->y = y;
	
	change();
	/*changeChildrens();
	for (auto hijo : hijos) {
		hijo->setY(y);
	}
	cambiado();
	update();/**/
};
void Transform::setZ(float z) {
	_position->z = z;
	change();
	/*changeChildrens();
	for (auto hijo : hijos) {
		hijo->setZ(z);
	}
	cambiado();
	update();/**/
};
void Transform::setPosition(float x, float y, float z, bool propagate) {
	//if (_position->x != x || _position->y != y || _position->z != z) {
		_position->x = x;
		_position->y = y;
		_position->z = z;
		
		
		change();
		
	//}
}
void Transform::addPosition(float x, float y, float z, bool propagate) {
	if (entidad) {
		entidad->setRenderUpdatable();
	}
	_position->x += x;
	_position->y += y;
	_position->z += z;
	change();
	/*if (propagate) {
		changeChildrens();
		for (auto hijo : hijos) {
			hijo->addPosition(x, y, z, propagate);
		}
	}
	cambiado();
	update();/**/
	
}
void Transform::setScale(float x, float y, float z, bool propagate) {
	if (_scale->x != x || _scale->y != y || _scale->z != z) {
		_scale->x = x;
		_scale->y = y;
		_scale->z = z;
		
		change();
		/*if (propagate) {
			changeChildrens();
			for (auto hijo : hijos) {
				hijo->setScale(x, y, z);
			}
		}
		update();
		cambiado();/**/
	}
}
void Transform::addScale(float x, float y, float z, bool propagate) {
		if (entidad) {
			entidad->setRenderUpdatable();
		}
		_scale->x += x;
		_scale->y += y;
		_scale->z += z;
		change();
		/*if (propagate) {
			changeChildrens();
			for (auto hijo : hijos) {
				hijo->addScale(x, y, z);
			}
		}
		update();
		cambiado();/**/
}
void Transform::setRotation(float x, float y, float z, bool propagate) {
	if (_rotation->x != x || _rotation->y != y || _rotation->z != z) {
		_rotation->x = x;
		_rotation->y = y;
		_rotation->z = z;
		
		change();
		/*if (propagate) {
			changeChildrens();
			for (auto hijo : hijos) {
				hijo->_rotation2[0] = x;
				hijo->_rotation2[1] = y;
				hijo->_rotation2[2] = z;
				hijo->update();
				hijo->cambiado();
			}
		}
		
		update();
		cambiado();/**/
	}
}
void Transform::addRotation(float x, float y, float z, bool propagate) {
	
	_rotation->x += x;
	_rotation->y += y;
	_rotation->z += z;
	change();
	/*if (propagate) {
		changeChildrens();
		for (auto hijo : hijos) {
			hijo->addRotation(x, y, z);
		}
	}
	if (entidad) {
		entidad->setRenderUpdatable();
	}
	update();
	cambiado();/**/
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
	for (auto itr = hijos.begin(); itr != hijos.end(); itr++) {
		if ((*itr) == child) {
			hijos.erase(itr);
			return;
		}
	}
	/* //Esto seguramente esté mal
	auto itr = hijos.begin();

	bool seguir = true;
	while (seguir && itr != hijos.end()) {
		if ((*itr) == child) {
			hijos.erase(itr);
			seguir = true;
			itr=hijos.begin();
		} else {
			itr++;
		}
	}/**/
}

float* Transform::matrix(bool recalculate, bool copy) {
	float* m=0;
	if (recalculate) {
		m=matrizCompleta((copy)?0:transformacion);
	}else {
		if (copy) {
			m = new float[16];
			for (int i = 0; i < 16; i++) {
				m[i] = transformacion[i];
			}
		} else {
			m = transformacion;
		}
	}
	return m;
	
};

float* Transform::matrixScale(float scale) {
	float* res = new float[16];
	bool inverse = false;
	float* pM = 0;
	float* piM = 0;
	if (conPivote) {
		pM = matrizTranslacion(inverse, _pivot[0], _pivot[1], _pivot[2]);
		piM = matrizTranslacion(inverse, -_pivot[0], -_pivot[1], -_pivot[2]);
	}
	auto tM = matrizTranslacion(inverse, _position->x, _position->y, _position->z);
	auto sM = matrizScala(_scale->x*scale, _scale->y*scale, _scale->z*scale);
	auto rMX = matrizRotacionX((inverse ? -1 : 1) * _rotation->x);
	auto rMY = matrizRotacionY((inverse ? -1 : 1) * _rotation->y);
	auto rMZ = matrizRotacionZ((inverse ? -1 : 1) * _rotation->z);
	float temp[16];
	float temp2[16];
	float temp3[16];
	//multMatrix(rM, 4, 4, tM, 4, 4, temp);

	
	if (conPivote) {
		multMatrix(tM, 4, 4, pM, 4, 4, temp2);
		multMatrix(temp2, 4, 4, rMX, 4, 4, temp);
	} else {
		multMatrix(tM, 4, 4, rMX, 4, 4, temp);
	}
	//multMatrix(tM, 4, 4, rMX, 4, 4, temp2);
	//multMatrix(temp, 4, 4, rMX, 4, 4, temp);
	multMatrix(temp, 4, 4, rMY, 4, 4, temp2);
	multMatrix(temp2, 4, 4, rMZ, 4, 4, temp3);
	if (conPivote) {
		multMatrix(temp3, 4, 4, piM, 4, 4, temp);
		//multMatrix(temp, 4, 4, tM, 4, 4, temp2);
		multMatrix(temp, 4, 4, sM, 4, 4, res);
	} else {
		multMatrix(temp3, 4, 4, sM, 4, 4, res);
	}
	
	//calculateMatrix(transformacion, _position->x, _position->y, _position->z, _rotation->x, _rotation->y, _rotation->z, _scale->x, _scale->y, _scale->z,0);
	delete[]tM;
	delete[]sM;
	delete[]rMX;
	delete[]rMY;
	delete[]rMZ;
	if (pM != 0) {
		delete[] pM;
	}
	if (piM != 0) {
		delete[] piM;
	}
	/**/
	
	
	return res;
}
float* Transform::rotationPivot(float x, float y, float z, float a, float b, float g) {
	bool inverse = false;
	float* res = new float[16];

	auto iM = identity();
	auto tM = matrizTranslacion(inverse, _position->x, _position->y, _position->z);
	auto pM = matrizTranslacion(inverse, x, y, z);
	auto piM = matrizTranslacion(inverse, -x, -y, -z);
	auto sM = matrizScala(_scale->x, _scale->y, _scale->z);
	auto rMX = matrizRotacionX(a);
	auto rMY = matrizRotacionY(b);
	auto rMZ = matrizRotacionZ(g);
	float temp[16];
	float temp2[16];
	float temp3[16];
	//multMatrix(rM, 4, 4, tM, 4, 4, temp);
	//multMatrix(tM, 4, 4, pM, 4, 4, temp3);
	multMatrix(iM, 4, 4, pM, 4, 4, temp3);
	multMatrix(temp3, 4, 4, rMX, 4, 4, temp);
	multMatrix(temp, 4, 4, rMY, 4, 4, temp2);
	multMatrix(temp2, 4, 4, rMZ, 4, 4, temp3);
	multMatrix(temp3, 4, 4, piM, 4, 4, temp);
	multMatrix(temp, 4, 4, sM, 4, 4, res);
	//multMatrix(temp2, 4, 4, tM, 4, 4, res);
	//multMatrix(temp3, 4, 4, iM, 4, 4, res);
	/**/
	
	//calculateMatrix(transformacion, _position->x, _position->y, _position->z, _rotation->x, _rotation->y, _rotation->z, _scale->x, _scale->y, _scale->z,0);
	delete[]tM;
	delete[]pM;
	delete[]piM;
	delete[]sM;
	delete[]rMX;
	delete[]rMY;
	delete[]rMZ;
	delete[]iM;
	return res;
}
void Transform::update() {
	if (entidad) {
		entidad->setRenderUpdatable();
	}
	updateForward = true;
	updateUp = true;
	//matrix(true);
	matrizCompleta(transformacion);
	//calculateMatrix(transformacion, _position->x, _position->y, _position->z, _rotation->x, _rotation->y, _rotation->z, _scale->x, _scale->y,_scale->z);
	
	
}
float * Transform::identity() {
	float * transform=new float[16];
	for (int i = 0; i < 16; i++) {
		transform[i] = identidad[i];
	}
	return transform;
}

float * Transform::matrizTranslacion(bool inverse, float x, float y, float z){
	float* transform = identity();
	if (inverse) {
		transform[12] = x;
		transform[13] = y;
		transform[14] = z;/**/
	} else {
		transform[3] = x;
		transform[7] = y;
		transform[11] = z;/**/
	}
	return transform;
};
float* Transform::matrizRotacionX(float angle) {
	//float x = (inverse ? -1 : 1) * _rotation->x;
	double cX = cos(angle);
	double sX = sin(angle);

	auto mX = identity();
	mX[5] = cX;
	mX[6] = sX;
	mX[9] = -sX;
	mX[10] = cX;
	return mX;
}
float* Transform::matrizRotacionY(float angle) {
	//float y = (inverse ? -1 : 1) * _rotation->y;
	double cY = cos(angle);
	double sY = sin(angle);
	auto mY = identity();
	mY[0] = cY;
	mY[2] = -sY;
	mY[8] = sY;
	mY[10] = cY;
	return mY;
}
float* Transform::matrizRotacionZ(float angle) {
	//float z = (inverse ? -1 : 1) * _rotation->z;
	double cZ = cos(angle);
	double sZ = sin(angle);
	auto mZ = identity();
	mZ[0] = cZ;
	mZ[1] = sZ;
	mZ[4] = -sZ;
	mZ[5] = cZ;
	return mZ;
}
float *Transform::matrizRotacion(){
	float* transform = identity();
	float rotX = _rotation->x;
	float rotY = _rotation->y;
	float rotZ = _rotation->z;
	//rotX *= M_GRAD_RAD;
	//rotY *= M_GRAD_RAD;
	//rotZ *= M_GRAD_RAD;
	double cX = cos(rotX);
	double sX = sin(rotX);
	double cY = cos(rotY);
	double sY = sin(rotY);
	double cZ = cos(rotZ);
	double sZ = sin(rotZ);

	auto mX = identity();
	mX[5] = cX;
	mX[6] = sX;
	mX[9] = -sX;
	mX[10] = cX;
	auto mY = identity();
	mY[0] = cY;
	mY[2] = -sY;
	mY[8] = sY;
	mY[10] = cY;
	auto mZ = identity();
	mZ[0] = cZ;
	mZ[1] = sZ;
	mZ[4] = -sZ;
	mZ[5] = cZ;

	

	delete[] mZ;
	delete[] mY;
	delete[] mX;
	//Solo Z
	//transform[0] = cZ ;
	//transform[1] = -sZ;
	//transform[4] = sZ;
	//transform[5] = cZ;
	
	transform[0] = cZ * cY ;
	transform[1] = cY * sZ;
	transform[2] = -sY;

	transform[4] = sX*sY*cZ-cX*sZ;
	transform[5] = sX*sY*sZ+cX*cZ;
	transform[6] = sX * cY;

	transform[8] = cX*sY*cZ+sX*sZ;
	transform[9] = cX*sY*sZ-sX*cZ;
	transform[10] = cX*cY;

	transform[15] = 1.00f;
	/*Rotate[0][0] = c + temp[0] * axis[0];
	Rotate[0][1] = temp[0] * axis[1] + s * axis[2];
	Rotate[0][2] = temp[0] * axis[2] - s * axis[1];

	Rotate[1][0] = temp[1] * axis[0] - s * axis[2];
	Rotate[1][1] = c + temp[1] * axis[1];
	Rotate[1][2] = temp[1] * axis[2] + s * axis[0];

	Rotate[2][0] = temp[2] * axis[0] + s * axis[1];
	Rotate[2][1] = temp[2] * axis[1] - s * axis[0];
	Rotate[2][2] = c + temp[2] * axis[2];

	mat<4, 4, T, Q> Result;
	Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
	Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
	Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
	Result[3] = m[3];/**/
	
	return transform;
};
float * Transform::matrizScala(float x, float y, float z) {
	float* transform = identity();;
	transform[0] = x;
	transform[5] = y;
	transform[10] = z;
	return transform;
};

float* Transform::matrizCompleta(float* m) {
	float cX = cosf(_rotation->x);
	float cY = cosf(_rotation->y);
	float cZ = cosf(_rotation->z);
	float sX = sinf(_rotation->x);
	float sY = sinf(_rotation->y);
	float sZ = sinf(_rotation->z);
	if (m == 0) {
		m = new float[16];
	}
	m[0] = _scale->x * cY * cZ;
	m[1] = _scale->x* cY * -sZ;
	m[2] = _scale->x* sY;
	m[3] = 0;
	m[4] =(_scale->y * -sX * -sY * cZ + _scale->y * cX * sZ);
	m[5] = (_scale->y * -sX * -sY * -sZ + _scale->y * cX * cZ);
	m[6] = _scale->y * -sX * cY;
	m[7] = 0;
	m[8] = (_scale->z * cX * -sY * cZ + _scale->z * sX * sZ);
	m[9] = (_scale->z * cX * -sY * -sZ + _scale->z * sX * cZ);
	m[10] = _scale->z* cX* cY;
	m[11] = 0;
	m[12] = _position->x;
	m[13] = _position->y;
	m[14] = _position->z;
	m[15] = 1;
	if (padre) {
		float temp[16];
		//multMatrix(padre->matrix(), 4, 4, m, 4, 4, temp);
		multMatrix(m, 4, 4, padre->matrix(), 4, 4, temp);
		for (int i = 0; i < 16; i++) {
			m[i] = temp[i];
		}
	}
	return m;

}
float* Transform::matrixCompleteScale(float scale) {
	float cX = cosf(_rotation->x);
	float cY = cosf(_rotation->y);
	float cZ = cosf(_rotation->z);
	float sX = sinf(_rotation->x);
	float sY = sinf(_rotation->y);
	float sZ = sinf(_rotation->z);
	
	float scaleX = (_scale->x * scale);
	float scaleY = (_scale->y * scale);
	float scaleZ = (_scale->z * scale);
	auto m = new float[16];
	m[0] = scaleX * cY * cZ;
	m[1] = scaleX * cY * -sZ;
	m[2] = scaleX * sY;
	m[3] = 0;
	m[4] = (scaleY * -sX * -sY * cZ + scaleY * cX * sZ);
	m[5] = (scaleY * -sX * -sY * -sZ + scaleY * cX * cZ);
	m[6] = scaleY * -sX * cY;
	m[7] = 0;
	m[8] = (scaleZ * cX * -sY * cZ + scaleZ * sX * sZ);
	m[9] = (scaleZ * cX * -sY * -sZ + scaleZ * sX * cZ);
	m[10] = scaleZ * cX * cY;
	m[11] = 0;
	m[12] = _position->x;
	m[13] = _position->y;
	m[14] = _position->z;
	m[15] = 1;
	if (padre) {
		float temp[16];
		//multMatrix(padre->matrix(), 4, 4, m, 4, 4, temp);
		multMatrix(m, 4, 4, padre->matrix(), 4, 4, temp);
		for (int i = 0; i < 16; i++) {
			m[i] = temp[i];
		}
	}
	return m;
}
void Transform::calculateMatrix(float *transform,float px, float py, float pz, float rx, float ry, float rz, float sx, float sy, float sz, int modo) {
	
	//return;
	float rotX = rx;
	float rotY = ry;
	float rotZ = rz;
	//rotX *= M_GRAD_RAD;
	//rotY *= M_GRAD_RAD;
	//rotZ *= M_GRAD_RAD;
	double cX = cos(rotX);
	double sX = sin(rotX);
	double cY = cos(rotY);
	double sY = sin(rotY);
	double cZ = cos(rotZ);
	double sZ = sin(rotZ);

	transform[0] = cZ * cY * sx;
	transform[1] = cY*-sZ*sy;//-cX * sZ + sY * cZ * sX;
	transform[2] = sY*sz;//sX * sZ + sY * cX * cZ;

	transform[4] = (cX * cY * cZ + -sX * sZ) * sx;//cY * sZ;
	transform[5] = (cX * cY * -sZ + -sX * cZ) * sy;//(cX * cZ + sY * sZ * sX) * sy;
	transform[6] = cX * sY * sz;//-sX * cZ + sY * cX * sZ;

	transform[8] = ((sX * cY + -sY) * cZ + cX * sZ) * sx;//-sY;
	transform[9] = ((sX * cY + -sY) * -sZ + cX * cZ) * sy;// cY* sX;
	transform[10] = (sX * sY + cY) * sz;// cX* cY* sz;

	transform[15] = 1.00f;

	switch (modo) {
		case 0:
			transform[3] = px;
			transform[7] = py;
			transform[11] = pz;
			transform[12] = 0.00f;
			transform[13] = 0.00f;
			transform[14] = 0.00f;
			//transform[3] = 0;
			//transform[7] = 0;
			//transform[11] = 0;
			//transform[12] = px;
			//transform[13] = py;
			//transform[14] = pz;
			break;
		case 1:
			transform[3] = 0;
			transform[7] = 0;
			transform[11] = 0;
			transform[12] = px;
			transform[13] = py;
			transform[14] = pz;
			break;
	}
	//return std::move(&transform[0]);
}

/**
* Se encarga de informar de la actualización de datos de transformada para los componentes e hijos
*/
void Transform::changeChildrens() {
	if (entidad) {
		auto componentes = entidad->getComponents();
		for (auto componente : *componentes) {
			componente->transformChanged();
		}
	}
	//std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
	/*for (auto it = renderables->begin(); it != renderables->end(); it++) {
		(*it)->update();
	}/**/
	/*for (auto hijo : hijos) {
		hijo->setX(x);
	}*/
};


std::tuple<float,float,float> Transform::getFordward() {
	if (updateForward) {
		updateForward = false;
		std::tie(forward[0], forward[1], forward[2]) = calculateForwardVector(_rotation->x, _rotation->y, _rotation->z, 0, 0, 1);
	}
	return { forward[0], forward[1], forward[2] };
};
std::tuple<float, float, float> Transform::getUp() {
	if (updateUp) {
		updateUp = false;
		std::tie(up[0], up[1], up[2]) = calculateForwardVector(_rotation->x, _rotation->y, _rotation->z, 0, 1, 0);
	}
	return { up[0], up[1], up[2] };
};


void Transform::multMatrix(const float* a, int rowsA, int colsA, const float* b, int rowsB, int colsB, float* result) {
	// Verificar que las dimensiones de las matrices sean compatibles para multiplicación
	if (colsA != rowsB) {
		//std::cerr << "Error: Dimensiones incompatibles para multiplicación de matrices" << std::endl;
		DBG("Error: Dimensiones incompatibles para multiplicación de matrices");
		return;
	}

	// Multiplicar las matrices a y b
	for (int i = 0; i < rowsA; i++) {
		for (int j = 0; j < colsB; j++) {
			float sum = 0.0f;
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
	float thetaX = x;// *M_GRAD_RAD;
	float thetaY = y;// *M_GRAD_RAD;
	float thetaZ = z;// *M_GRAD_RAD;

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
bool Transform::inverseMatrix(float *  mat, float* inv){
	// Algoritmo de Gauss-Jordan para calcular la matriz inversa
	// Adaptado de https://stackoverflow.com/a/1148405

	// Matriz aumentada [A|I]
	float aug[4][8];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			aug[i][j] = mat[i * 4 + j];
		}
		for (int j = 4; j < 8; j++) {
			aug[i][j] = (i == (j - 4)) ? 1.0f : 0.0f;
		}
	}

	// Reducción por filas
	for (int i = 0; i < 4; i++) {
		// Pivoteo parcial
		int max_row = i;
		for (int j = i + 1; j < 4; j++) {
			if (fabsf(aug[j][i]) > fabsf(aug[max_row][i])) {
				max_row = j;
			}
		}
		if (max_row != i) {
			// Intercambio de filas
			for (int j = 0; j < 8; j++) {
				std::swap(aug[i][j], aug[max_row][j]);
			}
		}
		// Eliminación por filas
		for (int j = i + 1; j < 4; j++) {
			float factor = aug[j][i] / aug[i][i];
			for (int k = i; k < 8; k++) {
				aug[j][k] -= factor * aug[i][k];
			}
		}
	}

	// Reducción por columnas
	for (int i = 3; i >= 0; i--) {
		// Normalización
		float factor = aug[i][i];
		for (int j = i + 1; j < 8; j++) {
			aug[i][j] /= factor;
		}
		aug[i][i] = 1.0f;
		// Eliminación por columnas
		for (int j = i - 1; j >= 0; j--) {
			factor = aug[j][i];
			for (int k = i; k < 8; k++) {
				aug[j][k] -= factor * aug[i][k];
			}
		}
	}

	// Copia de la matriz inversa a inv
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			inv[i * 4 + j] = aug[i][j + 4];
		}
	}

	// Verificación de determinante no nulo
	float det = mat[0] * inv[0] + mat[1] * inv[4] + mat[2] * inv[8] + mat[3] * inv[12];
	if (fabsf(det) < 1e-6f) {
		return false; // Matriz singular, no se puede invertir
	}

	return true;
}

std::tuple<float, float, float> Transform::crossProduct(float x1, float y1, float z1, float x2, float y2, float z2, bool normalize) {
	float resultX = y1 * z2 - z1 * y2;
	float resultY = z1 * x2 - x1 * z2;
	float resultZ = x1 * y2 - y1 * x2;
	if (normalize) {
		float l = sqrtf(resultX * resultX + resultY * resultY + resultZ * resultZ);
		return { resultX/l, resultY/l, resultZ/l };
	} else {
		return { resultX, resultY, resultZ };
	}
}

std::tuple<float, float, float> Transform::getHierarchicalPosition() {
	if (conPivotePadre) {
		return { _position->x + _pivot2[0],_position->y + _pivot2[1], _position->z + _pivot2[2] };
	}
	return {_position->x,_position->y, _position->z};
}
void Transform::setParent(Transform* parent) {
	padre = parent;
	change();
	/*
	DELETE_MULTI(_pivot2);
	DELETE_MULTI(_rotation2);
	DELETE_MULTI(_scale2);
	conPivotePadre = false;
	if (parent == NULL) {
		return;
	}
	_pivot2 = new float[3];
	conPivotePadre = true;
	std::tie(_pivot2[0], _pivot2[1], _pivot2[2]) = parent->getHierarchicalPosition();
	_pivot2[0] -= _position->x;
	_pivot2[1] -= _position->y;
	_pivot2[2] -= _position->z;
	_rotation2 = new float[3];
	std::tie(_rotation2[0], _rotation2[1], _rotation2[2]) = parent->getRotation();
	_scale2 = new float[3];
	std::tie(_scale2[0], _scale2[1], _scale2[2]) = parent->getScale();
	//DBG("pivote Padre {%, %, %}", _pivot2[0], _pivot2[1], _pivot2[2]);
	/**/
}



////// RESTAURACIÓN Y PRESENTACIÓN
bool Transform::interfazImGUI_C(ImGuiContext* imgui) {
	ImGui::SetCurrentContext(imgui);
	ImGui::TableNextColumn();
	ImGui::Text(U8(Posición));
	ImGui::TableNextColumn();
	float posicion[3] = { _position->x,_position->y, _position->z };
	if (ImGui::DragFloatN_Colored("##posicion", posicion, 3, 0.005f, 0.0f, 0.0f, "%.6f")) {
		setPosition(posicion[0], posicion[1], posicion[2]);
		
	}

	ImGui::TableNextColumn();
	ImGui::Text((const char*)u8"Escala");
	ImGui::TableNextColumn();
	float escala[3] = { _scale->x,_scale->y, _scale->z };
	if (ImGui::DragFloatN_Colored("##escala", escala, 3, 0.005f)) {
		setScale(escala[0], escala[1], escala[2]);
	}

	ImGui::TableNextColumn();
	ImGui::Text((const char*)u8"Rotación");
	ImGui::TableNextColumn();
	float rotacion[3] = { _rotation->x * M_RAD_GRAD,_rotation->y * M_RAD_GRAD, _rotation->z * M_RAD_GRAD };
	if (ImGui::DragFloatN_Colored("##rotacion", rotacion, 3, 0.1f, 0.0f, 360.0f)) {
		setRotation(rotacion[0] * M_GRAD_RAD, rotacion[1] * M_GRAD_RAD, rotacion[2] * M_GRAD_RAD);
	}
	ImGui::TableNextColumn();
	ImGui::Text((const char*)u8"Activar pivote");
	ImGui::TableNextColumn();
	
	if (ImGui::Checkbox("##pivoteActivo", &(conPivote))) {
		update();
		cambiado();
	};
	if (!conPivote) {
		ImGui::BeginDisabled();
	}
	ImGui::TableNextColumn();
	ImGui::Text((const char*)u8"Pivote");
	ImGui::TableNextColumn();
	//float pivote[3] = { _pivot->x, _pivot->y,  _pivot->z };
	if (ImGui::DragFloatN_Colored("##pivote", _pivot, 3, 0.01f)) {
		//setRotation(pivote[0], pivote[1], pivote[2]);
		update();
		cambiado();
		
	}
	if (!conPivote) {
		ImGui::EndDisabled();
	}
	return true;
};
int Transform::saveState_interno(std::vector<unsigned char>* data, bool withID) {
	return 0;
};
void Transform::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
};

void Transform::restoreState(std::vector<unsigned char>* data, bool withID, int pos) {
	restoreState_interno(data, withID, pos);
};
/**/