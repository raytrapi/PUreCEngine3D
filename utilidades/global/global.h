#ifndef _GLOBAL
#define _GLOBAL

#include "../utiles/utilidades.h"
enum class EXPORTAR_UTILIDADES StateCompile { NOTHING, COMPILED, COMPILING, INCORRECT, NEEDCOMPILE };
EXPORTAR_UTILIDADES class  Global {
public:
	//Input* input;
	StateCompile compileState= StateCompile::NOTHING;
	float deltaTime = 0;
	float fps = 0;
	bool showGizmoCollider = true;
	bool showGizmoColliderExpand = false;
	//StateCompile getStateCompile() { return compileState; };
};

#endif // !_GLOBAL

