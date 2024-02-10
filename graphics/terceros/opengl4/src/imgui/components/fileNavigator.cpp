#include "fileNavigator.h"
#include "../interface.h"

#include <log.h>
#include "../../../../../../components/modulos/renderables/resources/material.h"
#include "../../../../../../utilidades/imports/obj.h"
#include <motor.h>

void UI::Components::FileNavigator::nodoDirectorio(treeDirectory nodo) {
   int id = nodo.value.id;
   std::string nombre = std::to_string(id) + " " + nodo.value.name;
   //if (nodo.childrens.size() > 0) {
       ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
      if (nodo.childrens.size() == 0) {
         base_flags |= ImGuiTreeNodeFlags_Leaf;// | ImGuiTreeNodeFlags_NoTreePushOnOpen;
      }
      int i = 0;
      if (idDirectorio == id) {
         base_flags |= ImGuiTreeNodeFlags_Selected;
      }

      bool open = ImGui::TreeNodeEx((void*)(intptr_t)nodo.value.id, base_flags, nombre.c_str());
      //if (ImGui::IsWindowHovered() && ImGui::IsMouseClicked(ImGuiMouseButton_Right)) {
      //   DBG("Pulsamos %", nombre);
      //}
      if (ImGui::BeginPopupContextItem()) {
         
         
         ImGui::Text("Aquarium");
         ImGui::Text(nombre.c_str());

         ImGui::EndPopup();
      }
      if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
         idDirectorio = id;
         directorioActual= getDirectory(*directorios);
         recargar = true;
         
      }
         
      if (open) {
        
         
         for (auto hijo : nodo.childrens) {
            nodoDirectorio(hijo);
         }
         ImGui::TreePop();
      }
   /*} else {
      ImGui::Text(nombre.c_str());
      //ImGui::OpenPopupOnItemClick("popUpCarpetas");
      //ImGui::PushID(std::get<2>(nodo.value));
      if (ImGui::BeginPopupContextItem(std::to_string(id).c_str())) {
         ImGui::Text("Aquarium");
         ImGui::Text(nombre.c_str());

         ImGui::EndPopup();
      }
      //ImGui::PopID();
   }/**/
   
}
std::expected<treeDirectory, int> UI::Components::FileNavigator::getDirectory(treeDirectory node) {
   if (node.value.id == idDirectorio) {
      return node;
   }
   for (auto h : node.childrens) {
      auto res = getDirectory(h);
      if (res.has_value()) {
         return res.value();
      }
   }
   return std::unexpected(-1);
};
void UI::Components::FileNavigator::createLevel(char* path) {
   if (directorios) {
      if (strlen(path) == 0) {
         ERR("Se ha de indicar el nombre del nivel");
         return;
      }
      //auto folder = getDirectory(*directorios);
      if (directorioActual.has_value()) {
         treeDirectory& directorio = directorioActual.value();
         //std::filesystem::path carpeta(Global::getPathRoot() + directorio.value.path + "/" + directorio.value.name + "/" + path);
         //std::error_code error;
         auto nivel = Global::newLevel(directorio.value.path + "/" + directorio.value.name + "/" + path);
         if (nivel.has_value()) {
            recargar = true;
            //directorios = Global::getDirectory(true);
         } else {
            ERR("No se ha podido crear el nivel");
            //ERR(u8"jj");
            ERR("%", nivel.error().message);
         };/**/


      }
   }
}
void UI::Components::FileNavigator::createFolder(char* path) {
   if (directorios ) {
      if (strlen(path) == 0) {
         ERR("Se ha de indicar el nombre de la carpeta");
         return;
      }
      //auto folder = getDirectory(*directorios);
      if (directorioActual.has_value()) {
         treeDirectory& directorio = directorioActual.value();
         std::filesystem::path carpeta(Global::getPathRoot() + directorio.value.path + "/" + directorio.value.name + "/" + path);
         std::error_code error;
         if (!std::filesystem::create_directory(carpeta,error)) {
            ERR("No se ha podido crear la carpeta");
            //ERR(u8"jj");
            ERR("%", error.value());
         } else {
            recargar = true;
            directorios = Global::getDirectory(true);
         };
         

      }
   }
   //Buscamos el nodo actual;

}
void UI::Components::FileNavigator::createMaterial(char* path){
   if (directorios) {
      if (strlen(path) == 0) {
         ERR("Se ha de indicar el nombre");
         return;
      }
      //auto folder = getDirectory(*directorios);
      if (directorioActual.has_value()) {
         treeDirectory& directorio = directorioActual.value();
         //std::filesystem::path carpeta(Global::getPathRoot() + directorio.value.path + "/" + directorio.value.name + "/" + path);
         //std::error_code error;
         auto nivel = Material::createFileMaterial((const char *)(directorio.value.path + "/" + directorio.value.name + "/" + path).c_str());
            
         if (nivel.has_value()) {
            recargar = true;
            //directorios = Global::getDirectory(true);
         } else {
            ERR("No se ha podido crear el material");
         };/**/


      }
   }
}
void UI::Components::FileNavigator::newFolderModal() {
   Acciones opcion = NONE;
   if (ImGui::BeginPopupContextWindow()) {
      if (ImGui::Button("Nuevo Nivel...")) {
         opcion = NEW_LEVEL;
      }
      if (ImGui::Button("Nuevo Material")) {
         opcion = NEW_MATERIAL;
         
      }
      ImGui::Separator();
      if (ImGui::Button("Nueva Carpeta...")) {
         opcion = NEW_FOLDER;
      }
      
      ImGui::Separator();
      if (ImGui::Button("Borrar")) {
         opcion = DEL;
      }
      
      ImGui::EndPopup();
   }
   
   //if (opcion > 0) {
      switch (opcion) {
         case NEW_FOLDER:
            ImGui::OpenPopup("Gestión de Carpetas");
            break;
         case NEW_LEVEL:
            ImGui::OpenPopup("Gestión de Nivel");
            break;
         case NEW_MATERIAL:
            ImGui::OpenPopup("Gestión de Material");
            break;
         default:
            break;
      }
     
      bool openFolder = true;
      ImGui::SetNextWindowSize(ImVec2(400, 150));
      if (ImGui::BeginPopupModal("Gestión de Carpetas", &openFolder,ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize)) {
         static char nombreCarpeta[128] = "";
         ImGui::Text("Nombre: ");
         ImGui::SameLine();
         if (ImGui::IsAnyItemFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
            ImGui::SetKeyboardFocusHere(0);
         ImGui::InputText("##nuevaCarpeta", nombreCarpeta, IM_ARRAYSIZE(nombreCarpeta));
         if (ImGui::Button("Crear")) {
            createFolder(nombreCarpeta);
            ImGui::CloseCurrentPopup();
         };

         ImGui::EndPopup();
         //open = false;
      }
      bool openLevel = true;
      ImGui::SetNextWindowSize(ImVec2(400, 100));
      if (ImGui::BeginPopupModal("Gestión de Nivel", &openLevel, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize)) {
         static char nombreNivel[128] = "";
         ImGui::Text("Nombre nivel: ");
         ImGui::SameLine();
         if (ImGui::IsAnyItemFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
            ImGui::SetKeyboardFocusHere(0);
         ImGui::InputText("##nuevoNivel", nombreNivel, IM_ARRAYSIZE(nombreNivel));
         if (ImGui::Button("Crear")) {
            createLevel(nombreNivel);

            ImGui::CloseCurrentPopup();
         };

         ImGui::EndPopup();
         //open = false;
      }



      bool openMaterial = true;
      ImGui::SetNextWindowSize(ImVec2(400, 100));
      if (ImGui::BeginPopupModal("Gestión de Material", &openMaterial, ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoResize)) {
         static char nombre[128] = "";
         ImGui::Text("Nombre Material: ");
         ImGui::SameLine();
         if (ImGui::IsAnyItemFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0))
            ImGui::SetKeyboardFocusHere(0);
         ImGui::InputText("##nuevoMaterial", nombre, IM_ARRAYSIZE(nombre));
         if (ImGui::Button("Crear")) {
            createMaterial(nombre);

            ImGui::CloseCurrentPopup();
         };

         ImGui::EndPopup();
         //open = false;
      }
   //}

   
}

void UI::Components::FileNavigator::nodoFicheros() {
   //ImGui::Text(std::to_string(idDirectorio).c_str());

   /*if (ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
       posicionI = ImGui::GetMousePos();
       DBG("Pos I [%, %]", posicionI.x, posicionI.y);
   }
   if (ImGui::IsMouseDown(ImGuiMouseButton_Left))   {
      posicionF = ImGui::GetMousePos();
      ImDrawList* draw_list = ImGui::GetForegroundDrawList(); //ImGui::GetWindowDrawList();
      draw_list->AddRect(posicionI, posicionF, ImGui::GetColorU32(IM_COL32(0, 130, 216, 255)));   // Border
      draw_list->AddRectFilled(posicionI, posicionF, ImGui::GetColorU32(IM_COL32(0, 130, 216, 50)));    // Background
   }/**/
   auto global = Global::getInstance();
   auto g = Module::get<modules::graphics::Graphic>();

   if (recargar && directorioActual.has_value()) {
      files.clear();
      treeDirectory& directorio = directorioActual.value();
      std::filesystem::path carpeta(Global::getPathRoot() + directorio.value.path + "/" + directorio.value.name);
      //std::error_code err;
      //Primero las carpetas
      for (auto &fichero : std::filesystem::directory_iterator(carpeta)) {
         if (fichero.is_directory()) {
            std::string nameDirectory=fichero.path().filename().string();
            files.push_back({ fichero.path().filename().string(), directorio.value.path + "/" + directorio.value.name, FILE_FOLDER, global->idTexturaIconos });
         }
      }
      //Ahora los ficheros
      for (auto& fichero : std::filesystem::directory_iterator(carpeta)) {
         //DBG("%", fichero.path().extension());
         auto extension = fichero.path().extension();
         
         if (extension==Global::getExt()) {
            auto tipoFichero = GenericFile::getType(fichero.path().string().c_str());
            if (tipoFichero.has_value()) {
               //std::string nameDirectory = fichero.path().stem().string();
               files.push_back({ fichero.path().stem().string(), directorio.value.path + "/" + directorio.value.name, *tipoFichero, global->idTexturaIconos });

            }
         } else if (extension == ".png" || extension == ".jpg" || extension == ".jpeg") {
            //Es una imagen
            //Añadimos la imágen a la lista de disponibles
            if (g) {
               auto datImagen = Texture::loadImage(fichero.path().string().c_str());
               //auto datImagen = g->loadTexture(fichero.path().string(), modules::graphics::Graphic::TYPE_TEXTURE::T_IMG, modules::graphics::Graphic::TYPE_REPEAT::REPEAT);
               files.push_back({ fichero.path().filename().string(), directorio.value.path + "/" + directorio.value.name,TYPE_FILE::FILE_IMG, std::get<0>(datImagen)});
            }
         } else if (extension == ".obj") {
             //Comprobamos si existe un fichero análogo (con el mismo nombre) pero con la extensión del sistema
             //DBG("THUMB [%]", (fichero.path().parent_path().string()+"/"+fichero.path().stem().string() + global->getExt()).c_str());
             if (!std::filesystem::exists((fichero.path().parent_path().string() + "/" + fichero.path().stem().string() + global->getExt()).c_str())) {
                 imports::Obj::createThumbnail((  fichero.path().string()).c_str());
                 files.push_back({ fichero.path().stem().string(), directorio.value.path + "/" + directorio.value.name, TYPE_FILE::FILE_OBJ,global->idTexturaIconos });
             }
         }
      }
      //DBG("[%]", carpeta);
      //DBG("[%]", Global::getPathRoot() + "/" + carpeta);
      recargar = false;
   }
   //Mostramos los ficheros
   //TODO: Averiguar el tamaño de la ventan y tener un numero de columnas en función del hueco
   auto tamVentana = ImGui::GetWindowContentRegionWidth();
   int numColumnas = tamVentana/ anchoFichero;
   auto posVentana = ImGui::GetWindowPos();
   /*auto posViewport = ImGui::GetWindowViewport()->Pos;
   posVentana.x += posViewport.x;
   posVentana.y += posViewport.y;/**/
   if (numColumnas > 0) {
       ImGui::Columns(numColumnas, 0, false);
       int ixFile = 1;//ImGui::GetActiveID()+1;
       
       for (auto file : files) {
           auto encima = false;

           //TODO: Mejorar la presentación
           //Ponemos color de fondo
           //ImGui::PushStyleColor(ImGuiCol_FrameBg, { 0,0,1.f,1.f });
           auto posI = ImGui::GetCursorPos();
           ImVec2 posF;
           auto draw_list = ImGui::GetForegroundDrawList();
           draw_list->ChannelsSplit(2);
           draw_list->ChannelsSetCurrent(1);
           {
               ImGui::PushID(ixFile);
               ImGui::BeginGroup();


               //ImGui::Selectable(("##"+ file.name).c_str()); 
               //ImGui::SameLine();

               //{
               int filImagen = 2;
               int colImagen = 2;
               int bloquesAncho = 2;
               bool recalcular = true;
               float u1 = global->uBotonCompilacion * colImagen;// InterfaceGL::uBotonCompilacion * 0;
               float u2 = global->uBotonCompilacion * (colImagen + bloquesAncho);
               float v1 = 1.0f - (filImagen * global->vBotonCompilacion);
               float v2 = 1.0f - ((filImagen + bloquesAncho) * global->vBotonCompilacion);
               switch (file.type) {
               case FILE_LEVEL:
                   colImagen = 4;
                   filImagen = 2;
                   bloquesAncho = 2;
                   break;
               case FILE_MATERIAL:
                   colImagen = 0;
                   filImagen = 4;
                   bloquesAncho = 2;
                   break;
               case FILE_IMG:
                  u1 = 0.0f;
                  v1 = 1.0f;
                  u2 = 1.0f;
                  v2 = 0.0f; 
                  recalcular = false;
                  break;
               case FILE_OBJ:
                   colImagen = 8;
                   filImagen = 2;
                   bloquesAncho = 2;
                   break;
               default:
                   break;
               }
               if (recalcular) {
                   u1 = global->uBotonCompilacion * colImagen;// InterfaceGL::uBotonCompilacion * 0;
                   u2 = global->uBotonCompilacion * (colImagen + bloquesAncho);
                   v1 = 1.0f - (filImagen * global->vBotonCompilacion);
                   v2 = 1.0f - ((filImagen + bloquesAncho) * global->vBotonCompilacion);
               }
               auto posActual = ImGui::GetCursorPos();
               ImGui::SetCursorPos({ posActual.x + (anchoFichero - 46) * 0.5f, posActual.y });
               ImGui::Image((void*)(intptr_t)file.idImagen, ImVec2(46, 46), ImVec2(u1, v1), ImVec2(u2, v2));

               //}

               ImGui::Text(file.name.c_str());
               ImGui::EndGroup();/**/
               {
                   if (ImGui::BeginDragDropSource(ImGuiDragDropFlags_AcceptPeekOnly | ImGuiDragDropFlags_SourceAllowNullID)) {
                       //Creamos el payload
                       ficheroMovido = { ixFile,file.name.c_str(), file.path.c_str(), file.type };
                       switch (file.type) {
                       case TYPE_FILE::FILE_MATERIAL:
                           ficheroMovido.UID = Material::getUID((Global::getPathRoot() + file.path + "/" + file.name + Global::getExt()).c_str());
                           //DBG("Leo el valor uid %", ficheroMovido.UID);
                           ImGui::SetDragDropPayload("DRAG_MATERIAL", &ficheroMovido, sizeof(DragFile));
                           break;
                       case TYPE_FILE::FILE_FOLDER:
                           ImGui::SetDragDropPayload("DRAG_FOLDER", &ficheroMovido, sizeof(DragFile));
                           break;
                       case TYPE_FILE::FILE_IMG:
                          ficheroMovido.idImagen = file.idImagen;
                          ImGui::SetDragDropPayload("DRAG_IMAGEN", &ficheroMovido, sizeof(DragFile));
                          break;
                       case TYPE_FILE::FILE_OBJ:
                           ficheroMovido.UID = Material::getUID((Global::getPathRoot() + file.path + "/" + file.name + Global::getExt()).c_str());
                           //ficheroMovido.idImagen = file.idImagen;
                           ImGui::SetDragDropPayload("DRAG_OBJ", &ficheroMovido, sizeof(DragFile));
                           break;
                       }
                       marcado = ixFile;
                       //DBG("Marcado %", marcado);
                       //Este sería el dibujo

                       ImGui::Image((void*)(intptr_t)global->idTexturaIconos, ImVec2(32, 32), ImVec2(u1, v1), ImVec2(u2, v2));

                       ImGui::EndDragDropSource();
                   }

               }
               ImGui::PopID();
               encima = ImGui::IsItemHovered();
               posF = ImGui::GetCursorPos();
           }
           //posF.y += 100.0f;
           draw_list->ChannelsSetCurrent(0);
           bool activo = ImGui::IsItemActive();
           if (encima || activo) {
               posF.x += anchoFichero;
               ImColor colorFondo(0.0f, 0.0f, 1.0f, 1.0f);
               posI.x += posVentana.x;
               posI.y += posVentana.y;
               posF.x += posVentana.x;
               posF.y += posVentana.y;
               if (activo) {
                   draw_list->AddRect(posI, posF, ImGui::GetColorU32(IM_COL32(0, 130, 216, 255)));
               }
               if (encima) {
                   draw_list->AddRectFilled(posI, posF, ImGui::GetColorU32(IM_COL32(0, 130, 216, 50)));
                   // render a background quad
               }
           }
           ixFile++;
           draw_list->ChannelsMerge();
           //ImGui::PopStyleColor();
           //ImGui::PopStyleVar();
           if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0)) {

               //DBG("Clicke en %", fichero.path().filename().string().c_str());
               treeDirectory actual = directorioActual.value();

               for (auto hijo : actual.childrens) {
                   if (hijo.value.name == file.name) {
                       actual = hijo;
                       break;
                   }
               }
               switch (file.type) {
               case FILE_FOLDER:
                   idDirectorio = actual.value.id;
                   directorioActual = actual;
                   recargar = true;
                   break;
               case FILE_LEVEL:
                   //auto idArbol = Global::getDirectory()
                   //DBG("Fichero de nivel [%]", (Global::getPathRoot() + "/" + file.path + "/" + file.name + Global::getExt()).c_str());
                   auto g = Global::getInstance();
                   if (g) {
                       g->loadLevel((file.path + "/" + file.name + Global::getExt()).c_str());
                   }
                   InterfaceGL::level = Global::getLevelFile();
                   break;
               }
               //DBG("Tengo %", actual.value.name.c_str());

           };
           ImGui::NextColumn();
       }
   }
}



void UI::Components::FileNavigator::view(){
   //ImGui::Begin("Explorador", 0, ImGuiWindowFlags_NoCollapse);
   ImGui::Columns(2);
   ImGui::SetColumnWidth(0, 300.0f);
   directorios = Global::getDirectory();
   {
      
      ImGuiWindowFlags window_flags = ImGuiWindowFlags_HorizontalScrollbar;// | ImGuiWindowFlags_AlwaysAutoResize;
      if (directorios) {
         ImGui::BeginChild("Folders");
         nodoDirectorio(*directorios);
         ImGui::EndChild();
      }
      ImGui::Text(std::to_string(idDirectorio).c_str());
   }
   //ImGui::End();
   //ImGui::Begin("Ficheros", 0, ImGuiWindowFlags_NoCollapse);
   ImGui::NextColumn();
   {
      if (idDirectorio > -1) {
         ImGui::BeginChild("Files");
            nodoFicheros();
            newFolderModal();
         
         ImGui::EndChild();
      } else {
         if (idDirectorio == -1 && directorios && directorios->childrens.size()>0) {
            idDirectorio = 0;
            directorioActual = getDirectory(*directorios);
         }
      }
      /*ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
      ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 5.0f);
      ImGui::BeginChild("ChildR", ImVec2(0, 260), true, window_flags);
      if (ImGui::BeginTable("split", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings))      {
         for (int i = 0; i < 100; i++)
         {
            char buf[32];
            ImGui::TableNextColumn();
            ImGui::Button(buf, ImVec2(-FLT_MIN, 0.0f));
         }
         ImGui::EndTable();
      }
      ImGui::EndChild();
      ImGui::PopStyleVar();/**/
   }
   //ImGui::End();
}

int UI::Components::FileNavigator::idDirectorio=-1;
treeDirectory* UI::Components::FileNavigator::directorios = 0;
std::expected<treeDirectory, int> UI::Components::FileNavigator::directorioActual = std::unexpected(-1);

bool UI::Components::FileNavigator::recargar=true;
std::vector<UI::Components::File> UI::Components::FileNavigator::files;

const float UI::Components::FileNavigator::anchoFichero = 80.0f;;
ImVec2 UI::Components::FileNavigator::posicionI;
ImVec2 UI::Components::FileNavigator::posicionF;
int UI::Components::FileNavigator::marcado = 0;
DragFile UI::Components::FileNavigator::ficheroMovido;