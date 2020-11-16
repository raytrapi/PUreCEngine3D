#ifndef __PROYECTO
#define __PROYECTO
#include <filesControl.h>
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <compile.h>
class Proyecto {
	static std::map<std::string, std::string> parametros;
	static std::map<std::string, std::string> conf;
	static std::vector<std::string> split(std::string cadena, char caracter);
	static std::string trim(std::string cadena);
public:
	static const char* generarProyecto(const char* proyecto, const char* ruta);
	static const char* escribir(std::string carpeta, const char* destino, const char* origen);
	static bool cargarProyecto(const char* ruta);
	static const char* cogerRutaCodigoProyecto();
	static const char* cogerRutaCompilacionProyecto();
	static const char* cogerNombreProyecto();
	static bool estaCargado();

};
#endif // !__PROYECTO
