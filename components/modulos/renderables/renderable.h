#ifndef _COMP_REND
#define _COMP_REND

#include "../../src/exportar.h"
#include "../../src/component.h"
#include <module.h>
#include "../../../graphics/src/renderable/object.h"
#include <vector>
class EXPORTAR_COMPONENTE RenderableComponent : public Component {
public:
	renderable::Object  * objeto; 

public:

	RenderableComponent(renderable::Object *obj);
	~RenderableComponent();
};


#endif // !_COMP_REND

