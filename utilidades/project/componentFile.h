#ifndef _COMPONENT_FILE
#define _COMPONENT_FILE

extern class EntityFile;

class ComponentFile {
	friend class EntityFILE;
	char* nombre = 0;
	char* ruta = 0;
	//std::vector<EntityFile> entidades;

	//int load(const char* path);
	//int save();
private:
};

#endif // !_COMPONENT_FILE
