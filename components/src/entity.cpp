#include "entity.h"
#include <../../utilidades/timer/timer.h>
#include "../../components/modulos/code/code.h"
#include "../../utilidades/project/serializer/serializer.h"
#include "../../utilidades/project/serializer/deserializer.h"

std::map<unsigned, std::vector<Entity*>> Entity::entidades;
unsigned Entity::defaultStack = 0;
std::vector<unsigned> Entity::entidadesStacks; 
Entity* Entity::instancia = NULL;
  
Transform* Entity::transform() { 
	return transformada;
}  

bool Entity::decreaseLife() {
	if (vida > -1) {
		vida -=  Time::deltaTime();
		if (vida <= 0) {
			vida = 0;
			return true;
		}
	}
	return false;
};
void Entity::setLifeTime(float miliseconds) {
	vida = miliseconds;
}
bool Entity::updateLifeTime(unsigned stack) {
	bool muertos = false;
	for (int i = 0; i < entidades[stack].size(); i++) {
		muertos =muertos || entidades[stack][i]->decreaseLife();
	}
	return muertos;
}
void Entity::destroyDead(unsigned stack) {
	auto entidadesT = &entidades[stack];
	for (int i = 0; i < entidadesT->size(); i++) {
		if (entidadesT->operator[](i)->vida == 0) {
			entidadesT->operator[](i)->erase();
			
			i--;
		}
	}
}
void Entity::checkLifeCicle(float delta) {
	auto ess = getAllEntities();
	//int muertos = 0;
	for (auto j = ess->begin(); j != ess->end();) {
		auto es = (*j);
		bool suma = true;
		for (int i = 0; i < ess->operator[](es.first).size();i++) {
			
			auto entidad = ess->operator[](es.first)[i];
			if (entidad->vida == 0) {
				if (entidad->active) {
					entidad->active = false;
					j++;
				} else {
					auto elementos = ess->operator[](es.first).size();
					//DBG("Antes %", ess->operator[](es.first).size());
					graphic->removeEntity(entidad);
					//entidad->destroy();
					//ess->operator[](es.first).erase(ess->operator[](es.first).begin()+i);
					delete entidad;
					i--;
					suma = false;
					//DBG("Despues %", ess->operator[](es.first).size());
					return;
				}
			} else {
				if (entidad->vida > 0) {
					entidad->vida -= 1000 * delta;
					if (entidad->vida < 0) {
						entidad->vida = 0;
					}
				}
				
			}
		}
		if (suma) {
			j++;
		}
	}

}
/**
* Call start method for all Code components 
*/
void Entity::startCodes(unsigned stack,Input *input) { 
	//Coge todos los componentes de todas las entidades y bucas aquellos componentes que sean Codigo. Luego llama al método Start;
	for (int i = 0; i < entidades[stack].size(); i++) { 
		std::vector<Code*> *codigos =  entidades[stack][i]->getComponents<Code>();
		for (int j = 0; j < codigos->size(); j++) {
			codigos->operator[](j)->setInput(input);
			codigos->operator[](j)->start(); 
		}
	}
	
}
void Entity::stopCodes(unsigned stack) {
	//Coge todos los componentes de todas las entidades y bucas aquellos componentes que sean Codigo. Luego llama al método Start;
	for (int i = 0; i < entidades[stack].size(); i++) {
		std::vector<Code*>* codigos = entidades[stack][i]->getComponents<Code>();
		for (int j = 0; j < codigos->size(); j++) {
			codigos->operator[](j)->destroy();
		}
	}

}
void Entity::updateCode() {
	
	auto lasEntidades = entidades[defaultStack];//Hacemos una copia para evitar que falle si el update de código añade o quita entidades

	for (auto entidad:lasEntidades) {
		if (entidad->isActive()) {
			std::vector<Code*>* codigos = (std::vector<Code*>*)entidad->getComponents<Code>();
			if (codigos != NULL) {
				for (auto itrC = codigos->begin(); itrC != codigos->end(); itrC++) {
					(*itrC)->update();
					
				}
			}
			/*if ((*itrE)->actualizarRender) {
				(*itrE)->actualizarRender = false;
				(*itrE)->update();
			}/**/
			
		}
	}
}

void Entity::setRenderUpdatable() {
	actualizarRender = true;
	changeModel = true;
}
void Entity::preUpdateCode(){
	for (auto itrE = entidades[defaultStack].begin(); itrE != entidades[defaultStack].end(); itrE++) {
		if ((*itrE)->isActive()) {
			std::vector<Code*>* codigos = (std::vector<Code*>*)(*itrE)->getComponents<Code>();
			if (codigos != NULL) {
				for (auto itrC = codigos->begin(); itrC != codigos->end(); itrC++) {
					(*itrC)->preUpdate();
				}
			}
		}
	}

}
void Entity::erase() {
	graphic->removeEntity(this);
	delete this;

};
void Entity::clear() {
	for (auto entidad : entidades) {
		for (auto ent : entidad.second) {
			ent->deleteComponents();
			
			delete ent;
		}
	}
	entidades.clear();
	entidadesStacks.clear();
	//idEntidadMax = 0;
	//std::vector<Component*> componentesOrden;
	//std::map<Entity::TIPO, std::vector<Component*>> componentes;
};
float* Entity::getModel() {
	if (changeModel) {
		changeModel = false;

		
		auto [x, y, z] = transformada->getPosition();
		auto [a, b, g] = transformada->getRotation();
		auto [w, h, d] = transformada->getScale();
		Transform::calculateMatrix(model, x, y, z, a, b, g, w, h, d);
	}
	return model;
}
std::vector<Component*>* Entity::getComponents() {
	return &this->componentesOrden;
}
void Entity::deleteComponents() {
	for (auto componente : componentesOrden) {
		delete componente;
	}
	componentesOrden.clear();
	componentes.clear();
}

std::vector<Entity*> Entity::getEntities(unsigned stack, Entity* parent) {
	std::vector<Entity*> resultado;
	if (parent == NULL) {
		auto entidadesCompletas = entidades[stack];
		for (auto e : entidadesCompletas) {
			if (e->padre == parent) {
				resultado.push_back(e);
			}
		}
	} else {
		return parent->hijos;
	}
	return resultado; 
}
void Entity::setParent(Entity* e) { 
	if (e == this || padre==e) {
		return;
	}
	if (padre != NULL) {
		padre->borrarHijo(this);
	}
	padre = e;
	if (e != NULL) {
		e->appendChild(this);
	}
	
	transformada->setParent((e!=NULL)?e->transformada:NULL);
	
}
void Entity::borrarHijo(Entity* hijo) {
	transformada->removeChild(hijo);
	for (auto itr = hijos.begin(); itr != hijos.end(); itr++){
		if (*itr == hijo) {
			//Lo hemos encontrado
			hijos.erase(itr);
			return;
		}

	}

}

void modules::graphics::Graphic::updateEntities(unsigned stack, modules::graphics::Graphic::TYPE_OPERATION type) {
	std::vector<Entity*> entidades = Entity::getEntities(stack);
	for (auto entidad : entidades) {
		if (entidad->isActive()  && entidad->isUpdatingRender()) { //&& entidad->isVisible()
			updateEntity(entidad, type);
		}
	}
	
}

void Collider::recalcular() {
	//cX = entidad->transform()->position()->x;
	//cY = entidad->transform()->position()->y;
	//cZ = entidad->transform()->position()->z;
};



std::string Entity::serializar() {
	//TODO: Penasar en cifrar los datos
	//Nombre
	//Activo o no
	//Tranform
	//Padre <- Necesitamos primero almacenar el padre para luego enlazarlo 
	std::string resultado = "{\r\n";
	resultado += GenericFile::serializate("name", nombre);
	resultado += GenericFile::serializate("active", (active ? "S" : "N"));
	resultado += GenericFile::serializate("trans_position", this->transformada->getPosition());
	resultado += GenericFile::serializate("trans_scale", this->transformada->getScale());
	resultado += GenericFile::serializate("trans_ratation", this->transformada->getRotation(), false);
	auto componentes = getComponents();
	if (componentes->size() > 0) {
		resultado += ",";
	}
	for(auto componente:*componentes){
		resultado += componente->serializar();
	}
	resultado += "}\r\n";
	return resultado;
}
int Entity::desserializar(std::string s, int pos, modules::graphics::Graphic*g) {
	switch (s[pos]) {
		case '[':
		case ',':
			{
				//Tenemos una nueva entidad
				//¿tipo?
			/*
			* e = new Entity(stack);
		//if (g) {
			////g->addEntity(e);
		//}
		r = e->addComponent<RenderableComponent>();
		r->add<renderable::Cube>();
		r->setUpdated(true);
			*/
				Entity* entidad = new Entity();
				entidad->graphic = g;
				pos=GenericFile::jumpSerializateTo('{',s,pos+1);
				while (pos<s.length() && s[pos] != '}') {
					auto [posT, clave, valor] = GenericFile::unserializate(s, pos + 1);
					pos = posT;
					if (clave == "name") {
						entidad->setName(valor);
					} else if (clave == "active") {
						entidad->setActive(valor == "S");
					} else if (clave == "trans_position") {
						auto [x, y, z] = GenericFile::unserializate3f(valor);
						entidad->transformada->setPosition(x,y,z);
					} else if (clave == "trans_scale") {
						auto [x, y, z] = GenericFile::unserializate3f(valor);
						entidad->transformada->setScale(x, y, z);
					} else if (clave == "trans_rotation") {
						auto [x, y, z] = GenericFile::unserializate3f(valor);
						entidad->transformada->setRotation(x, y, z);
					} else if (clave == "componente") {
						//DBG("C %", valor);
						 Component::desserializar(valor, 0, entidad);
						 pos += valor.length() + 2;
					} else {
						pos++;
					}
				}
			}
			break;
		case ' ':
		case '\t':
		case '\r':
		case '\n':
				pos = desserializar(s, pos++);
				break;
	}

	return pos;
}
int Entity::saveState(std::vector<unsigned char>* data, bool withID, int pos) {
	int longitud = 0;
	std::vector<unsigned char> dataT;
	if (withID) {
		longitud+=Serializer::serialize(data, this);
	}
	if (pos > -1) {
		longitud+=Serializer::serialize(data, pos);
	}
	Serializer::serialize(&dataT, nombre.c_str(), (active ? 'S' : 'N'));
	float a, b, c;
	std::tie(a, b, c) = this->transformada->getPosition();
	Serializer::serialize(&dataT, a, b, c);
	std::tie(a, b, c) = this->transformada->getScale();
	Serializer::serialize(&dataT, a, b, c);
	std::tie(a, b, c) = this->transformada->getRotation();
	Serializer::serialize(&dataT, a, b, c);
	auto componentes = getComponents();
	Serializer::serialize(&dataT, (int)componentes->size());
	for (auto componente : *componentes) {
		//if (componente->__vfptr) {
			componente->saveState(&dataT, withID);
		//}
	}

	//Ahora guardamos los hijos
	auto hijos = getEntities(0, this);
	Serializer::serialize(&dataT, (int)hijos.size());
	for (auto hijo : hijos) {
		
		hijo->saveState(&dataT, withID);
		
	}
	
	longitud += Serializer::serialize(data, &dataT);


	return longitud;
};
void Entity::restoreState(std::vector<unsigned char>* data, bool withID) {
	if (data != 0) {
		Deserializer::setBytes(data);
	}
	//Primero obtenemos la longitud
	int longitudEntidad;
	Deserializer::deserialize(&longitudEntidad);
	std::vector<unsigned char> dataT;
	Deserializer::extract(&dataT, longitudEntidad);
	Deserializer::stackBytes(&dataT);
	//Ahora restauramos
	int longitud = Deserializer::getLengthString();
	char* nombre = new char[longitud];
	Deserializer::deserialize(&nombre);
	this->nombre = std::string(nombre);
	char activo;
	Deserializer::deserialize(&activo);
	this->active = activo=='S'?true:false;
	float x, y, z;
	Deserializer::deserialize(&x);
	Deserializer::deserialize(&y);
	Deserializer::deserialize(&z);
	this->transform()->setPosition(x, y, z);
	Deserializer::deserialize(&x);
	Deserializer::deserialize(&y);
	Deserializer::deserialize(&z);
	this->transform()->setScale(x, y, z);
	Deserializer::deserialize(&x);
	Deserializer::deserialize(&y);
	Deserializer::deserialize(&z);
	this->transform()->setRotation(x, y, z);
	deleteComponents();
	int numComponentes = 0;
	Deserializer::deserialize(&numComponentes);
	if (numComponentes > 100) {
		ERR("No se pueden tener más de 100 componentes");
		Deserializer::unstackBytes();
		return;
	}
	for (int i = 0; i < numComponentes; i++) {
		bool existeComponente = false;
		void* idComponente = 0;
		if (withID) {
			Deserializer::deserialize(&idComponente);
			auto misComponetes = getComponents();
			for (auto componente : *misComponetes) {
				if (componente == idComponente) {
					existeComponente = true;
					break;
				}
			}
		}
		std::vector<unsigned char> dataTComponent;
		int longitudDataT = 0;
		Deserializer::deserialize(&longitudDataT);
		Deserializer::extract(&dataTComponent, longitudDataT);
		Deserializer::stackBytes(&dataTComponent);
		int tipoComponente=0;
		Deserializer::deserialize(&tipoComponente);
		//Buscamos componente
		if (!existeComponente) {
			DBG("No existe el componente para %",nombre);
			DBG("Creamos tipo %", tipoComponente);
			//Creamos el componente
			switch ((TYPE_OBJECT_SERIALIZABLES)tipoComponente){
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RENDERABLE:
					idComponente=addComponent<RenderableComponent>();
					break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RIGIDBODY:
					idComponente = addComponent<physics::RigidBodyComponent>();
					break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_SHADER:
					idComponente = addComponent<graphics::ShaderComponent>();
					break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_BOXCOLLIDER:
					idComponente = addComponent<BoxColliderComponent>();
					break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_CAMERA:
					idComponente = addComponent<Camera>();
					break;
				//case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_AUDIO:
				//	idComponente = addComponent<Audio>();
				//	break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_CODE:
					idComponente = addComponent<Code>();
					break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_LUZ:
					idComponente = addComponent<LightComponent>();
					break;
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_INTERFACE:
					idComponente = addComponent<InterfaceComponent>();
					break;
				default:
					idComponente = NULL;
					break;
			}
		} else {

		}
		if (idComponente) {
			((Component*)idComponente)->restoreState(0,withID);
		}
		Deserializer::unstackBytes();
	}

	//Obtenemos el número de hijos
	int numHijos = 0;
	Deserializer::deserialize(&numHijos);
	
	for (int i = 0; i < numHijos; i++) {
		Entity* hijo = new Entity();
		hijo->graphic = graphic;
		hijo->restoreState(0, withID);
		hijo->setParent(this);
	}


	Deserializer::unstackBytes();
};

int Entity::onDelete(std::function<void(Entity*)>function) { 
	return Handler::setHandle(&funcionesCierre, function);
}
void Entity::removeOnDelete(int pos) {
	Handler::removeHandle(&funcionesCierre, pos);
};
/*int Entity::desserializar(std::string s, int pos, Component* c) {
	while (pos < s.length()) {
		auto [posT, clave, valor] = GenericFile::unserializate(s, pos + 1);
		pos = posT;
		if (clave == "tipo") {
			renderable::Object::TYPE t = (renderable::Object::TYPE)std::atoi(valor.c_str());
			switch (t) {
			case renderable::Object::TYPE::CUBE:
			{
				//auto cubo = c->add<Cube>();
				//cubo->desserializar(valor);
				pos += valor.length() + 2;
			}
			break;
			default:
				ERR("No se reconoce el tipo de Objeto [Tipo: %]", (int)t);
				return s.length();
				break;
			}
		}
	}
	return pos;
}
int Entity::desserializar(std::string s, int pos, RenderableComponent* c) {
	while (pos < s.length()) {
		auto [posT, clave, valor] = GenericFile::unserializate(s, pos + 1);
		pos = posT;
		if (clave == "tipo") {
			renderable::Object::TYPE t = (renderable::Object::TYPE)std::atoi(valor.c_str());
			switch (t) {
			case renderable::Object::TYPE::CUBE:
			{
				//auto cubo = c->add<renderable::Cube>();
				//cubo->desserializar(valor);
				pos += valor.length() + 2;
			}
			break;
			default:
				ERR("No se reconoce el tipo de Objeto [Tipo: %]", (int)t);
				return s.length();
				break;
			}
		}
	}
	return pos;
}/**/
unsigned long Entity::getNewId() {
	idMutex.lock();
	auto idA=idEntidadMax++;
	idMutex.unlock();
	return idA;
}
void Entity::renewIds() {
	idMutex.lock();
	idEntidadMax = 1;
	idMutex.unlock();
}


void Entity::controlInterface(std::tuple<int, int> pos, int buttonPress) {
	auto [x, y] = pos;
	auto gl = Global::getInstance();
	x -= gl->marginLeft;
	y -= gl->marginTop;
	//TODO: Deberíamos guardar los componentes de Interfaz en un array statico.
	for (auto e_s : entidades) {
		for (auto e : e_s.second) {
			if (e->componentes.find(INTERFAZ) != e->componentes.end()) {
				for (auto c : e->componentes[INTERFAZ]) {
					//TODO: Comprobar las Z
					if (c->controlMouse(x,y, buttonPress)) {
						break;
					};
				}
			}
		}
	}

};

modules::graphics::Graphic* Entity::graphic = NULL;
unsigned long Entity::idEntidadMax = 0;
std::mutex Entity::idMutex;