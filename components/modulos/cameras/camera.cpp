#include "camera.h"

void Camera::ponerOrto() {
	proyeccion[0] = 2.f / (derecha - izquierda);
	proyeccion[1] = proyeccion[2] = 0.f;
	proyeccion[3] = -((derecha+izquierda)/(derecha-izquierda));
	proyeccion[4] = 0.f;
	proyeccion[5] = 2.f / (arriba - abajo);
	proyeccion[6] =  0.f;
	proyeccion[7] = -((arriba + abajo) / (arriba - abajo));
	proyeccion[8] = proyeccion[9] = 0.f;
	proyeccion[10] = -2.f / (lejos - cerca);
	proyeccion[11] = -((lejos+cerca) / (lejos-cerca));
	proyeccion[12] = proyeccion[13] = proyeccion[14] = 0.f;
	proyeccion[15] = 1;
	/*proyeccion[0] = 2.f / (derecha - izquierda);
	proyeccion[1] = proyeccion[2] = proyeccion[3] = 0.f;
	proyeccion[4] = 2.f / (arriba - abajo);
	proyeccion[5] = proyeccion[6] = proyeccion[7] = 0.f;
	proyeccion[8] = -2.f / (lejos - cerca);
	proyeccion[9] = proyeccion[10] = proyeccion[11] = 0.f;
	proyeccion[12] = -(derecha + izquierda) / (derecha - izquierda);
	proyeccion[13] = -(arriba + abajo) / (arriba - abajo);
	proyeccion[14] = -(lejos + cerca) / (lejos - cerca);
	proyeccion[15] = 1.f;/**/
}
/*void Camera::ponerOrto() {
	proyeccion[0] = 2.f / (derecha - izquierda);
	proyeccion[1] = proyeccion[2] = 0.f;
	proyeccion[3] = -((derecha + izquierda) / (derecha - izquierda));
	proyeccion[4] = 0.f;
	proyeccion[5] = 2.f / (arriba - abajo);
	proyeccion[6] = 0.f;
	proyeccion[7] = -((arriba + abajo) / (arriba - abajo));
	proyeccion[8] = proyeccion[9] = 0.f;
	proyeccion[10] = -2.f / (lejos - cerca);
	proyeccion[11] = -((lejos + cerca) / (lejos - cerca));
	proyeccion[12] = proyeccion[13] = proyeccion[14] = 0.f;
	proyeccion[15] = 1;

}/**/

void Camera::ponerPerspectiva() {
	if (!focal) {

		proyeccion[0] = 2.f  / (derecha - izquierda);
		proyeccion[1] = 0;
		proyeccion[2] = (derecha + izquierda) / (derecha - izquierda);
		proyeccion[3] = 0.f;
		proyeccion[4] = 0.f;
		proyeccion[5] = 2.f / (arriba - abajo);
		proyeccion[6] = (arriba + abajo) / (arriba - abajo);
		proyeccion[7] = proyeccion[8] = proyeccion[9] = 0.f;
		proyeccion[10] = -(lejos + cerca) / (lejos - cerca);
		proyeccion[11] = -2.f*lejos*cerca/(lejos-cerca);
		proyeccion[12] = proyeccion[13] = 0.f;
		proyeccion[14] = 1.f;
		proyeccion[15] = 0.f;
		/*proyeccion[0] = 2.f * cerca / (derecha - izquierda);
		proyeccion[1] = proyeccion[2] = proyeccion[3] = 0.f;
		proyeccion[4] = 2.f * cerca / (arriba - abajo);
		proyeccion[5] = proyeccion[6] = proyeccion[7] = 0.f;
		proyeccion[8] = (derecha + izquierda) / (derecha - izquierda);
		proyeccion[9] = (arriba + abajo) / (arriba - abajo);
		proyeccion[10] = -(lejos + cerca) / (lejos - cerca);
		proyeccion[11] = -1.f;
		proyeccion[12] = -2.f * (lejos * cerca) / (lejos - cerca);
		proyeccion[13] = proyeccion[14] = proyeccion[15] = 0.f;/**/
	} else {
		float const a = 1.f / tanf(anguloFocal / 2.f);

		proyeccion[0] = a / ((derecha-izquierda) / (arriba- abajo));
		proyeccion[1] = proyeccion[2] = proyeccion[3] = 0.f;
		proyeccion[4] = 0.f;
		proyeccion[5] = a;
		proyeccion[6] = proyeccion[7] = proyeccion[8] = proyeccion[9] = 0.f;
		proyeccion[10] = -((lejos + cerca) / (lejos - cerca));
		proyeccion[11] = -1.f;
		
		proyeccion[12] = proyeccion[13] = proyeccion[14] = 0.f;
		proyeccion[15] = 1.f;
		/*proyeccion[12] = proyeccion[13] = 0.f;
		proyeccion[14] = -((2.f * lejos * cerca) / (lejos - cerca));
		proyeccion[15] = 0.f;/**/
	}
}

void Camera::ponerVista() {

	
	//TODO: crear método par calcular la dimensión y la normal
	//float f_t[3] = { eye[0] - target[0], eye[1] - target[1], eye[2] - target[2] };
	float f_t[3] = { target[0] - eye[0], target[1] - eye[1], target[2] - eye[2] };

	//OJO puede ser todo 0;
	distanciaObjetivo= sqrtf(f_t[0] * f_t[0] + f_t[1] * f_t[1] + f_t[2] * f_t[2]);
	//float normalDistancia = 1.f / distanciaObjetivo;
	//float f_dimension =  sqrtf(f_t[0]* f_t[0] + f_t[1]* f_t[1]  + f_t[2]*f_t[2]);
	float axiZ[3] = { f_t[0] / distanciaObjetivo, f_t[1] / distanciaObjetivo, f_t[2] / distanciaObjetivo };

	//float s_t[3] = { f[1] * up[2] - f[2] * up[1], f[2] * up[0] - f[0] * up[2], f[0] * up[1] - f[1] * up[0] };
	//Producto en cuz de axiZ y Up
	float s_t[3] = {
		axiZ[1] * up[2] - axiZ[2] * up[1],
		axiZ[2] * up[0] - axiZ[0] * up[2],
		axiZ[0] * up[1] - axiZ[1] * up[0]
	};/**/
	
	/*float s_t[3] = {
		up[1] * axiZ[2] - up[2] * axiZ[1],
		up[2] * axiZ[0] - up[0] * axiZ[2],
		up[0] * axiZ[1] - up[1] * axiZ[0]
	};/**/
	float s_hipo = sqrtf(s_t[0]* s_t[0] + s_t[1]* s_t[1] + s_t[2]* s_t[2]);
	float s_dimension = (s_hipo != 0) ? s_hipo : 1;
	//OJO puede ser todo 0;
	float axiX[3] = { s_t[0] / s_dimension, s_t[1] / s_dimension, s_t[2] / s_dimension };

	//float t[3] = { s[1] * f[2] - s[2] * f[1], s[2] * f[0] - s[0] * f[2], s[0] * f[1] - s[1] * f[0] };
	float axiY[3] = {
		axiX[1] * axiZ[2] - axiX[2] * axiZ[1],
		axiX[2] * axiZ[0] - axiX[0] * axiZ[2],
		axiX[0] * axiZ[1] - axiX[1] * axiZ[0]
	};/**/
	/*float axiY[3] = {
		axiZ[1] * axiX[2] - axiZ[2] * axiX[1],
		axiZ[2] * axiX[0] - axiZ[0] * axiX[2],
		axiZ[0] * axiX[1] - axiZ[1] * axiX[0]
	};/**/


	//look_at
	vista[0] = axiX[0];
	vista[1] = axiY[0];
	vista[2] = -axiZ[0];
	vista[3] = 0.f;
	vista[4] = axiX[1];
	vista[5] = axiY[1];
	vista[6] = -axiZ[1];
	vista[7] = 0.f;
	vista[8] = axiX[2];
	vista[9] = axiY[2];
	vista[10] = -axiZ[2];
	vista[11] = 0.f;
	vista[12] = (axiX[0] * -eye[0]) + (axiY[0] * -eye[1]) + (axiZ[0] * eye[2]);
	vista[13] = (axiX[1] * -eye[0]) + (axiY[1] * -eye[1]) + (axiZ[1] * eye[2]);
	vista[14] = (axiX[2] * -eye[0]) + (axiY[2] * -eye[1]) + (axiZ[2] * eye[2]);
	vista[15] = 1.f;
}
void Camera::ponerVista2() {


	//TODO: crear método par calcular la dimensión y la normal
	float f_t[3] = { eye[0] - target[0], eye[1] - target[1], eye[2] - target[2] };
	//float f_t[3] = { target[0] - eye[0], target[1] - eye[1], target[2] - eye[2] };

	//OJO puede ser todo 0;
	float f_dimension = sqrtf(f_t[0] * f_t[0] + f_t[1] * f_t[1] + f_t[2] * f_t[2]);
	float axiZ[3] = { f_t[0] / f_dimension, f_t[1] / f_dimension, f_t[2] / f_dimension };

	//float s_t[3] = { f[1] * up[2] - f[2] * up[1], f[2] * up[0] - f[0] * up[2], f[0] * up[1] - f[1] * up[0] };
	/*float s_t[3] = {
		axiZ[1] * up[2] - axiZ[2] * up[1],
		axiZ[2] * up[0] - axiZ[0] * up[2],
		axiZ[0] * up[1] - axiZ[1] * up[0]
	};/**/
	float s_t[3] = {
		up[1] * axiZ[2] - up[2] * axiZ[1],
		up[2] * axiZ[0] - up[0] * axiZ[2],
		up[0] * axiZ[1] - up[1] * axiZ[0]
	};/**/
	float s_hipo = sqrtf(s_t[0] * s_t[0] + s_t[1] * s_t[1] + s_t[2] * s_t[2]);
	float s_dimension = (s_hipo != 0) ? s_hipo : 1;
	//OJO puede ser todo 0;
	float axiX[3] = { s_t[0] / s_dimension, s_t[1] / s_dimension, s_t[2] / s_dimension };

	//float t[3] = { s[1] * f[2] - s[2] * f[1], s[2] * f[0] - s[0] * f[2], s[0] * f[1] - s[1] * f[0] };
	/*float axiY[3] = {
		axiX[1] * axiZ[2] - axiX[2] * axiZ[1],
		axiX[2] * axiZ[0] - axiX[0] * axiZ[2],
		axiX[0] * axiZ[1] - axiX[1] * axiZ[0]
	};/**/
	float axiY[3] = {
		axiZ[1] * axiX[2] - axiZ[2] * axiX[1],
		axiZ[2] * axiX[0] - axiZ[0] * axiX[2],
		axiZ[0] * axiX[1] - axiZ[1] * axiX[0]
	};/**/


	//look_at
	vista[0] = axiX[0];
	vista[1] = axiY[0];
	vista[2] = axiZ[0];
	vista[3] = 0.f;
	vista[4] = axiX[1];
	vista[5] = axiY[1];
	vista[6] = axiZ[1];
	vista[7] = 0.f;
	vista[8] = axiX[2];
	vista[9] = axiY[2];
	vista[10] = axiZ[2];
	vista[11] = 0.f;
	vista[12] = (axiX[0] * -eye[0]) + (axiX[1] * -eye[1]) + (axiX[2] * -eye[2]); //MAL
	vista[13] = (axiY[0] * -eye[0]) + (axiY[1] * -eye[1]) + (axiY[2] * -eye[2]); //MAL
	vista[14] = (axiZ[0] * -eye[0]) + (axiZ[1] * -eye[1]) + (axiZ[2] * -eye[2]); //MAL
	vista[15] = 1;
}
void Camera::actualizarProyeccion() {
	if (ortogonal) {
		//Modificamos la tabla a modo ortogonal
		ponerOrto();
	} else {
		ponerPerspectiva();
	}
	if (activa) {
		if (graphic == NULL) {
			graphic=Module::get<modules::graphics::Graphic>();
		}
		if (graphic != NULL) {
			graphic->updateEntities();
		}
		/*modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->changeCamera(this);
		}/**/

	}
}

Camera::Camera() {
	//transformada = new Transform();
	graphic = Module::get<modules::graphics::Graphic>();
	
}

Camera::~Camera() {
	//delete transformada;
}

Transform* Camera::transform() {
	//return transformada;
	return NULL;
}

bool Camera::isActive() {
	return activa;
}

void Camera::setActive(bool active) {
	activa = active;
	if (active) {
		if (graphic == NULL) {
			graphic = Module::get<modules::graphics::Graphic>();
		}
		
		if (graphic != NULL) {
			graphic->changeCamera(this);
		}
	}
}

bool Camera::isOrtho() {
	return ortogonal;
}

void Camera::setOrto(bool ortho) {
	ortogonal = ortho;
	actualizarProyeccion();
}

void Camera::setSize(float x, float y, float width, float height) {
	izquierda = x;
	derecha = width;
	arriba = height;
	abajo = y;
	if (activa) {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->resizeCamera();
		}/**/
		actualizarProyeccion();
	}
}

void Camera::setDistance(float _near, float _far) {
	cerca = _near;
	lejos = _far;
	actualizarProyeccion();
	conCambio = true;

}

void Camera::setFocalAngle(float angle) {
	anguloFocal = angle;
	actualizarProyeccion();
}

void Camera::setFocal(float focal) {
	this->focal = focal;
}

//void Camera::setLookAt(float eye[3], float target[3], float up[3]) {
void Camera::setLookAt(float eyeX, float eyeY, float eyeZ, float targetX, float targetY, float targetZ, float upX, float upY, float upZ){
	this->eye[0] = eyeX;
	this->eye[1] = eyeY;
	this->eye[2] = eyeZ;
	this->target[0] = targetX;
	this->target[1] = targetY;
	this->target[2] = targetZ;
	this->up[0] = upX;
	this->up[1] = upY;
	this->up[2] = upZ;

	float dX = eye[0] - target[0];
	float dY = eye[1] - target[1];
	float dZ = eye[2] - target[2];
	distanciaObjetivo = sqrtf(dX * dX + dY * dY + dZ * dZ);
	

	ponerVista();
	conCambio = true;
	/*if (activa) {
		modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
		if (g) {
			g->changeCamera(this);
		}
	}/**/
}

const float* Camera::getViewMatrix() {
	return vista;
}

const float* Camera::getProjectionMatrix() {
	return proyeccion;
}

float Camera::getWidth() {
	return derecha-izquierda;
}

float Camera::getHeight() {
	return abajo-arriba;
}
float Camera::getLeft() {
	return izquierda;
}
float Camera::getRight() {
	return derecha;
}
float Camera::getTop() {
	return arriba;
}
float Camera::getBottom() {
	return abajo;
}

const float Camera::getFocalAngle() {
	return anguloFocal;
}

void Camera::setPosX(float v) {
	eye[0] = v;
	conCambio = true;
};
void Camera::setPosEyeX(float v) {
	target[0] = v;
	conCambio = true;
};
float Camera::getPosX() {
	return eye[0];
};
float Camera::getPosEyeX() {
	return target[0];
};
void Camera::setPosY(float v) {
	eye[1] = v;
	conCambio = true;
};
void Camera::setPosEyeY(float v) {
	target[1] = v;
	conCambio = true;
};
float Camera::getPosY() {
	return eye[1];
};
float Camera::getPosEyeY() {
	return target[1];
};
void Camera::setPosZ(float v) {
	eye[2] = v;
	conCambio = true;
};
void Camera::setPosEyeZ(float v) {
	target[2] = v;
	conCambio = true;
};
float Camera::getPosZ() {
	return eye[2];
};
float Camera::getPosEyeZ() {
	return target[2];
}
std::tuple<float, float> Camera::getNormalizeScreenExtra(double x, double y) {
	if (graphic == NULL) {
		graphic = Module::get<modules::graphics::Graphic>();
	}
	if (graphic != NULL) {
		auto [w, h] = graphic->getScreenSize();
		return { (((float)x / (float)w) * 2.0f) - 1.f,(((float)y / (float)h) * 2.0f) - 1.f };
	} else {
		return { 0,0 };
	}

};
std::tuple<float, float> Camera::getNormalizeScreen(double x, double y) {
	if (graphic == NULL) {
		graphic = Module::get<modules::graphics::Graphic>();
	}
	if (graphic != NULL) {
		auto [w,h]=graphic->getScreenSize();
		return {(float)x/(float)w,(float)y / (float)h};
	} else {
		return { 0,0 };
	}
	
};

float Camera::getRotX() {
	return anguloCamara[0];
};
float Camera::getRotY() {
	return anguloCamara[1];
};
float Camera::getRotZ() {
	return anguloCamara[2];
};
void Camera::setRotate(float x, float y, float z) {
	anguloCamara[0] = x;
	anguloCamara[1] = y;
	anguloCamara[2] = z;
	target[0] = distanciaObjetivo * sinf(y);
	target[2] = distanciaObjetivo * cosf(y);
	conCambio = true;
};
void Camera::refresh(int modo) {

	if ((modo & 1)>0) {
		ponerVista();
	}
	if ((modo & 2)>0) {
		if (ortogonal) {
			//Modificamos la tabla a modo ortogonal
			ponerOrto();
		} else {
			ponerPerspectiva();
		}
	}
	
	/*if (activa) {
		if (graphic == NULL) {
			graphic = Module::get<modules::graphics::Graphic>();
		}
		if (graphic != NULL) {
			graphic->updateEntities();
		}

	}/**/
}

bool Camera::isChange() {
	if (conCambio) {
		conCambio = false;
		return true;
	}
	return false;
}
bool modules::graphics::Graphic::isChangeCamera(Camera* camera) {
	if (camera != NULL) {
		return camera->isChange();
	}
	return false;
}