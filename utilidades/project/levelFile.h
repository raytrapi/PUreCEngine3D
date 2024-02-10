#ifndef _LEVEL
#define _LEVEL
#include <vector>
#include "entityFile.h"
#include "../errors/error.h"
#include "../utiles/utilidades.h"
#include <expected>
extern class Project;
extern class Global;

class EXPORTAR_UTILIDADES LevelFile {
	friend class Project;
	char* nombre = 0;
	char* ruta = 0;
	std::vector<EntityFile> entidades;
	std::string serializado = "";
	std::vector<unsigned char> serializadoBytes;
	//int load(const char* path);
	//friend class InterfaceGL;
	int save();
public:
	~LevelFile() {
		if (nombre) {
			delete[]nombre;
			nombre = 0;
		}
		if (ruta) {
			delete[]ruta;
			ruta = 0;
		}
		entidades.clear();
	}
	LevelFile() {};
	LevelFile(LevelFile& o);
	LevelFile(LevelFile&& o);
	static std::expected<LevelFile, Error> create(const char* path);
	static std::tuple<LevelFile*, unsigned int> load(const char* path);
	const char* getName();
	const char* getRoot();
	int save(std::string resto, unsigned int version = 0);
	int save(std::vector<unsigned char>* resto, unsigned int version = 0);
	std::string getSerialized();
	std::vector<unsigned char>* getSerializedByte();
};

#endif // !_LEVEL
