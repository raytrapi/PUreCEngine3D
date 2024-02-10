#include "./interface.h"
#include "../../components/modulos/collider/collider.h"
#include "../../components/src/entity.h"
#include "../../components/modulos/code/code.h"
#include "../../modules/tape/tape.h"
#include "../../utilidades/project/serializer/serializer.h"
#include "../../utilidades/project/serializer/deserializer.h"

#include <functional>
#include "../files/filesControl.h"

//TODO: Quitar esto para cuando tengamos la carga dinámica de los componentes
#include "../../../../../components/vendors/mapsGenerator/mapsGenerator.h"
//TODO: /Quitar esto para cuando tengamos la carga dinámica de los componentes

//#include "../opengl.h"
//extern Global global;
//#include "../opengl.h"
void InterfaceGL::init(GLFWwindow* window, ImGuiConfigFlags options){
    this->window = window;
    //setlocale(LC_ALL, "");
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO(); //(void)io;
    io->ConfigFlags = options;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io->ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io->ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    ImFontConfig configFuente;
    configFuente.FontDataOwnedByAtlas = false;
    fonts.push_back(io->Fonts->AddFontFromFileTTF("resources/fonts/OpenSans-Regular.ttf", 18));
    static const ImWchar ranges[] ={
        0x0020, 0x00FF, // Basic Latin + Latin Supplement
        0x20AC, 0x20AC, // €
        0x2122, 0x2122, // ™
        0x2196, 0x2196, // ↖
        0x21D6, 0x21D6, // ⇖
        0x2B01, 0x2B01, // ⬁
        0x2B09, 0x2B09, // ⬉
        0x2921, 0x2922, // ⤡ ⤢
        0x263A, 0x263A, // ☺
        0x266A, 0x266A, // ♪
        0x2715, 0x2715, // ✕
        0,
    };
    fonts.push_back(io->Fonts->AddFontFromFileTTF("resources/fonts/NotoSansSymbols2-Regular.ttf", 32,0, ranges));
    
    
    //ImFont* fuenteOpenSan = io->Fonts->AddFontFromFileTTF("resources/fonts/pixelart.ttf", 20);
    io->FontDefault = fonts[0];


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImGuiStyle& style = ImGui::GetStyle();
    if (io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
       style.WindowRounding = 0.0f;
       style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }
    /***/
    auto& colors = ImGui::GetStyle().Colors;
    colors[ImGuiCol_WindowBg] = ImVec4{ 0.1f, 0.105f, 0.11f, 1.0f };

    // Headers
    colors[ImGuiCol_Header] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_HeaderHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_HeaderActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Buttons
    colors[ImGuiCol_Button] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_ButtonHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_ButtonActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Frame BG
    colors[ImGuiCol_FrameBg] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };
    colors[ImGuiCol_FrameBgHovered] = ImVec4{ 0.3f, 0.305f, 0.31f, 1.0f };
    colors[ImGuiCol_FrameBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };

    // Tabs
    colors[ImGuiCol_Tab] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabHovered] = ImVec4{ 0.38f, 0.3805f, 0.381f, 1.0f };
    colors[ImGuiCol_TabActive] = ImVec4{ 0.28f, 0.2805f, 0.281f, 1.0f };
    colors[ImGuiCol_TabUnfocused] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TabUnfocusedActive] = ImVec4{ 0.2f, 0.205f, 0.21f, 1.0f };

    // Title
    colors[ImGuiCol_TitleBg] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgActive] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    colors[ImGuiCol_TitleBgCollapsed] = ImVec4{ 0.15f, 0.1505f, 0.151f, 1.0f };
    /***/
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 410");
    
    consoleLog = new LogOpenGL(false);
    GLuint texturaId;
    glGenTextures(1, &texturaId);
    modules::resources::Resource* res = Module::get<modules::resources::Resource>();
    float* miTextura;
    TextureImg::FORMAT_COLOR formato;
    int ancho;
    int alto;
    int longitud;
    std::tie(miTextura, ancho, alto, longitud, formato) = res->loadImage("resources/icons/interface.png");
    //ERR("el pixel es %", miTextura[404]);
    glBindTexture(GL_TEXTURE_2D, texturaId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);//GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);//GL_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST,GL_LINEAR 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_FLOAT, miTextura);
    delete[]miTextura;
    
    global->idTexturaIconos = texturaId;
    global->uBotonCompilacion = 23.0f / ancho;
    global->vBotonCompilacion = 23.0f / alto;

    globalTripletasF.push_back(new float[3] { global->rLA, global->gLA, global->bLA });
    globalF.push_back(new float[1] { global->iLA });
    globalTripletasF.push_back(new float[3] { global->xL, global->yL, global->zL });
    globalTripletasF.push_back(new float[3] { global->rL, global->gL, global->bL });
    globalF.push_back(new float[1] { global->iL });

    
}

void InterfaceGL::render(){
   /*static bool show = true;
   
   ImGui_ImplOpenGL3_NewFrame();
   ImGui_ImplGlfw_NewFrame();
   ImGui::NewFrame();
   ImGuiViewport* viewport2 = ImGui::GetWindowViewport();
   ImGui::DockSpaceOverViewport(viewport2);
   ImGui::ShowDemoWindow(&show);
   auto io2 = ImGui::GetIO();
   io2.DisplaySize = ImVec2(2000, 1000);
   ImGui::Render();
   graphic->preRender();
   ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

   if (io != NULL && io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
      auto backupContext = glfwGetCurrentContext();

      ImGui::UpdatePlatformWindows();
      ImGui::RenderPlatformWindowsDefault();
      glfwMakeContextCurrent(backupContext);
      
   }
   return;/**/
    //const ImGuiViewport* ventana = ImGui::GetMainViewport();
   int width, height;
   bool panelVistaActivo = false;
   glfwGetWindowSize(window, &width, &height);
    

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    //ImGuizmo::BeginFrame();
    
    ImGuiViewport* viewport = ImGui::GetWindowViewport();
    ImGuiID idDock = ImGui::DockSpaceOverViewport(viewport);
    
    /****** MENU   *******/
    ImVec2 vPos = ImGui::GetMainViewport()->Pos;
    ImVec2 vSize = ImGui::GetMainViewport()->Size;
    menuSuperior(viewport->Size.x, 24, viewport->Pos.x, viewport->Pos.y);
    ImGui::SetNextWindowPos(ImVec2(vPos.x, vPos.y+23));
    herramientasSuperior(30);
    //ImGui::SetNextWindowViewport(idDock);
    
    /***** STATUS *****/
    barraEstadoInferior(vSize.x, 30, vPos.x, vPos.y+vSize.y-30);//viewport->Size.x  viewport->Size.y
   

       

      {
         ImGui::Begin("Entidades", 0, ImGuiWindowFlags_NoCollapse);
         panelEntidadesActivo = ImGui::IsWindowFocused();
         mostrarEntidades();
         if (ImGui::BeginPopupContextWindow()) {
            if (ImGui::MenuItem("Vacio")) {
               Entity* e = Entity::create<Entity::EMPTY>();
               if (e) {
                  e->setName("Nueva Entidad Creada");
               }

            }
            if (ImGui::MenuItem("Cubo")) {
               Entity* e = Entity::create<Entity::CUBE>();
               if (e) {
                  e->setName("Cubo");

               }
               if (entidadesSeleccionadas.size() > 0) {
                  desmarcarEntidadesSeleccionadas();
               }
               seleccionaEntidad(e);
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Luz dirigida")) {
               Entity* e = Entity::create<Entity::LIGHT>();
               if (e) {
                  e->setName("Luz");
               }
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Interfaz")) {
                Entity* e = Entity::create<Entity::INTERFACE>();
                if (e) {
                    e->setName("Interfaz");
                }
            }
            ImGui::EndPopup();
         }


         ImGui::End();
      }
       

      {
         ImGui::Begin("Componentes", 0, ImGuiWindowFlags_NoCollapse);
         mostrarEntidad();
         ImGui::End();
      }
      {
         ImGui::Begin("Mundo", 0, ImGuiWindowFlags_NoCollapse);
         mostrarVentanaMundo();
         ImGui::End();
      }

      if (consoleLog != NULL) {
         ImGui::Begin("Log", 0, ImGuiWindowFlags_NoCollapse);
         ImGui::BeginChild("scrolling");
         ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
         for (auto linea : consoleLog->getLines()) {
            ImGui::PushStyleColor(ImGuiCol_Text, std::get<1>(linea));
            if (std::get<2>(linea) > 1) {
               ImGui::TextWrapped("[%s] %s: %s (%d)", std::get<3>(linea), std::get<4>(linea), std::get<0>(linea), std::get<2>(linea));
            } else {
               ImGui::TextWrapped("[%s] %s: %s", std::get<3>(linea), std::get<4>(linea), std::get<0>(linea));
            }
            ImGui::PopStyleColor();
         }
         if (consoleLog->hasNewLog()) {
            ImGui::SetScrollHereY(1.0f);
            consoleLog->setNewLog(false);
         }
         ImGui::PopStyleVar();
         ImGui::EndChild();
         ImGui::End();

      }
      {
         ImGui::Begin("Navegador", 0, ImGuiWindowFlags_NoCollapse);
         UI::Components::FileNavigator::view();
         ImGui::End();
      }

      ///*** Ventana para materiales   ****///
      ventanaMaterial();
      ///*** Ventana para materiales   ****///

      /********* Panel  Vista **********/
      panelVistaActivo = mostrarView();
      //ACCIONES DE MENU
      controlAccionesGlobales();
      switch (accion) {
      case A_NUEVO_PROYECTO:
         ImGui::OpenPopup("Nuevo Proyecto");
         break;
      case A_ABRIR_PROYECTO:
         openProject();
         break;
      case A_NUEVO_NIVEL:
         Modal::Level::create();
         break;
      case A_GUARDAR_NIVEL:
         saveLevel();
         break;
      case A_ABRIR_MATERIALES:
         mostrarVentanaMaterial = true;
         break;
      }
      accion = A_NINGUNA;
      newProjectModal();

    
    //ImGui::End();
    ImGui::EndFrame();
    if (idCursor != ImGuiMouseCursor_None) {
       ImGui::SetMouseCursor(idCursor);
    }
    //ImGui::SetMouseCursor(8);
    //mostrarGuizmo();
    ImGui::Render();
    graphic->preRender();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    if (io != NULL && io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
       auto backupContext = glfwGetCurrentContext();
       ImGui::UpdatePlatformWindows();
       ImGui::RenderPlatformWindowsDefault();
       glfwMakeContextCurrent(backupContext);
    }

    //Marcamos si estamos en modo de pantalla editor
    panelEditorActivo = panelVistaActivo || panelEntidadesActivo;
}

void InterfaceGL::mostrarComponentes() {
   if (entidadesSeleccionadas.size()==1) {
      auto componentes = ((std::get<0>(entidadesSeleccionadas[0]))->getComponents());
      int iBorrar = -1;
      int iC = 0;
      for (auto componente : *componentes) {
         ;
         if (componente->interfazImGUI(ImGui::GetCurrentContext(),true,iC)) {
            iBorrar = iC;
         }
         iC++;
      };
      if (iBorrar >= 0) {
         (*componentes).erase((*componentes).begin()+iBorrar);
      }
   }
}
void InterfaceGL::mostrarComponente(Component* componente) {
   switch (componente->getType()){
      case TYPE_OBJECT_SERIALIZABLES::SERIALIZABLE_COMPONENTE_CODE:
         ImGui::Text("CODIGO");
         if(((Code*)componente)->codigoBase!=NULL){
            for (auto p : ((Code*)componente)->codigoBase->getParameters()) {
               ImGui::Text(p.nombre.c_str());
            }
         } else {
            DBG("No HAY PARAMETROSSS");
         }
         break;
      default:
         break;
   }
}
bool InterfaceGL::mostrarView(){
   ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
   ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
   ImGui::Begin("Juego",0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
   bool panel = ImGui::IsWindowFocused();
   
   ImVec2 ventana= ImGui::GetContentRegionAvail();//GetLargestConsoleWindowSize();
   ImVec2 posVentana = ImGui::GetWindowPos();
   ImVec2 posApp = ImGui::GetWindowViewport()->Pos;
   posicionVentana=ImGui::GetWindowPos();
   if (ventana.x != (float)ventanaJuego.x || ventana.y!=(float)ventanaJuego.y) {
      ventanaJuego.x = ventana.x;
      ventanaJuego.y = ventana.y;
      graphic->setSize((unsigned int)ventana.x, (unsigned int)ventana.y);
      //graphic->getActiveCamera()->setChange(true);
      graphic->getActiveCamera()->transformChanged();
      auto gl = graphic->getGlobal();
      gl->marginLeft = posVentana.x - posApp.x;
      gl->marginTop = posVentana.y - posApp.y + altoCabecera;
      gl->widthScreen = ventana.x;
      gl->heightScreen = ventana.y;

   }
   //ventana.x += ImGui::GetScrollX();
   //ventana.y += 20;
   ImVec2 posicion = ImVec2(0, altoCabecera);
   ImGui::SetCursorPos(ImVec2(posicion.x, posicion.y));
   //ImGui::SetCursorPos(ImVec2(0, 0));
   GLuint texturaId = global->idTexturaIconos;
   //ImGui::Image((void*)(intptr_t)idTexturaIconos , { ventanaJuego.x ,ventanaJuego.y }, ImVec2(0, 1), ImVec2(1, 0));
   //ImGui::Image((void*)(intptr_t)graphic->getImageFrame(), { ventanaJuego.x ,ventanaJuego.y}, ImVec2(0, 1), ImVec2(1, 0));
   auto imm = graphic->getImageFrame();
   ImGui::Image((void*)(intptr_t)graphic->getImageFrame(), { ventanaJuego.x, ventanaJuego.y }, ImVec2(0, 1), ImVec2(1, 0));
   if (graphic->getGlobal()->executing!=StateExecuting::PLAY ){
     
      mostrarGuizmo();
      if (gizmoSinPulsar) {
         
         auto [xM, yM, zM] = graphic->getInput()->getMouse3DPosition(posVentana.x - posApp.x, posVentana.y - posApp.y+altoCabecera, true);
         //auto [xM2, yM2, zM2] = graphic->getInput()->getMouse3DPosition(ventanaJuego.x- posApp.x, ventanaJuego.y- posApp.y, true);
         //DBG("Pos %, %", posVentana.x, posVentana.y);
         //DBG("RAT %, %, %", xM, yM, zM);
         
         //bool soltando = false;
        
         if (ImGui::IsWindowHovered() || !comienzaMovimientoCamara) {
            bool clickIzquierdo = ImGui::IsMouseClicked(ImGuiMouseButton_Left);
            
            if (clickIzquierdo) {
               bool seleccionMultiple = ImGui::IsKeyDown(ImGuiKey::ImGuiKey_ModCtrl);
               int idEntidad = graphic->getPixel_id(xM, yM, 0);
               //Buscamos la entidad
               bool noEncontrada = true;
               auto entidades = Entity::getEntities();
               auto itrE = entidades.begin();
               
               while (itrE != entidades.end() && noEncontrada) {
                  if ((*itrE)->id == idEntidad) {
                     noEncontrada = false;
                     if (clickIzquierdo) {
                        seleccionaEntidad((*itrE));
                        cambioEntidad = true;
                     } else {
                        objetoEncima = (*itrE);
                     }
                  }
                  itrE++;
               }
               if (noEncontrada && clickIzquierdo) {
                  desmarcarEntidadesSeleccionadas();
               }
            }
            if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
               if (comienzaMovimientoCamara) {
                  //ImGui::SetMouseCursor(ImGuiMouseCursor_None);
                  //auto [miXRaton,miYRaton] = Mouse::getPosition();
                  //posicionRaton = ImGui::GetMousePos();
                  comienzaMovimientoCamara = false;
               }
               if (!conRotacionCamara) {
                  conRotacionCamara = true;
                  xRatonMovimiento = xM;
                  yRatonMovimiento = yM;

               } else {
                  if (xRatonMovimiento != xM || yRatonMovimiento != yM) {
                     float rotY = xM - xRatonMovimiento;
                     float rotX = yM - yRatonMovimiento;
                     //auto [aC, bC, gC]=graphic->getActiveCamera()->get
                     auto camera = graphic->getActiveCamera();
                     if (camera) {
                        //auto tranformCamara = camera->getEntity()->getTransform();
                        auto tranformCamara = camera->transform();
                        auto [rXC, rYC, rZC] = tranformCamara->getRotation();
                        rYC += rotY * velocidadRotacion;
                        rXC += rotX * velocidadRotacion;
                        tranformCamara->setRotation(rXC, rYC, rZC);
                        graphic->getActiveCamera()->transformChanged();
                     }
                     //DBG("Movemos a [%, %] [%,%]", xM, yM, xM - xRatonMovimiento, yM-yRatonMovimiento );


                     xRatonMovimiento = xM;
                     yRatonMovimiento = yM;
                  }

               }


               if (graphic->getInput()->isKeyDown(Key::W) || ImGui::IsKeyDown(ImGuiKey_UpArrow)) {
                  //Hacia delante
                  moverCamara(ImGui::GetIO().DeltaTime * velocidadZ, 0);

               } else if (graphic->getInput()->isKeyDown(Key::S) || ImGui::IsKeyDown(ImGuiKey_DownArrow)) {
                  //Hacia delante
                  moverCamara(-(ImGui::GetIO().DeltaTime * velocidadZ), 0);
               }
               if (graphic->getInput()->isKeyDown(Key::D) || ImGui::IsKeyDown(ImGuiKey_RightArrow)) {
                  //Hacia delante
                  moverCamara(-(ImGui::GetIO().DeltaTime * velocidadZ), 1);
                  //DBG("Incremento Z [%]", ImGui::GetIO().DeltaTime * velocidadZ);
               } else if (graphic->getInput()->isKeyDown(Key::A) || ImGui::IsKeyDown(ImGuiKey_LeftArrow)) {
                  //Hacia delante
                  moverCamara((ImGui::GetIO().DeltaTime * velocidadZ), 1);
                  //DBG("Incremento Z [%]", ImGui::GetIO().DeltaTime * velocidadZ);
               }
               if (graphic->getInput()->isKeyDown(Key::Q)) {
                  //Hacia delante
                  moverCamara(-(ImGui::GetIO().DeltaTime * velocidadZ), 2);
                  //DBG("Incremento Z [%]", ImGui::GetIO().DeltaTime * velocidadZ);
               } else if (graphic->getInput()->isKeyDown(Key::E)) {
                  //Hacia delante
                  moverCamara((ImGui::GetIO().DeltaTime * velocidadZ), 2);
                  //DBG("Incremento Z [%]", ImGui::GetIO().DeltaTime * velocidadZ);
               }
               //graphic->setMousePosition(posicionRaton.x, posicionRaton.y);
            }
            if (ImGui::IsMouseDown(ImGuiMouseButton_Middle)) {
               //Hacemos Pan
               if (comienzaMovimientoCamara) {
                  //ImGui::SetMouseCursor(ImGuiMouseCursor_None);
                  //auto [miXRaton,miYRaton] = Mouse::getPosition();
                  //posicionRaton = ImGui::GetMousePos();
                 // ImGui::SetMouseCursor(ImGuiMouseCursor_COUNT);
                  comienzaMovimientoCamara = false;
               }
               if (!conMovimientoCamara) {
                  conMovimientoCamara = true;
                  xRatonMovimiento = xM;
                  yRatonMovimiento = yM;
               } else {
                  if (xRatonMovimiento != xM || yRatonMovimiento != yM) {
                     float movY = xM - xRatonMovimiento;
                     float movX = yM - yRatonMovimiento;
                     auto camera = graphic->getActiveCamera();
                     if (camera) {
                        //auto tranformCamara = camera->getEntity()->getTransform();
                        camera->move(movY * velocidadRotacion, -movX * velocidadRotacion, 0);
                     }
                     //DBG("Movemos a [%, %] [%,%]", xM, yM, xM - xRatonMovimiento, yM-yRatonMovimiento );


                     xRatonMovimiento = xM;
                     yRatonMovimiento = yM;
                  }
               }
            }
            
            if (ImGui::IsKeyDown(ImGuiKey_MouseWheelY)) {
               float delta = ((float)ImGui::GetIO().MouseWheel * velocidadZWhell);
               moverCamara(delta, 0);
               //DBG("Incremento Z [%]", ImGui::GetIO().MouseWheel);
            }
         }

         /** Drop de objetos **/
         if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && ImGui::BeginDragDropTarget()) {
            int idEntidad = graphic->getPixel_id(xM, yM, 0);
            if (objetoEncima == NULL || idEntidad != objetoEncima->getId()) {
               //Buscamos la entidad
               bool noEncontrada = true;
               auto entidades = Entity::getEntities();
               auto itrE = entidades.begin();

               while (itrE != entidades.end() && noEncontrada) {
                  if ((*itrE)->id == idEntidad) {
                     noEncontrada = false;
                     objetoEncima = (*itrE);
                  }
                  itrE++;
               }
            }
            //DBG("Suelta un objeto");
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("DRAG_MATERIAL")){
               if (payload->DataSize == sizeof(DragFile) && objetoEncima) {
                  auto datos = *(DragFile *)payload->Data;
                  auto rend = objetoEncima->getComponent<RenderableComponent>();
                  if (rend) {
                     auto m=rend->setMaterial(datos.UID,0);
                     if (m) {
                        m->setName(datos.name.c_str());
                     }
                  }
                  //DBG("Soltamas el fichero % sobre el objeto %", datos.name, objetoEncima->getName().c_str());
               }
            }
            ImGui::EndDragDropTarget();
         }
      }
   }
   if (ImGui::IsMouseReleased(ImGuiMouseButton_Right) && conRotacionCamara) {
      //DBG("Liberamos");
      comienzaMovimientoCamara = true;
      conRotacionCamara = false;
      ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
   }
   if (ImGui::IsMouseReleased(ImGuiMouseButton_Middle) && conMovimientoCamara) {
      //DBG("Liberamos");
      comienzaMovimientoCamara = true;
      conMovimientoCamara = false;
      ImGui::SetMouseCursor(ImGuiMouseCursor_Arrow);
   }

   ImGui::End();
   ImGui::PopStyleVar(2);
   return panel;
}
void InterfaceGL::mostrarGuizmo() {
   //return;
   
   if (graphic->getGlobal()->executing != StateExecuting::PLAY) {

      if (entidadesSeleccionadas.size()>0) {
         //Añadimos el gizmo
         //Ahora cogemos la información de la cámara
         auto camaraProjection = graphic->getActiveCamera()->getProjectionMatrix();
         auto camaraView = graphic->getActiveCamera()->getViewMatrixGuizmo();
         auto camaraInverseView = graphic->getActiveCamera()->getInverseViewMatrix();
         
         ImGuizmo::BeginFrame();
         // Obtener el tamaño de la ventana de ImGui
         ImVec2 windowSize = ImGui::GetWindowSize();
         ImVec2 pos = ImGui::GetWindowPos();
         ImVec2 posV = ImGui::GetWindowViewport()->Pos;//ImGui::GetWindowPos();
         ImGui::SetNextWindowSize(windowSize);
         //ImGuizmo::SetGizmoSizeClipSpace(40.0f);
         ImGuizmo::SetRect(pos.x + posGizmo.x, pos.y + posGizmo.y, windowSize.x, windowSize.y);
         ImGui::PushClipRect(ImVec2(pos.x, pos.y ), ImVec2(pos.x+100, pos.y ), false);
         //ImGui::PushClipRect(ImVec2(pos.x, pos.y + 15.0f), ImVec2(windowSize.x, windowSize.y), false);
         ImGuizmo::SetOrthographic(false);
         if (gizmoSinPulsar || posicionGizmo == 0) {
               if (transformGizmo == 0) {
                  if (entidadesSeleccionadas.size() == 1) {
                     transformGizmo = std::get<0>(entidadesSeleccionadas[0])->transform();
                  } else {
                     transformGizmo = new Transform(0);
                  }
               }
               posicionGizmo = transformGizmo->matrix(false, true);// true, true);
         }
         bool withSnap = ImGui::IsKeyDown(ImGuiKey::ImGuiKey_ModCtrl);
         float valueSnap = operation == ImGuizmo::ROTATE ? 45.0f : 0.5f;
         const float snap[3] = { 
            valueSnap,
            valueSnap,
            valueSnap };
         // Dibujar el gizmo de transformación
         ImGuizmo::Manipulate(
            camaraView,       // Matriz de vista de la cámara
            camaraProjection,        // Matriz de proyección de la cámara
            operation,               // Operación de transformación (TRANSLATE, ROTATE, SCALE)
            mode,                    // Modo de transformación (LOCAL, WORLD)
            posicionGizmo,            // Matriz de transformación del objeto
            0,
            withSnap ? snap:0
         );/**/
         //ImGuizmo::DrawGrid(camaraView, camaraProjection, posicionGizmo, 1.0f);
         if (ImGuizmo::IsUsing()) {
            gizmoSinPulsar = false;

            float matrixTranslation[3], matrixRotation[3], matrixScale[3];

            ImGuizmo::DecomposeMatrixToComponents(posicionGizmo, matrixTranslation, matrixRotation, matrixScale);
            //DBG("Z: % --- %", matrixRotation[2],std::get<2>(entidadSeleccionada->transform()->getRotation())*M_RAD_GRAD);

            //DBG("TRANS %, %, %", matrixTranslation[0], matrixTranslation[1], matrixTranslation[2]);
            //DBG("ROTTRANS %, %, %", matrixTranslation[0], matrixTranslation[1], matrixTranslation[2]);
            switch (operation) {
            case ImGuizmo::TRANSLATE:
                  {
                     if (entidadesSeleccionadas.size() > 0) {
                        for (auto entidadManejador : entidadesSeleccionadas) {
                           auto [x, y, z] = std::get<0>(entidadManejador)->transform()->getWorldPosition();
                           std::get<0>(entidadManejador)->transform()->addPosition(matrixTranslation[0] - x, matrixTranslation[1] - y, matrixTranslation[2] - z);
                           //std::get<0>(entidadManejador)->transform()->setPosition(matrixTranslation[0], matrixTranslation[1], matrixTranslation[2]);
                        }
                     }
                     //transformGizmo->addPosition(matrixTranslation[0] - x, matrixTranslation[1] - y, matrixTranslation[2] - z);
                  }
                  break;
               case ImGuizmo::ROTATE:
                  {
                     //DBG("Z: %", -matrixRotation[2]);
                     auto [x, y, z] = transformGizmo->getRotation();
                     float incX = (-matrixRotation[0] * M_GRAD_RAD) - x;
                     float incY = (-matrixRotation[1] * M_GRAD_RAD) - y;
                     float incZ = (-matrixRotation[2] * M_GRAD_RAD) - z;
                     //transformGizmo->addRotation(incX, incY, incZ);
                     std::tie(x, y, z) = transformGizmo->getRotation();
                     if (incX != 0 || incY != 0 || incZ != 0) {
                        if (entidadesSeleccionadas.size() > 0) {
                           //DBG("Rotacion: %, %, %", incX, incY, incZ);
                           for (auto entidadManejador : entidadesSeleccionadas) {
                              auto transformEntidad = std::get<0>(entidadManejador)->transform();
                              transformEntidad->addRotation(incX, incY, incZ);
                              /*auto [px, py, pz] = transformGizmo->getPosition();
                              auto [ex, ey, ez] = transformEntidad->getPosition();
                              float posicion[4] = { ex, ey, ez, 1.0f };
                              float posicionCorregida[4];
                              auto pos = transformEntidad->rotationPivot(px, py, pz, incX, incY, incZ);

                              Transform::multMatrix(pos, 4, 4, posicion, 4, 1, posicionCorregida);
                              std::get<0>(entidadManejador)->transform()->addPosition(posicionCorregida[0]-ex, posicionCorregida[1]-ey, posicionCorregida[2]-ez);
                              delete[] pos;/**/
                           }
                        }
                     }
                  }
                  break;
               case ImGuizmo::SCALE:
                  {
                     auto [x, y, z] = transformGizmo->getScale();
                     if (entidadesSeleccionadas.size() > 0) {
                        for (auto entidadManejador : entidadesSeleccionadas) {
                           std::get<0>(entidadManejador)->transform()->addScale(matrixTranslation[0] - x, matrixTranslation[1] - y, matrixTranslation[2] - z);
                        }
                     }
                     transformGizmo->setScale(matrixScale[0], matrixScale[1], matrixScale[2]);
                  }
                  break;
            }
            //ImGuizmo::RecomposeMatrixFromComponents(matrixTranslation, matrixRotation, matrixScale, posicionGizmo);
         } else {
            gizmoSinPulsar = true;
            /*if (posicionGizmo != NULL) {
               delete[] posicionGizmo;
               posicionGizmo = NULL;
            }/*/
         }/**/
         ImGui::PopClipRect();
      }
   }
}
void InterfaceGL::ventanaMaterial(){
  if (mostrarVentanaMaterial) {
      if (modalMaterial == NULL) {
          modalMaterial = new ui::Modal("Material");
          modalMaterial->addControl(new NodeGrapchic(), ImVec2(0, 0), ImVec2(0, 0));
      }
      mostrarVentanaMaterial=modalMaterial->show();
      return;
      //ImGui::PushID("Material");
      //auto draw_list = ImGui::GetForegroundDrawList();
      ImGuiWindowFlags f = ImGuiWindowFlags_NoTitleBar;// | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_Modal;
      
      //draw_list->ChannelsSplit(2);
      //draw_list->ChannelsSetCurrent(1);
      //ImGuiViewport* viewport = ImGui::Get();
      //ImGuiID idDock = ImGui::DockSpaceOverViewport(viewport);

      /****** MENU   *******/
      ImVec2 vPos = ImGui::GetWindowPos();
      ImVec2 vSize = ImGui::GetWindowSize();
      ImVec2 menu_bar_size = ImVec2(vSize.x, 24);
      
      ImGui::Begin("Materiales", &mostrarVentanaMaterial, f);
          auto es=ImGui::IsWindowDocked();
          if (!es) {
            //ImGui::PushID("menuMaterial1");
            auto pos = ImGui::GetWindowPos();
            ImVec2 margen(50.f, 10.f);
            auto rect = ImRect(pos.x+margen.x,pos.y+margen.y, pos.x+ImGui::GetWindowWidth()+margen.x,pos.y+margen.y);
            if (ImGui::BeginMenuBar("##MaterialesMenu", rect)){
                if (ImGui::BeginMenu("Archivo")) {
                    if (ImGui::MenuItem("Cerrar")) {
                        mostrarVentanaMaterial = false;
                    };
                    ImGui::EndMenu();
                }
                ImGui::EndMenuBar2();
            }

            //Boton de cierre
            //TODO: Esto está mal hay que averiguar el tamaño antes
            ImGui::Text(U8(✕));

            //ImGui::EndGroup();
            //ImGui::PopID();
            //ImGui::xpandSafeArea(40, ImGuiAxis_Y, ImGuiDir_Down);
            ImGui::SetCursorPos(ImVec2(0, 50));

            ImGui::Text("HILA");
            // ImGui::PopStyleVar();
             /*if (ImGui::BeginMenu("##menuMaterial")) {
                ImGui::PushID("menuMaterial1");
                if (ImGui::BeginMenu("Archivo")) {
                   if (ImGui::MenuItem("Cerrar")) {
                      mostrarVentanaMaterial = false;
                   };
                   ImGui::EndMenu();
                }
                ImGui::PopID();
                ImGui::EndMenu();
                //ImGui::End();
             }*/
             //ImGui::PopID();
         
          }
      
          /*
             /**/
      ImGui::End();
      //draw_list->ChannelsSetCurrent(0);
      
      //draw_list->ChannelsMerge();
      //ImGui::PopID();
   }
}
void InterfaceGL::desmarcarEntidadesSeleccionadas(){
   for (auto entidadManejador : entidadesSeleccionadas) {
      std::get<0>(entidadManejador)->setSelected(false);
      std::get<0>(entidadManejador)->removeOnDelete(std::get<1>(entidadManejador));
   }
   if (entidadesSeleccionadas.size() > 1) {
      delete transformGizmo;
   }
   transformGizmo = 0;
   entidadesSeleccionadas.clear();
}
void InterfaceGL::seleccionaEntidad(Entity* entidad, bool mantener){
    if (posicionGizmo != NULL) {
        delete[] posicionGizmo;
        posicionGizmo = NULL;
    }
   bool seleccionMultiple = ImGui::IsKeyDown(ImGuiKey::ImGuiKey_ModCtrl) || mantener;
   if (!seleccionMultiple && entidadesSeleccionadas.size() > 0 ) {
      desmarcarEntidadesSeleccionadas();
   }

   
   bool incluir = true;
   if (seleccionMultiple) {
      for (auto itr = entidadesSeleccionadas.begin(); itr != entidadesSeleccionadas.end(); itr++) {
         if (std::get<0>(*itr) == entidad) {
            incluir = false;
            //Quitamos el elemento
            std::get<0>(*itr)->removeOnDelete(std::get<1>(*itr));
            std::get<0>(*itr)->setSelected(false);
            entidadesSeleccionadas.erase(itr);
            if (entidadesSeleccionadas.size() == 1) {
               if (transformGizmo) {
                  delete transformGizmo;
               }
               transformGizmo = 0;
            }
            break;
         }
      }
   }
   if (incluir) {
      entidad->setSelected(true);
      entidadesSeleccionadas.push_back({ entidad, entidad->onDelete(std::bind_front(&InterfaceGL::quitarEntidad,this)) });
   }
   if (entidadesSeleccionadas.size() > 1) {
      if (entidadesSeleccionadas.size() == 2) {
         transformGizmo = new Transform(0);
      }
      auto[x,y,z]=std::get<0>(entidadesSeleccionadas[0])->transform()->getPosition();
      float xMax = x;
      float xMin = x;
      float yMax = y;
      float yMin = y;
      float zMax = z;
      float zMin = z;
      for (auto e : entidadesSeleccionadas) {
         auto [x, y, z] = std::get<0>(e)->transform()->getPosition();
         if (x > xMax) {
            xMax = x;
         }
         if (x < xMin) {
            xMin = x;
         }
         if (y > yMax) {
            yMax = y;
         }
         if (y < yMin) {
            yMin = y;
         }
         if (z > zMax) {
            zMax = z;
         }
         if (z < zMin) {
            zMin = z;
         }
      }
      transformGizmo->setPosition(xMin + (xMax - xMin) * .5f, yMin + (yMax - yMin) * .5f, zMin + (zMax - zMin) * .5f);
   }
   
}
void InterfaceGL::moverCamara(float delta, int modo) {
   auto camara = graphic->getActiveCamera();
   auto tranformCamara = camara->transform();
   auto [xC, yC, zC] = tranformCamara->getPosition();
   switch (modo) {
      case 0: //Con Forward
         {
            auto [fX, fY, fZ] = tranformCamara->getFordward();
            fX *= delta;
            fY *= delta;
            fZ *= delta;
            xC += fX;
            yC += fY;
            zC += fZ;

         }
         break;
      case 1: //Se mueve lateral
         {
            
            auto [fX, fY, fZ] = tranformCamara->getFordward();
            auto [rX, rY, rZ] = Transform::crossProduct(fX, fY, fZ, 0.0f, 1.0f, 0.0f, true);
            rX *= delta;
            rY *= delta;
            rZ *= delta;
            xC += rX;
            yC += rY;
            zC += rZ;
            
         }
         break;
      case 2: // Hacia UP
         {
            auto [fX, fY, fZ] = tranformCamara->getUp();
            fX *= delta;
            fY *= delta;
            fZ *= delta;
            xC += fX;
            yC += fY;
            zC += fZ;
         }
         break;
   }
   
   
   
   tranformCamara->setPosition(xC, yC, zC);
   camara->transformChanged();

}
void InterfaceGL::mostrarEntidad() {
   Entity* entidadSeleccionada = NULL;
   if (entidadesSeleccionadas.size() == 1) {
      entidadSeleccionada = std::get<0>(entidadesSeleccionadas[0]);
   }
   if (entidadSeleccionada != NULL) {
      //auto [xP, yP, zP] = entidadSeleccionada->transformada->getPosition();
      //auto [xS, yS, zS] = entidadSeleccionada->transformada->getScale();
      //auto [xR, yR, zR] = entidadSeleccionada->transformada->getRotation();
      //xR *= M_RAD_GRAD;
      //yR *= M_RAD_GRAD;
      //zR *= M_RAD_GRAD;
      /*if (cambioEntidad) {
         deleteParametros();
         //tripletasF.push_back(new float[3] { xP, yP, zP });
         //tripletasF.push_back(new float[3] { xS, yS, zS });
         //tripletasF.push_back(new float[3] { xR, yR, zR });
         cambioEntidad = false;
         
         cadenas.push_back(new char[500]);
         strcpy(cadenas[0], entidadSeleccionada->getName().c_str());
         booleanos.push_back(new bool);
         *booleanos[0] = entidadSeleccionada->isActive();
      } else {
         //tripletasF[0][0] = xP; tripletasF[0][1] = yP; tripletasF[0][2] = zP;
         //tripletasF[1][0] = xS; tripletasF[1][1] = yS; tripletasF[1][2] = zS;
         //tripletasF[2][0] = xR; tripletasF[2][1] = yR; tripletasF[2][2] = zR;
         
      }/**/
      


      /*ImGui::PushStyleColor(ImGuiCol_TableRowBg, ImVec4(0.2f, 0.2f, 0.2f, 1.f));
      ImGui::BeginTable("tabla",2, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg);
      ImGui::TableNextRow();
      
      ImGui::TableSetColumnIndex(0);
      ImGui::Text("Nombre");
      ImGui::TableSetColumnIndex(1);
      ImGui::Text(entidadSeleccionada->getName().c_str());
      
      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      ImGui::Text("Posicion");
      ImGui::TableSetColumnIndex(1);
      //std::tuple<float, float, float> posicion = entidadSeleccionada->transformada->getPosition();
      
        //float vec4a[4] = {std::get<0>(posicion),std::get<1>(posicion) ,std::get<2>(posicion), 0 };
      //ImGui::InputFloat3("", vec4a);
      //ImGui::InputFloat("", entidadSeleccionada->transformada->);

      //ImGui::InputText("", &entidadSeleccionada->nombre);
      
      ImGui::PushStyleColor(ImGuiCol_TableRowBg, ImVec4(0.f, 0.f, 1.f, 1.f));
      ImGui::TableNextRow();
      ImGui::TableSetColumnIndex(0);
      mostrarComponentes();
      ImGui::PopStyleColor();
      
      ImGui::EndTable();
      ImGui::PopStyleColor();
      /**/
      flagsTablas0= ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoSavedSettings;// | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders
      bool seleccionada = entidadSeleccionada->isActive();
      if(ImGui::Checkbox("##activo", &seleccionada)) {
         entidadSeleccionada->setActive(seleccionada);
      }
      ImGui::SameLine();
      bool open = ImGui::CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen);
      if (open && ImGui::BeginTable("TableEntidad", 2, flagsTablas0, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 5))) {
         ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 70.0f);
         ImGui::TableNextColumn();
         ImGui::Text("Nombre");
         ImGui::TableNextColumn();
         char* nombre = new char[500];
         strcpy(nombre, entidadSeleccionada->getName().c_str());
         if (ImGui::InputText("##nombre", nombre, 500)) {
            entidadSeleccionada->setName(nombre);
         }
         delete[]nombre;
         ImGui::TableNextRow();
         entidadSeleccionada->transformada->interfazImGUI_C(ImGui::GetCurrentContext());
         ImGui::EndTable();
      }
      /*****************/
      /* Más Compentes */
      /*****************/

      {
         //Boton para añadir compontentes
         ImGui::PushID(10);
         ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor(0.1f, 0.0f, 0.6f));
         ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor(0.1f, 0.0f, 0.7f));
         ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor(0.1f, 0.0f, 0.8f));
         if (ImGui::Button(U8(Añadir nuevo componente), ImVec2(150, 30))) {
            //clicked++;
            ImGui::OpenPopup("menu_nuevo_componente");
         }
         if (ImGui::BeginPopup("menu_nuevo_componente")) {
            if (ImGui::Selectable("Renderizable")) {
               entidadSeleccionada->addComponent<RenderableComponent>();
            };
            ImGui::Separator();
            if (ImGui::Selectable("RigidBody")) {
               entidadSeleccionada->addComponent<physics::RigidBodyComponent>();
            };
            if (ImGui::Selectable("Box Collider")) {
               auto c = entidadSeleccionada->addComponent<BoxColliderComponent>();
               //c->setSize()
            };

            if (graphic->getGlobal()->cartucho) {
               ImGui::Separator();
               if (ImGui::BeginMenu("Codigo")) {
                  for (auto modulo : *graphic->getGlobal()->cartucho->getClassCodeBase()) {
                     if (ImGui::MenuItem(modulo.c_str())) {
                        auto c = entidadSeleccionada->addComponent<Code>();
                        c->linkDirectClass(graphic->getGlobal()->cartucho->createCodeBase(modulo.c_str()));
                        c->setName(modulo.c_str());
                     };
                  }
                  ImGui::EndMenu();
               }
            }
            ImGui::Separator();
            {
                //TODO: Aquí iría la carga de componentes dinámicos
                if (ImGui::Selectable("Generador de Mapa")) {
                    auto con = new MapsGeneratorComponent();
                    con->setGraphic(graphic);
                    auto c = entidadSeleccionada->addComponent(con,0,true);
                   // delete con;
                    //c->setSize()
                };
            }
            ImGui::EndPopup();
         }
         ImGui::PopStyleColor(3);
         ImGui::PopID();

      }
      
      mostrarComponentes();
      

      /*
      static ImGuiTableFlags flags = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_NoSavedSettings;
        ImGui::CheckboxFlags("ImGuiTableFlags_ScrollY", &flags, ImGuiTableFlags_ScrollY);
        ImGui::CheckboxFlags("ImGuiTableFlags_SizingFixedFit", &flags, ImGuiTableFlags_SizingFixedFit);
        for (int n = 0; n < 3; n++)
        {
            char buf[32];
            sprintf(buf, "Synced Table %d", n);
            bool open = ImGui::CollapsingHeader(buf, ImGuiTreeNodeFlags_DefaultOpen);
            if (open && ImGui::BeginTable("Table", 3, flags, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 5)))
            {
                ImGui::TableSetupColumn("One");
                ImGui::TableSetupColumn("Two");
                ImGui::TableSetupColumn("Three");
                ImGui::TableHeadersRow();
                const int cell_count = (n == 1) ? 27 : 9; // Make second table have a scrollbar to verify that additional decoration is not affecting column positions.
                for (int cell = 0; cell < cell_count; cell++)
                {
                    ImGui::TableNextColumn();
                    ImGui::Text("this cell %d", cell);
                }
                ImGui::EndTable();
            }
        }
      */
      //ImGui::InputFloat3("input float3", tripletasF[0]);
 
   } else {
      if (entidadesSeleccionadas.size() > 0 && transformGizmo) {
         transformGizmo->interfazImGUI_C(ImGui::GetCurrentContext());
      }
   }


   


}
void InterfaceGL::mostrarVentanaMundo() {
   auto flagsTablas0 = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoSavedSettings;// | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders
   bool open = ImGui::CollapsingHeader("Mundo", ImGuiTreeNodeFlags_DefaultOpen);
   if (open && ImGui::BeginTable("Mundo", 2, flagsTablas0, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 5))) {
      ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 70.0f);
      ImGui::TableNextColumn();
      ImGui::Text("Color Luz Ambiente");
      ImGui::TableNextColumn();
      globalTripletasF[0][0] = global->rLA;
      globalTripletasF[0][1] = global->gLA;
      globalTripletasF[0][2] = global->bLA;
      ImGui::ColorEdit3("##LuzColor", globalTripletasF[0]);

      ImGui::TableNextColumn();
      ImGui::Text("Intensidad Luz Ambiente");
      ImGui::TableNextColumn();
      globalF[0][0] = global->iLA;
      ImGui::DragFloat("##IntensidadLuz", &globalF[0][0], 0.01F, 0.0F, 1.0f);

      if (global->setGlobalLight(globalTripletasF[0][0], globalTripletasF[0][1], globalTripletasF[0][2], globalF[0][0])) {
         graphic->refresh();
      }


      /*ImGui::TableNextColumn();
      ImGui::Text((char*)u8"Posición Luz");
      ImGui::TableNextColumn();
      ImGui::DragFloatN_Colored("##posicionLuz", globalTripletasF[1], 3, 0.005f);

      ImGui::TableNextColumn();
      ImGui::Text("Color Luz");
      ImGui::TableNextColumn();
      ImGui::ColorEdit3("##colorLuz", globalTripletasF[2]);
      ImGui::TableNextColumn();
      ImGui::Text("Intensidad Luz");
      ImGui::TableNextColumn();
      ImGui::DragFloat("##IntensidadLuz2", &globalF[1][0], 0.01F, 0.0F);

      if (global->setLight0(globalTripletasF[1][0], globalTripletasF[1][1], globalTripletasF[1][2], globalTripletasF[2][0], globalTripletasF[2][1], globalTripletasF[2][2], globalF[1][0])) {
         graphic->refresh();
      }/**/

      {
         ImGui::TableNextRow();
         ImGui::TableNextColumn();
         ImGui::Text("Pos guizmo");
         ImGui::TableNextColumn();
         float posi[2]{posGizmo.x,posGizmo.y};
         if (ImGui::DragFloat2("##posGizmo", posi)) {
            posGizmo.x = posi[0];
            posGizmo.y = posi[1];
         }
      }

      ImGui::EndTable();
   }
   auto camara = graphic->getActiveCamera();
   if (camara) {
      bool open = ImGui::CollapsingHeader("Camara Activa", ImGuiTreeNodeFlags_DefaultOpen);
      //if (open && ImGui::BeginTable("Camara Activa", 2, flagsTablas0, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 5))) {
     //    ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 70.0f);
         camara->interfazImGUI(ImGui::GetCurrentContext(), false);
         

     //    ImGui::EndTable();
     // }
   }
}
void InterfaceGL::menuSuperior(float ancho, float alto, float x, float y){
   ImVec2 menu_bar_size = ImVec2(ancho, alto);
   ImGui::SetNextWindowPos(ImVec2(x, y));
   ImGui::SetNextWindowSize(menu_bar_size);
   ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
   //if (ImGui::Begin("##Menu", NULL, window_flags) && ImGui::BeginMenuBar()) {
   if(ImGui::BeginMainMenuBar()){
      if (ImGui::BeginMenu("Archivo")) {
         ImGui::Separator();
         if (ImGui::MenuItem("Guardar nivel", "Ctrl+S")) {
            accion = A_GUARDAR_NIVEL;
         };
         ImGui::Separator();
         if (ImGui::MenuItem("Nuevo Proyecto ...", NULL)) {
            accion = A_NUEVO_PROYECTO;

         };
         if (ImGui::MenuItem("Abrir Proyecto ...", NULL)) {
            accion = A_ABRIR_PROYECTO;
         };
         //ShowExampleMenuFile();
         ImGui::EndMenu();
      }
      if (ImGui::BeginMenu((const char*)u8"Añadir")) {
         if (ImGui::MenuItem("Nuevo Nivel...", NULL)) {
            accion = A_NUEVO_NIVEL;
         };

         ImGui::CenteredSeparator();
         ImGui::MenuItem("Luz", NULL);
         ImGui::MenuItem("Camara", NULL);
         ImGui::MenuItem("Cubo", NULL);
         //ShowExampleMenuFile();
         ImGui::EndMenu();
      }
      if (ImGui::BeginMenu("Ventanas")) {
         if (ImGui::MenuItem("Materiales", NULL)) {
            accion = A_ABRIR_MATERIALES;
         };
         //ShowExampleMenuFile();
         ImGui::EndMenu();
      }
      if (ImGui::BeginMenu((const char*)u8"Añadir")) {
         if (ImGui::MenuItem("Nuevo Nivel...", NULL)) {
            accion = A_NUEVO_NIVEL;
         };

         ImGui::CenteredSeparator();
         ImGui::MenuItem("Luz", NULL);
         ImGui::MenuItem("Camara", NULL);
         ImGui::MenuItem("Cubo", NULL);
         //ShowExampleMenuFile();
         ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
      //ImGui::End();
   }
}
void InterfaceGL::barraEstadoInferior(float w, float h, float x, float y){
   ImGui::xpandSafeArea(h+2, ImGuiAxis_Y, ImGuiDir_Up);
   ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
   ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));
   auto menu_bar_size = ImVec2(w, h); 
   ImGui::SetNextWindowPos(ImVec2(x, y));
   ImGui::SetNextWindowSize(menu_bar_size);

   bool is_open = ImGui::Begin("##Status", NULL, windowFlags) && ImGui::BeginMenuBar();
   ImGui::PopStyleVar(2);
   ImGui::Columns(4);
   //Añadimos Frames Por Segundo
   //auto [xM, yM, zM] = graphic->getInput()->getMouse3DPosition(posicionVentana.x, posicionVentana.y+ altoCabecera, true);
   auto [xM, yM] = graphic->getInput()->getMousePosition();
   xM -= graphic->getGlobal()->marginLeft;
   yM -= graphic->getGlobal()->marginTop;
   ImGui::Text("FPS: %.1f  [%.1f,%.1f] [%i,%i] %i", ImGui::GetIO().Framerate, xRatonMovimiento, yRatonMovimiento, xM, yM, Mouse::getButtons());
   ImGui::NextColumn();
   ImGui::Text("DT: %f", global->deltaTime);
   //ImGui::Text("FPS: %f", global->fps);
   ImGui::NextColumn();

   ImGuiStyle& style = ImGui::GetStyle();
   style.WindowBorderSize = 0.0f;
   //DBG("padding % %", style.FramePadding.x, style.FramePadding.y);
   ImVec2 padding = style.FramePadding;
   style.FramePadding = ImVec2(0, 2.0);
   //style.FrameBorderSize = 0;
   ImVec4 fondoBoton = style.Colors[ImGuiCol_Button];
   style.Colors[ImGuiCol_Button] = ImVec4(0, 0, 0, 0);
   float u2 = global->uBotonCompilacion * 2;
   float u1 = global->uBotonCompilacion;
   if (global != NULL) {

      switch (global->compileState) {
      case StateCompile::COMPILING:
         u1 = global->uBotonCompilacion * 2;
         u2 = global->uBotonCompilacion * 3;
         break;
      case StateCompile::COMPILED:
         u1 = global->uBotonCompilacion * 3;
         u2 = global->uBotonCompilacion * 4;
         break;
      case StateCompile::INCORRECT:
         u1 = global->uBotonCompilacion * 4;
         u2 = global->uBotonCompilacion * 5;
         break;
      case StateCompile::NEEDCOMPILE:
         u1 = 0;
         u2 = global->uBotonCompilacion;
         break;
      case StateCompile::NOTHING:
         u1 = global->uBotonCompilacion;
         u2 = global->uBotonCompilacion * 2;
         break;
      }
      if (ImGui::ImageButton((void*)(intptr_t)global->idTexturaIconos, ImVec2(23, 23), ImVec2(u1, 1.0f), ImVec2(u2, 1.0f - global->vBotonCompilacion))) {
         //DBG("click");
         if (global->compileState != StateCompile::COMPILING) {
            global->compileState = StateCompile::NEEDCOMPILE;
         }

      };
      ImGui::PushID(2);
      u1 = global->uBotonCompilacion * (global->showGizmoCollider ? 7 : 6);
      u2 = u1 + global->uBotonCompilacion;
      if (ImGui::ImageButton((void*)(intptr_t)global->idTexturaIconos, ImVec2(23, 23), ImVec2(u1, 1.0f), ImVec2(u2, 1.0f - global->vBotonCompilacion))) {
         //DBG("Pulso boton 1");
         global->showGizmoCollider = !global->showGizmoCollider;
         auto colliders = graphic->getEntity()->getAllComponents<Collider>();
         for (auto collider : colliders) {
            collider->refresh();
         }
      };
      ImGui::PushID(3);
      u1 = global->uBotonCompilacion * (global->showGizmoColliderExpand ? 9 : 8);
      u2 = u1 + global->uBotonCompilacion;
      if (ImGui::ImageButton((void*)(intptr_t)global->idTexturaIconos, ImVec2(23, 23), ImVec2(u1, 1.0f), ImVec2(u2, 1.0f - global->vBotonCompilacion))) {
         //DBG("Pulso boton 2");
         global->showGizmoColliderExpand = !global->showGizmoColliderExpand;
         auto colliders = graphic->getEntity()->getAllComponents<Collider>();
         for (auto collider : colliders) {
            collider->refresh();
         }

      };
      ImGui::PopID();
      ImGui::PopID();
   }/**/
   style.FramePadding = padding;
   //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
  //Añadimos icono
  // ImGui::ImageButton()
   ImGui::EndMenuBar();
   ImGui::End();
}
void InterfaceGL::herramientasSuperior(float altura){
   /********* Caja herramients superior ************/
   //ImGui::SetNextWindowPos(ImVec2(0, 24));
   
   ImGui::xpandSafeArea(altura+2, ImGuiAxis_Y, ImGuiDir_Down); //3
   
   ImGui::SetNextWindowSize(ImVec2(ImGui::GetContentRegionAvail().x, altura));
   //int alto = 222; //150 panel inferior + 24 menu +24 panel superior +24 estado
   //int altoPanel = Screen::getHeight() - alto;
   //int superior = 48;
   ImGui::Begin("PanelSuperior", 0,
      ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoTitleBar |
      ImGuiWindowFlags_NoNavFocus |
      ImGuiWindowFlags_NoBringToFrontOnFocus |
      ImGuiWindowFlags_NoDecoration |
      ImGuiWindowFlags_NoDocking
   );

   ImGuiStyle& style = ImGui::GetStyle();
   style.WindowBorderSize = 0.0f;
   ImVec2 padding = style.FramePadding;
   style.FramePadding = ImVec2(0, 1.0);
   //style.FrameBorderSize = 0;
   ImVec4 fondoBoton = style.Colors[ImGuiCol_Button];
   style.Colors[ImGuiCol_Button] = ImVec4(0, 0, 0, 0);
   bool estadoBoton = false;
   if (global) {
      //PLAY
      estadoBoton = global->executing == StateExecuting::STOP;
      float u1 = global->uBotonCompilacion * (estadoBoton ? 0 : 1);
      float u2 = global->uBotonCompilacion * (estadoBoton ? 1 : 2);
      float v1 = 1.0f - global->vBotonCompilacion;
      float v2 = 1.0f - (global->vBotonCompilacion * 2);
      ImGui::PushID(4);
      if (estadoBoton) {
         if (ImGui::ImageButton((void*)(intptr_t)global->idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2))) {
            global->executing = StateExecuting::PLAY;

         }
      } else {
         ImGui::Image((void*)(intptr_t)global->idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2));
      };
      ImGui::PopID();
      ImGui::SameLine();
      //PAUSE
      estadoBoton = global->executing == StateExecuting::PLAY;
      bool estadoBoton2 = global->executing == StateExecuting::PAUSED;
      u1 = global->uBotonCompilacion * (estadoBoton ? 2 : (estadoBoton2 ? 3 : 4));
      u2 = global->uBotonCompilacion * (estadoBoton ? 3 : (estadoBoton2 ? 4 : 5));
      ImGui::PushID(5);
      if (estadoBoton || estadoBoton2) {
         if (ImGui::ImageButton((void*)(intptr_t)global->idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2))) {
            global->paused = !global->paused;
         };
      } else {
         ImGui::Image((void*)(intptr_t)global->idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2));
      }
      ImGui::PopID();
      ImGui::SameLine();
      estadoBoton = global->executing == StateExecuting::PLAY || global->executing == StateExecuting::PAUSED;
      u1 = global->uBotonCompilacion * (estadoBoton ? 5 : 6);
      u2 = global->uBotonCompilacion * (estadoBoton ? 6 : 7);
      ImGui::PushID(6);
      if (estadoBoton) {
         if (ImGui::ImageButton((void*)(intptr_t)global->idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2))) {
            global->executing = StateExecuting::STOPING;
            global->paused = false;

         };
      } else {
         ImGui::Image((void*)(intptr_t)global->idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2));
      }
      ImGui::PopID();
   }
   ImGui::End();
}
void InterfaceGL::mostrarEntidades(Entity* padre) {
   if (padre == 0) {
      //TODO: Punto a mejorar, evitar que tengamos que llamar a getLevel continuamente, por ejemplo mover el nivel a la clase InterfeceGL
      bool pulsarCabecera = false;
      if (Global::getLevelFile()) {
         pulsarCabecera = ImGui::CollapsingHeader(Global::getLevelFile()->getName(), ImGuiTreeNodeFlags_DefaultOpen);
         if (!pulsarCabecera) {
            return;
         }
         if (ImGui::BeginDragDropTarget()) {
            auto payload = ImGui::GetDragDropPayload();
            if (payload != NULL && !ImGui::IsMouseDown(ImGuiMouseButton_Left) && payload->IsDataType("ENTITY_NODE")) {
               //Sabemos que es una entidad

               (*((Entity**)payload->Data))->setParent(NULL);

            }
            ImGui::EndDragDropTarget();
         }
      }
   }
   if (graphic) {
      static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
      static bool align_label_with_current_x_position = false;
      static bool test_drag_and_drop = false;
      static int selection_mask = (1 << 2);


      for (auto entidad : Entity::getEntities(0, padre)) {
         ImGuiTreeNodeFlags node_flags = base_flags;
         
         
         const bool is_selected = entidad->isSelected();// (node_clicked == entidad->id);
         if (is_selected) {
            node_flags |= ImGuiTreeNodeFlags_Selected;
            /*if (entidadSeleccionada != entidad) {
               if (entidadSeleccionada) {
                  entidadSeleccionada->removeOnDelete(handleCierreEntidadSeleccionada);
               }
               entidadSeleccionada = entidad;
               //[&](Entity* e) {if (entidadSeleccionada == e) { entidadSeleccionada = NULL; } }
               handleCierreEntidadSeleccionada = entidadSeleccionada->onDelete(std::bind_front(&InterfaceGL::quitarEntidad, this));
               cambioEntidad = true;
            }/**/
         }
         int numeroHijos = entidad->getChildNumber();
         if (numeroHijos == 0) {
            node_flags |= ImGuiTreeNodeFlags_Leaf;// | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
         }
         std::string nombre = std::to_string(entidad->getId()) + " " + entidad->getName();
         //auto open=ImGui::TreeNodeEx((void*)(intptr_t)entidad->getId(), node_flags, nombre.c_str());//, entidad->getId()
         //ImTextureID 
         auto open = ImGui::IconTreeNode((void*)(intptr_t)entidad->getId(), node_flags, nombre.c_str(), (void*)(intptr_t)global->idTexturaIconos, ImVec2(0, 1.f - (138.f / 240.f)), ImVec2(23.f/240.f,1.f- (161.f / 240.f)));
         //ImGui::Image((void*)(intptr_t)(global->idTexturaIconos), ImVec2(20, 20), ImVec2(0, 1.f - (138.f / 240.f)), ImVec2(23.f / 240.f, 1.f - (161.f / 240.f)));
         if (open) {
            if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) { 
               //node_clicked = entidad->id;
               seleccionaEntidad(entidad);
               cambioEntidad = true;
            }
            //ImGui::TreePop();
            if (ImGui::BeginDragDropTarget()) {
               auto payload = ImGui::GetDragDropPayload();
               if (!ImGui::IsMouseDown(ImGuiMouseButton_Left) && payload != NULL && payload->IsDataType("ENTITY_NODE")) {
                  //Sabemos que es una entidad

                  (*((Entity**)payload->Data))->setParent(entidad);

               }
               ImGui::EndDragDropTarget();
            }

            if (ImGui::BeginDragDropSource()) {
               // Some processing...
               int idNodo = entidad->getId();
               ImGui::SetDragDropPayload("ENTITY_NODE", &(entidad), sizeof(Entity*));
               ImGui::Text(nombre.c_str());
               idCursor = ImGuiMouseCursor_NotAllowed;

               ImGui::EndDragDropSource();
            }

            mostrarEntidades(entidad);
            //if (numeroHijos > 0) {
            ImGui::TreePop();
            //}
         }
      }

      /*if (node_clicked != 0) {
         // Update selection state
         // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
         if (ImGui::GetIO().KeyCtrl)
            selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
         else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
            selection_mask = (1 << node_clicked);           // Click to single-select
      }/**/
   }
   if (Global::getLevelFile()) {
   }
   
   

   
}


/**** FUNCIONES DE MENÚ ****/
char InterfaceGL::nombreNuevoProyecto[256];
void InterfaceGL::newProjectModal() {
   
   ImVec2 center = ImGui::GetMainViewport()->GetCenter();
   ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
   if (ImGui::BeginPopupModal("Nuevo Proyecto", NULL, ImGuiWindowFlags_MenuBar)){
      ImGui::Text("Nombre del proyecto: ");
      ImGui::SameLine();
      ImGui::InputText("ss", nombreNuevoProyecto, 256, ImGuiInputTextFlags_None);
      /*ImGui::Text("Hello from Stacked The First\nUsing style.Colors[ImGuiCol_ModalWindowDimBg] behind it.");

      // Testing behavior of widgets stacking their own regular popups over the modal.
      static int item = 1;
      static float color[4] = { 0.4f, 0.7f, 0.0f, 0.5f };
      ImGui::Combo("Combo", &item, "aaaa\0bbbb\0cccc\0dddd\0eeee\0\0");
      ImGui::ColorEdit4("color", color);

      if (ImGui::Button("Add another modal.."))
         ImGui::OpenPopup("Stacked 2");

      // Also demonstrate passing a bool* to BeginPopupModal(), this will create a regular close button which
      // will close the popup. Note that the visibility state of popups is owned by imgui, so the input value
      // of the bool actually doesn't matter here.
      bool unused_open = true;
      if (ImGui::BeginPopupModal("Stacked 2", &unused_open))
      {
         ImGui::Text("Hello from Stacked The Second!");
         if (ImGui::Button("Close"))
            ImGui::CloseCurrentPopup();
         ImGui::EndPopup();
      }
      /**/
      if (ImGui::Button("Cerrar")) {
        // DBG("El nombre es '%'", nombreNuevoProyecto);
         ImGui::CloseCurrentPopup();
      }
      ImGui::EndPopup();
   }
}
void InterfaceGL::openProject() {
   #ifdef WIN32
   /*BROWSEINFOA carpetas;
   ZeroMemory(&carpetas, sizeof(carpetas));
   char carpeta[512];
   //HWND hwnd;              // owner window
   carpetas.hwndOwner = glfwGetWin32Window(window);
   carpetas.pidlRoot = NULL;
   carpetas.pszDisplayName = carpeta;
   carpetas.pszDisplayName[0] = '\0';
   carpetas.lpszTitle = "PRUEBA";
   carpetas.ulFlags = 0;
   carpetas.lpfn = NULL;
   carpetas.iImage = 0;
   auto valor=SHBrowseForFolderA(
      &carpetas
   );/**/

   
   ////FICHERO
   OPENFILENAMEA carpeta;
   char szFile[260]; 
   HWND hwnd= glfwGetWin32Window(window); // owner window
   HANDLE hf;                             // file handle
   ZeroMemory(&carpeta, sizeof(carpeta));
   
   // Initialize OPENFILENAME
   carpeta.lStructSize = sizeof(carpeta);
   carpeta.hwndOwner = hwnd;
   carpeta.lpstrFile = szFile;
   // Set lpstrFile[0] to '\0' so that GetOpenFileName does not 
   // use the contents of szFile to initialize itself.
   carpeta.lpstrFile[0] = '\0';
   carpeta.nMaxFile = sizeof(szFile);
   carpeta.lpstrFilter = "Pure C 3D Proyecto\0*.pc3d\0";
   carpeta.nFilterIndex = 1;
   carpeta.lpstrFileTitle = NULL;
   carpeta.nMaxFileTitle = 0;
   carpeta.lpstrInitialDir = NULL;
   carpeta.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

   // Display the Open dialog box. 

   if (GetOpenFileName(&carpeta) == TRUE) {
      std::filesystem::path p=carpeta.lpstrFile;

      //DBG("La carpeta es %", (char*) p.parent_path().string().c_str());
      if (global->loadProject((const char*)p.string().c_str(),true)!=0) {
         //TODO: Definir como un error
         DBG("No se ha podido cargar el proyecto");
      }
      

      //global->folderProject = p.parent_path().string();
      //global->executing = StateExecuting::RELOAD_PROJECT;

      /*hf = CreateFile(carpeta.lpstrFile,
         GENERIC_READ,
         0,
         (LPSECURITY_ATTRIBUTES)NULL,
         OPEN_EXISTING,
         FILE_ATTRIBUTE_NORMAL,
         (HANDLE)NULL);*/
   } else {
      DWORD dw = GetLastError();
      LPVOID lpMsgBuf;
      LPVOID lpDisplayBuf;
      FormatMessage(
         FORMAT_MESSAGE_ALLOCATE_BUFFER |
         FORMAT_MESSAGE_FROM_SYSTEM |
         FORMAT_MESSAGE_IGNORE_INSERTS,
         NULL,
         dw,
         MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
         (LPTSTR)&lpMsgBuf,
         0, NULL);

      // Display the error message and exit the process

      DBG("Error al abrir el modal: [%] %", dw, (char*)lpMsgBuf);
      //MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("Error"), MB_OK);

      LocalFree(lpMsgBuf);
      
   }
   /**/

   #endif
}



void InterfaceGL::deleteParametros() {
   for (auto fs : tripletasF) {
      delete [] fs;
   }
   tripletasF.clear();
   for (auto fs : cadenas) {
      delete[] fs;
   }
   cadenas.clear();
   for (auto fs : booleanos) {
      delete fs;
   }/**/
   booleanos.clear();
}
void InterfaceGL::deleteParametrosGlobales() {
   for (auto fs : globalTripletasF) {
      delete[] fs;
   }
   for (auto fs : globalF) {
      delete[] fs;
   }
  
   tripletasF.clear();
}

void InterfaceGL::quitarEntidad(Entity* e){
   for (auto itrE = entidadesSeleccionadas.begin(); itrE != entidadesSeleccionadas.end(); itrE++) {
      if (std::get<0>(*itrE) == e) {
         entidadesSeleccionadas.erase(itrE);
         return;
      }
   }
  
}


void InterfaceGL::controlAccionesGlobales() {
    if (global->executing == StateExecuting::PLAY) {
        return;
    }
   //Guardar Nivel
   if (graphic->getInput()->isKeyPress(Key::S, false) && ImGui::IsKeyDown(ImGuiKey_ModCtrl)) {
      saveLevel();
   } 

   if (graphic->getInput()->isKeyPress(Key::X, false) && ImGui::IsKeyDown(ImGuiKey_ModCtrl)) {

       DBG("Aleatorio de long long = %", FileControl::generateUID<unsigned long long>());
       DBG("Aleatorio de int = %", FileControl::generateUID<int>());
   }

   
   /*if (graphic->getInput()->isKeyPress(Key::M, false)) {
       //Guardamos el material Rojo
       auto m = Material::load(68255623622704);//rojo 49130134253616
       if (m!=NULL) {
           std::string s = "";
           s += "vec4 color(){\r\n";
           s += "\treturn vec4(1.0,0,0,1.0);\r\n";
           s += "}";
           m->setCode(s.c_str());

           m->save();
           delete m;
       }
   }/**/
   if (graphic->getInput()->isKeyPress(Key::N, false) && ImGui::IsKeyDown(ImGuiKey_ModCtrl)) {
       //Mostrar todos los UIDs obtenidos
       auto listaUIDs=FileControl::getUIDs();
       for (auto item : listaUIDs) {
           DBG("[%] %", std::get<0>(item), std::get<1>(item));
       }
   }

   if (ImGui::IsKeyPressed(ImGuiKey_Delete, false)) {
      //TODO: Borrar entidades
      if (panelEditorActivo) {
         for (auto em : entidadesSeleccionadas) {
            std::get<0>(em)->setSelected(false);
            std::get<0>(em)->removeOnDelete(std::get<1>(em));
            std::get<0>(em)->erase();
            
         } 
         entidadesSeleccionadas.clear();
      }/**/

   }

   //Cambio de modo en Guizmo
   if (!ImGui::IsMouseDown(ImGuiMouseButton_Right) && panelEditorActivo) {
      if (graphic->getInput()->isKeyPress(Key::Q, false)) {
         operation = ImGuizmo::OPERATION::TRANSLATE;
      }
      if (graphic->getInput()->isKeyPress(Key::W, false)) {
         operation = ImGuizmo::OPERATION::ROTATE;
      }
      if (graphic->getInput()->isKeyPress(Key::E, false)) {
         operation = ImGuizmo::OPERATION::SCALE;
      }
      if (graphic->getInput()->isKeyPress(Key::L, false)) {
         if (mode == ImGuizmo::MODE::LOCAL) {
            mode = ImGuizmo::MODE::WORLD;
         } else {
            mode = ImGuizmo::MODE::LOCAL;
         }
         //operation = ImGuizmo::OPERATION::SCALE;
      }
   }
   //Copiado de objeto
   if (graphic->getInput()->isKeyPress(Key::D,false) && ImGui::IsKeyDown(ImGuiKey_ModCtrl)) {
      //TODO: Duplicar contenidos

      if (entidadesSeleccionadas.size() > 0 && panelEditorActivo) {
         std::vector<Entity*> nuevasEntidades; 
         for (auto ent_man : entidadesSeleccionadas) {
            //Duplicamos la entidad
            Entity* entidadCopia = new Entity(); //TODO: Colocar la nueva entidad debajo de la actual
            std::vector<unsigned char> estado;
            std::get<0>(ent_man)->saveState(&estado, false);
            entidadCopia->restoreState(&estado, false);
            entidadCopia->setName(entidadCopia->getName() + " copia");
            nuevasEntidades.push_back(entidadCopia);
         }
         desmarcarEntidadesSeleccionadas();
         for (auto e : nuevasEntidades) {
            seleccionaEntidad(e, true);
         }
      }/**/
   }
   /*
   //Almacenar Estado
   if (ImGui::IsKeyPressed(ImGuiKey_G, false) && ImGui::IsKeyDown(ImGuiKey_ModCtrl)) {
      auto estadoActual = global->getDataState();
      estadoActual->clear();
      auto entidadesStack = Entity::getAllEntities();
      for (auto stack : *entidadesStack) {

         for (auto entidad : stack.second) {
            entidad->saveState(estadoActual,true);
         }
      }
      char* resultado = new char[estadoActual->size()+1];
      for (int i = 0; i < estadoActual->size(); i++) {
         char c = estadoActual->operator[](i);
         resultado[i]= (c != '\0' ? c : '$');
      }
      resultado[estadoActual->size()] = '\0';
      DBG(resultado);
      delete[] resultado;
      
   }
   if (ImGui::IsKeyPressed(ImGuiKey_H, false) && ImGui::IsKeyDown(ImGuiKey_ModCtrl)) {
      //Entity::clear();

      auto estadoActual = global->getDataState();
      auto entidadesPila = Entity::getAllEntities();
      Deserializer::setBytes(estadoActual);
      while (!Deserializer::end()) {
         void* entidadSalvada = 0;
         Deserializer::deserialize(&entidadSalvada);
         bool existeEntidad = false;
         for (auto entidadPila : *entidadesPila) {
            for (auto entidad : entidadPila.second) {
               if (entidad == entidadSalvada) {
                  existeEntidad = true;
                  break;
               }
            }
            if (existeEntidad) {
               break;
            }
         }
         if (existeEntidad) {
            ((Entity*)entidadSalvada)->restoreState(0,true);
            DBG("Existe Entidad");
         } else {
            DBG("No existe entidad");
         }
      }

      //int tipo;
      //Deserializer::deserialize(&tipo);
      

   }/**/
   
}

void InterfaceGL::saveLevel(){
   if (Global::getLevelFile()) { //TODO: Obviamente si no hay nivel se debería crear uno
      //Modo 2;
      std::vector<unsigned char> datos;
      std::vector<unsigned char> datos2;
      
      Serializer::serialize(&datos2, global->iLA, global->rLA, global->gLA, global->bLA,(float)1.f);
      auto camara = graphic->getActiveEditorCamera();
      if (camara) {
         auto [x, y, z] = camara->getPosition();
         Serializer::serialize(&datos2, x, y, z);
         std::tie(x, y, z) = camara->getRotation();
         Serializer::serialize(&datos2, x, y, z);
         std::tie(x, y, z) = camara->getScale();
         Serializer::serialize(&datos2, x, y, z);
         Serializer::serialize(&datos, &datos2);
         /*auto entidadesPila = Entity::getAllEntities();
         for (auto k_Entidad : *entidadesPila) {
            for (auto entidad : k_Entidad.second) {
               entidad->saveState(&datos);
            }
         }/**/
         auto entidades = Entity::getEntities(0, NULL);
         for (auto entidad : entidades) {
             entidad->saveState(&datos);
         }

      }
      
      Global::getLevelFile()->save(&datos,1);

      
      /*
      std::string entidadesSerializadas = "{";
      //LUZ
      std::string luz=GenericFile::serializate("intensidad", global->iLA);
      luz += GenericFile::serializate("color", std::tuple<float,float,float,float>{ global->rLA, global->gLA, global->bLA, 1.f }, false);
      entidadesSerializadas += GenericFile::serializate("luz", "{" + luz + "}",true,false);
      //Camara
      auto camara = graphic->getActiveEditorCamera();
      if (camara) {
         std::string camaraS = GenericFile::serializate("posicion", camara->getPosition());
         //camaraS += GenericFile::serializate("escala", camara->get);
         //camaraS += GenericFile::serializate("rotacion", camara->getPosition());
         entidadesSerializadas += GenericFile::serializate("camara", "{" + camaraS + "}", true, false);
      }
      entidadesSerializadas += "\"entidades\":";
      entidadesSerializadas += "[";
      int i = 0;
      if (global->executing == StateExecuting::STOP) {
         auto entidadesPila = Entity::getAllEntities();
         for (auto k_Entidad : *entidadesPila) {
            for (auto entidad : k_Entidad.second) {
               entidadesSerializadas += (i > 0 ? "," : "") + entidad->serializar();
               i++;
            }
         }
      }
      entidadesSerializadas += "]}";
      Global::getLevelFile()->save(entidadesSerializadas);
      DBG(entidadesSerializadas);
      /**/
   }
   //Ahora tenemos que guardar información del proyecto.
   Global::getInstance()->saveConfig();
}

std::vector<float*> InterfaceGL::tripletasF;

std::vector<float*> InterfaceGL::globalF;
std::vector<float*> InterfaceGL::globalTripletasF;
std::vector<char*> InterfaceGL::cadenas;
std::vector<bool*> InterfaceGL::booleanos;
std::vector<ImFont*> InterfaceGL::fonts;
ImGuiTableFlags InterfaceGL::flagsTablas0;
//GLuint InterfaceGL::idTexturaIconos = -1;
//float InterfaceGL::uBotonCompilacion = 0;
//float InterfaceGL::vBotonCompilacion = 0;
LevelFile* InterfaceGL::level = 0;