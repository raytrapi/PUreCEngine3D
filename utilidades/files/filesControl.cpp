#include "filesControl.h"
fileControl::fileControl() {
	//Ejecutamos cuando cojemos el foco
}
fileControl::~fileControl() {
	for (auto itr = carpetasCambio.begin(); itr != carpetasCambio.end(); itr++) {
		delete (*itr);
	}
	carpetasCambio.clear();
	for (auto itr = ficherosCambio.begin(); itr != ficherosCambio.end(); itr++) {
		delete (*itr);
	}
	ficherosCambio.clear();
}
bool fileControl::check(fileControl::EstadoRuta *mod, fileControl::Tipos tipo) {
	std::filesystem::file_time_type t;
	bool cambio = false;
	//Buscamos dentro de la carpeta para ver si hay cambios
	switch (tipo) {
	case fileControl::CARPETA:

		break;
	case fileControl::FICHERO:
		//Cogemos la fecha del fichero
		//std::filesystem::file_time_type ftime = std::filesystem::last_write_time(p.path());
		//std::file

		if (std::filesystem::exists(std::filesystem::path(mod->ruta))) {
			if (mod->existe) {
				t = std::filesystem::last_write_time(std::filesystem::path(mod->ruta));
				if (t > mod->ultimoCambio) {
					mod->ultimoCambio = t;
					cambio = true;
				}
			} else {
				mod->ultimoCambio = std::filesystem::last_write_time(std::filesystem::path(mod->ruta));
				mod->existe = true;
				cambio = true;
			}
		} else {
			if (mod->existe) {
				mod->existe = false;
				cambio = true;
			}
		}
		break;
	default:
		break;
	}
	return cambio;
}
bool fileControl::fileChange(const char* path, void(*callback)()) {
	ficherosCambio.push_back(new EstadoRuta(path, callback));

	if (std::filesystem::exists(std::filesystem::path(path))) {
		ficherosCambio[ficherosCambio.size() - 1]->existe = true;
		ficherosCambio[ficherosCambio.size() - 1]->ultimoCambio = std::filesystem::last_write_time(std::filesystem::path(path));
		return true;
	}
	return false;
}
void fileControl::folderChange(const char* path, void(* callback)()) {
	carpetasCambio.push_back(new EstadoRuta(path,callback));
}
void fileControl::onFocus(bool focus) {
	if (focus) {
		for (auto itr = carpetasCambio.begin(); itr != carpetasCambio.end(); itr++) {
			if (check(*itr,Tipos::CARPETA)) {
				((*itr)->callback)();
			}
		}
		for (auto itr = ficherosCambio.begin(); itr != ficherosCambio.end(); itr++) {
			if (check(*itr, Tipos::FICHERO)) {
				((*itr)->callback)();
			}
		}
	}
}
std::vector<fileControl::EstadoRuta *> fileControl::carpetasCambio;
std::vector<fileControl::EstadoRuta *> fileControl::ficherosCambio;