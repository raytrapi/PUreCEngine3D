#ifndef __FILE_CONTROL
#define __FILE_CONTROL

#include <vector>
#include <iostream>
#include <filesystem>
//#include "../../modules/src/module.h"
#include "../log/log.h"

/**
* Este módulo contiene la funcionalidad para controlar una carpeta y ejecutar la función solicitada
*/

class EXPORTAR_UTILIDADES fileControl {
	class EstadoRuta {
	public:
		char* ruta;
		void(*callback)();
		bool existe = false;
		std::filesystem::file_time_type ultimoCambio;
		EstadoRuta(const char* r, void(*c)()){
			callback = c;
			utiles::Log::debug("longitud");
			int longitud = strlen(r);
			utiles::Log::debug(longitud);
			ruta = new char[longitud + 1];
			for (int i = 0; i < longitud; i++) {
				ruta[i] = r[i];
			}
			ruta[longitud] = '\0';
		};
		~EstadoRuta() {
			delete[] ruta;
		}
		
	};
	enum Tipos { CARPETA, FICHERO };
	static std::vector<EstadoRuta *> carpetasCambio;
	static std::vector<EstadoRuta *> ficherosCambio;
	static bool check(EstadoRuta *estado, Tipos tipo);
public:
	fileControl();
	~fileControl();
	static void folderChange(const char* path, void(*callback)());
	static bool fileChange(const char* path, void(*callback)());
	static void onFocus(bool focus);
};


#endif // !__FILE_CONTOL
