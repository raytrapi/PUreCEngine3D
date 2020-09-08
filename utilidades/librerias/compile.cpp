#include "compile.h"

void Compile::compileProject(const char* project, Types tipo) {
	std::string comando;
	int i;
	switch (tipo) {
	case Compile::NINJA:
#ifdef WIN32
		comando= std::string(entornoCompilador) + " && cd  " + std::string(project) + "&&ninja" + +" 1>c.txt 2>e.txt";
		for (int j = 0; j < comando.length(); j++) {
			if (comando[j] == '/') {
				comando[j] = '\\';
			}

		}

		WinExec(comando.c_str(),0);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
#else
		if (!system(NULL)) {
			return;
		}
		//TODO: CAMBIAR ESTO PARA QUES ALGO MÁS EFICIENTE
		comando = std::string(entornoCompilador) + " && cd  " + std::string(project)+ "&&ninja" +  + " 1>c.txt 2>e.txt";
		for (int j = 0; j < comando.length(); j++) {
			if (comando[j] == '/') {
				comando[j] = '\\';
			}

		}
		i=system(comando.c_str());
#endif

		break;
	default:
		break;
	}
	


}


char* Compile::entornoCompilador = "\"u:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat\" x86_amd64";