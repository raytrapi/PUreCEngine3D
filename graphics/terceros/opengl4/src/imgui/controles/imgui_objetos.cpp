#include "imgui_objetos.h"
/*#include "../../../../../../utilidades/files/filesControl.h"
UID ImGui::selectionObject(const char * typeDrop, ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0, const ImVec2& uv1, const ImVec4& tint_col, const ImVec4& border_col){
	UID uid= 0;
	ImGui::Image(user_texture_id, size, uv0, uv1);
	if (typeDrop) {
		if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::BeginDragDropTarget()) {
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload(typeDrop)) {
				if (payload->DataSize == sizeof(DragFile)) {
					uid=(*((DragFile*)payload->Data)).UID;
				}
			}

			ImGui::EndDragDropTarget();
		}
	}
	return uid;
}/**/