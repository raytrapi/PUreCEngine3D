#include "genericFile.h"
#include "../utiles/string.h"

std::expected<bool, Error> GenericFile::loadFile(const char* path) {
	std::filesystem::path ruta(path);

	if (ruta.extension() != std::string(".pc3d")) {
		return std::unexpected(Error(-1, "No tiene una extensión conocida"));
	}
	if (!std::filesystem::exists(ruta)) {
		return std::unexpected(Error(-2, "El fichero no existe"));
	}
	return true;
}
std::expected<TYPE_FILE, Error> GenericFile::getType(const char* path) {
	//Cargamos el fichero
	auto ficheroCargado = loadFile(path);
	if (!ficheroCargado.has_value()) {
		return std::unexpected(ficheroCargado.error());
	}
	std::ifstream fs(path, std::ios::binary);
	
	unsigned int longitud = 0;
	fs.read((char*)&longitud, sizeof(unsigned int));
	char* firma = new char[longitud];
	fs.read(firma, longitud);
	TYPE_FILE tipo;
	bool conTipo = false;
	if (strcmp(firma, UID_LEVEL) == 0) {
		tipo = TYPE_FILE::FILE_LEVEL;
		conTipo = true;
		
	} else if (strcmp(firma, UID_MATERIAL) == 0) {
		tipo = TYPE_FILE::FILE_MATERIAL;
		conTipo = true;
	}else if (strcmp(firma, UID_OBJ) == 0) {
		tipo = TYPE_FILE::FILE_OBJ;
		conTipo = true;
	}
	fs.close();

	if (conTipo) {
		return tipo;
	}
	return std::unexpected(Error(-1,"Fichero no válido"));
}
std::expected<std::pair<unsigned long long, unsigned int>, Error> GenericFile::getUID_P(const char* path) {
	auto ficheroCargado = loadFile(path);
	if (!ficheroCargado.has_value()) {
		return std::unexpected(ficheroCargado.error());
	}
	std::ifstream fs(path, std::ios::binary);
	unsigned long long uid = 0;
	unsigned int longitud = 0;
	fs.read((char*)&longitud, sizeof(unsigned int));
	fs.seekg(longitud,true); //Lo hacemos relativo
	//TODO: Comprobar si el fichero tiene la longitud suficiente para almacenar el UID
	fs.read((char*)&uid, sizeof(unsigned long long));
	unsigned int pos = fs.tellg();

	fs.close();
	return std::pair<unsigned long long, unsigned int>{uid,pos};
}
std::expected<unsigned long long, Error> GenericFile::getUID(const char* path) {
	auto r = getUID_P(path);
	if (r.has_value()) {
		return (*r).first;
	}
	return std::unexpected(r.error());
}
char* GenericFile::getString(const char* path, int pos) {
	auto ficheroCargado = loadFile(path);
	if (!ficheroCargado.has_value()) {
		return NULL;
	}
	std::ifstream fs(path, std::ios::binary);
	char* cadena = 0;
	unsigned int longitud = 0;
	fs.read((char*)&longitud, sizeof(unsigned int));
	fs.seekg(longitud + sizeof(unsigned long long)+pos, true); //Lo hacemos relativo

	fs.read((char*)&longitud, sizeof(unsigned int));
	if (longitud > 0) {
		cadena = new char[longitud];
		fs.read(cadena, sizeof(char)*longitud);
	}
	fs.close();
	return cadena;
}
std::string GenericFile::serializate(const char* key, std::string value,bool conSeparador, bool conComillas) {
	//TODO: Controlar que el value no lleve /@/....
	return "\""+std::string(key) + "\":"+(conComillas?"\"":"") + value + (conComillas ? "\"" : "") + (conSeparador ? "," : "") + "\r\n";
}
std::string GenericFile::serializate(const char* key, std::tuple<float, float, float> value, bool conSeparador) {
	return "\"" + std::string(key) + "\":["+std::to_string(std::get<0>(value)) + "," + std::to_string(std::get<1>(value)) + "," + std::to_string(std::get<2>(value))+"]" + (conSeparador ? "," : "") + "\r\n";
}
std::string GenericFile::serializate(const char* key, std::tuple<float, float, float,float> value, bool conSeparador) {
	return "\"" + std::string(key) + "\":[" + std::to_string(std::get<0>(value)) + "," + std::to_string(std::get<1>(value)) + "," + std::to_string(std::get<2>(value)) + "," + std::to_string(std::get<3>(value)) + "]" + (conSeparador ? "," : "") + "\r\n";
}
std::string GenericFile::serializate(const char* key, float value, bool conSeparador) {
	return "\"" + std::string(key) + "\":"+std::to_string(value) + (conSeparador ? "," : "") + "\r\n";
}
std::string GenericFile::serializate(const char* key, int value, bool conSeparador) {
	return "\"" + std::string(key) + "\":" + std::to_string(value) + (conSeparador ? "," : "") + "\r\n";
}


std::tuple<int, std::string, std::string> GenericFile::unserializate(std::string s, int pos) {
	std::string clave = "";
	std::string valor = "";
	std::string* actual = &clave;
	char cierre = '"';
	char apertura = '"';
	int cierres = 1;
	int modo = -1;
	bool enValor = false;
	bool conValor = false;
	while (modo<3 && pos < s.length()) {
		if (s[pos] == cierre) {
			if (cierres > 1) {
				cierres--;
				if (conValor) {
					(*actual) += s[pos];
				}
			} else {
				if (!conValor) {
					conValor = true;
					if (modo == -1) {
						modo = 0;
					}
				} else {
					conValor = false;
					modo++;
				}
			}
		} else if (s[pos] == ' ' || s[pos] == '\t' || s[pos] == '\r' || s[pos] == '\n') {
			//De momento no hacemos nada
		} else if (s[pos] == ':') {
			if (modo == 1) {
				modo++;
				actual = &valor;
				conValor = false;
			} else {
				if (conValor) {
					(*actual) += s[pos];
				}
			}
		} else if (s[pos] == '[') {
			if (modo == 2 && !conValor ) {
				cierre = ']';
				apertura = '[';
				conValor = true;
			} else {
				if (apertura == '[') {
					cierres++;
				}
				(*actual) += s[pos];
			}
		} else if (s[pos] == '{') {
			if (modo == 2 && !conValor) {
				cierre = '}';
				apertura = '{';
				conValor = true;
			} else {
				if (apertura == '{') {
					cierres++;
				}
				(*actual) += s[pos];
			}
		} else {
			if ((modo == 0 || modo == 2)) {
				if (!conValor && modo == 2) {
					cierre = ',';
					conValor = true;
				}
				(*actual) += s[pos];
			}
		}
		pos++;
	}
	return { pos,clave,valor };
}
int GenericFile::jumpSerializateTo(char c, std::string s, int pos) {
	while (s[pos] != c && pos < s.length()) {
		pos++;
	}
	return pos+1;
}

float GenericFile::unserializatef(std::string s) {
	return std::atof(s.c_str());
}
int GenericFile::unserializatei(std::string s) {
	return std::atoi(s.c_str());
}
std::tuple<float, float> GenericFile::unserializate2f(std::string s) {
	auto valores=utils::String::split(s, ',');
	return { std::atof(valores[0].c_str()),std::atof(valores[1].c_str()) };
}
std::tuple<float, float, float> GenericFile::unserializate3f(std::string s) {
	auto valores = utils::String::split(s, ',');
	return { std::atof(valores[0].c_str()),std::atof(valores[1].c_str()),std::atof(valores[2].c_str()) };
}
std::tuple<float, float, float, float> GenericFile::unserializate4f(std::string s) {
	auto valores = utils::String::split(s, ',');
	return { std::atof(valores[0].c_str()),std::atof(valores[1].c_str()),std::atof(valores[2].c_str()),std::atof(valores[3].c_str()) };
}

std::string GenericFile::eraseCharacters(std::string sO, char caracteres[]) {
	std::string s;
	int longitud = sizeof(caracteres) / sizeof(char);
	for (auto c : sO) {
		bool sirve = true;
		for (int i = 0; i < longitud && sirve;i++) {
			sirve = (c != caracteres[i]);
		}
		if (sirve) {
			s += c;
		}
		
	}
	return s;
}