#pragma once
#include <string>
#include "../../modules/graphic/motor.h"
#include "../../components/src/entity.h"
#include "../../utilidades/project/genericFile.h"


class LoadLevel {

	friend void procesarNivel(unsigned int);

	static int load(std::string s, int pos, modules::graphics::Graphic * m, unsigned int version=0);
	static int desserializarEntidades(std::string s, int pos, modules::graphics::Graphic* m);
	static int desserializarComponente(std::string s, int pos, Entity* e);
	public:
	static int load(std::vector<unsigned char> *s, int pos, modules::graphics::Graphic* m, unsigned int version = 0);
};