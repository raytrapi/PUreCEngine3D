#include "entity.h"
#include "rigidBodyComponent.h"
#include <imgui.h>


physics::RigidBodyComponent::RigidBodyComponent(Entity* entity, modules::graphics::Graphic* g, Component* p) {
	entidad = entity;
	graphic = g;
	//DBG("Creamos un cuerpo Rígido");
	if (graphic != NULL && fisicas==NULL) {
		fisicas = graphic->getPhysics();
	}

	if (fisicas != NULL) {
		//DBG("Tengo fisicas");
		
		fisicas->appendRigidBody(this);
	} else {
		//DBG("NOOOO Tengo físicas");
	}/**/
	setName("RigidBody");
}

bool physics::RigidBodyComponent::interfazImGUI_C(ImGuiContext* imgui) {
	ImGui::SetCurrentContext(imgui);
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text((const char*)u8"Gravedad?");
	ImGui::TableNextColumn();
	//estatico = gravedad;
	if (ImGui::Checkbox("##estatico", &this->gravedad)) {
		if (fisicas) {
			//TODO: Revisar esto para ver si siempre es necesario
			fisicas->appendRigidBody(this);
		}
	}
	/*if (gravedad != estatico) {
		gravedad = estatico;
		
	}/**/
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text((const char*)u8"Modo");
	ImGui::TableNextColumn();
	modoEstatico = modo;
	const char* items[] = { (char*)u8"Estático", (char*)u8"Dinámido", "Kinematic" };
	struct Funcs {  };
	ImGui::Combo("##tipo", &modoEstatico, &itemGetterMode, items, IM_ARRAYSIZE(items));
	modo = (MODE) modoEstatico;
	return true;
}
void physics::RigidBodyComponent::transformChanged() {
	if (fisicas) {
		fisicas->transformChanged(this);
	}
}
std::string physics::RigidBodyComponent::serializar() {
	std::string objetoSerializado = "";
	
	std::string resultado = GenericFile::serializate("componente", "{\r\n" + GenericFile::serializate("tipo", TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RIGIDBODY) + objetoSerializado + "}\r\n", false, false);
	return resultado;

};
bool  physics::RigidBodyComponent::itemGetterMode(void* data, int n, const char** out_str) {
	*out_str = ((const char**)data)[n]; return true; 
}

int physics::RigidBodyComponent::saveState_interno(std::vector<unsigned char>* data, bool withID) {
	int longitud = Serializer::serialize(data, (int)TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_RIGIDBODY);
	//Guaramos si está activa la gravedad
	longitud = Serializer::serialize(data, gravedad, (int)modo);

	return longitud;
};
void physics::RigidBodyComponent::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
	Deserializer::deserialize(&gravedad);
	Deserializer::deserialize(&modo);
};

bool physics::RigidBodyComponent::estatico = true;
int physics::RigidBodyComponent::modoEstatico = physics::RigidBodyComponent::MODE::STATIC;