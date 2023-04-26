#include "log.h"

	void LogOpenGL::escribirVirtual(std::string& s, utiles::Log::NIVEL nivel) {
		std::time_t ahora = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		char* tipo;
		char* tiempo;
		std::stringstream os;
		ImVec4 color;
		switch (nivel) {
		case utiles::Log::FAT:
			//os << "FAT\t";
			tipo = new char[] {"FAT\0"};
			color = ImVec4(1.0f, 0, 0, 1.0f);
			break;

		case utiles::Log::ERR:
			//os << "ERR\t";
			tipo = new char[] {"ERR\0"};
			color = ImVec4(0.977f, 0.425f, 0.425f, 1.0f);
			break;
		case utiles::Log::WAR:
			//os << "WAR\t";
			tipo = new char[] {"WAR\0"};
			color = ImVec4(1.0f, 0.664f, 0.152f, 1.0f);
			break;
		case utiles::Log::INF:
			//os << "INF\t";
			tipo = new char[] {"INF\0"};
			color = ImVec4(0.6f, 0.6f, 1.0f, 1.0f);
			break;
		case utiles::Log::DEB:
			//os << "DEB\t";
			tipo = new char[] {"DBG\0"};
			color = ImVec4(1.f, 1.f, 1.f, 1.0f);
			break;
		}
		os << std::put_time(std::localtime(&ahora), "%F %T%z");
		//if (os) {
		//	os << std::put_time(std::localtime(&ahora), "%F %T%z") << "\t" << s << std::endl;
		//}
		/*const char* sinUTF8 = os.str().c_str();
		const char* strUTF8 = Log::to_utf8(os.str());/**/
		
		/*int tamañoAnterior = buffer.size();
		buffer.append(os.str().c_str());
		int nuevoTamaño = buffer.size();
		for (int i = tamañoAnterior; i < nuevoTamaño; i++) {
			if (buffer[i] == '\n') {
				indicesLinea.push_back(i);
			}
		}/**/
		bool igual = false;
		if (lineas.size() > 0) {
			const char* cadena = std::get<0>(lineas[lineas.size() - 1]);
			const char* cadena2 = strdup(s.c_str());
			int comparacion = strcmp(cadena, cadena2);
			igual = comparacion == 0;
		}
		if (lineas.size() > 0 && igual) {
			std::get<2>(lineas[lineas.size() - 1])++;
			std::get<4>(lineas[lineas.size() - 1])=strdup(os.str().c_str());
		}else {
			lineas.push_back({ strdup(s.c_str()), color, 1,strdup(tipo),strdup(os.str().c_str())});
		}
		conScroll = true;
		delete[]tipo;
		if (lineas.size() > 1000) {
			lineas.erase(lineas.begin());
		}
	}
