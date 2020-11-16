#ifndef __COMPILE
#define __COMPILE
#include <stdlib.h>
#include <string>
#include <thread>
#ifdef WIN32
#include <windows.h>
#endif
#include "../log/log.h"
#include <filesystem>

class Compile {
	static std::string rutaCompilador;
	static std::string entornoCompilador;
	static void buscarCompilador();
   static enum tipoReg{DOBLE,BOOLEANO,CADENA};
   static void leerRegistro(HKEY clave, const char* subClave, std::string& valor);
	static void leerRegistro(HKEY clave, const char* subClave, bool& valor);

public:
	enum Types{NINJA};
	static void compileProject(const char* project, Types tipo);
	static void generateProject(const char* project, Types tipo, bool generar = true);
	static const char* pathCompiler();
	static const char* compilerScope();
};



#endif // !__COMPILE
