#ifndef __MATERIAL
#define __MATERIAL
#include "texture.h"
#include <vector>
#include <expected>
#include <filesystem>
#include "../../../../utilidades/files/filesControl.h"
#include <iostream>
#include "../../../../utilidades/project/serializer/serializer.h"
#include "../../../../utilidades/project/serializer/deserializer.h"
#include "../../../src/exportar.h"
#include <imgui.h>
#include "../../../../utilidades/utiles/pointers.h"
class EXPORTAR_COMPONENTE Material {
	UID uid=0;

public:
	enum TYPE {
		RGB,
		FILE
	};
	Material();
	Material(UID uid);
	Material(const Material&);
	~Material();
	void setTexture(Texture* t);
	void setTexture(unsigned int idTexture);
	void setTexture(float*, unsigned int, int width, int height, TextureImg::FORMAT_COLOR formatColor = TextureImg::FORMAT_COLOR::RGBA, int repeat = 0, int nearest = 0);
	unsigned int getIdTexture() { if (textures.size() > 0) { return textures[0]->getIdTexture(); } else { return 0; } };
	std::vector<Texture*>* getTextures() { return &textures; };
	bool haveTextures() { return textures.size() > 0; };

	static std::expected<bool, int> createFileMaterial(const char* path);
	void save();
	static Material* load(long long UID);
	void load(const char* path);
	bool interfazImGUI(ImGuiContext* imgui);
	int saveState(std::vector<unsigned char>* data, bool withID);
	void restoreState(std::vector<unsigned char>* data, bool withID);
	void setName(const char* name);
	const char* getName() { return (const char *)nombre; }
	unsigned long long getUID() { return uid; }
	static unsigned long long getUID(const char* path);
	void onChange(std::function<void(Texture* texture, Material* material)> callback) { funcionCambio = callback; };
	void removeChange() { funcionCambio = 0; };
	const float* getAmbient() { return ambient; };
private:
	
	char* nombre = NULL;
	char* fichero = NULL;
	unsigned int idImagenIcono = -1;
	std::string codigo;

	float* ambient = NULL; //Ka Color
	int lenA = 0;
	TYPE typeAmbient;
	float* difuse = NULL; //Kd Color
	int lenD = 0;
	TYPE typeDifuse;
	float* specular = NULL; //Ks Color
	int lenS = 0;
	TYPE typeSpecular;
	float* emission = NULL;
	int lenE = 0;
	TYPE typeEmission;
	int ilumination;
	float opacity; //d escalar
	float exponenteSpecular; //Ns escalar
	int sharpness = 60; //0 a 1000
	float densityOptical; //Ni
	//.mpc textura color
	//.mps textura escalar
	//.mpb textura de bump
	std::vector<TextureImg*> imgTextures;
	std::vector<Texture*> textures;

	std::function<void(Texture* texture, Material* material)>funcionCambio= 0;

public:
	void setCode(const char* code);
};



#endif // !__MATERIAL
