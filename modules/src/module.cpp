#include "module.h" 
std::map<Module::MODULES_TYPE, Module*> Module::modulos;

void Module::set(MODULES_TYPE type, Module* module) {
	modulos[type] = module;
}
 