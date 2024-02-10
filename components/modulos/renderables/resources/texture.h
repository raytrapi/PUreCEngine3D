#ifndef __TEXTURE
#define __TEXTURE
#include <vector>
#include <imgui.h>
#include "../../../../utilidades/utiles/pointers.h"

#include "../../../src/exportar.h"
#include "../../../../utilidades/files/filesControl.h"

class EXPORTAR_COMPONENTE TextureImg {
public:
	enum TYPE {

		COLOR,
		SCALAR,
		BUMP
	};
	enum FORMAT_COLOR {
		DEPTH,
		DEPTH_STENCIL,
		RED,
		RG,
		RGB,
		RGBA
	};

	TextureImg() {};
	TextureImg(const TextureImg&);
	TextureImg(float* image, unsigned int length, TYPE tipo, int width = 0, int height = 0, FORMAT_COLOR formatColor = RGB);
	~TextureImg() {
		if (image != NULL) {
			delete[]image;
			image = NULL;
		};
	};
	void setImage(float* image, unsigned int length, TYPE tipo, int width = 0, int height = 0, FORMAT_COLOR formatColor = RGB);
	bool interfazImGUI(ImGuiContext* imgui);
	int saveState(std::vector<unsigned char>* data, bool withID);
	void restoreState(std::vector<unsigned char>* data, bool withID);
	static std::map<char*, std::tuple<unsigned int, int, int, TextureImg::FORMAT_COLOR>, cmp_str> textures; //TODO: Optimizar esto con una estructura para almacenar cadenas tipo árbol
	static std::tuple<unsigned int, int, int, TextureImg::FORMAT_COLOR> getIdImagen(const char* path);
	static void deleteTextures();
private:
	TYPE type;
	float* image = NULL;
	unsigned int length = 0;
	int width;
	int height;
	FORMAT_COLOR formatColor;
	void chargeImage(float* image, unsigned int lenght);
};
class EXPORTAR_COMPONENTE Texture {
public:
	Texture() {};
	Texture(const Texture&);
	Texture(const char* file);
	~Texture() {
		if (texture != NULL) {
			delete texture;
			texture = NULL;
		};
		DELETE_MULTI(ruta);
	};
	static std::tuple<unsigned int, int, int, TextureImg::FORMAT_COLOR> loadImage(const char* file);
	void setImage(float* image, unsigned int length, int width, int height, unsigned  idTexture, TextureImg::FORMAT_COLOR formatColor = TextureImg::FORMAT_COLOR::RGBA);
	void setTexture(float*, unsigned int, int width, int height, TextureImg::FORMAT_COLOR formatColor = TextureImg::FORMAT_COLOR::RGBA, int repeat = 0, int nearest = 0);
	void setTexture(unsigned  idTexture);
	unsigned int getIdTexture() { return idTexture; };
	void setIdTexture(unsigned int id) { idTexture = id; };
	bool interfazImGUI(ImGuiContext* imgui);
	int saveState(std::vector<unsigned char>* data, bool withID);
	void restoreState(std::vector<unsigned char>* data, bool withID);
	const char* getPath();
	void setPath(const char* path);
	void setUV(float u1, float v1, float u2, float v2) { this->u1 = u1; this->v1 = v1; this->u2 = u2; this->v2 = v2;}
	std::tuple<float, float, float, float> getUV() { return {u1,v1,u2,v2}; }
	void setUID(UID uid) { this->uid = uid; }
private:
	TextureImg* texture = NULL;
	unsigned int idTexture = -1;
	int ancho = 0;
	int alto = 0;
	float u1 = 0;
	float v1 = 1;
	float u2 = 1;
	float v2 = 0;
	TextureImg::FORMAT_COLOR formato;
	UID uid=0;
	char* ruta = NULL;
};
#endif // !__TEXTURE
