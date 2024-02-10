#include "texture.h"
#include "../../../../modules/src/module.h"
#include "../../../../modules/graphic/motor.h"
#include "../modules/resources/resource.h"
#include <module.h>
Texture::Texture(const Texture& t) {
	this->idTexture = t.idTexture;
	if (t.texture != NULL) {
		this->texture = new TextureImg(*t.texture);
	}
};
Texture::Texture(const char* file) {
	COPY_CHAR(file, ruta);
	
	std::tie(idTexture, ancho, alto, formato) = loadImage(file);
	
}
std::tuple<unsigned int, int, int, TextureImg::FORMAT_COLOR> Texture::loadImage(const char* file) {
	//Localizamos la textura
	auto pos = TextureImg::textures.find((char*)file);
	if (pos == TextureImg::textures.end()) {
		modules::graphics::Graphic* motor = Module::get<modules::graphics::Graphic>();
		if (motor) {
			auto v = motor->loadTexture(std::string(file), modules::graphics::Graphic::TYPE_TEXTURE::T_IMG, modules::graphics::Graphic::TYPE_REPEAT::REPEAT);
			auto l = strlen(file);
			char* n = new char[l + 1];
			for (int i = 0; i < l; i++) {
				n[i] = file[i];
			}
			n[l] = '\0';
			TextureImg::textures[n] = v;
			return v;
		} else {
			return { 0,0,0,TextureImg::RGBA };
		}
	}
	return (*pos).second;
}

void Texture::setTexture(unsigned int idTexture) {
	this->idTexture = idTexture;
}
void Texture::setTexture(float* image, unsigned int length, int width, int height, TextureImg::FORMAT_COLOR formatColor, int repeat, int nearest) {
	this->texture = new TextureImg(image, length, TextureImg::TYPE::COLOR);
	//Ahora deberemos cargar la imagen en nuestro sistema para obtener el ID de la textura
	modules::graphics::Graphic* g = Module::get<modules::graphics::Graphic>();
	if (g->addTexture(image, length, width, height, this->idTexture, formatColor, (modules::graphics::Graphic::TYPE_REPEAT)repeat, (modules::graphics::Graphic::TYPE_FILTERING)nearest)) {
	};
}
void Texture::setImage(float* image, unsigned int length, int width, int height, unsigned  idTexture, TextureImg::FORMAT_COLOR formatColor) {
	this->idTexture = idTexture;
	this->texture = new TextureImg(image, length, TextureImg::TYPE::COLOR, width, height, formatColor);
}
const char* Texture::getPath() {
	return (const char*)ruta;
}
void Texture::setPath(const char* path) {
	if (ruta) {
		delete[]ruta;
	}
	auto l = strlen(path);
	ruta = new char[l + 1];
	for (int i = 0; i < l; i++) {
		ruta[i] = path[i];
	}
	ruta[l] = '\0';/**/
	//COPY_CHAR(path, ruta);
}
bool Texture::interfazImGUI(ImGuiContext* imgui) {
	
	return true;
}
int Texture::saveState(std::vector<unsigned char>* data, bool withID) {
	int mode = 0;
	Serializer::serialize(data, mode);
	//unsigned int l = strlen(ruta)+1;
	//Serializer::serialize(data, l);
	
	Serializer::serialize(data, ruta);
	Serializer::serialize(data, u1, v1, u2, v2);

	return 0;
};
void Texture::restoreState(std::vector<unsigned char>* data, bool withID) {
	int mode = 0;
	Deserializer::deserialize(&mode);
	if (mode == 0) {
		unsigned int l;
		l=Deserializer::getLengthString();
		if (ruta != 0) {
			delete[] ruta;
		}
		ruta = new char[l];
		Deserializer::deserialize(&ruta);
		Deserializer::deserialize(&u1, &v1, &u2, &v2);
		std::tie(idTexture, ancho, alto, formato) = loadImage((Global::getInstance()->getPathRoot()+"/"+ruta).c_str());
		if (l > 1) {
			DBG("%", ruta);
		}

	}
};
bool TextureImg::interfazImGUI(ImGuiContext* imgui) {
	return true;
}
int TextureImg::saveState(std::vector<unsigned char>* data, bool withID) {
	return 0;
};
void TextureImg::restoreState(std::vector<unsigned char>* data, bool withID) {
};

TextureImg::TextureImg(const TextureImg& t) {
	this->type = t.type;
	chargeImage(t.image, t.length);

};
TextureImg::TextureImg(float* image, unsigned int length, TYPE tipo, int width, int height, FORMAT_COLOR formatColor) {
	setImage(image, length, tipo, width, height, formatColor);
}
void TextureImg::setImage(float* image, unsigned int length, TYPE tipo, int width, int height, FORMAT_COLOR formatColor) {
	this->type = type;
	chargeImage(image, length);
	this->width = width;
	this->height = height;
	this->formatColor = formatColor;
};
void TextureImg::chargeImage(float* image, unsigned int lenght) {
	this->image = new float[length];
	for (int i = 0; i < length; i++) {
		this->image[i] = image[i];
	}
	this->length = length;

};

std::tuple<unsigned int, int, int, TextureImg::FORMAT_COLOR> TextureImg::getIdImagen(const char* path) {
	auto pos = textures.find((char*)path);
	if (pos != textures.end()) {
		return (*pos).second;
	}
	return {0,0,0,RGBA};
}
void TextureImg::deleteTextures() {
	for (auto a : textures) {
		delete[]a.first;
	}
	textures.clear();
}
std::map<char*, std::tuple<unsigned int, int, int, TextureImg::FORMAT_COLOR>, cmp_str> TextureImg::textures;