#ifndef __MODAL
#define __MODAL
#include <imgui.h>
#include <string>
#include <vector>
#include "../utiles/pointers.h"
#include "../imgui_controles.h"
#include "../interface/src/interfaceControl.h"
namespace ui {
	class Modal {
		ImVec2 *sizeCierre=0;
		//std:string nombre;
		char* nombre = 0;
		char* nombreMenu = 0;
		char* nombreCierre = 0;
		bool abierto = true;
		std::vector<std::tuple<InterfaceControl*,ImVec2,ImVec2>> controles;
	public:
		Modal(const char* name);
		~Modal();

		void addControl(InterfaceControl* control, ImVec2 pos, ImVec2 size);
		bool show();
	};
}
#endif // !__MODAL
