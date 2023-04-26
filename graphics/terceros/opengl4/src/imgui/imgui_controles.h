
#pragma once


namespace ImGui {
	static void PushMultiItemsWidthsAndLabels(const char* labels[], int components, float w_full);
	bool DragFloatNEx(const char* labels[], float* v, int components, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 0);
	bool DragFloatN_Colored(const char* label, float* v, int components, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 0);
};