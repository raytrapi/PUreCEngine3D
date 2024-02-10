
#include "log.h"
#include "logFile.h"
namespace utiles {
	
	Log::Log(bool selected){
		instancias.push_back(this);
		if (selected) {
			idInstanciaActual = instancias.size() - 1;
		}
		/*fichero.open(nombreFichero, std::ios::app | std::ios::out);
		salida=new std::ostream(&fichero);/**/
	}
	
	
	void Log::destroy() {
		for (auto instancia : instancias) {
			delete instancia;
		}
	}
	void Log::setInstanceId(unsigned idInstance) {
		idInstanciaActual = idInstance;
	}
	int Log::getNumberInstances() {
		return instancias.size();
	}
	
	void Log::escribir(std::string& s, utiles::Log::NIVEL nivel) {

		if (instancias.size()>0) {
			instancias[idInstanciaActual]->escribirVirtual(s, nivel);
			return;
		}
		escribir().escribirVirtual(s, nivel);
	}
	void Log::escribirF(std::string& s, utiles::Log::NIVEL nivel) {
		instancias[0]->escribirVirtual(s, nivel);
	}
	Log& Log::escribir() {
		Log* instancia;
		if (instancias.size()==0) {

			instancia = new LogFile();
			//instancia->init();
		} else {
			instancia = instancias[idInstanciaActual];
		}
		return (*instancia);
	}


	const char* Log::to_utf8(std::string text, const std::locale& loc) {
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring str = converter.from_bytes(text);
		std::vector<char> buf(str.size());
		use_facet<std::ctype<wchar_t>>(loc).narrow(str.data(), str.data() + str.size(), '?', buf.data());
		return std::string(buf.data(), buf.size()).c_str();
		
	}

	std::vector<Log*> Log::instancias;
	unsigned Log::idInstanciaActual=0;
	
} /* namespace utiles */
