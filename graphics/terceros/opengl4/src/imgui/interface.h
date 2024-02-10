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
#include <ImGuizmo.h>
#include "log.h"
#include <component.h>
#include <wchar.h>


#include "../../../../../modules/graphic/interface.h"
#include "../../../../../modules/graphic/motor.h"
#include "../../../../../modules/resources/resource.h"
#include "../../../../../utilidades/global/screen.h"
#include "../../../../../utilidades/librerias/dll.h"
#include "../../../../../components/src/transform.h"

#include "modals/levelModal.h"
#include "components/fileNavigator.h"
#include "modals/modal.h"

#include "../interface/node_editors/nodeGraphic.h"



//#include "../../../../../utilidades/librerias/compile.h"
//#include "../../../../../utilidades/global/global.h"
#ifdef WIN32
	#include <Windows.h>
	#include <Shlobj.h>
	#include <Shlobj_core.h>
	#define GLFW_EXPOSE_NATIVE_WIN32
	#include<GLFW/glfw3native.h>
#endif // WIN32

namespace renderable {
	extern class Object;
}

class InterfaceGL: public modules::graphics::Interface {
	enum Acciones {
		A_NINGUNA,
		A_NUEVO_PROYECTO,
		A_ABRIR_PROYECTO,
		A_NUEVO_NIVEL,
		A_GUARDAR_NIVEL,
		A_ABRIR_MATERIALES
	};
	ImGuiIO* io=NULL;
	LogOpenGL* consoleLog = NULL;
	bool logDockeado = false;
	GLFWwindow* window=NULL;
	float altoCabecera = 25.0f;
	ImVec2 posicionVentana=ImVec2(0,0);

	//MotorGl* motor = NULL;
	friend class UI::Components::FileNavigator;
	friend class renderable::Object;
	friend class UI::Components::FileNavigator;
	friend class renderable::Object;
	

	//friend class UI::Components::FileNavigator;
	static LevelFile* level;

	//Entity* entidadSeleccionada = NULL;
	std::vector<std::tuple<Entity*,int>> entidadesSeleccionadas;
	Transform* transformGizmo=NULL;
	bool gizmoSinPulsar = true;
	float* posicionGizmo = 0;
	ImVec2 posGizmo = { 0.f, 0.f };
	ImGuizmo::OPERATION operation = ImGuizmo::TRANSLATE;
	ImGuizmo::MODE mode = ImGuizmo::WORLD;

	//ImVec2 tamanioVentanaRender;

	/* Funcionamiento del interfaz*/
	bool panelEditorActivo = false;
	bool panelEntidadesActivo = false;
	//int handleCierreEntidadSeleccionada = -1;
	int windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;

	void menuSuperior(float w, float h, float x, float y);
	void barraEstadoInferior(float w, float h, float x, float y);
	void herramientasSuperior(float altura=24);
	void mostrarEntidades(Entity * padre=0);
	void mostrarEntidad();
	void mostrarVentanaMundo();
	void mostrarComponentes();
	void mostrarComponente(Component *c);
	bool mostrarView();
	void mostrarGuizmo();
	Entity* objetoEncima = 0;


	bool mostrarVentanaMaterial = false;
	
	ui::Modal *modalMaterial=0;
	void ventanaMaterial();

	void desmarcarEntidadesSeleccionadas();
	void seleccionaEntidad(Entity* entidad,  bool mantener=false);

	int anchoPanelIzquierdo = 200;
	int anchoPanelDerecho = 600;

	ImGuiMouseCursor idCursor = ImGuiMouseCursor_None;
	ImVec2 ventanaJuego;

	//Parámetros de interfaz
	Acciones accion = A_NINGUNA;
	void newProjectModal();
	void openProject();
	static char nombreNuevoProyecto[256];//Almacenará el nombre del nuevo proyecto
	static ImGuiTableFlags flagsTablas0;
	bool cambioEntidad = false;
	friend class ui::Modal;
	static std::vector<ImFont*> fonts;

	

	//Movimiento Raton
	ImVec2 posicionRaton;
	bool comienzaMovimientoCamara = true;
	bool conRotacionCamara=false;
	bool conMovimientoCamara = false;
	float xRatonMovimiento = 0;
	float yRatonMovimiento = 0;
	float xRatonMovimientoAnterior = 0;
	float yRatonMovimientoAnterior = 0;
	float velocidadZ = 1.2f;
	float velocidadZWhell = 0.2f;
	float velocidadRotacion = 0.01f;
	void moverCamara(float delta, int modo);
	void controlAccionesGlobales();

	void saveLevel();
public:
	InterfaceGL() {
	}
	~InterfaceGL() {
		deleteParametros();
		deleteParametrosGlobales();
		/*if (m_ContextNode) {
			ax::NodeEditor::DestroyEditor(m_ContextNode);
		}/**/
		if (modalMaterial) {
			delete modalMaterial;
		}/**/
		for (auto f : fonts) {
			delete f;
		}
	}
	void init(GLFWwindow * window, ImGuiConfigFlags options);
	void render();
	char* nombre() { return (char*)"INTERFACE OPENGL 4"; };
	LogOpenGL* getConsoleLog() { return consoleLog; };


	/**Estas son variables utilizadas por el interfaz**/
	
	void deleteParametros();
	void deleteParametrosGlobales();
	static std::vector<float*> tripletasF;
	static std::vector<char*> cadenas;
	static std::vector<bool*> booleanos;

	static std::vector<float*> globalF;
	static std::vector<float*> globalTripletasF;
	
	void quitarEntidad(Entity* e);

	
};
#endif // !__OPENGL_INTERFAZ
