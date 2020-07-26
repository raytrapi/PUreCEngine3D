#ifndef __CARGA_DLL
#define __CARGA_DLL
#include <module.h>
#include <dll.h>
#include <map>
#include <vector>

#include <regex>
//Ficheros
#include <filesystem>
//Tiempo
#include <chrono>
#include <iomanip>
#include <ctime>
#include <cstring>

class Libreria {
	char* fichero;
	char* nombre;
	bool activo;
	bool descargando = false;
	void* instancia=NULL;
	std::filesystem::file_time_type ultimaActualizacion;
public:
	Libreria(const char*, const char*, std::filesystem::file_time_type );
	~Libreria();
	bool esActivo();
	void ponerActivo(bool);
	bool cargar(char*);
	bool descargar(char*);
	bool descargar(utilidades::Libreria<Module>&);
	void* cogerInstancia(char *raiz);
	const char* cogerNombreFichero();
	const char* cogerNombre();
	
};
class CargaDLL {
	static std::map<Module::MODULES_TYPE, std::vector<Libreria*>*> libreriasDisponibles;
	//static char* raiz;
public:
	static bool cargar(char *, char *);
	template <class T>
	static T* cogerModulo(Module::MODULES_TYPE tipo);
	template <class T>
	static T* cogerModulo(Module::MODULES_TYPE tipo, const char* nombre);
	static void descargar();
	static int hayModulos(Module::MODULES_TYPE);
};
template<class T>
static inline T* CargaDLL::cogerModulo(Module::MODULES_TYPE tipo) {
	if (libreriasDisponibles.contains(tipo) && libreriasDisponibles[tipo]->size() > 0) {

		void* ins = (*(libreriasDisponibles[tipo]))[0]->cogerInstancia(".");
		if (ins != NULL) {
			return (T*)ins;
		}

	}
	return NULL;
}
template<class T>
static inline T* CargaDLL::cogerModulo(Module::MODULES_TYPE tipo, const char* nombre) {
	if (libreriasDisponibles.contains(tipo) && libreriasDisponibles[tipo]->size() > 0) {
		for (int i = 0; i < (*(libreriasDisponibles[tipo])).size(); i++) {
			if (strcmp(nombre, (*(libreriasDisponibles[tipo]))[i]->cogerNombre()) == 0) {
				void* ins = (*(libreriasDisponibles[tipo]))[i]->cogerInstancia(".");
				if (ins != NULL) {
					return (T*)ins;
				}
			}
			
		}

	}
	return NULL;
}
#endif // !__CARGA_DLL
