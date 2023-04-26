#include "./interface.h"
#include "../../components/modulos/collider/collider.h"
#include "../../components/src/entity.h"
#include "../../components/modulos/code/code.h"
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
    ImFont* fuenteOpenSan = io->Fonts->AddFontFromFileTTF("resources/fonts/OpenSans-Regular.ttf", 18);
    //ImFont* fuenteOpenSan = io->Fonts->AddFontFromFileTTF("resources/fonts/pixelart.ttf", 20);
    io->FontDefault = fuenteOpenSan;


    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    consoleLog = new LogOpenGL(false);
    GLuint texturaId;
    glGenTextures(1, &texturaId);
    modules::resources::Resource* res = Module::get<modules::resources::Resource>();
    float* miTextura;
    modules::graphics::TextureImg::FORMAT_COLOR formato;
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
    *(&idTexturaIconos) = texturaId;
    uBotonCompilacion = 23.0f / ancho;
    vBotonCompilacion = 23.0f / alto;

    globalTripletasF.push_back(new float[3] { global->rLA, global->gLA, global->bLA });
    globalF.push_back(new float[1] { global->iLA });
    globalTripletasF.push_back(new float[3] { global->xL, global->yL, global->zL });
    globalTripletasF.push_back(new float[3] { global->rL, global->gL, global->bL });
    globalF.push_back(new float[1] { global->iL });
}

void InterfaceGL::render(){
    //const ImGuiViewport* ventana = ImGui::GetMainViewport();
   int width, height;

    glfwGetWindowSize(window, &width, &height);
    

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    
    
    /**ImGui::Begin("OpenGL Texture Text");
    ImGui::Text("pointer = %p", idTexturaIconos);
    ImGui::Text("size = %d x %d", 240, 240);
    ImGui::Image((void*)(intptr_t)idTexturaIconos, ImVec2(240, 240),ImVec2(0, 1.0f), ImVec2(24.0f/240.0f, 1.0f-(24.0f / 240.0f)));

    ImGui::End();/**/
    /*const char* tooltip_text =
       "Filter usage:[-excl],incl\n"
       "For example:\n"
       "   \"button\" will search for \"button\"\n"
       "   \"-widget,button\" will search for \"button\" without \"widget\"";
    ImGui::BeginTooltip();
    ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
    ImGui::TextUnformatted(tooltip_text);
    ImGui::PopTextWrapPos();
    ImGui::EndTooltip();/**/

    ImGuiViewport* viewport = ImGui::GetWindowViewport();

    herramientasSuperior();

    int windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
    ImGui::SetNextWindowPos(ImVec2(0, 38), ImGuiCond_Always);
    ImGui::SetNextWindowSize(ImVec2(width, height-60));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f,0.0f));
    windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove 
       | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoBackground;
    ImGui::Begin("Area", 0, windowFlags);
    ImGui::PopStyleVar(3);
    ImGuiID idDock = ImGui::GetID("Dockspace");
    ImGui::DockSpace(idDock);

    

    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));
    
    /****** MENU   *******/
    ImVec2 menu_bar_size = ImVec2(viewport->Size.x, 24);
    ImGui::SetNextWindowPos(ImVec2(0,0));
    ImGui::SetNextWindowSize(menu_bar_size);
    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
    if (ImGui::Begin("##Menu", NULL, window_flags) && ImGui::BeginMenuBar()) {
       if (ImGui::BeginMenu("Archivo")){
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
          ImGui::MenuItem("Luz", NULL);
          ImGui::MenuItem("Camara", NULL);
          ImGui::MenuItem("Cubo", NULL);
          //ShowExampleMenuFile();
          ImGui::EndMenu();
       }
       ImGui::EndMenuBar();
       ImGui::End();
    }
    
    
    /***** STATUS *****/
    menu_bar_size = ImVec2(viewport->Size.x, 30);
    ImGui::SetNextWindowPos(ImVec2(0, viewport->Size.y - 30));
    ImGui::SetNextWindowSize(menu_bar_size);

    bool is_open = ImGui::Begin("##Status", NULL, window_flags) && ImGui::BeginMenuBar();
    ImGui::PopStyleVar(2);
    ImGui::Columns(4);
    //Añadimos Frames Por Segundo
    auto [xM, yM, zM] = graphic->getInput()->getMouse3DPosition(posicionVentana.x, posicionVentana.y+ altoCabecera, true);
	 ImGui::Text("FPS: %.1f  [%.1f,%.1f]   [%f]", ImGui::GetIO().Framerate, xM,yM,graphic->getPixel_id(xM, yM));
    ImGui::NextColumn();
    ImGui::Text("DT: %f", global->deltaTime);
    //ImGui::Text("FPS: %f", global->fps);
    ImGui::NextColumn();
    
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowBorderSize = 0.0f;
    //DBG("padding % %", style.FramePadding.x, style.FramePadding.y);
    ImVec2 padding = style.FramePadding;
    style.FramePadding = ImVec2(0,2.0);
    //style.FrameBorderSize = 0;
    ImVec4 fondoBoton = style.Colors[ImGuiCol_Button];
    style.Colors[ImGuiCol_Button] = ImVec4(0, 0, 0, 0);
    float u2 = uBotonCompilacion * 2; 
    float u1 = uBotonCompilacion;
    if (global != NULL) {

        switch (global->compileState) {
        case StateCompile::COMPILING:
            u1 = uBotonCompilacion * 2;
            u2 = uBotonCompilacion * 3;
            break;
        case StateCompile::COMPILED:
            u1 = uBotonCompilacion * 3;
            u2 = uBotonCompilacion * 4;
            break;
        case StateCompile::INCORRECT:
            u1 = uBotonCompilacion * 4;
            u2 = uBotonCompilacion * 5;
            break;
        case StateCompile::NEEDCOMPILE:
            u1 = 0;
            u2 = uBotonCompilacion;
            break;
        case StateCompile::NOTHING:
            u1 = uBotonCompilacion;
            u2 = uBotonCompilacion * 2;
            break;
        }
        if (ImGui::ImageButton((void*)(intptr_t)idTexturaIconos, ImVec2(23, 23), ImVec2(u1, 1.0f), ImVec2(u2, 1.0f - vBotonCompilacion))) {
			//DBG("click");
			if (global->compileState != StateCompile::COMPILING) {
				global->compileState = StateCompile::NEEDCOMPILE;
			}
		
        };
        ImGui::PushID(2);
        u1 = uBotonCompilacion * (global->showGizmoCollider ? 7 : 6);
        u2 = u1 + uBotonCompilacion;
        if (ImGui::ImageButton((void*)(intptr_t)idTexturaIconos, ImVec2(23, 23), ImVec2(u1, 1.0f), ImVec2(u2, 1.0f - vBotonCompilacion))) {
           //DBG("Pulso boton 1");
           global->showGizmoCollider = !global->showGizmoCollider;
           auto colliders = graphic->getEntity()->getAllComponents<Collider>();
           for (auto collider : colliders) {
              collider->refresh();
           }			
        };
        ImGui::PushID(3);
        u1 = uBotonCompilacion * (global->showGizmoColliderExpand ? 9 : 8);
        u2 = u1 + uBotonCompilacion;
        if (ImGui::ImageButton((void*)(intptr_t)idTexturaIconos, ImVec2(23, 23), ImVec2(u1, 1.0f), ImVec2(u2, 1.0f - vBotonCompilacion))) {
           //DBG("Pulso boton 2");
           global->showGizmoColliderExpand = !global->showGizmoColliderExpand;
           auto colliders=graphic->getEntity()->getAllComponents<Collider>();
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


   

    /********* Panel lateral izquierdo ****************/
   /* int superior = 48;
    ImGui::SetNextWindowPos(ImVec2(0, superior));
    ImGui::SetNextWindowSize(ImVec2(anchoPanelIzquierdo, altoPanel));

    ImGui::Begin("PanelIzquierdo", 0,
       ImGuiWindowFlags_NoMove |
       ImGuiWindowFlags_NoCollapse |
       ImGuiWindowFlags_NoTitleBar |
       ImGuiWindowFlags_NoNavFocus |
       ImGuiWindowFlags_NoBringToFrontOnFocus |
       ImGuiWindowFlags_NoDecoration
    );

    
    

    
    /** mostra elementos **/
    //ImGui::GetID()
    //ImGui::SetNextWindowDockID(idDock, ImGuiCond_FirstUseEver);
    ImGui::Begin("Entidades", 0, ImGuiWindowFlags_NoCollapse);
    mostrarEntidades();
    if (ImGui::BeginPopupContextWindow()) {
       if (ImGui::MenuItem("Vacio")) {
          Entity* e = Entity::create<Entity::EMPTY>();
          e->setName("Nueva Entidad Creada");

       }
       if (ImGui::MenuItem("Cubo")) {
          Entity* e = Entity::create<Entity::CUBE>();
          e->setName("Cubo");

       }
       ImGui::EndPopup();
    }


    ImGui::End();

   
    /********* Panel lateral derecho ****************/
    /*ImGui::SetNextWindowPos(ImVec2(Screen::getWidth() - anchoPanelDerecho, superior));
    ImGui::SetNextWindowSize(ImVec2(anchoPanelDerecho, altoPanel));
    ImGuiID idDockDerecho;
    ImGui::Begin("PanelDerecho", 0,
       ImGuiWindowFlags_NoMove |
       ImGuiWindowFlags_NoCollapse |
       ImGuiWindowFlags_NoTitleBar |
       ImGuiWindowFlags_NoNavFocus |
       ImGuiWindowFlags_NoBringToFrontOnFocus |
       ImGuiWindowFlags_NoDecoration
    );
      idDockDerecho=ImGui::GetWindowDockID();
    
    ImGui::End();/**/
   
    ImGui::Begin("Propiedades", 0, ImGuiWindowFlags_NoCollapse);
      mostrarEntidad();
    ImGui::End();
    //ImGui::do
    /***** Panel inferior *******/
    /*ImGui::SetNextWindowPos(ImVec2(0, altoPanel + 48));
    ImGui::SetNextWindowSize(ImVec2(Screen::getWidth(), 150));
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
    ImGui::Begin("Footer", 0,
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar |
        //ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBringToFrontOnFocus
    );//|ImGuiWindowFlags_NoBackground
    ImGui::End();*/
    if (consoleLog != NULL) {
        //ImGui::SetNextWindowPos(ventana->WorkPos);
        //ImGui::SetNextWindowSize(ventana->WorkSize);
        //ImGui::SetNextWindowViewport(ventana->ID);
        //ImGui::SetNextWindowPos(ImVec2(0, Screen::getHeight()));

        //Status bar
        /** Deberíamos hacer un método para esto **/
        //ImGuiContext& g = *ImGui::GetWindowViewport();
        
		
        
		
        
        //ImGui::SetNextWindowSize(ImVec2(Screen::getWidth(), 150));		
		//ImGui::DockSpace()
		
        
        ImGui::Begin("Log", 0, ImGuiWindowFlags_NoCollapse);
		//ImGui::IsWindowDocked
        /*if (ImGui::IsWindowDocked) {
            //DBG("Se junta");
            if (!logDockeado) {
                DBG("Se junta");
            }
            logDockeado = true;
        }else {
            if (logDockeado) {
                DBG("Se desjunta");
            }
            logDockeado = false;
        }/**/
		//if (ImGui::Button("Clear")) Clear();
        //ImGui::SameLine();
        //bool copy = ImGui::Button("Copy");
        //ImGui::SameLine();
        //Filter.Draw("Filter", -100.0f);
        //ImGui::Separator();
        ImGui::BeginChild("scrolling");
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 1));
        //if (copy) ImGui::LogToClipboard();

        /*if (Filter.IsActive())
        {
            const char* buf_begin = Buf.begin();
            const char* line = buf_begin;
            for (int line_no = 0; line != NULL; line_no++)
            {
                const char* line_end = (line_no < LineOffsets.Size) ? buf_begin + LineOffsets[line_no] : NULL;
                if (Filter.PassFilter(line, line_end))
                    ImGui::TextUnformatted(line, line_end);
                line = line_end && line_end[1] ? line_end + 1 : NULL;
            }
        }
        else
        {/**/
        for (auto linea : consoleLog->getLines()) {
            ImGui::PushStyleColor(ImGuiCol_Text, std::get<1>(linea));
			//ImGui::TextUnformatted(std::get<0>(linea));
            if (std::get<2>(linea) > 1) {
                ImGui::TextWrapped("[%s] %s: %s (%d)", std::get<3>(linea), std::get<4>(linea), std::get<0>(linea), std::get<2>(linea));
            }else {
                ImGui::TextWrapped("[%s] %s: %s", std::get<3>(linea), std::get<4>(linea),std::get<0>(linea));
            }
            ImGui::PopStyleColor();
        }
        //ImGui::TextUnformatted(consoleLog->getBuffer().begin());
        //}

        if (consoleLog!=NULL && consoleLog->hasNewLog()) {
            ImGui::SetScrollHereY(1.0f);
            consoleLog->setNewLog(false);
        }
        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::End();


		
			
    }
    mostrarView();

    //Creamos una ventana para la textura de luz
    ImGui::Begin("Shadow Map", 0, ImGuiWindowFlags_NoCollapse);
    if (entidadSeleccionada) {
       //Miramos si tiene luces
       if (entidadSeleccionada->has<LightComponent>()) {
          auto luz = entidadSeleccionada->getComponent<LightComponent>();
          if (luz) {
             ImVec2 ventana = ImGui::GetContentRegionAvail();//GetLargestConsoleWindowSize();
             if (ventana.x != ventanaJuego.x || ventana.y != ventanaJuego.y) {
                ventanaJuego.x = ventana.x;
                ventanaJuego.y = ventana.y;
                //graphic->setSize((unsigned int)ventana.x, (unsigned int)ventana.y);

             }
             //ventana.x += ImGui::GetScrollX();
             //ventana.y += 20;
             ImVec2 posicion = ImVec2(0, 25);
             ImGui::SetCursorPos(ImVec2(posicion.x, posicion.y));
             GLuint texturaId = idTexturaIconos;
             //ImGui::Image((void*)(intptr_t)luz->getTexture(), { ventanaJuego.x ,ventanaJuego.y }, ImVec2(0, 1), ImVec2(1, 0));
             ImGui::Image((void*)(intptr_t)luz->profundidadTextura2D_DBG, { ventanaJuego.x ,ventanaJuego.y }, ImVec2(0, 1), ImVec2(1, 0));
             
          }
       }
    }
    ImGui::End();

    //Creamos una ventana para la textura de luz
    ImGui::Begin("Mapa Id", 0, ImGuiWindowFlags_NoCollapse);
    
       //Miramos si tiene luces
    
   ImVec2 ventana = ImGui::GetContentRegionAvail();//GetLargestConsoleWindowSize();
   if (ventana.x != ventanaJuego.x || ventana.y != ventanaJuego.y) {
      ventanaJuego.x = ventana.x;
      ventanaJuego.y = ventana.y;
      //graphic->setSize((unsigned int)ventana.x, (unsigned int)ventana.y);

   }
   //ventana.x += ImGui::GetScrollX();
   //ventana.y += 20;
   ImVec2 posicion = ImVec2(0, 25);
   ImGui::SetCursorPos(ImVec2(posicion.x, posicion.y));
   //GLuint texturaId = idTexturaIconos;
   //ImGui::Image((void*)(intptr_t)luz->getTexture(), { ventanaJuego.x ,ventanaJuego.y }, ImVec2(0, 1), ImVec2(1, 0));
   ImGui::Image((void*)(intptr_t)graphic->getTextureId(), {ventanaJuego.x ,ventanaJuego.y}, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();

    //ACCIONES DE MENU
    switch (accion) {
       case A_NUEVO_PROYECTO:
         ImGui::OpenPopup("Nuevo Proyecto");
         break;
       case A_ABRIR_PROYECTO:
          openProject();
          break;
      
    }
    accion=A_NINGUNA;
    newProjectModal();


    ImGui::End();
    ImGui::Render();
    ImGui::EndFrame();
    if (io != NULL && io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
       ImGui::UpdatePlatformWindows();
       ImGui::RenderPlatformWindowsDefault();
    }
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void InterfaceGL::mostrarComponentes() {
   if (entidadSeleccionada != NULL) {
      for (auto componente : *entidadSeleccionada->getComponents()) {
            //ImGui::PushStyleColor( ImGuiCol_FrameBg,ImVec4(1.f,0.f,0.f,1.f));
            {
               ImVec2 s = ImGui::CalcTextSize(componente->getName().c_str());
               ImDrawList* drawListR = ImGui::GetWindowDrawList();
               const ImVec2 posR = ImGui::GetCursorScreenPos();
               drawListR->AddRectFilled(posR, ImVec2(200,posR.y+s.y), IM_COL32(30, 30, 30, 255));
               ImGui::Text(componente->getName().c_str());
               ImGui::BeginGroup();
                  mostrarComponente(componente);
               ImGui::EndGroup();
            }
            //ImGui::PopStyleColor();
            
         
      };
   }
}
void InterfaceGL::mostrarComponente(Component* componente) {
   switch (componente->componentType()){
      case TYPE_COMPONENT::CODE:
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
void InterfaceGL::mostrarView(){
   ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
   ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
   ImGui::Begin("Juego",0, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse);
   ImVec2 ventana= ImGui::GetContentRegionAvail();//GetLargestConsoleWindowSize();
   posicionVentana=ImGui::GetWindowPos();
   if (ventana.x != ventanaJuego.x || ventana.y!=ventanaJuego.y) {
      ventanaJuego.x = ventana.x;
      ventanaJuego.y = ventana.y;
      graphic->setSize((unsigned int)ventana.x, (unsigned int)ventana.y);
      
   }
   //ventana.x += ImGui::GetScrollX();
   //ventana.y += 20;
   ImVec2 posicion = ImVec2(0, altoCabecera);
   ImGui::SetCursorPos(ImVec2(posicion.x, posicion.y));
   GLuint texturaId = idTexturaIconos;
   //ImGui::Image((void*)(intptr_t)idTexturaIconos , { ventanaJuego.x ,ventanaJuego.y }, ImVec2(0, 1), ImVec2(1, 0));
   ImGui::Image((void*)(intptr_t)graphic->getImageFrame(), { ventanaJuego.x ,ventanaJuego.y}, ImVec2(0, 1), ImVec2(1, 0));
   ImGui::End();
   ImGui::PopStyleVar(2);
}
void InterfaceGL::mostrarEntidad() {
   if (entidadSeleccionada != NULL) {
      if (cambioEntidad) {
         deleteParametros();
         auto [xP, yP, zP] = entidadSeleccionada->transformada->getPosition();
         tripletasF.push_back(new float[3] { xP, yP, zP });
         auto [xS, yS, zS] = entidadSeleccionada->transformada->getScale();
         tripletasF.push_back(new float[3] { xS, yS, zS });
         auto [xR, yR, zR] = entidadSeleccionada->transformada->getRotator();
         tripletasF.push_back(new float[3] { xR, yR, zR });
         cambioEntidad = false;
      }
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
      bool open = ImGui::CollapsingHeader("General", ImGuiTreeNodeFlags_DefaultOpen);
      if (open && ImGui::BeginTable("TableEntidad", 2, flagsTablas0, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 5))) {
         ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 70.0f);
         ImGui::TableNextColumn();
         ImGui::Text("Nombre");
         ImGui::TableNextColumn();
         ImGui::Text(entidadSeleccionada->getName().c_str());
         
         ImGui::TableNextColumn();
         ImGui::Text((const char*)u8"Posición");
         ImGui::TableNextColumn();
         
         ImGui::DragFloatN_Colored("##posicion", tripletasF[0], 3, 0.005f);
         entidadSeleccionada->transformada->setPosition(tripletasF[0][0], tripletasF[0][1], tripletasF[0][2]);

         ImGui::TableNextColumn();
         ImGui::Text((const char*)u8"Escala");
         ImGui::TableNextColumn();
         
         ImGui::DragFloatN_Colored("##escala", tripletasF[1], 3, 0.005f);
         entidadSeleccionada->transformada->setScale(tripletasF[1][0], tripletasF[1][1], tripletasF[1][2]);

         ImGui::TableNextColumn();
         ImGui::Text((const char*)u8"Rotación");
         ImGui::TableNextColumn();
         
         ImGui::DragFloatN_Colored("##rotacion", tripletasF[2], 3, 1.0f,-360.0f, 360.0f);
         entidadSeleccionada->transformada->setRotator(tripletasF[2][0], tripletasF[2][1], tripletasF[2][2]);

         ImGui::EndTable();
      }



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
 
   }


   flagsTablas0 = ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_Hideable | ImGuiTableFlags_NoSavedSettings;// | ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders
   bool open = ImGui::CollapsingHeader("Mundo", ImGuiTreeNodeFlags_DefaultOpen);
   if (open && ImGui::BeginTable("Mundo", 2, flagsTablas0, ImVec2(0.0f, ImGui::GetTextLineHeightWithSpacing() * 5))) {
      ImGui::TableSetupColumn("", ImGuiTableColumnFlags_WidthFixed, 70.0f);
      ImGui::TableNextColumn();
      ImGui::Text("Color Luz Ambiente");
      ImGui::TableNextColumn();
      ImGui::ColorEdit3("##LuzColor",globalTripletasF[0]);
      
      ImGui::TableNextColumn();
      ImGui::Text("Intensidad Luz Ambiente");
      ImGui::TableNextColumn();
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
      ImGui::EndTable();
   }


}
void InterfaceGL::herramientasSuperior(){
   /********* Caja herramients superior ************/
   ImGui::SetNextWindowPos(ImVec2(0, 24));
   ImGui::SetNextWindowSize(ImVec2(Screen::getWidth(), 30));
   int alto = 222; //150 panel inferior + 24 menu +24 panel superior +24 estado
   int altoPanel = Screen::getHeight() - alto;
   //int superior = 48;
   ImGui::Begin("PanelSuperior", 0,
      ImGuiWindowFlags_NoMove |
      ImGuiWindowFlags_NoCollapse |
      ImGuiWindowFlags_NoTitleBar |
      ImGuiWindowFlags_NoNavFocus |
      ImGuiWindowFlags_NoBringToFrontOnFocus |
      ImGuiWindowFlags_NoDecoration
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
      float u1 = uBotonCompilacion * (estadoBoton ? 0 : 1);
      float u2 = uBotonCompilacion * (estadoBoton ? 1 : 2);
      float v1 = 1.0f - vBotonCompilacion;
      float v2 = 1.0f - (vBotonCompilacion * 2);
      ImGui::PushID(4);
      if (estadoBoton) {
         if (ImGui::ImageButton((void*)(intptr_t)idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2))) {
            global->executing = StateExecuting::PLAY;

         }
      } else {
         ImGui::Image((void*)(intptr_t)idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2));
      };
      ImGui::PopID();
      ImGui::SameLine();
      //PAUSE
      estadoBoton = global->executing == StateExecuting::PLAY;
      bool estadoBoton2 = global->executing == StateExecuting::PAUSED;
      u1 = uBotonCompilacion * (estadoBoton ? 2 : (estadoBoton2 ? 3 : 4));
      u2 = uBotonCompilacion * (estadoBoton ? 3 : (estadoBoton2 ? 4 : 5));
      ImGui::PushID(5);
      if (estadoBoton || estadoBoton2) {
         if (ImGui::ImageButton((void*)(intptr_t)idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2))) {
            global->paused = !global->paused;
         };
      } else {
         ImGui::Image((void*)(intptr_t)idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2));
      }
      ImGui::PopID();
      ImGui::SameLine();
      estadoBoton = global->executing == StateExecuting::PLAY || global->executing == StateExecuting::PAUSED;
      u1 = uBotonCompilacion * (estadoBoton ? 5 : 6);
      u2 = uBotonCompilacion * (estadoBoton ? 6 : 7);
      ImGui::PushID(6);
      if (estadoBoton) {
         if (ImGui::ImageButton((void*)(intptr_t)idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2))) {
            global->executing = StateExecuting::STOPING;
            global->paused = false;

         };
      } else {
         ImGui::Image((void*)(intptr_t)idTexturaIconos, ImVec2(23, 23), ImVec2(u1, v1), ImVec2(u2, v2));
      }
      ImGui::PopID();
   }
   ImGui::End();
}
void InterfaceGL::mostrarEntidades() {
   
   if (graphic) {
      static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
      static bool align_label_with_current_x_position = false;
      static bool test_drag_and_drop = false;
      static int selection_mask = (1 << 2);
      

      for (auto entidad : Entity::getEntities()) {
         ImGuiTreeNodeFlags node_flags = base_flags;
         const bool is_selected = node_clicked== entidad->getId();
         
         if (is_selected) {
            node_flags |= ImGuiTreeNodeFlags_Selected;
            if (entidadSeleccionada != entidad) {
               entidadSeleccionada = entidad;
               cambioEntidad = true;
            }
         }

         node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
         ImGui::TreeNodeEx((void*)(intptr_t)entidad->getId(), node_flags, (entidad->getName() == "" ? std::string("Entidad ") + std::to_string(entidad->getId()) : entidad->getName()).c_str(), entidad->getId());
         if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen()) {
            node_clicked = entidad->getId();
            if (entidadSeleccionada != entidad) {
               entidadSeleccionada = entidad;
               cambioEntidad = true;
            }
         }
         //ImGui::TreePop();
         
      }
      
      if (node_clicked != -1)     {
         // Update selection state
         // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
         if (ImGui::GetIO().KeyCtrl)
            selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
         else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
            selection_mask = (1 << node_clicked);           // Click to single-select
      }
   }
   /*
   * 
    if (ImGui::TreeNode("Trees"))
    {
        IMGUI_DEMO_MARKER("Widgets/Trees/Basic trees");
        if (ImGui::TreeNode("Basic trees"))
        {
            for (int i = 0; i < 5; i++)
            {
                // Use SetNextItemOpen() so set the default state of a node to be open. We could
                // also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
                if (i == 0)
                    ImGui::SetNextItemOpen(true, ImGuiCond_Once);

                if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
                {
                    ImGui::Text("blah blah");
                    ImGui::SameLine();
                    if (ImGui::SmallButton("button")) {}
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }

        IMGUI_DEMO_MARKER("Widgets/Trees/Advanced, with Selectable nodes");
        if (ImGui::TreeNode("Advanced, with Selectable nodes"))
        {
            HelpMarker(
                "This is a more typical looking tree with selectable nodes.\n"
                "Click to select, CTRL+Click to toggle, click on arrows or double-click to open.");
            static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
            static bool align_label_with_current_x_position = false;
            static bool test_drag_and_drop = false;
            ImGui::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnArrow",       &base_flags, ImGuiTreeNodeFlags_OpenOnArrow);
            ImGui::CheckboxFlags("ImGuiTreeNodeFlags_OpenOnDoubleClick", &base_flags, ImGuiTreeNodeFlags_OpenOnDoubleClick);
            ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanAvailWidth",    &base_flags, ImGuiTreeNodeFlags_SpanAvailWidth); ImGui::SameLine(); HelpMarker("Extend hit area to all available width instead of allowing more items to be laid out after the node.");
            ImGui::CheckboxFlags("ImGuiTreeNodeFlags_SpanFullWidth",     &base_flags, ImGuiTreeNodeFlags_SpanFullWidth);
            ImGui::Checkbox("Align label with current X position", &align_label_with_current_x_position);
            ImGui::Checkbox("Test tree node as drag source", &test_drag_and_drop);
            ImGui::Text("Hello!");
            if (align_label_with_current_x_position)
                ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

            // 'selection_mask' is dumb representation of what may be user-side selection state.
            //  You may retain selection state inside or outside your objects in whatever format you see fit.
            // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
            /// of the loop. May be a pointer to your own node type, etc.
            static int selection_mask = (1 << 2);
            int node_clicked = -1;
            for (int i = 0; i < 6; i++)
            {
                // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
                // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter selection.
                ImGuiTreeNodeFlags node_flags = base_flags;
                const bool is_selected = (selection_mask & (1 << i)) != 0;
                if (is_selected)
                    node_flags |= ImGuiTreeNodeFlags_Selected;
                if (i < 3)
                {
                    // Items 0..2 are Tree Node
                    bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Node %d", i);
                    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        node_clicked = i;
                    if (test_drag_and_drop && ImGui::BeginDragDropSource())
                    {
                        ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                        ImGui::Text("This is a drag and drop source");
                        ImGui::EndDragDropSource();
                    }
                    if (node_open)
                    {
                        ImGui::BulletText("Blah blah\nBlah Blah");
                        ImGui::TreePop();
                    }
                }
                else
                {
                    // Items 3..5 are Tree Leaves
                    // The only reason we use TreeNode at all is to allow selection of the leaf. Otherwise we can
                    // use BulletText() or advance the cursor by GetTreeNodeToLabelSpacing() and call Text().
                    node_flags |= ImGuiTreeNodeFlags_Leaf | ImGuiTreeNodeFlags_NoTreePushOnOpen; // ImGuiTreeNodeFlags_Bullet
                    ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, "Selectable Leaf %d", i);
                    if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
                        node_clicked = i;
                    if (test_drag_and_drop && ImGui::BeginDragDropSource())
                    {
                        ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
                        ImGui::Text("This is a drag and drop source");
                        ImGui::EndDragDropSource();
                    }
                }
            }
            if (node_clicked != -1)
            {
                // Update selection state
                // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
                if (ImGui::GetIO().KeyCtrl)
                    selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
                else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
                    selection_mask = (1 << node_clicked);           // Click to single-select
            }
            if (align_label_with_current_x_position)
                ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
            ImGui::TreePop();
        }
        ImGui::TreePop();
    } 
    
   * 
   * /
      
      /*for (int i = 0; i < 5; i++)
      {
         // Use SetNextItemOpen() so set the default state of a node to be open. We could
         // also use TreeNodeEx() with the ImGuiTreeNodeFlags_DefaultOpen flag to achieve the same thing!
         if (i == 0)
            ImGui::SetNextItemOpen(true, ImGuiCond_Once);

         if (ImGui::TreeNode((void*)(intptr_t)i, "Child %d", i))
         {
            ImGui::Text("blah blah");
            ImGui::SameLine();
            if (ImGui::SmallButton("button")) {}
            ImGui::TreePop();
         }
      }/**/

   
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
   carpeta.lpstrFilter = "Pure C Proyecto\0*.pcep\0";
   carpeta.nFilterIndex = 1;
   carpeta.lpstrFileTitle = NULL;
   carpeta.nMaxFileTitle = 0;
   carpeta.lpstrInitialDir = NULL;
   carpeta.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

   // Display the Open dialog box. 

   if (GetOpenFileName(&carpeta) == TRUE) {
      std::filesystem::path p=carpeta.lpstrFile;

      //DBG("La carpeta es %", (char*) p.parent_path().string().c_str());
      global->folderProject = p.parent_path().string();
      global->executing = StateExecuting::RELOAD_PROJECT;

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

std::vector<float*> InterfaceGL::tripletasF;

std::vector<float*> InterfaceGL::globalF;
std::vector<float*> InterfaceGL::globalTripletasF;

ImGuiTableFlags InterfaceGL::flagsTablas0;



