#ifndef __COMPILE
#define __COMPILE
#include <stdlib.h>
#include <string>
class Compile {
public:
	static char* entornoCompilador;
	enum Types{NINJA};
	static void compileProject(const char* project, Types tipo);
};



#endif // !__COMPILE
