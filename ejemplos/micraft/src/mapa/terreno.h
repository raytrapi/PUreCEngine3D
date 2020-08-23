#ifndef _TERRENO
#define _TERRENO
#include <list>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>
enum class Tipo {
	VACIO,
	TIERRA_SECA, TIERRA_VERDE, 
	PIEDRA,
	AGUA
};
enum class Direccion {
	ESTE, NORESTE, NORTE, NOROESTE, OESTE, SUROESTE, SUR, SURESTE
};
class Terreno {
	short tamaño = 8;
	std::list<Tipo**> generados;
	std::vector<float> probabilidades;
	const short numeroTiposTierras = 5;
	std::vector<Terreno*> terrenosVecinos;
	int preProbabilidades(std::vector<Tipo> vecinos, std::vector<Tipo> descartar);
	bool hay(Tipo tipo, std::vector<Tipo> vecinos);
	Tipo** porcion=0;
public:
	Terreno(short tamaño);
	~Terreno();
	Tipo** generar();
	Tipo** generar(Direccion);
	Tipo** cogerPorcion();
	void borrar(Tipo** porcion);
	Terreno* coger(Direccion v);
	void informar(Terreno* tierra, Direccion d);
		
};
#endif // !_TERRENO
