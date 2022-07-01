#include "motor.h"
#include "../../components/src/entity.h"
//#include "../../vendors/glfw/nuklear_glfw_gl4.h"
#include "../general.h"
void modules::graphics::Graphic::addEntity(void* entity) {
	/*int noEncontre = true;
	std::vector<Entity*> entities = Entity::getEntities();
	for (auto itr = entities.begin(); itr != entities.end() && noEncontre; itr++) {
		if (entity == (*itr)) {
			noEncontre = false;
		}
	}
	if (noEncontre) {
		entities.push_back(entity);
	}/**/
	updateEntity(entity);
}

void modules::graphics::Graphic::removeEntity(void* entity) {
	/*std::vector<Entity*> entities = Entity::getEntities();
	for (auto itr = entities.begin(); itr != entities.end(); itr++) {
		if (entity == (*itr)) {
			entities.erase(itr);
			//delete (*itr);
			return;
		}
	}/**/
}

void modules::graphics::Graphic::removeEntities() {
	/*bool seguir = true;
	for (auto itr = entities.begin(); itr != entities.end() && seguir; itr++) {
		
		seguir = false;
		//entities.erase(itr);
		delete (*itr);
	}
	entities.clear();/**/
}
void modules::graphics::Graphic::removeAll() {
	removeEntities();
	removeAllFocus();
}

void modules::graphics::Graphic::addOnFocus(void(*callback)(bool)) {
	onFocus.push_back(callback);
}

void modules::graphics::Graphic::addOnFocus(Tape* juego) {
	onFocusTapes.push_back(juego);
}
void modules::graphics::Graphic::removeOnFocus(Tape* juego) {
	int pos = -1;
	for (int i = 0; i < onFocusTapes.size(); i++) {
		if (onFocusTapes[i] == juego) {
			pos = i;
		}
	}
	if (pos != -1) {
		onFocusTapes.erase(onFocusTapes.begin()+pos);
	}
}

void modules::graphics::Graphic::removeAllFocus() {
	onFocusTapes.clear();
}

void  modules::graphics::Graphic::loadTexture(std::string name, std::string path, TYPE_TEXTURE type) {
	switch (type) {
		case modules::graphics::Graphic::NONE:
			break;
		case modules::graphics::Graphic::IMG:
			break;
		default:
			break;
	}
	//if(texturas.e)
	//texturas[name] = new Texture();
}

std::vector<void(*)(bool)> modules::graphics::Graphic::onFocus;
std::vector<modules::Tape*> modules::graphics::Graphic::onFocusTapes;
bool modules::graphics::Graphic::open = false;




/*MATERIALS*/
modules::graphics::Material::Material() {

}
modules::graphics::Material::Material(const modules::graphics::Material &m) {

	ambient = new float[m.lenA];
	for (int i = 0 ; i < m.lenA; i++) {
		ambient[i] = m.ambient[i];
	}
	lenA = m.lenA;
	typeAmbient=m.typeAmbient;
	lenD = m.lenD;
	difuse = new float[lenD];
	for (int i = 0; i < lenD; i++) {
		difuse[i] = m.difuse[i];
	}
	typeDifuse=m.typeDifuse;

	lenS = m.lenS;
	specular = new float[lenS];
	for (int i = 0; i < lenS; i++) {
		specular[i] = m.specular[i];
	}
	typeSpecular=m.typeSpecular;
	lenE = m.lenE;
	emission = new float[lenE];
	for (int i = 0; i < lenE; i++) {
		emission[i] = m.emission[i];
	}
	typeEmission=m.typeEmission;
	ilumination=m.ilumination;
	opacity=m.opacity;
	exponenteSpecular=m.exponenteSpecular;
	sharpness = m.sharpness;
	densityOptical=m.densityOptical;
	
	for (int i = 0; i < m.imgTextures.size(); i++) {
		imgTextures.push_back(new TextureImg(*m.imgTextures[i]));
	}
	for (int i = 0; i < m.textures.size(); i++) {
		textures.push_back(new Texture(*m.textures[i]));
	}
	
}
modules::graphics::Material::~Material() {
	//DBG_F("Destruyo el material");
	for (int i = 0; i < textures.size(); i++) {
		if (textures[i] != NULL) {

			//TODO: TENEMOS QUE LIBERAR LA TEXTURA DE LA MEMORIA DE LA TARJETA GRÁFICA
			delete textures[i];
		}
	}
	textures.clear();
	for (int i = 0; i < imgTextures.size(); i++) {
		delete imgTextures[i];
	}
	imgTextures.clear();
	if (ambient != NULL) {
		delete[]ambient;
		ambient = NULL;
	}
	if (difuse != NULL) {
		delete[]difuse;
		difuse = NULL;
	}
	if (specular != NULL) {
		delete[]specular;
		specular = NULL;
	}
	if (emission != NULL) {
		delete[]emission;
		emission = NULL;
	}
}
void modules::graphics::Material::setTexture(Texture* t) {
	this->textures.push_back(t);
}
void modules::graphics::Material::setTexture(unsigned int idTexture) {
	Texture *t = new Texture();
	t->setTexture(idTexture);
	this->textures.push_back(t);
};
void modules::graphics::Material::setTexture(float* img, unsigned int length, int width, int height, TextureImg::FORMAT_COLOR formatColor) {
	Texture* t = new Texture();
	t->setTexture(img, length,width,height,formatColor);
	this->textures.push_back(t);
};
modules::graphics::Texture::Texture(const Texture&t) {
	this->idTexture = t.idTexture;
	if (t.texture != NULL) {
		this->texture = new TextureImg(*t.texture);
	}
};
void modules::graphics::Texture::setTexture(unsigned int idTexture){
	this->idTexture = idTexture;
}
void modules::graphics::Texture::setTexture(float* image,  unsigned int length, int width, int height, TextureImg::FORMAT_COLOR formatColor) {
	this->texture = new TextureImg(image,length, modules::graphics::TextureImg::TYPE::COLOR);
	//Ahora deberemos cargar la imagen en nuestro sistema para obtener el ID de la textura
	graphics::Graphic *g= Module::get<modules::graphics::Graphic>();
	if (g->addTexture(image, length,width,height, this->idTexture,formatColor)) {
	};
}
void modules::graphics::Texture::setImage(float* image, unsigned int length, int width, int height, unsigned  idTexture, TextureImg::FORMAT_COLOR formatColor) {
	this->idTexture = idTexture;
	this->texture = new TextureImg(image,length, modules::graphics::TextureImg::TYPE::COLOR, width,height, formatColor);
}
modules::graphics::TextureImg::TextureImg(const TextureImg& t) {
	this->type = t.type;
	chargeImage(t.image, t.length);

};
modules::graphics::TextureImg::TextureImg(float* image, unsigned int length, TYPE tipo, int width, int height, FORMAT_COLOR formatColor) {
	setImage(image,length, tipo, width, height,formatColor);
}
void modules::graphics::TextureImg::setImage(float* image, unsigned int length, TYPE tipo, int width, int height, FORMAT_COLOR formatColor) {
	this->type = type;
	chargeImage(image, length);
	this->width = width;
	this->height = height;
	this->formatColor = formatColor;
};
void modules::graphics::TextureImg::chargeImage(float* image, unsigned int lenght) {
	this->image = new float[length];
	for (int i = 0; i < length; i++) {
		this->image[i] = image[i];
	}
	this->length = length;
	
};

//std::vector<std::tuple<Key, std::function<void(Key)>, bool>> Input::controlTeclasPulsadas;
//Input* Input::instancia;