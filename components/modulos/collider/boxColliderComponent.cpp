#include "boxColliderComponent.h"
#include "../../graphics/terceros/opengl4/src/imgui/imgui_controles.h"
//namespace collider {
	
std::string BoxColliderComponent::serializar(){
	std::string objetoSerializado = "";

	std::string resultado = GenericFile::serializate("componente", "{\r\n" + GenericFile::serializate("tipo", TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_BOXCOLLIDER) + objetoSerializado + "}\r\n", false, false);
	return resultado;
}

bool BoxColliderComponent::interfazImGUI_C(ImGuiContext* imgui){
	bool sinJugar= graphic->getGlobal()->executing != StateExecuting::PLAY;
	ImGui::SetCurrentContext(imgui);
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text((const char*)u8"Posición");
	ImGui::TableNextColumn();
	float pos[]{ cX, cY, cZ };
	ImGui::DragFloatN_Colored("##posicionColllision", pos, 3, 0.005f);
	if (pos[0] != cZ || pos[1] != cY || pos[2] != cZ) {
		setPosition(pos[0],pos[1],pos[2], sinJugar);
	}
	ImGui::TableNextRow();
	ImGui::TableNextColumn();
	ImGui::Text((const char*)u8"Dimensión");
	ImGui::TableNextColumn();
	float size[]{ w, h, d };
	ImGui::DragFloatN_Colored("##dimensionColllision", size, 3, 0.005f);
	if (size[0] != w || size[1] != h || size[2] != d) {
		setSize(size[0], size[1], size[2], sinJugar);
	}
	return true;
}

BoxColliderComponent::BoxColliderComponent(Entity* entity, modules::graphics::Graphic* g, Component * p):Collider(entity,g,BOX,p) {
	std::tie(w, h, d) = entity->transformada->getScale();
	iniciarFisicas();
}
	
BoxColliderComponent::~BoxColliderComponent() {
}

void BoxColliderComponent::setSize(float width, float height, float deph, bool withChangePhisics)	{
	w = width;
	h = height;
	d = deph;
	if (withChangePhisics) {
		changePhysics();
	}
}

bool BoxColliderComponent::haveCollision(Collider* object){
	return false;
}

void BoxColliderComponent::refresh(){
}

std::vector<collider::Hit> BoxColliderComponent::getCollisions(){
	return std::vector<collider::Hit>();
}

std::vector<collider::Hit> BoxColliderComponent::getCollisionsExpanding(float x, float y, float z){
	return std::vector<collider::Hit>();
}

std::vector<collider::Hit> BoxColliderComponent::getCollisions(float x, float y, float z){
	return std::vector<collider::Hit>();
}


int BoxColliderComponent::saveState_interno(std::vector<unsigned char>* data, bool withID) {
	int longitud = Serializer::serialize(data, (int)TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_BOXCOLLIDER);
	return longitud;
};
void BoxColliderComponent::restoreState_interno(std::vector<unsigned char>* data, bool withID, int pos) {
};