#include "object.h"

renderable::Object::~Object() {

}

void renderable::Object::setPosition(float x, float y, float z) {
	pX = x;
	pY = y;
	pZ = z;
}

void renderable::Object::setRotation(float x, float y, float z) {
	rX = x;
	rY = y;
	rZ = z;
}

float renderable::Object::getX() {
	return pX;
}

float renderable::Object::getY() {
	return pY;
}

float renderable::Object::getZ() {
	return pZ;
}

float renderable::Object::getRX() {
	return rX;
}
float renderable::Object::getRY() {
	return rY;
}
float renderable::Object::getRZ() {
	return rZ;
}


