#ifndef __LOG_OPENGL
#define __LOG_OPENGL
#include <sstream>
#include "../../../../../utilidades/log/log.h"
#include <imgui.h>
#include <mutex>;
	class LogOpenGL : public utiles::Log {
		void init() {};
		void destroy() {};
		std::mutex bloqueo;
	public:
		LogOpenGL(bool selected):utiles::Log(selected) {
		};
		~LogOpenGL() {
			clear();
		}
		void escribirVirtual(std::string& s, utiles::Log::NIVEL nivel = utiles::Log::NIVEL::INF);
		void clear() {
			buffer.clear();
			indicesLinea.clear();
			for (auto linea : lineas) {
				delete[] std::get<0>(linea);
				delete[] std::get<3>(linea);
				delete[] std::get<4>(linea);
			}
			lineas.clear();
		}
		ImGuiTextBuffer getBuffer() { return buffer; }
		//Vector de logs
		std::vector<std::tuple<char*, ImVec4, int, char*, char *>> getLines() { return lineas; }
		bool hasNewLog() { return conScroll; }
		void setNewLog(bool hasNewLog) { conScroll = hasNewLog; }
	private:
		ImGuiTextBuffer buffer;
		std::vector<std::tuple<char*, ImVec4,int, char*, char*>> lineas;
		ImGuiTextFilter filtro;
		ImVector<int> indicesLinea;
		bool conScroll=false;
	};


#endif // !__LOG_OPENGL