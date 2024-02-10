#include "log.h"


	void LogOpenGL::escribirVirtual(std::string& s, utiles::Log::NIVEL nivel) {
		//Esta función ha de ser bloqueante
		bloqueo.lock();
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
			//const char* cadena2 = strdup(s.c_str());
			if (cadena ) {
				int comparacion = strcmp(cadena, s.c_str());

				igual = comparacion == 0;
			}
		}
		int lenOS = os.str().length();
		if (lineas.size() > 0 && igual) {
			std::get<2>(lineas[lineas.size() - 1])++;
			std::string osS=os.str();
			auto len = osS.length();
			if (std::get<4>(lineas[lineas.size() - 1]) != 0) {
				delete[]std::get<4>(lineas[lineas.size() - 1]);
			}
			std::get<4>(lineas[lineas.size() - 1]) = 0;
			std::get<4>(lineas[lineas.size() - 1]) = new char[ len+ 1];
			for (int i = 0; i < len; i++) {
				std::get<4>(lineas[lineas.size() - 1])[i] = os.str()[i];
			}
			std::get<4>(lineas[lineas.size() - 1])[len] = '\0';
			//std::get<4>(lineas[lineas.size() - 1])=strdup(os.str().c_str());
		}else {
			if (s.length() > 0) {

				//lineas.push_back({ strdup(s.c_str()), color, 1,strdup(tipo),strdup(os.str().c_str())});
				lineas.push_back({ new char[s.length() + 1], color, 1,new char[strlen(tipo)+1],new char[os.str().length()+1]});
				auto linea = lineas[lineas.size() - 1];
				auto texto = std::get<0>(linea);
				auto longitudLinea = s.length();
				for (int i = 0; i < longitudLinea; i++) {
					texto[i] = s[i];
				}
				texto[longitudLinea] = '\0';
				texto = std::get<3>(linea);
				longitudLinea = strlen(tipo);
				for (int i = 0; i < longitudLinea; i++) {
					texto[i] = tipo[i];
				}
				texto[longitudLinea] = '\0';
				texto = std::get<4>(linea);
				longitudLinea = os.str().length();
				for (int i = 0; i < longitudLinea; i++) {
					texto[i] = os.str()[i];
				}
				texto[longitudLinea] = '\0';
			} else {

			}
		}
		conScroll = true;
		delete[]tipo;
		while (lineas.size() > 1000) {
			//Borramos la primera línea
			delete[] std::get<0>(lineas[0]);
			delete[] std::get<3>(lineas[0]);
			delete[] std::get<4>(lineas[0]);
			lineas.erase(lineas.begin());
		}
		bloqueo.unlock();
	}
