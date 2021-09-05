#include "transform.h"
#include "entity.h"

Vector3* Transform::position() { return _position; };
Vector3* Transform::rotation() { return _rotation; };
Vector3* Transform::scale() { return _scale; };
void Transform::setX(float x) {
	_position->x = x;
};
void Transform::setY(float y) {
	_position->y = y;
};
void Transform::setZ(float z) {
	_position->z = z;
};
void Transform::setPosition(float x, float y, float z) {
	entidad->setRenderUpdatable();
	_position->x = x;
	_position->y = y;
	_position->z = z;
	std::vector<RenderableComponent *> * renderables= entidad->getComponents<RenderableComponent>();
	for (auto it = renderables->begin(); it != renderables->end(); it++) {
		(*it)->update();
	}

}