#include "component.h"

#include "../src/entity.h"
#include "../../../utilidades/project/genericFile.h"
#include "../modulos/renderables/renderableComponent.h"

Component::Component() { }
Component::~Component() {
	DBG("borro componente Generico");
	if (nombre != NULL) {
		delete[] nombre;
		nombre = NULL;
	}
}

void Component::setName(std::string name) {
	if (nombre != NULL) {
		delete[] nombre;
		nombre = NULL;
	}
	nombre = new char[name.length()+1];
	for (int i = 0; i < name.length(); i++) {
		nombre[i] = name[i];
	}
	nombre[name.length()] = '\0';
}
std::string Component::getName() {
	if(nombre!=NULL){
		return std::string(nombre);
	}
	return std::string("Componente ");
};
int Component::desserializar(std::string s, int pos, Entity* e) { 
	Component* c = NULL;
	TYPE_OBJECT_SERIALIZABLES t;
	while (pos < s.length()) {
		auto [posT, clave, valor] = GenericFile::unserializate(s, pos );
		pos = posT;
		if (clave == "tipo") {
			t = (TYPE_OBJECT_SERIALIZABLES)std::atoi(valor.c_str());
			switch (t) {
				case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RENDERABLE:
					{
						c = e->addComponent<RenderableComponent>();
						
					}
					break;
				default:
					ERR("No se reconoce el tipo de Componente [Tipo: %]", (int)t);
					return  s.length();
					break;
			}
		} else if (clave == "objeto") {
			auto [posTO, claveO, valorO] = GenericFile::unserializate(valor, 0);
			if (claveO == "tipo") {
				int t = std::atoi(valorO.c_str());

				switch ((renderable::Object::TYPE)t) {
					case renderable::Object::TYPE::CUBE:
						e->desserializarObjeto<renderable::Cube, RenderableComponent>(valor,posTO, (RenderableComponent*)c);
						break;
				}/**/
					//c->desserializar(valor, 0);
			}
			pos+=valor.length()+2;
		} else {
			pos = s.length();
		}
	}
	return pos;
};
bool Component::interfazImGUI(ImGuiContext* imgui, bool header, int iPos) {
	ImGui::SetCurrentContext(imgui);
	//TODO: ImGui::SetAllocatorFunctions

	
	//interfazActivo = isActive();
	bool open = true;
	if (header) {
		if (this) {
			bool esActivo = this->activo;
			ImGui::Checkbox((std::string("##activo") ).c_str(), &esActivo);//+ getName()
			this->activo = esActivo;
		}
		//setActive(interfazActivo);
		ImGui::SameLine();
		if(nombre==NULL){ 
			nombre = new char[11];
			std::strcpy(nombre, "Sin Nombre");
			nombre[10] = '\0';
		}
		open = ImGui::CollapsingHeader(nombre, ImGuiTreeNodeFlags_DefaultOpen);
		
	}
	if (open) {

		/*ImVec2 s = ImGui::CalcTextSize(componente->getName().c_str());
		ImDrawList* drawListR = ImGui::GetWindowDrawList();
		const ImVec2 posR = ImGui::GetCursorScreenPos();
		drawListR->AddRectFilled(posR, ImVec2(200, posR.y + s.y), IM_COL32(30, 30, 30, 255));
		ImGui::Text(componente->getName().c_str());*/
		//ImGui::BeginGroup();
		auto flagsTablas0 = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoSavedSettings;// | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders
			
		if (ImGui::BeginTable("Componente", 2, flagsTablas0, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing()))) {
			ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 70.0f);
			//ImGui::TableNextColumn();
			
			if (interfazImGUI_C(imgui)) {
				ImGui::EndTable();
			}
		}
		//mostrarComponente(componente);
		//ImGui::EndGroup();
		//char* borrar=new char[]
		ImGui::PushID(100 + iPos);
		bool pulsado = ImGui::Button("Borrar");
		ImGui::PopID();
		return pulsado;
			
		
	}
	
	return false;
	
}
bool Component::interfazActivo = true;