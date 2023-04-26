#ifndef __CARGA_DLL
#define __CARGA_DLL
#include <module.h>
#include "..\utilidades\librerias\dll.h"
//#include "..\utilidades\global\input.h"
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
#include <log.h>

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
	bool cargar(const char*);
	bool descargar(const char*);
	bool descargar(utilidades::Libreria<Module>&);
	void* cogerInstancia(const char *raiz);
	void reiniciar();
	const char* cogerNombreFichero();
	const char* cogerNombre();
	
};
class CargaDLL {
	static std::map<Module::MODULES_TYPE, std::vector<Libreria*>*> libreriasDisponibles;
	static Libreria* existe(Module::MODULES_TYPE, const char* nombre);
	//static char* raiz;
	static bool cargarDLL(const std::filesystem::path& p, const char* carpeta);
	static void remplazarExtension(char*& cadena, const char*);
	static char* raizLibrerias;
	static void addLibreria(Module::MODULES_TYPE, const char* ruta, const char* nombre, std::filesystem::file_time_type tiempo);
public:
	static bool cargar(const char * raiz, const char *carpeta);
	static bool cargar(const char*fichero);
	template <class T>
	static T* cogerModulo(Module::MODULES_TYPE tipo);
	template <class T>
	static T* cogerModulo(Module::MODULES_TYPE tipo, const char* nombre);
	static void descargar();
	static int hayModulos(Module::MODULES_TYPE);
	static void liberarModulo(Module::MODULES_TYPE);
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
		//DBG("PARA % hay % librerías", tipo, (*(libreriasDisponibles[tipo])).size());
		for (int i = 0; i < (*(libreriasDisponibles[tipo])).size(); i++) {
			//DBG("----");
			//DBG("% == %",nombre, (*(libreriasDisponibles[tipo]))[i]->cogerNombre());
			if (strcmp(nombre, (*(libreriasDisponibles[tipo]))[i]->cogerNombre()) == 0) {
				void* ins = (*(libreriasDisponibles[tipo]))[i]->cogerInstancia("./");
				if (ins != NULL) {
					return (T*)ins;
				}
			}
			
		}

	}
	return NULL;
}
#endif // !__CARGA_DLL
