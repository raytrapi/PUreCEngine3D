
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




   void CenteredSeparator(float width) {
      ImGuiWindow* window = GetCurrentWindow();
      if (window->SkipItems)
         return;
      ImGuiContext& g = *GImGui;
      
      // Horizontal Separator
      float x1, x2;
      if (window->DC.CurrentColumns == NULL && (width == 0)) {
         x1 = window->DC.CursorPos.x;
         x2 = x1 + window->Size.x;
      } else {
         // Start at the cursor
         x1 = window->DC.CursorPos.x;
         if (width != 0) {
            x2 = x1 + width;
         } else {
            x2 = window->ClipRect.Max.x;
            // Pad right side of columns (except the last one)
				if (window->DC.CurrentColumns && (window->DC.CurrentColumns->Current < window->DC.CurrentColumns->Count - 1)) {
					x2 -= g.Style.ItemSpacing.x;
				}
         }
      }
      float y1 = window->DC.CursorPos.y + int(window->DC.CurrLineSize.y / 2.0f);
      float y2 = y1 + 1.0f;

      window->DC.CursorPos.x += width; //+ g.Style.ItemSpacing.x;

      if (!window->DC.IsSameLine)
         x1 += window->DC.CurrLineSize.x;

      const ImRect bb(ImVec2(x1, y1), ImVec2(x2, y2));
      ItemSize(ImVec2(0.0f, 0.0f)); // NB: we don't provide our width so that it doesn't get feed back into AutoFit, we don't provide height to not alter layout.
      if (!ItemAdd(bb, NULL))
      {
         return;
      }

      window->DrawList->AddLine(bb.Min, ImVec2(bb.Max.x, bb.Min.y), GetColorU32(ImGuiCol_Border));

      /* // Commented out because LogText is hard to reach outside imgui.cpp
      if (g.LogEnabled)
      LogText(IM_NEWLINE "--------------------------------");
      */
   }

   // Create a centered separator right after the current item.
   // Eg.: 
   // ImGui::PreSeparator(10);
   // ImGui::Text("Section VI");
   // ImGui::SameLineSeparator();
   void SameLineSeparator(float width = 0) {
      ImGui::SameLine();
      CenteredSeparator(width);
   }

   // Create a centered separator which can be immediately followed by a item
   void PreSeparator(float width) {
      ImGuiWindow* window = GetCurrentWindow();
      if (window->DC.CurrLineSize.y == 0)
         window->DC.CurrLineSize.y = ImGui::GetTextLineHeight();
      CenteredSeparator(width);
      ImGui::SameLine();
   }




   void DrawSplitter(int split_vertically, float thickness, float* size0, float* size1, float min_size0, float min_size1) {
      ImVec2 backup_pos = ImGui::GetCursorPos();
      if (split_vertically)
         ImGui::SetCursorPosY(backup_pos.y + *size0);
      else
         ImGui::SetCursorPosX(backup_pos.x + *size0);

      ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
      ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(0, 0, 0, 0));          // We don't draw while active/pressed because as we move the panes the splitter button will be 1 frame late
      ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.6f, 0.6f, 0.6f, 0.10f));
      ImGui::Button("##Splitter", ImVec2(!split_vertically ? thickness : -1.0f, split_vertically ? thickness : -1.0f));
      ImGui::PopStyleColor(3);

      ImGui::SetItemAllowOverlap(); // This is to allow having other buttons OVER our splitter. 

      if (ImGui::IsItemActive())
      {
         float mouse_delta = split_vertically ? ImGui::GetIO().MouseDelta.y : ImGui::GetIO().MouseDelta.x;

         // Minimum pane size
         if (mouse_delta < min_size0 - *size0)
            mouse_delta = min_size0 - *size0;
         if (mouse_delta > *size1 - min_size1)
            mouse_delta = *size1 - min_size1;

         // Apply resize
         *size0 += mouse_delta;
         *size1 -= mouse_delta;
      }
      ImGui::SetCursorPos(backup_pos);
   }
   void xpandSafeArea(float value, ImGuiAxis axis, ImGuiDir dir) {
      auto viewport = (ImGuiViewportP*) GetWindowViewport();//GetCurrentWindow();// GetWindowViewport();//(ImGui::GetMainViewport());
      if (dir == ImGuiDir_Down || dir == ImGuiDir_Right) {
         viewport->BuildWorkOffsetMin[axis] += value;
      } else {
         viewport->BuildWorkOffsetMax[axis] -= value;
      }
   }
   bool BeginMainMenuBar(const ImRect& rect)   {
		
		ImGuiContext& g = *GImGui;
		ImGuiViewportP* viewport = (ImGuiViewportP*)(void*)GetWindowViewport();
      viewport->BuildWorkOffsetMax.x += 50.f;
         //GetBuildWorkRect
		// For the main menu bar, which cannot be moved, we honor g.Style.DisplaySafeAreaPadding to ensure text can be visible on a TV set.
		// FIXME: This could be generalized as an opt-in way to clamp window->DC.CursorStartPos to avoid SafeArea?
		// FIXME: Consider removing support for safe area down the line... it's messy. Nowadays consoles have support for TV calibration in OS settings.
		g.NextWindowData.MenuBarOffsetMinVal = ImVec2(g.Style.DisplaySafeAreaPadding.x, ImMax(g.Style.DisplaySafeAreaPadding.y - g.Style.FramePadding.y, 0.0f));
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
		float height = GetFrameHeight();
		bool is_open = BeginViewportSideBar("##MainMenuBar3", viewport, ImGuiDir_Up, height, window_flags);
		g.NextWindowData.MenuBarOffsetMinVal = ImVec2(0.0f, 0.0f);

		if (is_open)
			BeginMenuBar("##MenuBar3",rect);
		else
			End();
		return is_open;

			
   }
   bool BeginMenuBar(const char* name, const ImRect &rect){
      ImGuiWindow* window = GetCurrentWindow();
      if (window->SkipItems)
         return false;
      //if (!(window->Flags & ImGuiWindowFlags_MenuBar))
      //   return false;

      IM_ASSERT(!window->DC.MenuBarAppending);
      BeginGroup(); // Backup position on layer 0 // FIXME: Misleading to use a group for that backup/restore
      PushID(name);

      // We don't clip with current window clipping rectangle as it is already set to the area below. However we clip with window full rect.
      // We remove 1 worth of rounding to Max.x to that text in long menus and small windows don't tend to display over the lower-right rounded area, which looks particularly glitchy.
      ImRect bar_rect = rect;
      bar_rect.Max.y += 20;
      ImRect clip_rect(IM_ROUND(bar_rect.Min.x + window->WindowBorderSize), IM_ROUND(bar_rect.Min.y + window->WindowBorderSize), IM_ROUND(ImMax(bar_rect.Min.x, bar_rect.Max.x - ImMax(window->WindowRounding, window->WindowBorderSize))), IM_ROUND(bar_rect.Max.y));
      clip_rect.ClipWith(window->OuterRectClipped);
      PushClipRect(clip_rect.Min, clip_rect.Max, false);

      // We overwrite CursorMaxPos because BeginGroup sets it to CursorPos (essentially the .EmitItem hack in EndMenuBar() would need something analogous here, maybe a BeginGroupEx() with flags).
      window->DC.CursorPos = window->DC.CursorMaxPos = ImVec2(bar_rect.Min.x + window->DC.MenuBarOffset.x, bar_rect.Min.y + window->DC.MenuBarOffset.y);
      window->DC.LayoutType = ImGuiLayoutType_Horizontal;
      window->DC.IsSameLine = false;
      window->DC.NavLayerCurrent = ImGuiNavLayer_Menu;
      window->DC.MenuBarAppending = true;
      AlignTextToFramePadding();
      return true;
   }
   void EndMenuBar2() {
      ImGuiWindow* window = GetCurrentWindow();
      if (window->SkipItems)
         return;
      ImGuiContext& g = *GImGui;

      // Nav: When a move request within one of our child menu failed, capture the request to navigate among our siblings.
      if (NavMoveRequestButNoResultYet() && (g.NavMoveDir == ImGuiDir_Left || g.NavMoveDir == ImGuiDir_Right) && (g.NavWindow->Flags & ImGuiWindowFlags_ChildMenu))
      {
         // Try to find out if the request is for one of our child menu
         ImGuiWindow* nav_earliest_child = g.NavWindow;
         while (nav_earliest_child->ParentWindow && (nav_earliest_child->ParentWindow->Flags & ImGuiWindowFlags_ChildMenu))
            nav_earliest_child = nav_earliest_child->ParentWindow;
         if (nav_earliest_child->ParentWindow == window && nav_earliest_child->DC.ParentLayoutType == ImGuiLayoutType_Horizontal && (g.NavMoveFlags & ImGuiNavMoveFlags_Forwarded) == 0)
         {
            // To do so we claim focus back, restore NavId and then process the movement request for yet another frame.
            // This involve a one-frame delay which isn't very problematic in this situation. We could remove it by scoring in advance for multiple window (probably not worth bothering)
            const ImGuiNavLayer layer = ImGuiNavLayer_Menu;
            IM_ASSERT(window->DC.NavLayersActiveMaskNext & (1 << layer)); // Sanity check (FIXME: Seems unnecessary)
            FocusWindow(window);
            SetNavID(window->NavLastIds[layer], layer, 0, window->NavRectRel[layer]);
            g.NavDisableHighlight = true; // Hide highlight for the current frame so we don't see the intermediary selection.
            g.NavDisableMouseHover = g.NavMousePosDirty = true;
            NavMoveRequestForward(g.NavMoveDir, g.NavMoveClipDir, g.NavMoveFlags, g.NavMoveScrollFlags); // Repeat
         }
      }

      IM_MSVC_WARNING_SUPPRESS(6011); // Static Analysis false positive "warning C6011: Dereferencing NULL pointer 'window'"
      //IM_ASSERT(window->Flags & ImGuiWindowFlags_MenuBar);
      //IM_ASSERT(window->DC.MenuBarAppending);
      PopClipRect();
      PopID();
      window->DC.MenuBarOffset.x = window->DC.CursorPos.x - window->Pos.x; // Save horizontal position so next append can reuse it. This is kinda equivalent to a per-layer CursorPos.
      g.GroupStack.back().EmitItem = false;
      EndGroup(); // Restore position on layer 0
      window->DC.LayoutType = ImGuiLayoutType_Vertical;
      window->DC.IsSameLine = false;
      window->DC.NavLayerCurrent = ImGuiNavLayer_Main;
      window->DC.MenuBarAppending = false;
      
   }
   /*void EndMenuBar_pos() {
      EndMenuBar();

      // When the user has left the menu layer (typically: closed menus through activation of an item), we restore focus to the previous window
      // FIXME: With this strategy we won't be able to restore a NULL focus.
      ImGuiContext& g = *GImGui;
      if (g.CurrentWindow == g.NavWindow && g.NavLayer == ImGuiNavLayer_Main && !g.NavAnyRequest)
         FocusTopMostWindowUnderOne(g.NavWindow, NULL);

      End();

   }/**/
   

   bool IconTreeNode(void* str_id, ImGuiTreeNodeFlags flags, const char* label, ImTextureID idImage, ImVec2 uv1, ImVec2 uv2) {
      ImGuiContext& g = *GImGui;
      ImGuiWindow* window = g.CurrentWindow;

      ImU32 id = window->GetID(str_id);
      ImVec2 pos = window->DC.CursorPos;
      ImRect bb(pos, ImVec2(pos.x + ImGui::GetContentRegionAvail().x, pos.y + g.FontSize + g.Style.FramePadding.y * 2));
      bool opened = ImGui::TreeNodeBehaviorIsOpen(id);
      bool hovered, held;
      if (ImGui::ButtonBehavior(bb, id, &hovered, &held, true))
         window->DC.StateStorage->SetInt(id, opened ? 0 : 1);
      if (hovered || held) {
         //window->DrawList->AddRectFilled(bb.Min, bb.Max, window->Color(held ? ImGuiCol_HeaderActive : ImGuiCol_HeaderHovered));
         window->DrawList->AddRectFilled(bb.Min, bb.Max, ImGui::GetColorU32(held ? ImGuiCol_HeaderActive : ImGuiCol_HeaderHovered));
      }

      // Icon, text
      //label_end = FindRenderedTextEnd(label);
      const ImVec2 label_size = CalcTextSize(label);
      const ImGuiStyle& style = g.Style;
      const ImU32 text_col = GetColorU32(ImGuiCol_Text);
      const bool is_leaf = (flags & ImGuiTreeNodeFlags_Leaf) != 0;
      const bool display_frame = (flags & ImGuiTreeNodeFlags_Framed) != 0;
      const ImVec2 padding = (display_frame || (flags & ImGuiTreeNodeFlags_FramePadding)) ? style.FramePadding : ImVec2(style.FramePadding.x, ImMin(window->DC.CurrLineTextBaseOffset, style.FramePadding.y));
      const float text_offset_x = g.FontSize + (display_frame ? padding.x * 3 : padding.x * 2);           // Collapser arrow width + Spacing
      const float text_offset_y = ImMax(padding.y, window->DC.CurrLineTextBaseOffset);                    // Latch before ItemSize changes it
      const float text_width = g.FontSize + (label_size.x > 0.0f ? label_size.x + padding.x * 2 : 0.0f);  // Include collapser
      ImVec2 text_pos(window->DC.CursorPos.x + text_offset_x, window->DC.CursorPos.y + text_offset_y);
      float button_sz = g.FontSize + g.Style.FramePadding.y * 2; 
      if (flags & ImGuiTreeNodeFlags_Bullet) {
         RenderBullet(window->DrawList, ImVec2(text_pos.x - text_offset_x * 0.60f, text_pos.y + g.FontSize * 0.5f), text_col);
         pos.x += button_sz + g.Style.ItemInnerSpacing.x;
      } else if (!is_leaf) {
         RenderArrow(window->DrawList, ImVec2(text_pos.x - text_offset_x + padding.x, text_pos.y), text_col, opened ? ImGuiDir_Down : ImGuiDir_Right, 1.0f);
         pos.x += button_sz + g.Style.ItemInnerSpacing.x;
      } else {
         // Leaf without bullet, left-adjusted text
         text_pos.x -= text_offset_x;
      }
      
      //window->DrawList->AddRectFilled(pos, ImVec2(pos.x + button_sz, pos.y + button_sz), opened ? ImColor(255, 0, 0) : ImColor(0, 255, 0));
      window->DrawList->AddImage(idImage, pos, ImVec2(pos.x + button_sz, pos.y + button_sz), uv1, uv2);
      ImGui::RenderText(ImVec2(pos.x + button_sz + g.Style.ItemInnerSpacing.x, pos.y + g.Style.FramePadding.y), label);

      ImGui::ItemSize(bb, g.Style.FramePadding.y);
      ImGui::ItemAdd(bb, id);

      if (opened)
         ImGui::TreePush(label);
      return opened;
   }
}