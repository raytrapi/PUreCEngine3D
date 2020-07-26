#include "renderable.h"
RenderableComponent::RenderableComponent(renderable::Object* obj) {
	objeto = obj;

};
	
RenderableComponent::~RenderableComponent() {
	delete objeto;
}
	