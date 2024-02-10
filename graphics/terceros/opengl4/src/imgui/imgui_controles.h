
#pragma once
#include <imgui_internal.h>

namespace ImGui {
	static void PushMultiItemsWidthsAndLabels(const char* labels[], int components, float w_full);
	bool DragFloatNEx(const char* labels[], float* v, int components, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 0);
	bool DragFloatN_Colored(const char* label, float* v, int components, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 0);
	void CenteredSeparator(float width = 0);
	void xpandSafeArea(float value, ImGuiAxis axis, ImGuiDir dir);

	bool BeginMainMenuBar(const ImRect& rect);
	bool BeginMenuBar(const char* name, const ImRect& rect);
	void EndMenuBar2();
	bool IconTreeNode(void* str_id, ImGuiTreeNodeFlags flags, const char* label, ImTextureID idImage, ImVec2 uv1, ImVec2 uv2);
	//void EndMenuBar_pos();
};