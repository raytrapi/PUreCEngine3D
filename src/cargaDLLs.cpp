#include "cargaDLLs.h"
#include <log.h>


bool CargaDLL::cargar(char* carpeta, char * raiz) {

	std::filesystem::path ruta=std::filesystem::current_path();
	utiles::Log::escribir(ruta.string());
	

	if(!std::filesystem::exists(carpeta)){
		return false;
	}
	int longitudCarpeta = strlen(carpeta);
	//CargaDLL::raiz = raiz;
	utilidades::Libreria<Module> dll(raiz);
	for (auto& p : std::filesystem::directory_iterator(carpeta)) {
	#ifdef _WIN32
		std::regex expresionDLL(".*\\\.dll$");
	#else
		std::regex expresionDLL(".*\\\.so$");
	#endif // _WIN32
		std::filesystem::file_time_type ftime = std::filesystem::last_write_time(p.path());
		//ftime.;
		//td::string ultimaEscritura(std::asctime(std::localtime(&cftime)));
		bool esDLL = std::regex_match(p.path().string(), expresionDLL);
		if (p.is_regular_file() && esDLL) {
			
			std::string ruta = p.path().string();
			char* ficheroDLL = new char[ruta.length()+1];
			
			char* nombreFichero= new char[ruta.length()-longitudCarpeta];
			int j = 0;
			for (int i = 0; i < ruta.length(); i++) {
				ficheroDLL[i] = (char)ruta[i];
				if (i > longitudCarpeta) {
					nombreFichero[j++] = (char)ruta[i];
				}
			}
			ficheroDLL[ruta.length()] = '\0';
			nombreFichero[j] = '\0';
			Module* libreria = dll.crearInstancia(ficheroDLL);
			if (libreria != NULL) {
				utiles::Log::escribir(std::string("Hemos encontrado esta librería ")+p.path().string()+std::string(" de tipo ")+std::to_string(libreria->tipo()));
				if (!libreriasDisponibles.contains(libreria->tipo())) {
					libreriasDisponibles[libreria->tipo()] = new std::vector<Libreria*>();
				}
				//Copiamos el fichero en una nueva ubicación
				if (!std::filesystem::exists("modulosTEMP")) {
					std::filesystem::create_directories("modulosTEMP");
				}
				char* ficheroTemp = new char[strlen("modulosTEMP/") + strlen(nombreFichero)+1];
				ficheroTemp[0] = '\0';
				strcat(ficheroTemp, "modulosTEMP/");
				strcat(ficheroTemp, nombreFichero);
				if (std::filesystem::exists(ficheroTemp)) {
					std::filesystem::remove(ficheroTemp);
				}
				std::filesystem::copy_file(ficheroDLL, ficheroTemp);
				libreriasDisponibles[libreria->tipo()]->push_back(new Libreria(ficheroTemp, libreria->nombre(),ftime));/**/
				
				//libreriasDisponibles[libreria->tipo()]->push_back(new Libreria(ficheroDLL, libreria->nombre(),ftime));
				delete libreria;
				dll.descargar(ficheroDLL);
			}
			//dll.~Libreria/**/
			delete [] ficheroDLL;

			delete[] nombreFichero;
			
		}
	}

	return false;
}
void CargaDLL::descargar() {
	utilidades::Libreria<Module> dll(".");
	for (std::map<Module::MODULES_TYPE, std::vector<Libreria*>*>::iterator it = libreriasDisponibles.begin(); it != libreriasDisponibles.end(); ++it) {
		for (std::vector<Libreria*>::iterator itV = it->second->begin(); itV != it->second->end(); ++itV) {
			(*itV)->descargar(dll);
		}
		delete it->second;
	}
}

int CargaDLL::hayModulos(Module::MODULES_TYPE tipo){
	
	
	return libreriasDisponibles.contains(tipo)?libreriasDisponibles[tipo]->size():0;
}


Libreria::Libreria(const char* fichero, const char* nombre, std::filesystem::file_time_type ftime) {
	this->fichero = new char[strlen(fichero)+1];
	strcpy(this->fichero, fichero);
	this->nombre = new char[strlen(nombre) + 1];
	strcpy(this->nombre, nombre);;
	this->ultimaActualizacion = ftime;
}
Libreria::~Libreria() {
	utilidades::Libreria<Module> dll(".");
	if (activo) {
		dll.descargar(fichero);
		activo = false;
	}
	delete[]this->fichero;
	delete[]this->nombre;
}

bool Libreria::esActivo() {
	return activo;
}
void Libreria::ponerActivo(bool activo) {
	this->activo = activo;
}
bool Libreria::cargar(char *raiz) {
	utilidades::Libreria<Module> dll(raiz);
	return dll.cargar(fichero);
}

bool Libreria::descargar(char *raiz) {
	utilidades::Libreria<Module> dll(raiz);

	return dll.descargar(fichero);
}
bool Libreria::descargar(utilidades::Libreria<Module>& dll) {
	descargando = true;
	bool descargado = dll.descargar(fichero);
	if (descargado) {
		delete[] fichero;
	}
	return descargado;
}
void* Libreria::cogerInstancia(char*raiz) {
	if (descargando) {
		return NULL;
	}
	if (!instancia) {
		utilidades::Libreria<Module> dll(raiz);
		instancia = dll.crearInstancia(fichero);
	}
	
	if (instancia != NULL) {
		activo=true;
	}
	return instancia;
}
const char* Libreria::cogerNombreFichero() {
	return fichero;
}

const char* Libreria::cogerNombre() {
	return nombre;
}

std::map<Module::MODULES_TYPE, std::vector<Libreria*>*> CargaDLL::libreriasDisponibles;
//char* raiz=".";