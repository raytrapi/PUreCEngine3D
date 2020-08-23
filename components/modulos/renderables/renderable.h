#ifndef _COMP_REND
#define _COMP_REND

#include "../../src/exportar.h"
#include "../../src/component.h"
#include "../../../modules/src/module.h"
#include "../../../graphics/src/renderable/object.h"
#include <vector>
class EXPORTAR_COMPONENTE RenderableComponent : public Component {
public:
	renderable::Object  * objeto; 

public:

	RenderableComponent(renderable::Object *obj);
	~RenderableComponent();
	renderable::Object* getRenderable() { return objeto; };
};


#endif // !_COMP_REND

