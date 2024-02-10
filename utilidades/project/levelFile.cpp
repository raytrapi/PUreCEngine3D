#include "levelFile.h"
#include "../global/global.h"
#include <log.h>

std::expected<LevelFile, Error> LevelFile::create(const char* path) {
	std::filesystem::path ruta(Global::getPathRoot() + path);
	if (ruta.extension() != "pc3d") {
		ruta += ".pc3d";
		
	}
	if (std::filesystem::exists(ruta)) {
		return std::unexpected(Error(-1,"El fichero ya existe"));
	}
	LevelFile level;
	auto parent = ruta.parent_path().string();
	//const char* rutaT = ruta.parent_path().string().c_str();
	//DBG("%", parent.parent_path());
	level.ruta = new char[parent.length() + 1];
	/*level.ruta = new char[parent.length() + 1- Global::getPathRoot().length()];
	int j = 0;
	for (int i = Global::getPathRoot().length(); i < parent.length();i++) {
		level.ruta[j++]=parent[i];
	}/**/
	strcpy(level.ruta, parent.c_str());
	level.ruta[parent.length()] = '\0';

	parent = ruta.stem().string();
	level.nombre = new char[parent.length() + 1];
	strcpy(level.nombre, parent.c_str());
	level.nombre[parent.length()] = '\0';
	//DBG("L[%] - [%]", level.ruta, level.nombre);
	level.save();
	return level;
}
int LevelFile::save() {
	return save("");
}
int LevelFile::save(std::string resto, unsigned int version) {
	if (ruta) {
		DBG("Grabo en %", ( std::string(ruta) + "/" + std::string(nombre) + Global::getExt()).c_str());
		std::ofstream fs((std::string(ruta)+"/"+std::string(nombre) + Global::getExt()).c_str(), std::ios::binary);
		unsigned int longitud = strlen(UID_LEVEL) + 1;
		fs.write((char*)&longitud, sizeof(unsigned int));
		fs.write(UID_LEVEL, longitud);
		fs.write((char*)&version, sizeof(unsigned int));
		longitud = resto.length();
		fs.write((char*)&longitud, sizeof(unsigned int));
		fs.write(resto.c_str(), longitud);

		fs.close();
	}
	return 0;
}
int LevelFile::save(std::vector<unsigned char>* resto, unsigned int version) {
	if (ruta) {
		DBG("Grabo en %", (std::string(ruta) + "/" + std::string(nombre) + Global::getExt()).c_str());
		std::ofstream fs((std::string(ruta) + "/" + std::string(nombre)+Global::getExt()).c_str(), std::ios::binary);
		unsigned int longitud = strlen(UID_LEVEL) + 1;
		fs.write((char*)&longitud, sizeof(unsigned int));
		fs.write(UID_LEVEL, longitud);
		fs.write((char*)&version, sizeof(unsigned int));
		longitud = resto->size();
		fs.write((char*)&longitud, sizeof(unsigned int));
		for (auto c : *resto) {
			fs.write((char*)&c, sizeof(unsigned char));
		}

		fs.close();
	}
	return 0;
}
std::tuple<LevelFile*,unsigned int> LevelFile::load(const char* path) {
	LevelFile* l = new LevelFile();
	//Solo por comodidad, en realidad se tendría que obtener el nombre en base a una búsqueda dentro del path
	std::filesystem::path rutaNivel((Global::getPathRoot() + ""+path));
	auto e = rutaNivel.extension();
	if (rutaNivel.extension() != Global::getExt()) {
		rutaNivel += Global::getExt();

	}
	auto nombreNivel = rutaNivel.stem().string();
	l->nombre = new char[nombreNivel.length() + 1];
	strcpy(l->nombre, nombreNivel.c_str());
	l->nombre[nombreNivel.length()] = '\0';

	auto parent = rutaNivel.parent_path().string();
	l->ruta = new char[parent.length() + 1];
	strcpy(l->ruta, parent.c_str());
	l->ruta[parent.length()] = '\0';

	std::ifstream fs(rutaNivel.c_str(), std::ios::binary);
	unsigned int version = 0;
	if (fs.peek() != std::ifstream::traits_type::eof()) {
		unsigned int longitud = 0;
		fs.read((char*)&longitud, sizeof(unsigned int));
		char * firma = new char[longitud];
		fs.read(firma, longitud);
		if (strcmp(firma, UID_LEVEL) != 0) {
			fs.close();
			return { NULL, 0}; //El fichero no es correcto
		}
		fs.read((char*)&version, sizeof(unsigned int));
		fs.read((char*)&longitud, sizeof(unsigned int));
		char* resto = new char[longitud];
		//l->serializado = std::string(' ', longitud);
		fs.read(resto, longitud);
		if (version > 0) {
			l->serializadoBytes.clear();
			for (int i = 0; i < longitud; i++) {
				l->serializadoBytes.push_back(resto[i]);
			}
		} else {
			l->serializado = std::string(resto);
		}
		delete[] resto;
		fs.close();
	}



	return { l, version};
}
std::string LevelFile::getSerialized() {
	return serializado;
}
std::vector<unsigned char>* LevelFile::getSerializedByte() {
	return &serializadoBytes;
}
LevelFile::LevelFile(LevelFile& o) {
	ruta = new char[strlen(o.ruta)+1];
	strcpy(ruta, o.ruta);
	ruta[strlen(o.ruta)] = '\0';
	nombre = new char[strlen(o.nombre) + 1];
	strcpy(nombre, o.nombre);
	nombre[strlen(o.nombre)] = '\0';
}
LevelFile::LevelFile(LevelFile&& o) {
	ruta = new char[strlen(o.ruta) + 1];
	strcpy(ruta, o.ruta);
	ruta[strlen(o.ruta)] = '\0';
	nombre = new char[strlen(o.nombre) + 1];
	strcpy(nombre, o.nombre);
	nombre[strlen(o.nombre)] = '\0';
}

const char* LevelFile::getName() {
	return (const char*) nombre;
}
const char* LevelFile::getRoot() {
	auto g = Global::getInstance();
	if (g) {
		auto s = g->getPathRoot();
		if (ruta[0] == s[0] && ruta[1] == s[1]) {
			return ruta + s.length();
		}
	}
	return ruta;
}