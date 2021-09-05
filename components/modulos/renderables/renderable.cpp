#include "renderable.h"
#include "entity.h"
RenderableComponent::RenderableComponent(renderable::Object* obj) {
	objeto = obj;

};
	
RenderableComponent::~RenderableComponent() {
	utiles::Log::debug("Borro render");
	if (objeto) {
		delete objeto;
		objeto = NULL; 
	}
	
}

void RenderableComponent::rotateX(float radian) {

	setRotation(radian, rY, rZ);
}
void RenderableComponent::rotateY(float radian) {
	setRotation(rX, radian, rZ);
}
void RenderableComponent::rotateZ(float radian) {
	setRotation(rX, rY, radian);
}
void RenderableComponent::setPosition(float x, float y, float z) {
	Transform* global = entidad->transform();
	actualizar = true;
	pX = x;
	pY = y;
	pZ = z;
	transformacion[3] = pX+global->position()->x;
	transformacion[7] = pY + global->position()->y;
	transformacion[11] =  pZ + global->position()->z;
}

void RenderableComponent::moveX(float x) {
	pX += x;
	transformacion[3] = pX;
}

void RenderableComponent::setRotation(float x, float y, float z) {
	entidad->setRenderUpdatable();
	rX = x;
	if (rX > M_2PI) {
		rX = rX-M_2PI ;
	} else if (rX < 0) {
		rX = M_2PI + rX;
	}
	rY = y;
	/*if (rY > M_2PI) {
		rY = rY - M_2PI;
	} else if (rY < 0) {
		rY = M_2PI + rY;
	}*/
	rZ = z;
	if (rZ > M_2PI) {
		rZ = rZ - M_2PI;
	} else if (rZ < 0) {
		rZ = M_2PI + rZ;
	}/**/
	double cX = cos(rX);
	double sX = sin(rX);
	double cY = cos(rY);
	double sY = sin(rY);
	double cZ = cos(rZ);
	double sZ = sin(rZ);
	
	transformacion[0] = cZ*cY;
	transformacion[1] = -cX*sZ+sY*cZ*sX;
	transformacion[2] = sX* sZ + sY * cX * cZ;

	transformacion[4] = cY * sZ;
	transformacion[5] = cX*cZ + sY*sZ*sX;
	transformacion[6] = -sX * cZ + sY * cX * sZ;

	transformacion[8] = sX;
	transformacion[9] = cY*sX;
	transformacion[10] = cX*cY;
	//transformacion[3] = 0.25f;
	//this->entidad->
	//updateEntityCUBE
	
}

void RenderableComponent::setRotationGimbal(float uX, float uY, float uZ, float angle) {
	float cA = cosf(angle);
	float cA_1 = 1 - cA;
	float sA = sinf(angle);
	//float SA_1 = 1 - sA;
	

	transformacion[0] = cA+(uX*uX)*cA_1;
	transformacion[1] = uX*uY*cA_1-uZ*sA;
	transformacion[2] = uX*uZ*cA_1+uY*sA;
	transformacion[3] = 0;
	transformacion[4] = uY*uX*cA_1+uZ*sA;
	transformacion[5] = cA+ (uY*uY)*cA_1;
	transformacion[6] = uY*uZ*cA_1-uX*sA;
	transformacion[7] = 0;
	transformacion[8] = uZ*uX*cA_1-uY*sA;
	transformacion[9] = uZ*uY*cA_1+uX*sA;
	transformacion[10] = cA+(uZ*uZ)*cA_1;
	transformacion[11] = 0;
	transformacion[12] = 0;
	transformacion[13] = 0;
	transformacion[14] = 0;
	transformacion[15] = 1;
}

float RenderableComponent::getX() {
	actualizar = true;
	return pX;
}

float RenderableComponent::getY() {
	actualizar = true;
	return pY;
}

float RenderableComponent::getZ() {
	actualizar = true;
	return pZ;
}

float RenderableComponent::getRX() {
	return rX;
}
float RenderableComponent::getRY() {
	return rY;
}
float RenderableComponent::getRZ() {
	return rZ;
}

float* RenderableComponent::matrixTrans() {
	return transformacion; 
}

bool RenderableComponent::isUpdatable() {
	if (actualizar) {
		actualizar = false;
		return true;
	}
	return false;
}
/**
* Este método forzará la actualización del objeto 
*/
void RenderableComponent::update() {
	actualizar = true;
	Transform* global = entidad->transform();
	double cX = cos(rX);
	double sX = sin(rX);
	double cY = cos(rY);
	double sY = sin(rY);
	double cZ = cos(rZ);
	double sZ = sin(rZ);

	transformacion[0] = cZ * cY;
	transformacion[1] = -cX * sZ + sY * cZ * sX;
	transformacion[2] = sX * sZ + sY * cX * cZ;

	transformacion[4] = cY * sZ;
	transformacion[5] = cX * cZ + sY * sZ * sX;
	transformacion[6] = -sX * cZ + sY * cX * sZ;

	transformacion[8] = sX;
	transformacion[9] = cY * sX;
	transformacion[10] = cX * cY;

	transformacion[3] = pX + global->position()->x;
	transformacion[7] = pY + global->position()->y;
	transformacion[11] = pZ + global->position()->z;
}


