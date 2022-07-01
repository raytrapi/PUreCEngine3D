#include "transform.h"
#include "entity.h"

void Transform::cambiado() {
	//Cogemos todos los que haya que notificar y notificamos
	//Por ejemplo los colliders
	if (entidad) {
		std::vector<collider::Collider*> *colliders = entidad->getComponents<collider::Collider>();
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
	std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
	for (auto it = renderables->begin(); it != renderables->end(); it++) {
		(*it)->update();
	}
	for (auto hijo : hijos) {
		hijo->setX(x);
	}
	cambiado();
};
void Transform::setY(float y) {
	_position->y = y;
	std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
	for (auto it = renderables->begin(); it != renderables->end(); it++) {
		(*it)->update();
	}
	for (auto hijo : hijos) {
		hijo->setY(y);
	}
	cambiado();
};
void Transform::setZ(float z) {
	_position->z = z;
	std::vector<RenderableComponent*>* renderables = entidad->getComponents<RenderableComponent>();
	for (auto it = renderables->begin(); it != renderables->end(); it++) {
		(*it)->update();
	}
	for (auto hijo : hijos) {
		hijo->setZ(z);
	}
	cambiado();
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
	for (auto hijo : hijos) {
		hijo->setPosition(x, y, z);
	}
	cambiado();
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
