#include "compile.h"

void Compile::buscarCompilador() {
#ifdef WIN32
	
	//PROBAMOS VS19
	HKEY clave;
	LONG respuesta = RegOpenKeyEx(HKEY_CLASSES_ROOT, "VisualStudio.DTE.16.0\\CLSID", 0, KEY_READ, &clave);
	bool correcto = respuesta == ERROR_SUCCESS;
	if (!correcto) {
		bool noExiste = respuesta == ERROR_FILE_NOT_FOUND;
	}

	std::string CLSID = "";
	leerRegistro(clave, "", CLSID);
	if (!CLSID.empty()) {
		//Tenemos el ID de la clave.
		respuesta = RegOpenKeyEx(HKEY_CLASSES_ROOT, (std::string("WOW6432Node\\CLSID\\")+CLSID+"\\LocalServer32").c_str(), 0, KEY_READ, &clave);
		bool correcto = respuesta == ERROR_SUCCESS;
		if (!correcto) {
			bool noExiste = respuesta == ERROR_FILE_NOT_FOUND;
		}
		//std::string ejecutable = "";
		leerRegistro(clave, "", rutaCompilador);
		//Sacamos la ruta del 
		if (!rutaCompilador.empty()) {
			
			std::filesystem::path ruta((rutaCompilador[0]!='\"')?rutaCompilador:rutaCompilador.substr(1,rutaCompilador.size()-2));
			std::string rutaBat=ruta.parent_path().string() + "\\..\\..\\VC\\Auxiliary\\Build\\vcvarsall.bat";
			if (std::filesystem::exists(rutaBat.c_str())) {
				entornoCompilador = std::string("\"")+rutaBat + std::string("\"") + " x86_amd64";
			}
		}
	}
	



#endif // WIN32


}

void Compile::leerRegistro(HKEY clave, const char* subClave, std::string& valor) {
	char* buffer[512];
	DWORD tamañoBuffer = sizeof(buffer);
	ULONG error;
	error = RegQueryValueEx(clave, subClave, 0, NULL, (LPBYTE)buffer, &tamañoBuffer);
	if (error == ERROR_SUCCESS) {
		valor = std::string((char*)buffer);
	}
}

void Compile::leerRegistro(HKEY clave, const char* subClave, bool& valor) {
	
}

void Compile::compileProject(const char* project, Types tipo, std::function<void()> callbackEnd) {
	LOG_DBG("Compilando el código %",project);
	std::string comando;
	int i;
	switch (tipo) {
	case Compile::NINJA:
#ifdef WIN32
		if (!std::filesystem::exists(std::string(project)+"/build.ninja")) {
			generateProject(project, tipo, false);
		}
		comando= std::string(compilerScope()) + " && cd  \"" + std::string(project) + "\"&&ninja" + +" 1>c.txt 2>e.txt";
		for (int j = 0; j < comando.length(); j++) {
			if (comando[j] == '/') {
				comando[j] = '\\';
			}

		}

		/*unsigned int idProceso=WinExec(comando.c_str(),0);
		unsigned int yo = utiles::Watchdog::setInterval([yo, idProceso]() {
			GetMessage(idProceso);
		}, 500);/**/
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		// Start the child process. 
		if (!CreateProcess(NULL,   // No module name (use command line)
			(char *)comando.c_str(),        // Command line
			NULL,           // Process handle not inheritable
			NULL,           // Thread handle not inheritable
			FALSE,          // Set handle inheritance to FALSE
			CREATE_NO_WINDOW,              // No creation flags
			NULL,           // Use parent's environment block
			NULL,           // Use parent's starting directory 
			&si,            // Pointer to STARTUPINFO structure
			&pi )           // Pointer to PROCESS_INFORMATION structure
			)
		{
			utiles::Log::error("No se puede ejecutar");
			return;
		}
		WaitForSingleObject(pi.hProcess, 120000);
		//utiles::Log::debug("Se termino de compilar");
		if (callbackEnd) {
			callbackEnd();
		}
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);


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

void Compile::generateProject(const char* project, Types tipo,bool generar) {
	std::string comando;
	int i;
	switch (tipo) {
	case Compile::NINJA:
		comando = std::string(compilerScope()) + " && cd  \"" + std::string(project) + (generar?"\\build":"") +"\"&&cmake -G \"Ninja\" .." + +" 1>c.txt 2>e.txt";
#ifdef WIN32
		
		for (int j = 0; j < comando.length(); j++) {
			if (comando[j] == '/') {
				comando[j] = '\\';
			}

		}

		WinExec(comando.c_str(), 0);
		//std::this_thread::sleep_for(std::chrono::milliseconds(1000));
#else
		if (!system(NULL)) {
			return;
		}
		//TODO: CAMBIAR ESTO PARA QUES ALGO MÁS EFICIENTE
		for (int j = 0; j < comando.length(); j++) {
			if (comando[j] == '/') {
				comando[j] = '\\';
			}

		}
		i = system(comando.c_str());
#endif

		break;
	default:
		break;
	}
}
const char* Compile::pathCompiler() {
	if (rutaCompilador.empty()) {
		//Buscamos el compilador
		buscarCompilador();
	}
	return rutaCompilador.c_str();
}

const char* Compile::compilerScope() {
	if (rutaCompilador.empty()) {
		//Buscamos el compilador
		buscarCompilador();
	}
	return entornoCompilador.c_str();
}

const void Compile::checkCompiled(const char* project) {
	//Leeremos el fichero línea a línea intentando buscar los errores
	std::ifstream fichero;
	std::string ficheroError(project);
	ficheroError += "c.txt";
	fichero.open(ficheroError.c_str(), std::ios::in);
	std::string linea;
	std::regex error("^(.*): error (.*) (.*)$");
	if (fichero.is_open()) {
		while (std::getline(fichero, linea)) {
			std::cmatch errores;
			std::regex_match(linea.c_str(), errores, error);
			if (errores.size() > 0) {
				LOG_DBG(linea);
			}
		}
	}
}


std::string Compile::entornoCompilador = "";// "\"u:/Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Auxiliary/Build/vcvarsall.bat\" x86_amd64";
std::string Compile::rutaCompilador = "";