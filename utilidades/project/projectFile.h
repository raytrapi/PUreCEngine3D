#ifndef __PROJECT
#define __PROJECT
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <tuple>
#include <filesystem>
#include<expected>
#include "../utiles/utilidades.h"
//#include "levelFile.h"
#include "UIDProject.h"

class ProjectFile;

struct TheProject {
	friend class ProjectFile;
	char* firma=0;
	unsigned int version=0;
	char* nivel = 0;
	
	~TheProject() {
		if (firma) {
			delete[] firma;
		}
		if (nivel) {
			delete[] firma;
		}
		
	}
	TheProject() {

	}
	TheProject(const TheProject& o) {
		version = o.version;
		unsigned int longitud = strlen(o.firma);
		firma = new char[longitud+1];
		strcpy(firma, o.firma);
		firma[longitud] = '\0';

		if (o.nivel) {
			longitud = strlen(o.nivel);
			nivel = new char[longitud + 1];
			strcpy(nivel, o.nivel);
			nivel[longitud] = '\0';
		} else {
			nivel = 0;
		}

	}
	// Constructor de movimiento
	/*TheProject(TheProject&& other) :firma(other.firma), version(other.version), numeroNiveles(other.numeroNiveles) {
		other.firma = nullptr;
		other.version = nullptr;
	}/**/

};


class EXPORTAR_UTILIDADES ProjectFile {

	char* ruta=0;
	TheProject* proyecto = 0;
public:
	ProjectFile();
	ProjectFile(ProjectFile& o);
	ProjectFile(ProjectFile&& o);/**/
	~ProjectFile();
	
	static int exists(const char* path);
	static std::expected<ProjectFile,int> load(const char* path, bool create=false);
	void save();

	friend std::ostream& operator<<(std::ostream& os, const ProjectFile& e) {
		if (e.proyecto) {
			os << " Firma: " << e.proyecto->firma << std::endl;
			os << " Vesrion: " << e.proyecto->version << std::endl;
		} else {
			os << "No hay proyecto";
		}
		return os;
	};
	ProjectFile& operator=(ProjectFile& o) noexcept;
};


#endif #__PROJECT