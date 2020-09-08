#ifndef __FILE_CONTROL
#define __FILE_CONTROL

#include <vector>
#include <iostream>
#include <filesystem>
#include <functional>

#include "../timer/watchdog.h"

//#include "../../modules/src/module.h"
#include "../log/log.h"

/**
* Este módulo contiene la funcionalidad para controlar una carpeta y ejecutar la función solicitada
*/

class EXPORTAR_UTILIDADES FileControl {
	class EstadoRuta {
	public:
		char* ruta;
		std::function<void()>callback;
		bool existe = false;
		unsigned int idTiempo = 0;
		std::filesystem::file_time_type ultimoCambio;
		EstadoRuta(const char* r, std::function<void()>c,unsigned int id=0){
			callback = c;
			int longitud = strlen(r);
			utiles::Log::debug(longitud);
			ruta = new char[longitud + 1];
			for (int i = 0; i < longitud; i++) {
				ruta[i] = r[i];
			}
			ruta[longitud] = '\0';
			idTiempo = id;
		};
		~EstadoRuta() {
			delete[] ruta;
		}
		
	};
	
	static std::vector<EstadoRuta *> carpetasCambio;
	static std::vector<EstadoRuta *> ficherosCambio;
	static std::vector<EstadoRuta*> ficherosCambioTiempo;
	
public:
	enum Tipos { CARPETA, FICHERO };
	FileControl();
	~FileControl();
	static void folderChange(const char* path, std::function<void()>callback);
	static bool fileChange(const char* path, std::function<void()>callback);
	static bool fileChangeTime(const char* path, std::function<void()>callback, unsigned int milliseconds);
	static void onFocus(bool focus);
	static bool check(EstadoRuta* estado, Tipos tipo);
};


#endif // !__FILE_CONTOL
