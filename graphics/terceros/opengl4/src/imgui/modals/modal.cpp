#include "modal.h"
#include "../interface.h"
namespace ui {
    Modal::Modal(const char* name){
	    COPY_CHAR(name, nombre);
	    CONCAT_CHAR("##menu", name, nombreMenu);
        CONCAT_CHAR("##cierre", name, nombreCierre);
	    
    }

    Modal::~Modal(){
	    DELETE_MULTI(nombre);
	    DELETE_MULTI(nombreMenu);
        DELETE_MULTI(nombreCierre);
        DELETE_SIMPLE(sizeCierre);
        for (auto c : controles) {
            delete std::get<0>(c);
        }
    }

    void Modal::addControl(InterfaceControl* control, ImVec2 pos, ImVec2 size) {
        controles.push_back({ control, pos, size });
    }

    bool Modal::show() {
        if (sizeCierre == 0) {
            ImGui::PushFont(InterfaceGL::fonts[1]);
            sizeCierre = new ImVec2(ImGui::CalcTextSize((char*)(u8"✕")));
            ImGui::PopFont();
        }
        bool visible = true;
        ImGuiWindowFlags f = ImGuiWindowFlags_NoTitleBar;// | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_Modal;

  
        /****** MENU   *******/
        ImVec2 vPos = ImGui::GetWindowPos();
        ImVec2 vSize = ImGui::GetWindowSize();
        ImVec2 menu_bar_size = ImVec2(vSize.x, 24);

        ImGui::Begin(nombre, &visible, f);
        auto es = ImGui::IsWindowDocked();
        auto pos = ImGui::GetWindowPos();
        //ImGui::GetWindowWidth
        if (!es) {

            //ImGui::PushID("menuMaterial1");
            ImVec2 margen(50.f, 10.f);
            auto rect = ImRect(pos.x + margen.x, pos.y + margen.y, pos.x + ImGui::GetWindowWidth() + margen.x, pos.y + margen.y);
            if (ImGui::BeginMenuBar(nombreMenu, rect)) {
                if (ImGui::BeginMenu("Archivo")) {
                    if (ImGui::MenuItem("Cerrar mm")) {
                        visible = false;
                     
                    };
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar2();
            }

            //Boton de cierre
            ImGui::PushFont(InterfaceGL::fonts[1]);
            auto posCierre = ImVec2(ImGui::GetContentRegionAvail().x - sizeCierre->x, 0);
            ImGui::SetCursorPos(posCierre);
            auto flagsOpcion = ImGuiSelectableFlags_NoHoldingActiveID | ImGuiSelectableFlags_NoSetKeyOwner | ImGuiSelectableFlags_SelectOnClick | ImGuiSelectableFlags_DontClosePopups;
            auto pulsarCierre=ImGui::Selectable(nombreCierre,true, flagsOpcion,ImVec2(sizeCierre->x,0.0f));
            ImGui::SetCursorPos(posCierre);
            //pressed = Selectable("", menu_is_open, selectable_flags, ImVec2(w, 0.0f));
            ImGui::Text((char*)(u8"✕"));
            if (pulsarCierre) {
                visible = false;
            }
            ImGui::PopFont();


           
           

        }
        auto posActual = ImVec2(10, 40);
        for (auto control : controles) {
            auto posControl = std::get<1>(control);
            ImGui::SetCursorPos(ImVec2(posActual.x + posControl.x, posActual.y + posControl.y));
            std::get<0>(control)->show();
        }
        ImGui::End();
        return visible;

    }
}