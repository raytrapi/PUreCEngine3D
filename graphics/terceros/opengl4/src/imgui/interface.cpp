#include "./interface.h"

//extern Global global;
//#include "../opengl.h"
void InterfaceGL::init(GLFWwindow* window, ImGuiConfigFlags options){
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
}

void InterfaceGL::render(){
    //const ImGuiViewport* ventana = ImGui::GetMainViewport();

    if (io!=NULL && io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    
    
    /**ImGui::Begin("OpenGL Texture Text");
    ImGui::Text("pointer = %p", idTexturaIconos);
    ImGui::Text("size = %d x %d", 240, 240);
    ImGui::Image((void*)(intptr_t)idTexturaIconos, ImVec2(240, 240),ImVec2(0, 1.0f), ImVec2(24.0f/240.0f, 1.0f-(24.0f / 240.0f)));

    ImGui::End();/**/
    
    
    
    
    /***** STATUS *****/
    ImGuiViewport* viewport = ImGui::GetWindowViewport();
    ImGui::SetNextWindowViewport(viewport->ID);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowMinSize, ImVec2(0, 0));
    ImVec2 menu_bar_pos = viewport->Pos;
    menu_bar_pos.y += viewport->Size.y - 24;
    ImVec2 menu_bar_size = ImVec2(viewport->Size.x, 24);
    ImGui::SetNextWindowPos(menu_bar_pos);
    ImGui::SetNextWindowSize(menu_bar_size);

    ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_MenuBar;
    bool is_open = ImGui::Begin("##Status", NULL, window_flags) && ImGui::BeginMenuBar();
    ImGui::PopStyleVar(2);
    ImGui::Columns(4);
    //Añadimos Frames Por Segundo
	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
    ImGui::NextColumn();
    //ImGui::Text("DT: %f", global->deltaTime);
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
    }/**/
    style.FramePadding = padding; 
    //ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0);
	//Añadimos icono
   // ImGui::ImageButton()
    ImGui::EndMenuBar();
    ImGui::End();



    ImGui::SetNextWindowPos(ImVec2(0, Screen::getHeight() - 150 - 24));
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
    ImGui::End();
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
        if (ImGui::IsWindowDocked) {
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

        if (consoleLog->hasNewLog()) {
            ImGui::SetScrollHereY(1.0f);
            consoleLog->setNewLog(false);
        }
        ImGui::PopStyleVar();
        ImGui::EndChild();
        ImGui::End();


		
			
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
