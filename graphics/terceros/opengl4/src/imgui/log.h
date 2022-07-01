#ifndef __LOG_OPENGL
#define __LOG_OPENGL
#include <sstream>
#include "../../../../../utilidades/log/log.h"
#include <imgui.h>

	class LogOpenGL : public utiles::Log {
		void init() {};
		void destroy() {};
	public:
		LogOpenGL(bool selected):utiles::Log(selected) {
		};
		void escribirVirtual(std::string& s, utiles::Log::NIVEL nivel = utiles::Log::NIVEL::INF);
		void clear() {
			buffer.clear();
			indicesLinea.clear();
			lineas.clear();
		}
		ImGuiTextBuffer getBuffer() { return buffer; }
		std::vector<std::tuple<const char*, ImVec4, int, const char*, const char *>> getLines() { return lineas; }
		bool hasNewLog() { return conScroll; }
		void setNewLog(bool hasNewLog) { conScroll = hasNewLog; }
	private:
		ImGuiTextBuffer buffer;
		std::vector<std::tuple<const char*, ImVec4,int, const char*, const char*>> lineas;
		ImGuiTextFilter filtro;
		ImVector<int> indicesLinea;
		bool conScroll=false;
	};


#endif // !__LOG_OPENGL