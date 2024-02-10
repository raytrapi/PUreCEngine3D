#include "mapsGenerator.h"
#include "../../../utilidades/global/constantes.h"
#include "../../modulos/renderables/objects/mesh.h"
#include "../../src/entity.h"
#include "../../../utilidades/math/math.h"



void MapsGeneratorComponent::generarMapa(){
	if (mapa==0) {
		//mapa->setLifeTime(1.0f);
		//graphic->removeEntity(mapa);
		mapa = Entity::create<Entity::TYPE::MESH>();
		mapa->setName("Mapa generado");
		mapa->setParent(this->getEntity());
	}


	if (mapaAlturas) {
		delete[] mapaAlturas;
	}
	if (mapaColores) {
		delete[] mapaColores;
	}
	DBG("Generando Mapa");
	if (modo1) {
		mapaAlturas = Math::perlin2D(posX, posY, ancho, alto, 8, semilla, 256.0f);
		DBG("Mapa Generado");
	} else {
		mapaAlturas = Math::perlin2D(posX, posY, ancho, alto, semilla,wG,hG,densidad,4,0.5f,2.f);
		DBG("Mapa Generado");
	}
	/*for (int i = 0; i < rectangulos; i++) {
		if (map[i] < 0) {
			map[i] = 0;
		} else if (map[i] > 1.0f) {
			map[i] = 1.0f;
		}
	}/**/
	mapaColores = generarMapaColor(mapaAlturas);
	graphic->addTexture(mapaColores, ancho * alto * 4, ancho, alto, idTextura, TextureImg::RGBA,modules::graphics::Graphic::REPEAT, modules::graphics::Graphic::NEAREST);
	
	generarMalla();



}

float* MapsGeneratorComponent::generarMapaColor(float * map){
	int size = ancho * alto;
	float* img = new float[size * 4];
	std::vector<std::tuple<float, float, float, float, float>>coloresLimite;
	coloresLimite.push_back({ 1.0f, 1.0f,1.0f,1.0f,1.0f });
	coloresLimite.push_back({ 0.9f, 0.5f,0.45f,0.0f,1.0f });
	coloresLimite.push_back({ 0.7f, 0.6f,0.55f,0.0f,1.0f });
	coloresLimite.push_back({ 0.6f, 0.0f,0.8f,0.0f,1.0f });
	coloresLimite.push_back({ 0.55f, 0.0f,1.0f,0.0f,1.0f });
	coloresLimite.push_back({ 0.45f, 0.902f,0.784f,0.098f,1.0f });
	coloresLimite.push_back({ 0.40f, 0.0f,.0f,1.0f,1.0f });
	coloresLimite.push_back({ 0.30f, 0.0f,0.0f,0.8f,1.0f });
	std::srand(semilla >= 0 ? semilla : std::time(nullptr));
	
	float* valores = map;
	//delete[]valores2;

	int i = 0;
	int j = 0;
	for (int y = 0; y < alto; y++) {
		for (int x = 0; x < ancho; x++) {
			float valor = valores[j];


			std::tuple<float, float, float, float> colorBase = { valor,valor,valor,1.0f };
			if (coloresLimite.size() > 0) {
				colorBase = { std::get<1>(coloresLimite[0]),std::get<2>(coloresLimite[0]) ,std::get<3>(coloresLimite[0]) ,std::get<4>(coloresLimite[0]) };
				for (auto color : coloresLimite) {
					if (std::get<0>(color) < valor) {
						break;
					}
					colorBase = { std::get<1>(color),std::get<2>(color) ,std::get<3>(color) ,std::get<4>(color) };
				}
			}

			img[i++] = std::get<0>(colorBase);
			img[i++] = std::get<1>(colorBase);
			img[i++] = std::get<2>(colorBase);
			img[i++] = std::get<3>(colorBase);
			j++;
			//i++;
		}
	}
	
	return img;
}

void MapsGeneratorComponent::generarMalla(){
	int rectangulos = ancho * alto;
	if (mapa == 0 || mapaAlturas == 0 || mapaColores == 0) {
		return;
	}
	auto renderable = mapa->getComponent<RenderableComponent>();

	//Vamos a hacer una pirámide para probar;
	/* {
		int triangulos = 4;
		float* vertices = new float[triangulos * 3 * 3];
		float* uv = new float[triangulos * 3 * 2];
		float* normales = new float[triangulos * 3 * 3];
		float incX = 2.f / ancho;
		float incZ = 2.f / alto;
		float incU = 1.f / ancho;
		float incV = 1.f / alto;
		float posZ = 1.f;
		float posV = 0;
		int posVertice = 0;
		int posUvs = 0;
		int posNormales = 0;
		//int z = 0;
		int incXMap = 1;
		int incZMap = 1;
		float pX1 = 0.f;
		float pY1 = altura;
		float pZ1 = 0.f;
		float pX2 = -1.f;
		float pY2 = 0.f;
		float pZ2 = 1.f;
		float pX3 = -1.f;
		float pY3 = 0.f;
		float pZ3 = -1.f;
		vertices[posVertice++] = pX1; vertices[posVertice++] = pY1; vertices[posVertice++] = pZ1;
		vertices[posVertice++] = pX2; vertices[posVertice++] = pY2; vertices[posVertice++] = pZ2;
		vertices[posVertice++] = pX3; vertices[posVertice++] = pY3; vertices[posVertice++] = pZ3;
		std::tie(normales[posNormales], normales[posNormales + 1], normales[posNormales + 2]) = Transform::crossProduct(pX3 - pX1, pY3 - pY1, pZ3 - pZ1, pX2 - pX1, pY2 - pY1, pZ2 - pZ1, true);
		posNormales += 3;
		normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2]= normales[posNormales - 1];
		posNormales += 3;
		normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
		posNormales += 3;

		pX1 = 0.f;
		pY1 = altura;
		pZ1 = 0.f;
		pX2 = -1.f;
		pY2 = 0.f;
		pZ2 = -1.f;
		pX3 = 1.f;
		pY3 = 0.f;
		pZ3 = -1.f;
		vertices[posVertice++] = pX1; vertices[posVertice++] = pY1; vertices[posVertice++] = pZ1;
		vertices[posVertice++] = pX2; vertices[posVertice++] = pY2; vertices[posVertice++] = pZ2;
		vertices[posVertice++] = pX3; vertices[posVertice++] = pY3; vertices[posVertice++] = pZ3;
		std::tie(normales[posNormales], normales[posNormales + 1], normales[posNormales + 2]) = Transform::crossProduct(pX3 - pX1, pY3 - pY1, pZ3 - pZ1, pX2 - pX1, pY2 - pY1, pZ2 - pZ1, true);
		posNormales += 3;
		normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
		posNormales += 3;
		normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
		posNormales += 3;

		pX1 = 0.f;
		pY1 = altura;
		pZ1 = 0.f;
		pX2 = 1.f;
		pY2 = 0.f;
		pZ2 = -1.f;
		pX3 = 1.f;
		pY3 = 0.f;
		pZ3 = 1.f;
		vertices[posVertice++] = pX1; vertices[posVertice++] = pY1; vertices[posVertice++] = pZ1;
		vertices[posVertice++] = pX2; vertices[posVertice++] = pY2; vertices[posVertice++] = pZ2;
		vertices[posVertice++] = pX3; vertices[posVertice++] = pY3; vertices[posVertice++] = pZ3;
		std::tie(normales[posNormales], normales[posNormales + 1], normales[posNormales + 2]) = Transform::crossProduct(pX3 - pX1, pY3 - pY1, pZ3 - pZ1, pX2 - pX1, pY2 - pY1, pZ2 - pZ1, true); posNormales += 3;
		normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
		posNormales += 3;
		normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
		posNormales += 3;

		pX1 = 0.f;
		pY1 = altura;
		pZ1 = 0.f;
		pX2 = 1.f;
		pY2 = 0.f;
		pZ2 = 1.f;
		pX3 = -1.f;
		pY3 = 0.f;
		pZ3 = 1.f;
		vertices[posVertice++] = pX1; vertices[posVertice++] = pY1; vertices[posVertice++] = pZ1;
		vertices[posVertice++] = pX2; vertices[posVertice++] = pY2; vertices[posVertice++] = pZ2;
		vertices[posVertice++] = pX3; vertices[posVertice++] = pY3; vertices[posVertice++] = pZ3;
		std::tie(normales[posNormales], normales[posNormales + 1], normales[posNormales + 2]) = Transform::crossProduct(pX3 - pX1, pY3 - pY1, pZ3 - pZ1, pX2 - pX1, pY2 - pY1, pZ2 - pZ1, true);
		posNormales += 3;
		normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
		posNormales += 3;
		normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
		posNormales += 3;

		
	
		Material* m = new Material();
		m->setTexture(idTextura);
		renderable::Mesh* malla = renderable->getRenderable<renderable::Mesh>();
		malla->setMaterial(m,0);
		malla->setTriangles(triangulos, vertices, 0, calculeNormales ? normales : 0, 0, renderable::Object::COLOR);
	}
	return;/**/
	int triangulos = rectangulos*2;
	float* vertices = new float[triangulos * 3*3];
	float* uv = new float[triangulos * 3 * 2];
	float* normales = new float[triangulos * 3 * 3];
	float incX = 2.f / ancho;
	float incZ = 2.f / alto;
	float incU = 1.f / ancho;
	float incV = 1.f / alto;
	float posZ = 1.f;
	float posV = 0;
	int posVertice = 0;
	int posUvs = 0;
	int posNormales = 0;
	//int z = 0;
	int incXMap = 1;
	int incZMap = 1;

	for (int z = 0; z < alto-1; z++) {
		float posX = -1.f;
		float posU = 0;
		int iT = 0;
		for (int iT = 0; iT < ancho-1; iT++) {
			float pX1 = posX + incX;
			float pY1 = ImGui::CurveValueSmooth(mapaAlturas[(iT + incXMap) + (z)*ancho], numPuntosCurva, curva) * altura;
			float pZ1 = posZ;
			float pX2 = posX;
			float pY2 = ImGui::CurveValueSmooth(mapaAlturas[(iT)+(z)*ancho], numPuntosCurva, curva) * altura;
			float pZ2 = posZ;
			float pX3 = posX;
			float pY3 = ImGui::CurveValueSmooth(mapaAlturas[(iT)+(z + incZMap) * ancho], numPuntosCurva, curva) * altura;
			float pZ3 = posZ - incZ;
			vertices[posVertice++] = pX1; vertices[posVertice++] = pY1; vertices[posVertice++] = pZ1;
			vertices[posVertice++] = pX2; vertices[posVertice++] = pY2; vertices[posVertice++] = pZ2;
			vertices[posVertice++] = pX3; vertices[posVertice++] = pY3; vertices[posVertice++] = pZ3;
			uv[posUvs++] = posU + incU; uv[posUvs++] = posV;
			uv[posUvs++] = posU; uv[posUvs++] = posV;
			uv[posUvs++] = posU; uv[posUvs++] = posV+incV;
			std::tie(normales[posNormales], normales[posNormales + 1], normales[posNormales + 2]) = Transform::crossProduct(pX3 - pX1, pY3 - pY1, pZ3 - pZ1, pX2 - pX1, pY2 - pY1, pZ2 - pZ1, true);
			posNormales += 3;
			normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
			posNormales += 3;
			normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
			posNormales += 3;


			pX1 = posX + incX;
			pY1 = ImGui::CurveValueSmooth(mapaAlturas[(iT + incXMap) + (z)*ancho], numPuntosCurva, curva) * altura;
			pZ1 = posZ;
			pX2 = posX;
			pY2 = ImGui::CurveValueSmooth(mapaAlturas[(iT)+(z + incZMap) * ancho], numPuntosCurva, curva) * altura;
			pZ2 = posZ - incZ;
			pX3 = posX + incX;
			pY3 = ImGui::CurveValueSmooth(mapaAlturas[(iT + incXMap) + (z + incZMap) * ancho], numPuntosCurva, curva) * altura;
			pZ3 = posZ - incZ;

			vertices[posVertice++] = pX1; vertices[posVertice++] = pY1; vertices[posVertice++] = pZ1;
			vertices[posVertice++] = pX2; vertices[posVertice++] = pY2; vertices[posVertice++] = pZ2;
			vertices[posVertice++] = pX3; vertices[posVertice++] = pY3; vertices[posVertice++] = pZ3;
			uv[posUvs++] = posU + incU; uv[posUvs++] = posV;
			uv[posUvs++] = posU; uv[posUvs++] = posV+incV;
			uv[posUvs++] = posU+ incU; uv[posUvs++] = posV + incV;
			std::tie(normales[posNormales], normales[posNormales + 1], normales[posNormales + 2]) = Transform::crossProduct(pX3 - pX1, pY3 - pY1, pZ3 - pZ1, pX2 - pX1, pY2 - pY1, pZ2 - pZ1, true);
			posNormales += 3;
			normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
			posNormales += 3;
			normales[posNormales] = normales[posNormales - 3]; normales[posNormales + 1] = normales[posNormales - 2]; normales[posNormales + 2] = normales[posNormales - 1];
			posNormales += 3;

			posX += incX;
			posU += incU;
			//iT += incXMap;
		}
		posZ -= incZ;
		posV += incV;
		//posz += incZMap;
	}
	//delete[] map;

	/*float* textura = new float[ancho * alto * 4];
	int posC = 0;
	for (int y = 0; y < alto; y++) {
		for (int x = 0; x < ancho; x++) {
			if (y < alto / 2) {
				if (x < ancho / 2) {
					textura[posC++] = 1.0f; textura[posC++] = 0.0f; textura[posC++] = 0.0f; textura[posC++] = 1.0f;
				} else {
					textura[posC++] = 0.0f; textura[posC++] = 1.0f; textura[posC++] = 0.0f; textura[posC++] = 1.0f;
				}
			} else {
				if (x < ancho / 2) {
					textura[posC++] = 0.0f; textura[posC++] = 0.0f; textura[posC++] = 1.0f; textura[posC++] = 1.0f;
				} else {
					textura[posC++] = 1.0f; textura[posC++] = 1.0f; textura[posC++] = 1.0f; textura[posC++] = 1.0f;
				}
			}
		}
	}/**/
	
	
	Material* m = new Material();
	m->setTexture(idTextura);
	renderable::Mesh* malla = renderable->getRenderable<renderable::Mesh>();
	malla->setMaterial(m,0);
	malla->setTriangles(triangulos, vertices,0, calculeNormales?normales:0,uv,renderable::Object::TEXTURE);
	//delete[] textura;
	
	
}

bool MapsGeneratorComponent::interfazImGUI_C(ImGuiContext* imgui){

	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(U8(Tamaño));
		ImGui::TableNextColumn();
		int t[2]{ancho,alto};
		if (ImGui::DragInt2("##tam", t, 1.0F, 0, 1000.0F)) {
			ancho = t[0];
			alto = t[1];
			//generarMapa();
		}
	}
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(U8(Posicion));
		ImGui::TableNextColumn();
		int t[2]{ posX, posY };
		if (ImGui::DragInt2("##pos", t, 1.0F, 0, 1000.0F)) {
			posX = t[0];
			posY = t[1];
			generarMapa();
			//generarMalla();
		}
	}
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(U8(Datos));
		ImGui::TableNextColumn();
		bool cambio = false;
		cambio =cambio || ImGui::DragFloat("den", &densidad,0.01F,1.0f);
		cambio = cambio || ImGui::DragInt("w", &wG,1.0f,1);
		cambio = cambio || ImGui::DragInt("h", &hG, 1.0f, 1);
		if (cambio) {
			generarMapa();
		}
	}
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(U8(Semilla));
		ImGui::TableNextColumn();
		int s=semilla;
		if (ImGui::DragInt("##sem", &s, 1.0F, -1)) {
			semilla = s;
			//generarMapa();
		}
	}
	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(U8(Altura));
		ImGui::TableNextColumn();
		float a = altura;
		if (ImGui::DragFloat("##altura",&a,0.01F,0,10.0F)) {
			altura = a;
			generarMalla();
		}
	}

	{
		ImGui::TableNextRow();
		ImGui::TableNextColumn();
		ImGui::Text(U8(Suavizado));
		ImGui::TableNextColumn();
		//ImVec2 puntos[2];
		//puntos[0] = ImVec2(0.0f,0.0f);
		//puntos[1] = ImVec2(1.0f,1.0f);
		int pun  = ImGui::Curve("##curva", ImVec2(100, 100), numPuntosCurva, curva);
		if (pun !=0) {
			pun= pun; 
			generarMalla();
		}
	}

	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text(U8(Perlin));
	ImGui::TableNextColumn();
	
	bool modo = modo1;
	if (ImGui::Checkbox("Modo 1", &modo)) {
		modo1 = modo;
	}
	if (ImGui::Checkbox("Normales", &this->calculeNormales)) {
		generarMalla();
	}
	if (ImGui::Button("Generar mapa")) {
		generarMapa();
	}


	return true;
}

int MapsGeneratorComponent::saveState_interno(std::vector<unsigned char>* data, bool withID){
	return 0;
}

void MapsGeneratorComponent::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos){
}

MapsGeneratorComponent::~MapsGeneratorComponent(){
	if (mapaAlturas) {
		delete [] mapaAlturas;
	}
	if (mapaColores) {
		delete[] mapaColores;
	}
	if (curva) {
		delete[] curva;
	}
}

MapsGeneratorComponent::MapsGeneratorComponent(){
	curva = new ImVec2[100];
	for (int i = 0; i < 100; i++) {
		curva[i] = ImVec2(0.0f, 0.0f);
	}
	numPuntosCurva = 4;
	curva[0] = ImVec2(0.0f, 0.0f);
	curva[1] = ImVec2(0.45f, 0.0f);
	curva[2] = ImVec2(0.70f, 0.30f);
	curva[3] = ImVec2(1.0f, 1.0f);
}

