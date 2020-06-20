#include "renderable.h"


Renderable::~Renderable(){
	for (int i = 0; i < renderizables.size(); i++) {
		delete renderizables[i];
	}
	renderizables.clear();
}

void Renderable::clearRenderable(){
	for (int i = 0; i < renderizables.size(); i++) {
		delete renderizables[i];
	}
	renderizables.clear();
}

std::vector<renderable::Object*> Renderable::renderizables;