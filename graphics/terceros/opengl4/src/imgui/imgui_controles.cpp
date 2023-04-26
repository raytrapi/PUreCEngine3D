
#include <imgui.h>
#include <imgui_internal.h>

#include "imgui_controles.h"

namespace ImGui {
	static void PushMultiItemsWidthsAndLabels(const char* labels[], int components, float w_full) {
		ImGuiWindow* window = GetCurrentWindow();
		const ImGuiStyle& style = GImGui->Style;
		if (w_full <= 0.0f)
			w_full = ImGui::GetContentRegionAvail().x;// GetContentRegionAvailWidth();

		const float w_item_one =
			ImMax(1.0f, (w_full - (style.ItemInnerSpacing.x * 2.0f) * (components - 1)) / (float)components) -
			style.ItemInnerSpacing.x;
		for (int i = 0; i < components; i++)
			window->DC.ItemWidthStack.push_back(w_item_one - CalcTextSize(labels[i]).x);
		window->DC.ItemWidth = window->DC.ItemWidthStack.back();
	}

	bool DragFloatNEx(const char* labels[], float* v, int components, float v_speed, float v_min, float v_max, const char* display_format, float power) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		bool value_changed = false;
		BeginGroup();

		PushMultiItemsWidthsAndLabels(labels, components, 0.0f);
		for (int i = 0; i < components; i++)
		{
			PushID(labels[i]);
			PushID(i);
			TextUnformatted(labels[i], FindRenderedTextEnd(labels[i]));
			SameLine();
			value_changed |= DragFloat("", &v[i], v_speed, v_min, v_max, display_format, power);
			SameLine(0, g.Style.ItemInnerSpacing.x);
			PopID();
			PopID();
			PopItemWidth();
		}

		EndGroup();

		return value_changed;
	}

	bool DragFloatN_Colored(const char* label, float* v, int components, float v_speed, float v_min, float v_max, const char* display_format, float power) {
		ImGuiWindow* window = GetCurrentWindow();
		if (window->SkipItems)
			return false;

		ImGuiContext& g = *GImGui;
		bool value_changed = false;
		BeginGroup();
		PushID(label);
		PushMultiItemsWidths(components, ImGui::GetContentRegionAvail().x);
		for (int i = 0; i < components; i++)
		{
			static const ImU32 colors[] = {
				 0xBB0000FF, // red
				 0xBB00FF00, // green
				 0xBBFF0000, // blue
				 0xBBFFFFFF, // white for alpha?
			};

			PushID(i);
			value_changed |= DragFloat("##v", &v[i], v_speed, v_min, v_max, display_format, power);

			const ImVec2 min = GetItemRectMin();
			const ImVec2 max = GetItemRectMax();
			const float spacing = g.Style.FrameRounding;
			const float halfSpacing = spacing / 2;

			// This is the main change
			window->DrawList->AddLine({ min.x + spacing, max.y - halfSpacing }, { max.x - spacing, max.y - halfSpacing }, colors[i], 4);

			SameLine(0, g.Style.ItemInnerSpacing.x);
			PopID();
			PopItemWidth();
		}
		PopID();

		TextUnformatted(label, FindRenderedTextEnd(label));
		EndGroup();

		return value_changed;
	}
}