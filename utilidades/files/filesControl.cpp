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
bool FileControl::fileChange(const char* path, std::function<void(char*)>callback) {
	ficherosCambio.push_back(new EstadoRuta(path, callback));

	if (std::filesystem::exists(std::filesystem::path(path))) {
		ficherosCambio[ficherosCambio.size() - 1]->existe = true;
		ficherosCambio[ficherosCambio.size() - 1]->ultimoCambio = std::filesystem::last_write_time(std::filesystem::path(path));
		return true;
	}
	return false;
}
bool FileControl::fileChangeTime(const char* path, std::function<void(char*)>callback, unsigned int milliseconds) {
	EstadoRuta* er = new EstadoRuta(path, callback);
	ficherosCambioTiempo.push_back(er);
	unsigned id = ficherosCambioTiempo.size() - 1;
	//se encarga de lanzar el callback cuando algo cambia
	er->idTiempo = utiles::Watchdog::setInterval([&,id]() {
		//utiles::Log::debug(id);
		//utiles::Log::debug(ficherosCambioTiempo[id]->ruta);
		if (FileControl::check(ficherosCambioTiempo[id], FileControl::Tipos::FICHERO)) {
			ficherosCambioTiempo[id]->callback(ficherosCambioTiempo[id]->ruta);
		}
	}, milliseconds);
	return false;
}
void FileControl::folderChange(const char* path, std::function<void(char*)>callback, bool subCarpeta) {
	carpetasCambio.push_back(new EstadoRuta(path,callback));
	if (subCarpeta) {
		for (auto& carpeta : std::filesystem::recursive_directory_iterator(std::filesystem::path(path))){
			utiles::Log::debug((char *)carpeta.path().c_str());
		}
	}
}
void FileControl::cargarSubcarpetas(const char* path, std::function<void(char*)>callback,  std::vector<FileControl::EstadoRuta*> *carpetas, bool subCarpeta, bool registrarTiempo) {
	if (carpetas->size() > 0) {
		//Vaciamos las carpetas
		for (int i = 0; i < carpetas->size(); i++) {
			delete carpetas->operator[](i);
		}
		carpetas->clear();

	}
	EstadoRuta* er = new EstadoRuta(path, callback);
	carpetas->push_back(er);
	if (registrarTiempo) {
		if (std::filesystem::exists(std::filesystem::path(er->ruta))) {
			auto t = std::filesystem::last_write_time(std::filesystem::path(er->ruta));
			er->ultimoCambio = t;
			er->existe = true;
		}
	}
	if (subCarpeta) {
		for (auto& carpeta : std::filesystem::recursive_directory_iterator(std::filesystem::path(path))) {
			if (carpeta.is_directory()) {
				std::string stringCarpeta = carpeta.path().string();
				int longitud = stringCarpeta.size();
				char* strCarpeta = new char[longitud + 1];
				for (int i = 0; i < longitud; i++) {
					strCarpeta[i] = stringCarpeta[i];
				}
				strCarpeta[longitud] = '\0';
				er = new EstadoRuta(strCarpeta, callback);
				carpetas->push_back(er);
				if (registrarTiempo) {
					if (std::filesystem::exists(std::filesystem::path(er->ruta))) {
						auto t = std::filesystem::last_write_time(std::filesystem::path(er->ruta));
						er->ultimoCambio = t;
						er->existe = true;
					}
				}
				//utiles::Log::debug(strCarpeta);
				delete[] strCarpeta;
			}
		}
	}
}
bool FileControl::folderChangeTime(const char* path, std::function<void(char*)>callback, unsigned int milliseconds, bool subCarpeta) {
	std::vector<FileControl::EstadoRuta*> carpetas;
	cargarSubcarpetas(path, callback, &carpetas, true,false);
	temporizadores.push_back(
		utiles::Watchdog::setInterval(
			[&, carpetas, path]() {
				bool sinCambio = true;
				for (auto carpeta = carpetas.begin(); sinCambio && carpeta != carpetas.end(); carpeta++) {
					if (FileControl::check(*carpeta, FileControl::Tipos::FICHERO)) { //TODO: Modificar para gestionar carpetas
						utiles::Log::debug("Hay cambios");
						utiles::Log::debug((*carpeta)->ruta);
						(*carpeta)->callback((*carpeta)->ruta);
						cargarSubcarpetas(path, (*carpeta)->callback, (std::vector<FileControl::EstadoRuta*>*)(&carpetas), true,true);
						carpeta = carpetas.begin();
						sinCambio = false;
					}
				}
			}
			, milliseconds)
	);
	return false; //TODO: Comprobar porqué siempre tenemos que devolver falso
}

void FileControl::onFocus(bool focus) {
	if (focus) {
		for (auto itr = carpetasCambio.begin(); itr != carpetasCambio.end(); itr++) {
			if (check(*itr,Tipos::CARPETA)) {
				((*itr)->callback)((*itr)->ruta);
			}
		}
		for (auto itr = ficherosCambio.begin(); itr != ficherosCambio.end(); itr++) {
			if (check(*itr, Tipos::FICHERO)) {
				((*itr)->callback)((*itr)->ruta);
			}
		}
	}
}
bool FileControl::existsFolder(const char* path) {
	return std::filesystem::is_directory(std::filesystem::path(path));
}
bool FileControl::createFolder(const char* path) {
	
	return std::filesystem::create_directory(std::filesystem::path(path));
}
bool FileControl::stopTimers() {	
	for (int i = 0; i < temporizadores.size(); i++) {
		utiles::Watchdog::clearInterval(temporizadores[i]);
	}
	temporizadores.clear();
	return true;
};
std::vector<FileControl::EstadoRuta *> FileControl::carpetasCambio;
std::vector<FileControl::EstadoRuta *> FileControl::ficherosCambio;
std::vector<FileControl::EstadoRuta*> FileControl::ficherosCambioTiempo;
std::vector<unsigned int> FileControl::temporizadores;