#include "levelModal.h"


void Modal::Level::create() {
	if (ImGui::BeginPopupModal("Stacked 1", NULL, ImGuiWindowFlags_MenuBar)) {

		if (ImGui::Button("Close")) {
			ImGui::CloseCurrentPopup();
		}
	}
}