#pragma once
#include "../../src/component.h"
#include "../../modulos/renderables/renderableComponent.h"
#include "../../../graphics/terceros/opengl4/src/imgui/controles/imgui_curve.h"
class EXPORTAR_COMPONENTE MapsGeneratorComponent: public Component {
private:
	Entity* mapa = 0;
	void generarMapa();
	float* mapaAlturas = 0;
	float* mapaColores = 0;
	float* generarMapaColor(float* map);
	void generarMalla();
	
	int bloques = 9;

	int ancho = 100;
	int alto = 100;
	int posX = 0;
	int posY = 0;
	int wG = 100;
	int hG = 100;
	float densidad=16.f;
	int semilla = 1;
	float altura = 1.0f;
	bool modo1 = false;
	unsigned int idTextura=0;
	ImVec2* curva = 0;
	int numPuntosCurva = 2;
	bool calculeNormales = true;

protected:
	bool interfazImGUI_C(ImGuiContext* imgui);
	int saveState_interno(std::vector<unsigned char>* data, bool withID = false);
	void restoreState_interno(std::vector<unsigned char>* data = 0, bool withID = false, int pos = -1);
public:
	TYPE_OBJECT_SERIALIZABLES getType() { return SERIALIZABLE_COMPONENTE_DINAMIC; };
	~MapsGeneratorComponent();
	MapsGeneratorComponent();
};