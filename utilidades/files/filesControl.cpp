#include "filesControl.h"
FileControl::FileControl() {
	//Ejecutamos cuando cojemos el foco
}
FileControl::~FileControl() {
	for (auto itr = carpetasCambio.begin(); itr != carpetasCambio.end(); itr++) {
		delete (*itr);
	}
	carpetasCambio.clear();
	for (auto itr = ficherosCambio.begin(); itr != ficherosCambio.end(); itr++) {
		delete (*itr);
	}
	ficherosCambio.clear();
}
bool FileControl::check(FileControl::EstadoRuta *mod, FileControl::Tipos tipo) {
	std::filesystem::file_time_type t;
	bool cambio = false;
	//Buscamos dentro de la carpeta para ver si hay cambios
	switch (tipo) {
	case FileControl::CARPETA:

		break;
	case FileControl::FICHERO:
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
bool FileControl::fileChange(const char* path, std::function<void()>callback) {
	ficherosCambio.push_back(new EstadoRuta(path, callback));

	if (std::filesystem::exists(std::filesystem::path(path))) {
		ficherosCambio[ficherosCambio.size() - 1]->existe = true;
		ficherosCambio[ficherosCambio.size() - 1]->ultimoCambio = std::filesystem::last_write_time(std::filesystem::path(path));
		return true;
	}
	return false;
}
bool FileControl::fileChangeTime(const char* path, std::function<void()>callback, unsigned int milliseconds) {
	EstadoRuta* er = new EstadoRuta(path, callback);
	ficherosCambioTiempo.push_back(er);
	unsigned id = ficherosCambioTiempo.size() - 1;
	er->idTiempo = utiles::Watchdog::setInterval([&,id]() {
		//utiles::Log::debug(id);
		//utiles::Log::debug(ficherosCambioTiempo[id]->ruta);
		if (FileControl::check(ficherosCambioTiempo[id], FileControl::Tipos::FICHERO)) {
			ficherosCambioTiempo[id]->callback();
		}
	}, milliseconds);
	return false;
}
void FileControl::folderChange(const char* path, std::function<void()>callback) {
	carpetasCambio.push_back(new EstadoRuta(path,callback));
}
void FileControl::onFocus(bool focus) {
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
std::vector<FileControl::EstadoRuta *> FileControl::carpetasCambio;
std::vector<FileControl::EstadoRuta *> FileControl::ficherosCambio;
std::vector<FileControl::EstadoRuta*> FileControl::ficherosCambioTiempo;