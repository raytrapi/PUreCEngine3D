#pragma once
#include <imgui.h>
#include <imgui_internal.h>

typedef int ImGuiLayoutType;            // -> enum ImGuiLayoutType_         // Enum: Horizontal or vertical
typedef int ImGuiLayoutItemType;        // -> enum ImGuiLayoutItemType_    // Enum: Item or Spring

namespace ImGui{
	

    /*IMGUI_API void          BeginHorizontal(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    IMGUI_API void          BeginHorizontal(const void* ptr_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    IMGUI_API void          BeginHorizontal(int id, const ImVec2& size = ImVec2(0, 0), float align = -1);
    IMGUI_API void          EndHorizontal();
    IMGUI_API void          BeginVertical(const char* str_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    IMGUI_API void          BeginVertical(const void* ptr_id, const ImVec2& size = ImVec2(0, 0), float align = -1.0f);
    IMGUI_API void          BeginVertical(int id, const ImVec2& size = ImVec2(0, 0), float align = -1);
    IMGUI_API void          EndVertical();
    IMGUI_API void          Spring(float weight = 1.0f, float spacing = -1.0f);
    IMGUI_API void          SuspendLayout();
    IMGUI_API void          ResumeLayout();/**/



}

struct ImGuiLayoutItem
{
    ImGuiLayoutItemType     Type;               // Type of an item
    ImRect                  MeasuredBounds;

    float                   SpringWeight;       // Weight of a spring
    float                   SpringSpacing;      // Spring spacing
    float                   SpringSize;         // Calculated spring size

    float                   CurrentAlign;
    float                   CurrentAlignOffset;

    unsigned int            VertexIndexBegin;
    unsigned int            VertexIndexEnd;

    ImGuiLayoutItem(ImGuiLayoutItemType type)
    {
        Type = type;
        MeasuredBounds = ImRect(0, 0, 0, 0);    // FIXME: @thedmd are you sure the default ImRect value FLT_MAX,FLT_MAX,-FLT_MAX,-FLT_MAX aren't enough here?
        SpringWeight = 1.0f;
        SpringSpacing = -1.0f;
        SpringSize = 0.0f;
        CurrentAlign = 0.0f;
        CurrentAlignOffset = 0.0f;
        VertexIndexBegin = VertexIndexEnd = (ImDrawIdx)0;
    }
};

struct ImGuiLayout
{
    ImGuiID                     Id;
    ImGuiLayoutType             Type;
    bool                        Live;
    ImVec2                      Size;               // Size passed to BeginLayout
    ImVec2                      CurrentSize;        // Bounds of layout known at the beginning the frame.
    ImVec2                      MinimumSize;        // Minimum possible size when springs are collapsed.
    ImVec2                      MeasuredSize;       // Measured size with springs expanded.

    ImVector<ImGuiLayoutItem>   Items;
    int                         CurrentItemIndex;
    int                         ParentItemIndex;
    ImGuiLayout* Parent;
    ImGuiLayout* FirstChild;
    ImGuiLayout* NextSibling;
    float                       Align;              // Current item alignment.
    float                       Indent;             // Indent used to align items in vertical layout.
    ImVec2                      StartPos;           // Initial cursor position when BeginLayout is called.
    ImVec2                      StartCursorMaxPos;  // Maximum cursor position when BeginLayout is called.

    ImGuiLayout(ImGuiID id, ImGuiLayoutType type)
    {
        Id = id;
        Type = type;
        Live = false;
        Size = CurrentSize = MinimumSize = MeasuredSize = ImVec2(0, 0);
        CurrentItemIndex = 0;
        ParentItemIndex = 0;
        Parent = FirstChild = NextSibling = NULL;
        Align = -1.0f;
        Indent = 0.0f;
        StartPos = ImVec2(0, 0);
        StartCursorMaxPos = ImVec2(0, 0);
    }
};