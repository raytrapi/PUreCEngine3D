#ifndef _RESOURCE_CON_DLL
#define _RESOURCE_CON_DLL

#include "../../../../modules/resources/resource.h"
#include "../../../../utilidades/log/log.h"
//#include "../../../../utilidades/global/input.h"
#include "../../../../components/modulos/renderables/resources/texture.h"
#include <png.h>
#include <module.h>
#include <vector>

class ResourcesDirect : public modules::resources::Resource {
private:

public:
	char* nombre() { return (char*)"RESOURCES WITH LOAD FILES"; };
	std::tuple<float*, int, int, unsigned int, TextureImg::FORMAT_COLOR> loadImage(const char*, bool inverse=true);
};


#endif // !_COMP_REND

