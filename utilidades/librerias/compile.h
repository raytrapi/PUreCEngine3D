#ifndef __COMPILE
#define __COMPILE
#include <stdlib.h>
#include <string>
#include <thread>
#ifdef WIN32
#include <windows.h>
#endif
#include "../log/log.h"

class Compile {
public:
	static char* entornoCompilador;
	enum Types{NINJA};
	static void compileProject(const char* project, Types tipo);
};



#endif // !__COMPILE
