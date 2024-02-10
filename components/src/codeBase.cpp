#include "codeBase.h"

Camera* CodeBase::getActiveCamera() {
	//Entity::getAc
	if (motorGrafico) {
		return motorGrafico->getActiveCamera();
	}
	return NULL;
}