#include "cargaDLLs.h"



Libreria * CargaDLL::existe(Module::MODULES_TYPE tipo, const char* nombre) {
	if (libreriasDisponibles.contains(tipo)) {
		for (auto itr = libreriasDisponibles[tipo]->begin(); itr != libreriasDisponibles[tipo]->end(); itr++) {
			if (strcmp((*itr)->cogerNombreFichero(), nombre) == 0) {
				return *itr;
			}
		}
	}
	return NULL;
}

bool CargaDLL::cargarDLL(const std::filesystem::path& p, const char* carpeta) {
#ifdef _WIN32
	std::regex expresionDLL(".*\\\.dll$");
#else
	std::regex expresionDLL(".*\\\.so$");
#endif // _WIN32

	bool esDLL = std::regex_match(p.string(), expresionDLL);
	if (esDLL) {
		std::filesystem::file_time_type ftime = std::filesystem::last_write_time(p);
		std::string ruta = p.string();
		int longitudCarpeta = p.parent_path().string().length();

		char* ficheroDLL = new char[ruta.length() + 1]; //Ruta completa + nombre del fichero
		char* nombreFichero = new char[ruta.length() - longitudCarpeta];

		//Obtenemos el nombre de la DLL + su Ruta de carga
		int j = 0;
		for (int i = 0; i < ruta.length(); i++) {
			ficheroDLL[i] = (char)ruta[i];
			if (i > longitudCarpeta) {
				nombreFichero[j++] = (char)ruta[i];
			}
		}
		ficheroDLL[ruta.length()] = '\0';
		nombreFichero[j] = '\0';


		utilidades::Libreria<Module> dll("");
		Module* libreria = dll.crearInstancia(ficheroDLL);
		if (libreria != NULL) {
			//utiles::Log::escribir(std::string("Hemos encontrado esta librería ") + p.string() + std::string(" de tipo ") + std::to_string(libreria->tipo()));
			
			//Copiamos el fichero en una nueva ubicación
			if (!std::filesystem::exists(carpeta)) {
				std::filesystem::create_directories(carpeta);
			}
			char* ficheroTemp = new char[strlen(carpeta) + strlen(nombreFichero) + 1];
			ficheroTemp[0] = '\0';

			strcat(ficheroTemp, carpeta);
			strcat(ficheroTemp, nombreFichero);
			//int casosCopia = 1;
			for (int iRep = 0; iRep < 2; iRep++) {
				if (iRep == 1) {
					remplazarExtension(ficheroDLL, "pdb");
					remplazarExtension(ficheroTemp, "pdb");
				}
				if (std::filesystem::exists(ficheroDLL)) {
					if (std::filesystem::exists(ficheroTemp)) {
						//Exite
						if (iRep == 0) {
							Libreria* l = existe(libreria->tipo(), ficheroTemp);
							if (l != NULL && l->esActivo()) {
								l->descargar((char*)carpeta);
							}
						}
						std::filesystem::remove(ficheroTemp);
					}
					std::filesystem::copy_file(ficheroDLL, ficheroTemp);
					
				}
				if (iRep == 1) {
#ifdef _WIN32
					remplazarExtension(ficheroDLL, "dll");
					remplazarExtension(ficheroTemp, "dll");
#else
					remplazarExtension(ficheroDLL, "so");
					remplazarExtension(ficheroTemp, "so");
#endif
				}
			}
			addLibreria(libreria->tipo(),ficheroTemp, libreria->nombre(), ftime);
			//libreriasDisponibles[libreria->tipo()]->push_back(new Libreria(ficheroTemp, libreria->nombre(), ftime));
			/**/
			delete[] ficheroTemp;
			//libreriasDisponibles[libreria->tipo()]->push_back(new Libreria(ficheroDLL, libreria->nombre(),ftime));
			dll.descargar(ficheroDLL);
			delete libreria;
		}
		//dll.~Libreria/**/
		delete[] ficheroDLL;
		delete[] nombreFichero;
		return true;
	}
	return false;
}

void CargaDLL::remplazarExtension(char*& cadena, const char* ext) {
	int lExtenxion = strlen(ext);
	int posCaracter = strlen(cadena) - lExtenxion;
	for (int i = 0; i < lExtenxion; i++) {
		cadena[posCaracter++] = ext[i];
	}
}

void CargaDLL::addLibreria(Module::MODULES_TYPE tipo, const char* ruta, const char* nombre, std::filesystem::file_time_type tiempo) {
	if (!libreriasDisponibles.contains(tipo)) {
		libreriasDisponibles[tipo] = new std::vector<Libreria*>();
		libreriasDisponibles[tipo]->push_back(new Libreria(ruta, nombre, tiempo));
	} else {
		//Buscamos si ya existe la librería
		bool noExiste = true;
		for (auto itr = libreriasDisponibles[tipo]->begin(); itr != libreriasDisponibles[tipo]->end() && noExiste; itr++) {
			if (strcmp((*itr)->cogerNombre(), nombre) == 0) {
				noExiste = false;
				(*itr)->reiniciar();
			}
		}

	}
	
}

bool CargaDLL::cargar(const char* carpeta, const char * raiz) {

	std::filesystem::path ruta=std::filesystem::current_path();
	utiles::Log::debug(ruta.string());
	

	if(!std::filesystem::exists(carpeta)){
		return false;
	}
	int longitudCarpeta = strlen(carpeta);
	//CargaDLL::raiz = raiz;
	utilidades::Libreria<Module> dll(raiz);
	bool correcto = true;
	for (auto& p : std::filesystem::directory_iterator(carpeta)) {
		correcto &=cargarDLL(p.path(), raizLibrerias);
	
	}

	return correcto;
}
bool CargaDLL::cargar(const char* path) {
	bool correcto = true;
	std::filesystem::path p(path);
	correcto &= cargarDLL(p, raizLibrerias);

	return correcto;
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

void CargaDLL::liberarModulo(Module::MODULES_TYPE tipo) {
	if (libreriasDisponibles.contains(tipo) && libreriasDisponibles[tipo]->size() > 0) {
		for (int i = 0; i < (*(libreriasDisponibles[tipo])).size(); i++) {
			if ((*(libreriasDisponibles[tipo]))[i]->esActivo()) {
				(*(libreriasDisponibles[tipo]))[i]->descargar(raizLibrerias);
			}
		}
	}
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
bool Libreria::cargar(const char *raiz) {
	utilidades::Libreria<Module> dll(raiz);
	return dll.cargar(fichero);
}

bool Libreria::descargar(const char *raiz) {
	utilidades::Libreria<Module> dll(raiz);

	return dll.descargar(fichero);
}
bool Libreria::descargar(utilidades::Libreria<Module>& dll) {
	descargando = true;
	bool descargado = dll.descargar(fichero);
	if (descargado) {
		delete[] fichero;
	}
	instancia = NULL;
	descargando = false;
	return descargado;
}
void* Libreria::cogerInstancia(const char*raiz) {
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
void Libreria::reiniciar() {
	instancia = NULL;
	descargando = false;
}

const char* Libreria::cogerNombreFichero() {
	return fichero;
}

const char* Libreria::cogerNombre() {
	return nombre;
}

std::map<Module::MODULES_TYPE, std::vector<Libreria*>*> CargaDLL::libreriasDisponibles;
char* CargaDLL::raizLibrerias = (char *)"modulosTEMP/";
//char* raiz=".";