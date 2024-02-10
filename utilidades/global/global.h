#ifndef _GLOBAL
#define _GLOBAL





#include <string>
#include <filesystem>
#include <functional>
#include "node.h"
#include "../utiles/utilidades.h"
#include "../project/projectFile.h"
#include "../project/levelFile.h"
#include "config.h"

namespace modules{
	extern class Tape;
}
extern class Entity;
struct Directory {
	std::string name;
	std::string path;
	int id;
	Directory* parent=0;

};

typedef Node<Directory> treeDirectory;

enum class EXPORTAR_UTILIDADES StateCompile { NOTHING, COMPILED, COMPILING, INCORRECT, NEEDCOMPILE };
enum class EXPORTAR_UTILIDADES StateExecuting { STOP, PLAY, STOPING, RELOADING, PAUSED, RELOAD_PROJECT };
class EXPORTAR_UTILIDADES  Global {
	static treeDirectory* directorioCarpetas;
	static LevelFile* actualLevel;
	static int cargarCarpetas(const char * ruta, treeDirectory*padre=0, int id=-1, std::string rutaPadre="");
	static const char* ext;//Contiene la extensión de los ficheros
	std::function<void(unsigned int)> funcionLoadLevel=0;
	static Global* instancia;
	std::vector<unsigned char> estadoActual;
	int versionNivel = 0;
	//Entity* entidad=0;
public:
	//Global(Entity *e);
	Global();
	~Global();

	static const char* getExt();
	//Entity* createEntity();
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
	static std::string rootProject;
	int getVersionLevel() { return versionNivel; };
	modules::Tape* cartucho = 0;
	bool juegoIniciado = false;
	//StateCompile getStateCompile() { return compileState; };

	float xL = 0.0f;
	float yL = 2.0f;
	float zL = 0.0f;
	float iL = 1000.0f;
	float rL = 1.0f;
	float gL = 0.0f;
	float bL = 0.0f;
	//float iL = 1000.0f;
	float iLA = 0.5f;
	float rLA = 1.0f;
	float gLA = 1.0f;
	float bLA = 1.0f;
	int modoEditor = 0;

	float outlineThink = 0.2f;

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
	/*bool setLight0(float& x, float& y, float& z, float& r, float& g, float& b, float& intensity) {
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
	};/**/
	ProjectFile proyecto;
	
	int loadProject(const char* path, bool create=false);
	static treeDirectory* getDirectory(bool refresh=false);
	static LevelFile* getLevelFile();
	static std::string getPathRoot();
	void setPathRoot(const char* path);
	static std::expected<LevelFile,Error> newLevel(std::string path);
	void loadLevel(const char * filePath);
	void onLoadLevel(std::function<void(unsigned int)> f);
	static void loadConfig();
	static void saveConfig();
	static Global* getInstance();

	//void saveState();
	std::vector<unsigned char>* getDataState() { return &estadoActual; };


	//Interfaz
	int xIniScreen = 0;
	int yIniScreen = 0;
	int marginTop = 0;
	int marginRight = 0;
	int marginButtom = 0;
	int marginLeft = 0;
	int widthScreen = 0;
	int heightScreen = 0;


	float uBotonCompilacion;
	float vBotonCompilacion;
	unsigned int idTexturaIconos;
};

#endif // !_GLOBAL

