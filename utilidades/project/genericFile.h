#ifndef _GENERIC_FILE
#define _GENERIC_FILE
#include "UIDProject.h"
#include "..\errors\error.h"
#include "../utiles/utilidades.h"
#include <iostream>
#include <fstream>
#include <expected>
#include <filesystem>

enum EXPORTAR_UTILIDADES TYPE_FILE {
	FILE_NULL,
	FILE_FOLDER,
	FILE_LEVEL,
	FILE_MATERIAL,
	FILE_IMG,
	FILE_OBJ
};
enum EXPORTAR_UTILIDADES TYPE_OBJECT_SERIALIZABLES {
	SERIALIZABLE_COMPONENTE_RENDERABLE,
	SERIALIZABLE_COMPONENTE_LUZ,
	SERIALIZABLE_COMPONENTE_RIGIDBODY,
	SERIALIZABLE_COMPONENTE_BOXCOLLIDER,
	SERIALIZABLE_COMPONENTE_CODE,
	SERIALIZABLE_COMPONENTE_SHADER,
	SERIALIZABLE_COMPONENTE_CAMERA,
	SERIALIZABLE_COMPONENTE_AUDIO,
	SERIALIZABLE_COMPONENTE_COLLIDER,
	SERIALIZABLE_COMPONENTE_INTERFACE,
	SERIALIZABLE_COMPONENTE_DINAMIC
};
class EXPORTAR_UTILIDADES GenericFile {
	static std::expected<bool, Error> loadFile(const char* path);
public:
	
	static std::expected<TYPE_FILE,Error> getType(const char* path);
	static std::expected<unsigned long long, Error> getUID(const char* path);
	static char* getString(const char* path,int pos=0);
	static std::expected<std::pair<unsigned long long,unsigned int>, Error> getUID_P(const char* path);
	
	static std::string serializate(const char* key, std::string value, bool conSeparador=true, bool conComillas=true);
	static std::string serializate(const char* key, std::tuple<float, float, float> value, bool conSeparador = true);
	static std::string serializate(const char* key, std::tuple<float, float, float,float> value, bool conSeparador = true);
	static std::string serializate(const char* key, float value, bool conSeparador = true);
	static std::string serializate(const char* key, int value, bool conSeparador = true);

	static std::tuple<int, std::string, std::string> unserializate(std::string s, int pos);
	static float unserializatef(std::string s);
	static int unserializatei(std::string s);
	static std::tuple<float,float> unserializate2f(std::string s);
	static std::tuple<float, float, float> unserializate3f(std::string s);
	static std::tuple<float, float, float, float> unserializate4f(std::string s);
	static int jumpSerializateTo(char c, std::string s, int pos);
	static std::string eraseCharacters(std::string s, char caracteres[]);
};


#endif // !_GENERIC_FILE
