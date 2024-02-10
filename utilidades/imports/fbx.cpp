#include "fbx.h"
#include "model.h"


std::vector<imports::ModelData*> imports::Fbx::load(const char* fileName, float directionY) {
	std::vector<imports::ModelData*> entidades;
	ofbx::IScene* escena = NULL;
	FILE* fp = fopen(fileName, "rb");

	if (!fp) return entidades;

	fseek(fp, 0, SEEK_END);
	long file_size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	auto* content = new ofbx::u8[file_size];
	fread(content, 1, file_size, fp);
	escena = ofbx::load((ofbx::u8*)content, file_size, (ofbx::u64)ofbx::LoadFlags::TRIANGULATE);
	if (!escena) {
		DBG("No hemos podido cargar la escena");
	} else {
		DBG("Tenemos % objetos", escena->getMeshCount());
	}
	delete[] content;
	fclose(fp);
	if (escena != NULL) {
		escena->destroy();
	}
	return entidades;
}
