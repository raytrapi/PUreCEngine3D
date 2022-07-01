#ifndef __OPENGL_INTERFAZ
#define __OPENGL_INTERFAZ

#include <GLFW/glfw3.h>
#include <imgui.h>
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "log.h"

#include "../../../../../modules/graphic/interface.h"
#include "../../../../../modules/graphic/motor.h"
#include "../../../../../modules/resources/resource.h"
#include "../../../../../utilidades/global/screen.h"
#include "../../../../../utilidades/librerias/dll.h"
//#include "../../../../../utilidades/librerias/compile.h"
//#include "../../../../../utilidades/global/global.h"



class InterfaceGL: public modules::graphics::Interface {
	ImGuiIO* io=NULL;
	LogOpenGL* consoleLog = NULL;
	bool logDockeado = false;
	//MotorGl* motor = NULL;

	GLuint idTexturaIconos=0;
	float uBotonCompilacion = 0;
	float vBotonCompilacion = 0;
	
	
public:
	InterfaceGL() {
		//motor = (MotorGL*) CargaDLL::cogerModulo<modules::graphics::Graphic>(Module::GRAPHIC, "OPENGL 4");
	};
	void init(GLFWwindow * window, ImGuiConfigFlags options);
	void render();
	char* nombre() { return (char*)"INTERFACE OPENGL 4"; };
	LogOpenGL* getConsoleLog() { return consoleLog; };
	
};
#endif // !__OPENGL_INTERFAZ
