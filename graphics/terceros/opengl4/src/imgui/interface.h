#ifndef __OPENGL_INTERFAZ
#define __OPENGL_INTERFAZ

#include <type_traits>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include <filesystem>
//#include "imgui_stdlib.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_glfw.h"
#include "imgui_controles.h"
#include "log.h"
#include <component.h>
#include <wchar.h>

#include "../../../../../modules/graphic/interface.h"
#include "../../../../../modules/graphic/motor.h"
#include "../../../../../modules/resources/resource.h"
#include "../../../../../utilidades/global/screen.h"
#include "../../../../../utilidades/librerias/dll.h"
//#include "../../../../../utilidades/librerias/compile.h"
//#include "../../../../../utilidades/global/global.h"
#ifdef WIN32
	#include <Windows.h>
	#include <Shlobj.h>
	#include <Shlobj_core.h>
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include<GLFW/glfw3native.h>
#endif // WIN32



class InterfaceGL: public modules::graphics::Interface {
	enum Acciones {
		A_NINGUNA,
		A_NUEVO_PROYECTO,
		A_ABRIR_PROYECTO
	};
	ImGuiIO* io=NULL;
	LogOpenGL* consoleLog = NULL;
	bool logDockeado = false;
	GLFWwindow* window=NULL;
	float altoCabecera = 25.0f;
	ImVec2 posicionVentana=ImVec2(0,0);

	//MotorGl* motor = NULL;

	GLuint idTexturaIconos=0;

	float uBotonCompilacion = 0;
	float vBotonCompilacion = 0;
	
	
	/* Funcionamiento del interfaz*/
	Entity* entidadSeleccionada = NULL;
	void herramientasSuperior();
	void mostrarEntidades();
	void mostrarEntidad();
	void mostrarComponentes();
	void mostrarComponente(Component *c);
	void mostrarView();

	int node_clicked = -1;
	int anchoPanelIzquierdo = 200;
	int anchoPanelDerecho = 600;
	ImVec2 ventanaJuego;

	//Parámetros de interfaz
	Acciones accion = A_NINGUNA;
	void newProjectModal();
	void openProject();
	static char nombreNuevoProyecto[256];//Almacenará el nombre del nuevo proyecto
	static ImGuiTableFlags flagsTablas0;
	bool cambioEntidad = false;
public:
	InterfaceGL() {
		//motor = (MotorGL*) CargaDLL::cogerModulo<modules::graphics::Graphic>(Module::GRAPHIC, "OPENGL 4");
		
	};
	~InterfaceGL() {
		deleteParametros();
		deleteParametrosGlobales();
	}
	void init(GLFWwindow * window, ImGuiConfigFlags options);
	void render();
	char* nombre() { return (char*)"INTERFACE OPENGL 4"; };
	LogOpenGL* getConsoleLog() { return consoleLog; };


	/**Estas son variables utilizadas por el interfaz**/

	void deleteParametros();
	void deleteParametrosGlobales();
	static std::vector<float*> tripletasF;

	static std::vector<float*> globalF;
	static std::vector<float*> globalTripletasF;
	
};
#endif // !__OPENGL_INTERFAZ
