#include "projectFile.h"
#include "../global/global.h"

ProjectFile::ProjectFile(){

}
ProjectFile::ProjectFile(ProjectFile& o) {
	ruta = new char(strlen(o.ruta) + 1);
	strcpy(ruta,o.ruta);
	proyecto=new TheProject(*o.proyecto);
	//o.ruta = 0;
	//o.proyecto = 0;
}
ProjectFile::ProjectFile(ProjectFile&& o) {
	ruta = o.ruta;
	proyecto = o.proyecto;
	o.ruta = 0;
	o.proyecto = 0;
}
ProjectFile::~ProjectFile(){
	if (proyecto) {
		delete proyecto;
	}
}

int ProjectFile::exists(const char* path){
	//TODO: Compromar que la extensión del proyecto sea la correcta .pc3d
	std::filesystem::path ruta(path);
	if (ruta.extension() != std::string(".pc3d")) {
		return -2;
	}
	
	return (std::filesystem::exists(ruta)?0:-1);
}

std::expected<ProjectFile, int> ProjectFile::load(const char* path, bool create){
	//¿Tenemos el fichero?

	std::filesystem::path ruta(path);
	
	if (ruta.extension() != std::string(".pc3d")) {
		return std::unexpected(-2);
	}
	bool cargado = true;
	if(!std::filesystem::exists(ruta)){
		if (!create) {
			return std::unexpected(-1);
		} 
		cargado = false;
	}
	ProjectFile p;
	p.ruta = new char[strlen(path) + 1];
	strcpy(p.ruta, path);
	if (cargado) {
		std::ifstream fs(path, std::ios::binary);
		if (fs.peek() == std::ifstream::traits_type::eof()) {
			cargado = false;
		} else {
			unsigned int longitud = 0;
			fs.read((char*)&longitud, sizeof(unsigned int));
			p.proyecto = new TheProject();
			p.proyecto->firma = new char[longitud];
			fs.read(p.proyecto->firma, longitud);
			if (strcmp(p.proyecto->firma, UID_PROJECT) != 0) {
				delete p.proyecto;
				p.proyecto = 0;
				fs.close();
				return std::unexpected(-3); //El fichero no es correcto
			}
			fs.read((char*)&p.proyecto->version, sizeof(unsigned int));
			fs.close();
		}
	}
	if (!cargado) {
		p.proyecto = new TheProject();
		p.proyecto->firma = new char[strlen(UID_PROJECT)+1];
		strcpy(p.proyecto->firma, UID_PROJECT);
		p.proyecto->version = 10000;
		p.save();
	}
	//Cargamos configuaracion
	
	return p;
}

void ProjectFile::save(){
	//TODO: Generar un Back
	if (ruta && proyecto) {
		std::ofstream fs(ruta, std::ios::binary);
		unsigned int longitud = strlen(proyecto->firma)+1;
		fs.write((char*)&longitud, sizeof(unsigned int));
		fs.write(proyecto->firma, longitud);
		fs.write((char*)&proyecto->version, sizeof(unsigned int));
		if (proyecto->nivel == 0) {
			longitud = 0;
			fs.write((char*)&longitud, sizeof(unsigned int));
		} else {
			longitud = strlen(proyecto->nivel) + 1;
			fs.write((char*)&longitud, sizeof(unsigned int));
			fs.write(proyecto->nivel, longitud);
		}
		fs.close();
	}
}

ProjectFile& ProjectFile::operator=(ProjectFile& o) noexcept {
	// Guard self assignment
	if (this == &o)
		return *this;
	if (proyecto) {
		delete proyecto;
	}
	if (o.proyecto) {
		proyecto = new TheProject(*o.proyecto);
	}
	return *this;
}
