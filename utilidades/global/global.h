#ifndef _GLOBAL
#define _GLOBAL
#include <string>
#include "../utiles/utilidades.h"
enum class EXPORTAR_UTILIDADES StateCompile { NOTHING, COMPILED, COMPILING, INCORRECT, NEEDCOMPILE };
enum class EXPORTAR_UTILIDADES StateExecuting { STOP, PLAY, STOPING, RELOADING, PAUSED, RELOAD_PROJECT };
EXPORTAR_UTILIDADES class  Global {
public:
	//Input* input;
	StateCompile compileState= StateCompile::NOTHING;
	float deltaTime = 0;
	float fps = 0;
	bool showGizmoCollider = false;
	bool showGizmoColliderExpand = true;
	StateExecuting executing = StateExecuting::STOP;
	bool paused = false;
	bool reloadTape = false;
	std::string folderProject = "";
	//StateCompile getStateCompile() { return compileState; };

	float xL = 0.0f;
	float yL = 2.0f;
	float zL = 0.0f;
	float iL = 1000.0f;
	float rL = 1.0f;
	float gL = 0.0f;
	float bL = 0.0f;
	//float iL = 1000.0f;
	float iLA = 0.0f;
	float rLA = 1.0f;
	float gLA = 1.0f;
	float bLA = 1.0f;

	bool setGlobalLight(float &r, float &g, float &b, float &intensity) {
		if (rLA != r || gLA != g || bLA != b || iLA != intensity) {
			rLA = r;
			gLA = g;
			bLA = b;
			iLA = intensity;
			return true;
		}
		return false;
	};
	bool setLight0(float &x, float &y, float &z, float &r, float &g, float &b, float &intensity) {
		if (rL != r || gL != g || bL != b || xL != x || yL != y || zL != z || iL!=intensity) {
			rL = r;
			gL = g;
			bL = b;
			xL = x;
			yL = y;
			zL = z;
			iL = intensity;
			return true;
		}
		return false;
	};

};

#endif // !_GLOBAL

