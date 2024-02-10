#include "opengl.h"





/*#define NK_GLFW_GL4_IMPLEMENTATION
#include "../../../../vendors/glfw/nuklear_glfw_gl4.h"/**/

MotorGL::MotorGL() { 
    //imagen = imagenes::PNG::cargar("h:/desarrollo/motor_videojuegos_2D/recursos/prueba.png");
#ifdef EDITOR
   //Creamos una cámara por defecto
   camaraEditor = new Camera(0,this,0);
   camaraEditor->transform()->setPosition(0, 0,-1.5f);
   camaraEditor->setOrto(false);
   camaraEditor->setFocal(true);
   camaraEditor->setFocalAngle(60*M_GRAD_RAD);
   camaraEditor->setDistance(1.f, 2000.f);
   camaraEditor->setLookAt(0.0f, 0.f, 0.0f, 0.f, 0.f, 100.f, 0.f, 1.f, 0.f);
   camaraEditor->setActive(true);
   camaraEditor->transformChanged();
   changeCamera(camaraEditor);
#endif // EDITOR
   resource = Module::get<modules::resources::Resource>();
}  

MotorGL::~MotorGL() {
    if (gestorLog != NULL) {
        gestorLog==NULL; //La instancia la eliminará el propio control de log
    }
    if (camaraEditor) {
       delete camaraEditor;
    }
}
void MotorGL::preRender(){
   if (!iniciado) {
      return;
   }
    int width, height;
    glfwPollEvents();
    if (widthFrameBuffer) {
        width = widthFrameBuffer;
        height = heightFrameBuffer;
    }else {
        width = Screen::getWidth();
        height = Screen::getHeight();
    }
    //glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   return;

    glfwGetWindowSize(window, &width, &height);
   
    //Screen::setDimension(width, height);/**/
    //Añadimos esto a la zona de renderizado

}
void MotorGL::iniciar() {
   if (withFrameBuffer) {

      glGenFramebuffers(1, &fbo);
      glBindFramebuffer(GL_FRAMEBUFFER, fbo);


      glGenTextures(1, &textureColorBuffer);
      glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthFrameBuffer, heightFrameBuffer, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);

      glGenTextures(1, &textureInterface);
      glBindTexture(GL_TEXTURE_2D, textureInterface);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthFrameBuffer, heightFrameBuffer, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glBindTexture(GL_TEXTURE_2D, 0);
      

      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureColorBuffer, 0);
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
         DBG("ERROR::FRAMEBUFFER:: No se ha podido completar el FrameBuffer");
     
      // Crear un búfer de profundidad
      glGenRenderbuffers(1, &depthBuffer);
      glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, widthFrameBuffer, heightFrameBuffer);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);

      
      glGenRenderbuffers(1, &rbo);
      glBindRenderbuffer(GL_RENDERBUFFER, rbo);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, widthFrameBuffer, heightFrameBuffer);
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
         DBG("ERROR::FRAMEBUFFER:: No se ha podido completar el RenderBurrer");
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
   } 

#ifdef EDITOR
   if (inicializado) {
      glGenFramebuffers(1, &fbo_id);
      glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);


      glGenTextures(1, &texture_id);
      glBindTexture(GL_TEXTURE_2D, texture_id);
      //glTexImage2D(GL_TEXTURE_2D, 0, GL_R32F, widthFrameBuffer, heightFrameBuffer, 0, GL_R32F, GL_UNSIGNED_BYTE, NULL);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthFrameBuffer, heightFrameBuffer, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//TODO: Que pasa en los bordes
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
      glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);
      glBindTexture(GL_TEXTURE_2D, 0);
      /**/
      glGenRenderbuffers(1, &depthBuffer_id);
      glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_id);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, widthFrameBuffer, heightFrameBuffer);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer_id);


      /*glGenRenderbuffers(1, &rbo_id);
      glBindRenderbuffer(GL_RENDERBUFFER, rbo_id);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, widthFrameBuffer, heightFrameBuffer);

      /*glGenRenderbuffers(1, &renderbuffer_id);
      glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);
      glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, widthFrameBuffer, heightFrameBuffer);
      glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT , GL_RENDERBUFFER, renderbuffer_id);
      /**/

      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
   }
#endif
}
int MotorGL::getPixel_id(int x, int y, int channel) {
   unsigned char valor[3] = { 0,0,0 };
   unsigned int ch = GL_RED+channel;
   
   glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
   //glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);
   //glReadBuffer(GL_COLOR_ATTACHMENT0);
   glReadPixels(x, Screen::getHeight()-y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &valor);

   //glBindRenderbuffer(GL_RENDERBUFFER, 0);
   glBindFramebuffer(GL_FRAMEBUFFER, 0);/**/
   //glBindTexture(GL_TEXTURE_2D, texture_id);
   //glReadPixels(x, y, 1, 1, ch, GL_FLOAT, &valor);
   //return valor[0];
   return ((valor[2] << 16) | (valor[1] << 8) | valor[0]);
}
void MotorGL::destruir() {
   if (points != NULL) {
      delete[]points; 
      points = NULL;
   }
   glfwTerminate(); 
   renderable::Object::freeAll();
}
/**
* Se encarga de renderizar cada escena
* 
* @param renderizable elemento a renderizar
*/
void MotorGL::render(void* rederizables) {
  // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   bool conCambioTamaño = false;
   if (withFrameBuffer) {


      glBindFramebuffer(GL_FRAMEBUFFER, fbo);
      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      glReadBuffer(GL_COLOR_ATTACHMENT0);
      glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
      //glClear(GL_DEPTH_BUFFER_BIT);
      if (changeSizeWindow) {
         conCambioTamaño = true;
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthFrameBuffer, heightFrameBuffer, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
         glBindTexture(GL_TEXTURE_2D, textureInterface);
         glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthFrameBuffer, heightFrameBuffer, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
         glBindTexture(GL_TEXTURE_2D, textureColorBuffer);
         glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, widthFrameBuffer, heightFrameBuffer);
         glBindRenderbuffer(GL_RENDERBUFFER, rbo);
         glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, widthFrameBuffer, heightFrameBuffer);
         glViewport(0, 0, widthFrameBuffer, heightFrameBuffer);
      }
   } else {
      if (changeSizeWindow) {
         glViewport(0, 0, Screen::getWidth(), Screen::getHeight());
      }
   }
   if (changeSizeWindow) {
      //changeSizeWindow = false;
      //Hemos de cambiar la camara
      auto mapEntidades = Entity::getAllEntities();
      for (auto m : *mapEntidades) {
         for (auto entidades : (m.second)) {
            for (auto camaras : *(entidades->getComponents<Camera>())) {
               camaras->refresh(2);
            }
            //TODO: Cambiar Interfaz si cambia la ventana
         }
      }
      //auto camaras = entity->getComponents<Camera>();

   }

   /** Preparamos las entidades  **/
   if (isChangeCamera(camaraActual, true)) {
      camaraActual->refresh(3);
      //TODO: Solo hacerlo a las entidades que sea visible o cercanas ya que afectan a la sombra
   }
   //Recorremos todas las pilas de entidades //get all entities from the stack
   auto pilas = Entity::getEntitiesStacks(); 
   for (auto pila : pilas) {
      updateEntities(pila); //TODO: Ver si podemos almacenar los Shaders que contengan la camara para evitar actulizar todas las entidades
   }

   glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
   //glClearColor(0.0, 0, 0, 0);
    //glViewport(0, 0, Screen::getWidth()/2, Screen::getHeight()/2);
   //glViewport(0, 0, widthFrameBuffer/2.f, heightFrameBuffer / 2.f);
   renderFinal(0);
   if (global->executing != StateExecuting::PLAY) {
      //Ahora a por el outline
      glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
      glStencilMask(0x00);
      //glDisable(GL_DEPTH_TEST);
      renderFinal(1); //Carga el outline

      //glStencilMask(0xFF);
      //glStencilFunc(GL_ALWAYS, 1, 0xFF); 
      //glEnable(GL_DEPTH_TEST);
   

      renderFinal(0,false, 1);
   
      //Ahora a por el outline
      glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
      glStencilMask(0x00);
      glDisable(GL_DEPTH_TEST);
      renderFinal(1,false,1); //Carga el outline

      glStencilMask(0xFF);
      glStencilFunc(GL_ALWAYS, 1, 0xFF);
      glEnable(GL_DEPTH_TEST);
   }
   //Pintamos la interfaz de usuario
   {
       renderUserInterface();
   }
   if (withFrameBuffer) {
      if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
         DBG("ERROR::FRAMEBUFFER:: No se ha completado el Framebuffer");
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glBindRenderbuffer(GL_RENDERBUFFER, 0);
      glBindTexture(GL_TEXTURE_2D, 0);
   }
#ifdef EDITOR
    glBindFramebuffer(GL_FRAMEBUFFER, fbo_id);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);
    glReadBuffer(GL_COLOR_ATTACHMENT0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    
    if (conCambioTamaño) {
       conCambioTamaño = false;
       glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthFrameBuffer, heightFrameBuffer, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
       glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer_id);
       glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, widthFrameBuffer, heightFrameBuffer);
       //glBindRenderbuffer(GL_RENDERBUFFER, rbo_id);
       //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, widthFrameBuffer, heightFrameBuffer);
       //glBindRenderbuffer(GL_RENDERBUFFER, renderbuffer_id);
       //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, widthFrameBuffer, heightFrameBuffer);
       //glViewport(0, 0, widthFrameBuffer, heightFrameBuffer);
       
    }
    //TODO: AQUÍ controlar que no estemos jugando
    if (global->executing != StateExecuting::PLAY) {
       glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
       renderFinal(2, true); //Carga el mapa de ID
       
    } 
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
#endif
    changeSizeWindow = false;
 
}

void MotorGL::renderInterface(){
    if (interfaz != NULL) { 
        interfaz->render();
    }
}

void MotorGL::refresh(int mode){
   if (mode & 1) {
      //DBG("Modo Shader");
      processShader();
   }
}

void MotorGL::postRender(bool sawp){
   if (!iniciado) {
      return;
   }
   //return;
   if (sawp) {
      try {
         glfwSwapBuffers(window);
      } catch(...){
         ERR("Error en el SWAP de Buffer (opengl.cpp)");
      }
   }
    // update other events like input handling 
    glfwPollEvents();
    if (glfwWindowShouldClose(window)) {
        setEnd();
    }
   
}
/*
* glGenTextures(1, &dev->font_tex);
    glBindTexture(GL_TEXTURE_2D, dev->font_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, (GLsizei)width, (GLsizei)height, 0,
                GL_RGBA, GL_UNSIGNED_BYTE, image);
*/
void MotorGL::renderizarImagen(renderable::Img* img) {
    

}

void MotorGL::renderizarCubo(renderable::Cube * cubo) {
    
}
void MotorGL::render() { 
   //glViewport(0, 0, ancho, alto);
   render(0);
}

void MotorGL::renderFinal(unsigned int idShader, bool modeId, int pass){
#ifdef EDITOR
   
#endif // EDITOR

      
      for (auto itr = misEntidades.begin(); itr != misEntidades.end(); itr++) {
         if (itr->first->isActive()) {
#ifdef EDITOR
            if (idShader == 1 || pass==1){
               if(!itr->first->isSelected() || global->executing == StateExecuting::PLAY) {
                  continue;
               } /*else {
                  //glStencilMask(0xFF);
                  glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
                  glStencilMask(0x00);
                  glDisable(GL_DEPTH_TEST);
                  
               }/**/
            }
#endif // EDITOR

            
            
            GLuint vao = *(itr->second->getVAO());
#ifdef EDITOR
            if (modeId) {
               vao = *(itr->second->getVAO_id());
            }
#endif // EDITOR
            GLuint ebo = *(itr->second->getEBO());

            if (idShader == 0) {
               /* Activamos los shaders*/
               if(global->showGizmoCollider){
                  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                  auto colliders = itr->first->getComponents<Collider>();
                  for (auto collider : *colliders) {
                     glUseProgram(collider->getShaderProgram());
                     renderObject(vao, ebo, itr->second->getMode(), itr->second->getVertextCount(), collider->getShaderProgram());
                  }
                  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
               }

            }

            //COGEMOS EL ID_PROGRAM PARA EL SHADER
            unsigned int ps = 0;
            auto shaders = itr->first->getComponent<graphics::ShaderComponent>();
            if (shaders == 0) {
               continue;
            }
            switch (idShader) {
               case 0:
                  ps = shaders->getMaterial();
                  break;
               case 1:
                  
                  ps = shaders->getOutline();
  
                  break;
               case 2:
                  ps = shaders->getClicking();
                  break;
               default:
                  break;
            }
            if (ps == 0) {
               continue;
            }
            glUseProgram(ps);
            switch (idShader) {
               case 1:
               {
                  float* color = new float[4] {0.83f, 0.36f, 0.003f, 0.9f};
                  if (pass == 1) {
                     //color[0] = 1.0f;
                     color[3] = 0.09f;
                  }
                  GLuint c = glGetUniformLocation(ps, "color");
                  if (c != GL_INVALID_INDEX) {
                     glUniform4f(c, color[0], color[1], color[2], color[3]);
                  }
                  delete[] color;
               }
               break;
            }
            if (idShader == 0) {
                auto r = itr->first->getComponent<RenderableComponent>();
                int numText = GL_TEXTURE0;
                //int idImagenLoc = 0;
                if (r) {
                    auto ms = r->getMaterials();
                    for (auto m : ms) {

                        if (m && m->getIdTexture() > 0) {
                            glActiveTexture(numText++);
                            unsigned int idTexturaActual = m->getIdTexture();
                            glBindTexture(GL_TEXTURE_2D, m->getIdTexture());
                            //glActiveTexture(numText+1);
                            //glBindTexture(GL_TEXTURE_2D, m->getIdTexture());
                            //glUniform1i(glGetUniformLocation(idShader, ("textura[" + std::to_string(idImagenLoc) + "]").c_str()), idImagenLoc);
                            //idImagenLoc++;
                        }
                    }
                }

                /*if (numText == GL_TEXTURE0) {
                   glActiveTexture(numText++);
                   glBindTexture(GL_TEXTURE_2D, 0);
                   numText++;
                }/**/
                //Añadimos las sombras
                //De momento de la primera Luz
                //TODO: ESTO MEJOR HACERLO FUERA
                auto luces = Entity::getAllGlobalComponents<LightComponent>();
                //Buscamos la primera luz visible
                LightComponent* luz = NULL; 
                for (auto l : luces) {
                   if (l->isActive()) {
                      luz = l;
                      break;
                   }
                } 
                if (luz) {
                   //Tengo luz
                   glActiveTexture(GL_TEXTURE6);
                   glBindTexture(GL_TEXTURE_2D, luz->getTexture());
                }
                /* ightComponent* luz = entity->getComponent<LightComponent>("LUZ");
                if (luz) {
                    glActiveTexture(numText++);
                    glBindTexture(GL_TEXTURE_2D, luz->getTexture());
                } /**/

            }


            renderObject(vao, ebo, itr->second->getMode(), itr->second->getVertextCount(),ps);
            
            /*if (idShader == 2) {
               glStencilMask(0xFF);
               glStencilFunc(GL_ALWAYS, 0, 0xFF);
               glEnable(GL_DEPTH_TEST);
            }/**/
         }
      }
      
}

void MotorGL::renderUserInterface(){
    //recuperamos los componentes de interfaz;
    /*glBindTexture(GL_TEXTURE_2D, textureInterface);
    glClearColor(0.00f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);*/
    glDisable(GL_DEPTH_TEST);
    auto interfaces = Entity::getAllGlobalComponents<InterfaceComponent>(true);
    for (auto interfaz : interfaces) {
        if (interfaz) {
            auto ps = interfaz->getShaderProgram();
            if (ps != 0) {
                glUseProgram(ps);
                auto idTextura = interfaz->getIdTexture();
                if (idTextura != 0) {
                    glActiveTexture(GL_TEXTURE0);
                    glBindTexture(GL_TEXTURE_2D, idTextura);
                }
                auto vao = interfaz->getVAO();
                if (vao != 0) {
                    glBindVertexArray(vao);
                    glDrawArrays(GL_TRIANGLE_FAN, 0, 4); //glDrawElements(GL_TRIANGLE_FAN, 2, GL_UNSIGNED_INT, 0);
                }
            }
        }
    }
    glEnable(GL_DEPTH_TEST);
    

    /*
    for (auto entidadesStack : *Entity::getAllEntities()) {
        for (auto entidad : entidadesStack.second) {
            //TODO: Mejorar esto haciendo que la entidad tenga el tipo del primer componte
            auto interfaz = entidad->getComponent<InterfaceComponent>();
            if (interfaz) {
                auto shaders= entidad->getComponent<graphics::ShaderComponent>();
                if (shaders) {
                    auto idS=shaders->getMaterial();
                    glUseProgram(idS);
                    auto render=entidad->
                }

            }
        }
    }


    for (auto itr = misEntidades.begin(); itr != misEntidades.end(); itr++) {
        if (itr->first->isActive()) {
#ifdef EDITOR
            if (idShader == 1 || pass == 1) {
                if (!itr->first->isSelected() || global->executing == StateExecuting::PLAY) {
                    continue;
                }
            }
#endif // EDITOR



            GLuint vao = *(itr->second->getVAO());
#ifdef EDITOR
            if (modeId) {
                vao = *(itr->second->getVAO_id());
            }
#endif // EDITOR
            GLuint ebo = *(itr->second->getEBO());

            if (idShader == 0) {
          
                if (global->showGizmoCollider) {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                    auto colliders = itr->first->getComponents<Collider>();
                    for (auto collider : *colliders) {
                        glUseProgram(collider->getShaderProgram());
                        renderObject(vao, ebo, itr->second->getMode(), itr->second->getVertextCount(), collider->getShaderProgram());
                    }
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }

            }

            //COGEMOS EL ID_PROGRAM PARA EL SHADER
            unsigned int ps = 0;
            auto shaders = itr->first->getComponent<graphics::ShaderComponent>();
            if (shaders == 0) {
                continue;
            }
            switch (idShader) {
            case 0:
                ps = shaders->getMaterial();
                break;
            case 1:

                ps = shaders->getOutline();

                break;
            case 2:
                ps = shaders->getClicking();
                break;
            default:
                break;
            }
            if (ps == 0) {
                continue;
            }
            glUseProgram(ps);
            switch (idShader) {
            case 1:
            {
                float* color = new float[4] {0.83f, 0.36f, 0.003f, 0.9f};
                if (pass == 1) {
                    //color[0] = 1.0f;
                    color[3] = 0.09f;
                }
                GLuint c = glGetUniformLocation(ps, "color");
                if (c != GL_INVALID_INDEX) {
                    glUniform4f(c, color[0], color[1], color[2], color[3]);
                }
                delete[] color;
            }
            break;
            }
            if (idShader == 0) {
                auto r = itr->first->getComponent<RenderableComponent>();
                int numText = GL_TEXTURE0;
                //int idImagenLoc = 0;
                if (r) {
                    auto ms = r->getMaterials();
                    for (auto m : ms) {

                        if (m && m->getIdTexture() > 0) {
                            glActiveTexture(numText++);
                            unsigned int idTexturaActual = m->getIdTexture();
                            glBindTexture(GL_TEXTURE_2D, m->getIdTexture());
                            
                        }
                    }
                }

                //Añadimos las sombras
                //De momento de la primera Luz
                //TODO: ESTO MEJOR HACERLO FUERA
                auto luces = Entity::getAllGlobalComponents<LightComponent>();
                //Buscamos la primera luz visible
                LightComponent* luz = NULL;
                for (auto l : luces) {
                    if (l->isActive()) {
                        luz = l;
                        break;
                    }
                }
                if (luz) {
                    //Tengo luz
                    glActiveTexture(GL_TEXTURE6);
                    glBindTexture(GL_TEXTURE_2D, luz->getTexture());
                }
                

            }


            renderObject(vao, ebo, itr->second->getMode(), itr->second->getVertextCount(), ps);

            
        }
    }/**/
}

void MotorGL::renderObject(unsigned int vao, unsigned int ebo, unsigned int mode, unsigned int numVertex, unsigned int ps){
    if (vao == 0) {
        return;
    }
   glBindVertexArray(vao);
    
   switch (mode) {

      case GL_TRIANGLE_STRIP:
      {
         //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(itr->second->getEBO()));
         glDrawElements(GL_TRIANGLES, numVertex, GL_UNSIGNED_INT, 0);
         //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
      }
      break;
      default:
         if (ebo == 0) {
            glDrawArrays(mode, 0, numVertex);
         } else {
            glDrawElements(mode, numVertex, GL_UNSIGNED_INT, 0);
         }
         break;
   }/**/
#ifdef EDITOR
   if (glGetError() != GL_NO_ERROR) {
      EntityGL4::checkCompileErrors(ps, "PROGRAM");
      EntityGL4::checkCompileErrors(ps, "PROGRAM3");
   
   }
#endif

   glBindVertexArray(0);
}


void MotorGL::inicializarLuz() {
    
}
void MotorGL::ponerCamara(float posX, float posY, float posZ, float targetX, float targetY, float targetZ) {
   
}
/**
* Método para acutalizar los VAO (Array de Vertices),.....
* 
* @param entity Entidad que contendrá la información necasaria para la renderización
*/
void MotorGL::updateEntity(void* entity, TYPE_OPERATION type) {
   
   auto itr = misEntidades.find((Entity*)entity);
   EntityGL4* entidad = NULL;
   if (itr != misEntidades.end()) { //Si existe la borramos
      entidad = misEntidades[(Entity*)entity];
      
   }
   //TODO: OJO, Esto podríamos mejorarlo mucho si en vez de obtener los componentes sabemos que tipo es
   
   auto renderables = ((Entity*)entity)->getComponents<RenderableComponent>();
   if (renderables != NULL) {
      for (auto itrR = renderables->begin(); itrR != renderables->end(); itrR++) {
         RenderableComponent* r = (RenderableComponent*)(*itrR);
         if (r && r->isActive() && r->getRenderable()) {
            switch (r->getRenderable()->getType()) {
               case renderable::Object::TYPE::LINE:
                  updateEntityLINE(r, entidad, (Entity*)entity, type);
                  break;
               case renderable::Object::TYPE::IMG: //Es una IMAGEN
                  updateEntityIMG(r, entidad, (Entity*)entity, type);
                  break;
               case renderable::Object::TYPE::CUBE:
                  //updateEntityCUBE(r, entidad, (Entity*)entity, type);
                  updateEntityMESH(r, entidad, (Entity*)entity, type);
                  break; 
               case renderable::Object::TYPE::MESH:
                  updateEntityMESH(r, entidad, (Entity*)entity, type);
                  break;
               case renderable::Object::TYPE::TEXT:
                  updateEntityTEXT(r, entidad, (Entity*)entity, type);
                  break;
                  
            }
            /*if (((Entity*)entity)->has<graphics::Shader>()) {
                graphics::Shader* shader = ((Entity*)entity)->getComponent<graphics::Shader>();
               if (!shader->isCompiled()) {
                  itr = misEntidades.find((Entity*)entity);
                  if (itr != misEntidades.end()) {
                     entidad = misEntidades[(Entity*)entity];
                  }
                  if (entidad!=NULL) {
                     int idComp = shader->compileShader();
                     entidad->addShaderProgram(idComp);
                  }
               }
            }/**/
         }

      }
   }
   //Ahora procesamos las luces
   auto luces = ((Entity*)entity)->getComponents<LightComponent>();
   if (luces != NULL) {
      //Como soy luz, me actualizo
      for (auto itrR = luces->begin(); itrR != luces->end(); itrR++) {
         LightComponent* r = (LightComponent*)(*itrR);
         if (r && r->isActive()) {
            updateEntityGIZMOLIGTH(r, entidad, (Entity*)entity, type);
         }
      }
   }
   
   if (((Entity*)entity)->has<graphics::ShaderComponent>()) {
      graphics::ShaderComponent* shader = ((Entity*)entity)->getComponent<graphics::ShaderComponent>();
      if (!shader->isCompiled()) {
         itr = misEntidades.find((Entity*)entity);
         if (itr != misEntidades.end()) {
            entidad = misEntidades[(Entity*)entity];
         }
         if (entidad != NULL) {
            int idComp = shader->compileShader();
            entidad->addShaderProgram(idComp);
         }
      }
   }

}

/**
* Borra una entidad del sistema
* 
*/
void MotorGL::removeEntity(void* entity) {
   
   auto entidades = Entity::getAllEntities();
   //for (auto entidad: *entidades) {
   for(auto itrM=entidades->begin();itrM!=entidades->end();itrM++){

      std::vector<Entity*> *entities = &entidades->operator[](itrM->first);//Entity::getEntities(0);
      for (auto itr = entities->begin(); itr != entities->end(); itr++) {
         if (entity == (*itr)) {
            auto itrEntidadGL4 = misEntidades.find((Entity*)entity);
            if (itrEntidadGL4 != misEntidades.end()) {
               clearEntity((*itrEntidadGL4).second);
               delete (*itrEntidadGL4).second;
               misEntidades.erase(itrEntidadGL4);
            }
            //delete ((Entity*)*itr);
            //(*itr)->remove();
            entities->erase(itr);

            return;
         }
      }
   }
}
/**
* Libera todo lo reservado de esta entidad
*/
void MotorGL::clearEntity(EntityGL4 * entidad) {
   entidad->clear();
}
void MotorGL::removeEntities() {
   std::vector<Entity*> entities = Entity::getEntities(0);
   auto itr = entities.begin();
   while(itr != entities.end()) {
         //GLuint* vao = ((Entity*)(*itr))->getVAO();
         //TODO: REVISAR ESTO QUE SEGURAMENTE ESTÁ MAL Y ADEMÁS FALTARÍAN EL EBO, Texts, Frames...
      EntityGL4* egl4 = misEntidades[((Entity*)(*itr))];
      if (egl4) {
         GLuint* vbo = egl4->getVBO();
         if (vbo !=NULL) {
            glDeleteBuffers(1, vbo);
         }
         GLuint* vao = egl4->getVAO();
         if (vbo != NULL) {
            glDeleteVertexArrays(1, vao);
         }
         delete egl4;
      }
      ////misEntidades.erase((Entity*)(*itr));
      //delete ((Entity*)*itr);
      ////itr = entities.begin();
      itr++;
   }
   misEntidades.clear();
   entities.clear();
}
void MotorGL::removeAll() {
   camaraActual = camaraEditor;
   removeEntities();
   removeAllFocus();
}
/*void MotorGL::newEntity(TYPE_ENTITY type, renderable::Object* object) {
    //vaos.push_back(Entity(type)GLuint(0));
    
    switch (type) {
    case modules::graphics::Graphic::IMG:
       
        
        entidades.push_back(Entity(GL_TRIANGLE_FAN,object));
        int idx = entidades.size() - 1;
        GLuint* vao=entidades[idx].getVAO();
        
        float points[] = {
            -0.8f,  -0.8f,  0.0f,
            -0.8f,   0.8f,  0.0f,
             0.8f,   0.8f,  0.0f,
             0.8f,  -0.8f,  0.0f
        };
        
        GLuint vbo = 0;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), points, GL_STATIC_DRAW);

        glGenVertexArrays(1, vao);
        
        entidades[idx].setVertextCount(4); //TODO: El número de vertices se obtendrá de la propia maya del objeto.
        glBindVertexArray(*vao);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        //glDisableVertexAttribArray(0);

        break;
    //case modulos::graficos::Grafico::MESH:
    //    break;
    }

    //glEnableVertexAttribArray(0);
}/**/




bool MotorGL::inicializar(void* hwnd, double ancho, double alto) {
    
    if (!glfwInit()) {
        //fprintf(stderr, "Error al inicializar GLFW\n");
        return false;
    }
    iniciado = true;
    /*glfwWindowHint(GLFW_SAMPLES, 4);   
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); */

    window = glfwCreateWindow(ancho, alto, "PureC3d", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    if (!window) {
        glfwTerminate();
        return false;
    }
    open = true;
    glfwSetWindowCloseCallback(window, closeWindow);
    glfwSetKeyCallback(window, key_callback);

    glfwSetMouseButtonCallback(window, mouseButtom_callback);
    glfwSetCursorPosCallback(window, mouseMove_callback);
    //glfwSetCursorEnterCallback(window, cursor_enter_callback);
    //glfwSetScrollCallback(window, scroll_callback);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetWindowPosCallback(window, windowsMove_callback);

    glfwSetWindowFocusCallback(window, focus);
    //glfwSetWindowAspectRatio(window, 1, 1); //Podemos indicarle la relación de tamaño de ventana por ejempo 4:3 o 16:9
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string

    interfaz = new InterfaceGL();
    interfaz->setGlobal(global);
    interfaz->setGraphic(this);

    ((InterfaceGL*)interfaz)->init(window, ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable); // 
    

    /*IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

    
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
    consolaLog = new LogOpenGL(false);
    setLog((utiles::Log*)consolaLog);/**/
	
    //Vamos a trucar temporalemente el tema de las fuentes
    /*nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();*/



    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    //glEnable(GL_DEPTH_TEST); // enable depth-testing
    //glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glEnable(GL_MULTISAMPLE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    //glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    //glShadeModel(GL_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      
    //Marcado de objetos
    //glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    //glStencilMask(0x00); // make sure we don't update the stencil buffer while drawing the floor
    

    




    //Activamos la sincronización vertical
    glfwSwapInterval(0);
    //Creamos el contexto
    /*ctx = nk_glfw3_init(window, NK_GLFW3_INSTALL_CALLBACKS, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
    nk_glfw3_font_stash_begin(&atlas);
    nk_glfw3_font_stash_end();/**/
	
    
    if (((InterfaceGL*)interfaz)->getConsoleLog() != NULL) {
        setLog((utiles::Log*)((InterfaceGL*)interfaz)->getConsoleLog());
    }
    inicializado = true;
    return true;
}
void MotorGL::setMousePosition(float x, float y){
   glfwSetCursorPos(window, x, y);

}
std::tuple<unsigned int,int, int,TextureImg::FORMAT_COLOR> MotorGL::loadTexture(std::string path, TYPE_TEXTURE type, TYPE_REPEAT repeat){
    GLuint texturaId=0;
    TextureImg::FORMAT_COLOR formato; 
    int ancho=0;
    int alto=0;
    if (resource) {
        glGenTextures(1, &texturaId);
        float* miTextura;
        int longitud;
        std::tie(miTextura, ancho, alto, longitud, formato) = resource->loadImage(path.c_str());
        //ERR("el pixel es %", miTextura[404]);
        glBindTexture(GL_TEXTURE_2D, texturaId);
        auto rep = GL_CLAMP;
        switch (repeat){
            case REPEAT:
                rep= GL_REPEAT;
                break;
        
        }
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, rep);// GL_CLAMP, GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, rep);//GL_REPEAT
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); //GL_NEAREST,GL_LINEAR 
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ancho, alto, 0, GL_RGBA, GL_FLOAT, miTextura);
        delete[]miTextura;
    }
    return {texturaId,ancho,alto,formato};
}
void MotorGL::generateRectangleInterface(float* data, unsigned int* vao, unsigned int* vbo, unsigned int* ebo){
    if (*vao == 0) {
        glGenVertexArrays(1, vao);
    }
    if (*vbo == 0) {
        glGenBuffers(1, vbo);
    }
    if (*ebo == 0) {
        glGenBuffers(1, ebo);
    }

    glBindVertexArray(*vao);

    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    
    glBufferData(GL_ARRAY_BUFFER, 20 * sizeof(float), data, GL_STATIC_DRAW);
    int parametros = 5;
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(3 * sizeof(float)));
    

}

const byte* MotorGL::loadShader(const char* path) {
    std::string texto=""; 
    std::ifstream textoStream(path, std::ios::in);
    if (textoStream.is_open()) {
        std::stringstream sstr;
        sstr << textoStream.rdbuf();
        texto = sstr.str();
        textoStream.close();
    } else {
       ERR("No se ha encontrado el shader \"%\"", path);
       //debug("No se ha podido abrir el fichero");
       return 0;
    }
    const char *c= texto.c_str();
    int lengthString = strlen(c) + 1;
    byte* textUTF8 = new byte[lengthString];
    for (int i = 0; i < lengthString; i++) {
        textUTF8[i] = (byte)c[i];
    }
    return (const byte*)textUTF8;
}/**/

unsigned int MotorGL::loadShader(const char* path, Graphics::Shader::TYPE_SHADER type) {

   //Buscamos si ya está el shader compilado
    GLuint s = obtenerShader(path);
    if (s != 0) {
       return s;
    }
    const char* data = (const char*)loadShader(path);
    std::string tipoShader = "GEOMETRY";
    if (data != 0) {
      switch (type) { 
      case Graphics::Shader::TYPE_SHADER::VERTEX:
         s = glCreateShader(GL_VERTEX_SHADER);
         if (s == 0) {
            DBG("Se ha producido un error al crear el Shader de tipo GL_VERTEX_SHADER para la ruta [%]",path);
         }
         tipoShader = "VERTEX";
         break;
      case Graphics::Shader::TYPE_SHADER::FRAGMENT:
         s = glCreateShader(GL_FRAGMENT_SHADER);
         if (s == 0) {
            DBG("Se ha producido un error al crear el Shader de tipo GL_FRAGMENT_SHADER para la ruta [%]", path);
         }
         tipoShader = "FRAGMENT";
         break;
      }
      glShaderSource(s, 1, &data, NULL);
      glCompileShader(s);
      EntityGL4::checkCompileErrors(s, tipoShader);
      //object->addShader(s, type, data, strlen(data) + 1);
    }
    if (data) {
        delete[] data;
    }
    std::string cadena(path);
    if (s != 0) {
       //shadersCompilados.push_back({ cadena,s });
    }
    return (int)s;
}
GLuint MotorGL::obtenerShader(const char* ruta){
   for (auto s : shadersCompilados) {
      if(std::get<0>(s)==std::string(ruta)){
         return std::get<1>(s);
      }
   }
   return 0;
}
GLuint MotorGL::obtenerShaderProgram(std::vector < GLuint> shaders) {
   for (auto ps : shadersProgramsCompilados) {
      //Averiguamos si ya tenemos un shader
      bool esValido = true;
      if (std::get<0>(ps).size() == shaders.size()) {
         auto itr = std::get<0>(ps).begin();
         while (esValido && itr != std::get<0>(ps).end()) {
            bool noEsta = true;
            auto itr2 = shaders.begin();
            while(noEsta && itr2!=shaders.end()){
               noEsta = *itr != *itr2;
               itr2++;
            }
            itr++;
            esValido = !noEsta;
         }
         if (esValido) {
            return std::get<1>(ps);
         }
      }
   }
   return 0;
}

void MotorGL::reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type, unsigned int id, unsigned int idProgram) {

   
   const char* data = (const char*)loadShader(path);
   
   //GLuint s = 0;
   if (data != 0) {
      glShaderSource(id, 1, &data, NULL);
      glCompileShader(id);

      //glDetachShader(idProgram,id);
      //glAttachShader(idProgram, id);
      glLinkProgram(idProgram);
      EntityGL4::checkCompileErrors(idProgram, "PROGRAM");
      //object->addShader(s, type, data, strlen(data) + 1);
   }
   if (data) {
      delete[] data;
   }
}
unsigned int MotorGL::compileShader(std::vector<unsigned int>* ids) {
   //Cambiar esto. Los objetos que utilizan distintos valores para el uniform no deberían compatir
   //GLuint ps = obtenerShaderProgram(*ids);
   GLuint ps = 0;
   if (ps == 0) {
      ps = glCreateProgram();
      GLuint temporal = 0;
      for (auto itr = ids->begin(); itr != ids->end(); itr++) {
         glAttachShader(ps, *itr);
      }
      glLinkProgram(ps);
      shadersProgramsCompilados.push_back({ *ids,ps });
      //DBG("Shader compilado %", ps);
   }
   return ps;
}


unsigned int MotorGL::compileShader(unsigned int ps) {
    /*int longitud = object->getShaders()->size();
    GLuint temporal = 0;
    if (longitud > 0) {
        for (int i = 0; i < longitud; i++) {
            glAttachShader(ps, object->getShaders()->operator[](i)->getId());
        }
        glLinkProgram(ps);
        object->addShader(ps, renderable::Shader::TYPE::COMPILE);
    }
    */
    glLinkProgram(ps);
    
    return ps;
}
unsigned int MotorGL::compileShader(std::vector<unsigned int>* shadersId, void* entity) {
   unsigned int id= compileShader(shadersId);
   /*bool noEncontre = true;
   for (auto itr = misEntidades.begin(); itr != misEntidades.end() && noEncontre; itr++) {
      if (itr->first == entity) {
         itr->second->addShaderProgram(id);
         noEncontre = false;
      }
   }*/
   /*if (noEncontre) {
      EntityGL4* egl4 = new EntityGL4();
      egl4->addShaderProgram(id);
      misEntidades[(Entity*)entity] = egl4;
   }/**/
   return id;
}
unsigned int MotorGL::compileShader(unsigned int ps, void* entity) {
   int id = compileShader(ps);
   return id;
}
void MotorGL::removeShader(unsigned int idProgram, std::vector<unsigned int>* ids){
   glDeleteProgram(idProgram);
   for (auto id : *ids) {
      glDeleteShader(id);
   }
}
void MotorGL::changeCamera(Camera* camera) {
   if (camaraActual != 0) {
      camaraActual->setActive(false);
   }
   camaraActual = camera;
   resizeCamera();
}
void MotorGL::resizeCamera() {
   //TODO: Calculamos la matriz de transformación
   if (camaraActual) {
      /*float centroAnchoVentana=((float)Screen::getWidth()) * 0.5f;
      float centroAltoVentana = ((float)Screen::getHeight()) * 0.5f;*/

      //float centroAnchoCamara = ((float)camaraActual->getWidth()) * 0.5f;
      //float centroAltoCamara = ((float)camaraActual->getHeight()) * 0.5f;
      //glViewport(centroAnchoVentana-centroAnchoCamara, centroAltoVentana-centroAltoCamara, centroAnchoVentana + centroAnchoCamara, centroAltoVentana + centroAltoCamara);
      //glViewport(0, 0, ((float)Screen::getWidth()), ((float)Screen::getHeight()));
      //glViewport(camaraActual->getLeft(), camaraActual->getBottom(), camaraActual->getRight()- camaraActual->getLeft(), camaraActual->getBottom()- camaraActual->getTop());
   }
}

bool MotorGL::addTexture(float* image, unsigned int length,int width, int height, unsigned int& idTexture, TextureImg::FORMAT_COLOR typeColor, TYPE_REPEAT repeat, TYPE_FILTERING nearest) {
   if (idTexture == -1 || idTexture==0) {
      glGenTextures(1, (unsigned*)&idTexture);
   }

   auto modoRepetir = GL_REPEAT;
   switch (repeat){
      case modules::graphics::Graphic::CLAMP:
         modoRepetir = GL_CLAMP;
        break;
   }
   auto modoTextura = GL_NEAREST;
   switch (nearest) {
      case modules::graphics::Graphic::LINEAR:
         modoTextura = GL_LINEAR;
         break;
   }
   glBindTexture(GL_TEXTURE_2D, idTexture);
   int formatoColor;
   switch (typeColor) {
   case TextureImg::DEPTH:
      formatoColor = GL_DEPTH;
      break;
   case TextureImg::DEPTH_STENCIL:
      formatoColor = GL_DEPTH_STENCIL;
      break;
   case TextureImg::RED:
      formatoColor = GL_RED;
      break;
   case TextureImg::RG:
      formatoColor = GL_RG;
      break;
   case TextureImg::RGB:
      formatoColor = GL_RGB;
      break;
   case TextureImg::RGBA:
      formatoColor = GL_RGBA;
      break;
   }
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, modoRepetir); 
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, modoRepetir);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, modoTextura); //GL_NEAREST,GL_LINEAR 
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, modoTextura);

   glTexImage2D(GL_TEXTURE_2D, 0, formatoColor, width, height, 0, formatoColor, GL_FLOAT, image);
   //glBindFramebuffer(GL_FRAMEBUFFER, 0);
   
   return true; 
}

void MotorGL::closeWindow(GLFWwindow* window) {
   open = false;
}
/*void MotorGL::renderNewViewPort(std::vector<Entity*> entidades, float x, float y, float width, float height) {
   //glViewport(x, y, width, height);
   return;
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
   glActiveTexture(GL_TEXTURE0);
   glBindTexture(GL_TEXTURE_2D, 1);
   
   for (auto entidad: entidades) {
      if (entidad->isActive()) {
         /*std::vector<GLuint>* texts = entidad->getTexts();
         int numText = GL_TEXTURE0;
         for (auto itrT = texts->begin(); itrT != texts->end(); itrT++) {
            glActiveTexture(numText++);
            glBindTexture(GL_TEXTURE_2D, *itrT);
         }

         auto comp = itr->second->getShadersPrograms();
         auto itrC = comp->begin();
         int shadersCompiledCount = itr->second->getShadersPrograms()->size();
         for (int j = 0; j < shadersCompiledCount; j++) {
            short int ps = itr->second->getShadersPrograms()->operator[](j);
            glUseProgram(ps);
         }

         GLuint vao = *(itr->second->getVAO());
         glBindVertexArray(vao);

         glDrawArrays(GL_TRIANGLES, 0, itr->second->getVertextCount()); / * * /
         
      }
   }
   glfwSwapBuffers(window);
   glfwPollEvents();
   if (glfwWindowShouldClose(window)) {
      setEnd();
   }

}/**/
Entity* MotorGL::drawLine(float *vertex, unsigned countVertex, float r, float g, float b, float a, unsigned width) {
   Entity* eLinea = Entity::create<Entity::TYPE::EMPTY>();
   eLinea->setName("Linea");
   float color[4]={ r,g,b,a };
   renderable::Line* linea = new renderable::Line(vertex, countVertex, (float *)&color ,width);
   RenderableComponent * rend=eLinea->addComponent<RenderableComponent>();
   //rend->setUpdated(true);
   rend->add<renderable::Line>(linea);
   //linea->setChange(true);
   eLinea->setUpdatingRender(true);
   return eLinea;
   
}
Entity* MotorGL::drawLineLoop(float* vertex, unsigned countVertex, float r, float g, float b, float a, unsigned width) {
   Entity* eLinea = Entity::create<Entity::TYPE::EMPTY>();
   eLinea->setName("Linea Loop");
   float color[4] = { b,g,r,a };
   renderable::Line* linea = new renderable::Line(vertex, countVertex, (float*)&color, width,2);
   RenderableComponent* rend = eLinea->addComponent<RenderableComponent>();
   rend->add<renderable::Line>(linea);
   eLinea->setUpdatingRender(true);
   return eLinea;
}



void MotorGL::getFrameBuffer(unsigned int* id){
   glGenFramebuffers(1, id);
}
void MotorGL::generateTexture2D(unsigned int* id, const unsigned int width, const unsigned int height, TYPE_TEXTURE2D formatTexture) {
   unsigned int f = 0;
   switch (formatTexture){
      case TEXT_DEPTH_COMPONENT:
         f = GL_DEPTH_COMPONENT;
         break;
      case TEXT_RGB:
         f = GL_RGB;
         break;
      case TEXT_RGBA:
         f = GL_RGBA;
         break;
      default:
         break;
   }
   glGenTextures(1, id);
   glBindTexture(GL_TEXTURE_2D, *id);
   glTexImage2D(GL_TEXTURE_2D, 0, f,
      width, height, 0, f, GL_FLOAT, NULL);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glBindTexture(GL_TEXTURE_2D, 0);


}
void MotorGL::generateTexture2DWithFBO(unsigned int* id, const unsigned int width, const unsigned int height, unsigned int depthFBO, TYPE_TEXTURE2D formatTexture, TYPE_FRAMEBUFER formatFB) {
   generateTexture2D(id, width, height,formatTexture);
   switch (formatFB){
      case FB_FRAMEBUFFER:
         glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
         glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, *id, 0);
         glDrawBuffer(GL_NONE);
         glReadBuffer(GL_NONE);
         glBindFramebuffer(GL_FRAMEBUFFER, 0);
         break;
      case FB_RENDERBUFFER:
         glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
         glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *id, 0);
         //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
         //f = GL_RENDERBUFFER;
         break;
      default:
         break;
   }
   


   

}
void MotorGL::renderShadowMap(LightComponent* ligth, unsigned int& depthFBO, unsigned int& depthTexture2D, const unsigned int widthTexture2D, const unsigned int heightTexture2D, TYPE_SHADOW_MAP type){
   
   glViewport(0, 0, widthTexture2D, heightTexture2D);
   glBindFramebuffer(GL_FRAMEBUFFER, depthFBO);
   glDrawBuffer(GL_COLOR_ATTACHMENT0);
   glReadBuffer(GL_COLOR_ATTACHMENT0);
   glBindTexture(GL_TEXTURE_2D, depthTexture2D);
   glClear(GL_DEPTH_BUFFER_BIT);
   
   //Movemos la 
   //  a la posición de la luz
   //auto [cx, cy, cz] = camaraActual->getPosition();
   //auto [cex, cey, cez] = camaraActual->getEye();

   //Cargarmos los datos por cada punto de luz
   for (auto entidad : misEntidades) {
      if (entidad.first->active) {

         auto renderables = entidad.first->getComponents<RenderableComponent>();
         if (renderables != NULL) {
            for (auto itrR = renderables->begin(); itrR != renderables->end(); itrR++) {
               RenderableComponent* r = (RenderableComponent*)(*itrR);
               if (r && r->isActive() && r->getRenderable()) {
                  //Le pasamos datos
                  //Buscamos el prgrama
                  auto comp = entidad.second->getShadersPrograms();
                  if (comp->size() > 1) {
                     GLuint* vao = entidad.second->getVAO();
                     GLuint* vbo = entidad.second->getVBO();
                     //GLuint* ebo = entidad->getEBO();

                     glBindVertexArray(*vao);
                     glBindBuffer(GL_ARRAY_BUFFER, *vbo);
                     auto idPrograma = comp->operator[](1);
                     glUseProgram(idPrograma);

                     processViewProjectionShader(idPrograma, ligth->getViewMatrix(), ligth->getProjectMatrix(), r->matrixTrans());
                     
                     unsigned int modelLoc = glGetUniformLocation(idPrograma, "lightSpaceMatrix");
                     if (modelLoc != -1) {
                        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, ligth->getViewProjectMatrix());
                     }
                  }
               }
            }
         } 
      } 
   }
   
   glCullFace(GL_FRONT);
   renderFinal(1);
   glCullFace(GL_BACK);
   
   glBindFramebuffer(GL_FRAMEBUFFER, 0);
   glUseProgram(0);/**/
 
   //Solo si estamos en modo depuración y editor

   {
      glBindFramebuffer(GL_FRAMEBUFFER, ligth->profundidadFBO_DBG);
      glDrawBuffer(GL_COLOR_ATTACHMENT0);
      glReadBuffer(GL_COLOR_ATTACHMENT0);
      glBindTexture(GL_TEXTURE_2D, ligth->profundidadTextura2D_DBG);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      glActiveTexture(GL_TEXTURE0);
      glBindTexture(GL_TEXTURE_2D, ligth->getTexture());
      auto shaderLuz = ligth->getEntity()->getComponent<graphics::ShaderComponent>();
      if (shaderLuz) {
         //renderFinal(0);


         if (ligth->VAO_DBG == 0) {
            float quadVertices[] = {
               // positions        // texture Coords
               -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
               -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
                1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
                1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
            };
            // setup plane VAO
            glGenVertexArrays(1, &ligth->VAO_DBG);
            glGenBuffers(1, &ligth->VBO_DBG);
            glBindVertexArray(ligth->VAO_DBG);
            glBindBuffer(GL_ARRAY_BUFFER, ligth->VBO_DBG);
            glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

            //Compilamos el sadher
            if (shaderLuz && !shaderLuz->isCompiled()) {
               shaderLuz->compileShaders();
            }
         }

         if (shaderLuz->shadersCompiled.size() > 1) {
            //for (int j = 0; j < shadersCompiledCount; j++) {
            short int ps = shaderLuz->shadersCompiled[1];
            glUseProgram(ps);
            int modelLoc = glGetUniformLocation(ps, "near_plane");
            if (modelLoc != -1) {
               glUniform1f(modelLoc, 0.001f);
            }

            modelLoc = glGetUniformLocation(ps, "far_plane");
            if (modelLoc != -1) {
               glUniform1f(modelLoc, 350.0f);
            }
            //}
         }
         glBindVertexArray(ligth->VAO_DBG);
         glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);/**/
      }

      glBindVertexArray(0);
      glUseProgram(0);
      glBindFramebuffer(GL_FRAMEBUFFER, 0);
      glBindTexture(GL_TEXTURE_2D, 0 ) ;
   }

   glViewport(0, 0, widthFrameBuffer, heightFrameBuffer);
   
}
/**/

void MotorGL::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (action) {
    case GLFW_PRESS:
        Input::setKeyDown(key, mods);
        break;
    case GLFW_RELEASE:
        Input::setKeyUp(key, mods);
        break;
    }    
}

void MotorGL::mouseMove_callback(GLFWwindow* window, double x, double y) {
   Input::setMousePosition(x, y,Screen::getWidth(), Screen::getHeight());
}

void MotorGL::mouseButtom_callback(GLFWwindow* window, int buttom, int action, int mods) {
   switch (action) {
      case GLFW_PRESS:
          Mouse::setButtomDown((Mouse::BUTTOMS)buttom, mods);
         break;
      case GLFW_RELEASE:
          Mouse::setButtomUp((Mouse::BUTTOMS)buttom, mods);
         break;
   }
}

void MotorGL::framebuffer_size_callback(GLFWwindow* window, int width, int height){
    if (controlarRedimension) {
        auto graphic = Module::get<modules::graphics::Graphic>();
        //glViewport(0, 0, width, height);
        graphic->setSize(width, height);
        //graphic->getActiveCamera()->setChange(true);
        graphic->getActiveCamera()->transformChanged();
        auto gl =Global::getInstance();
        gl->marginLeft = 0;
        gl->marginTop = 0;
        gl->widthScreen = width;
        gl->heightScreen = height;

    }
}

void MotorGL::windowsMove_callback(GLFWwindow* window, int x, int y){
    Global::getInstance()->xIniScreen = x;
    Global::getInstance()->yIniScreen = y;
}

void MotorGL::focus(GLFWwindow* window, int focused) {
   if (focused) {
      for (auto itr = onFocus.begin(); itr != onFocus.end(); itr++) {
         (*itr)(true);
      }
      for (auto itr = onFocusTapes.begin(); itr != onFocusTapes.end(); itr++) {
         (*itr)->onFocus(true);
      }
   }else {
      for (auto itr = onFocus.begin(); itr != onFocus.end(); itr++) {
         (*itr)(false);
      }
      for (auto itr = onFocusTapes.begin(); itr != onFocusTapes.end(); itr++) {
         (*itr)->onFocus(false);
      }
   }
}


void MotorGL::updateEntityMESH(RenderableComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type) {
   std::vector<RenderableComponent*>* renders = entity->getComponents<RenderableComponent>();//(renderable::Mesh*)render->getRenderable();
   if (renders == NULL) {
      return;
   }
   for (auto itrM = renders->begin(); itrM != renders->end(); itrM++) {
       auto tipoR = (*itrM)->getRenderable()->getType();
       if (tipoR != renderable::Object::TYPE::MESH && tipoR != renderable::Object::TYPE::CUBE) {
           return;
       }
       renderable::Mesh* malla = (renderable::Mesh*)(*itrM)->getRenderable();
       int tamañoVertices = malla->getAllSize();
       if (tamañoVertices == 0) {
           return;
       }
       if (entidad == 0) {
           entidad = new EntityGL4(GL_TRIANGLES, malla); //GL_TRIANGLE_FAN
           misEntidades[(Entity*)entity] = entidad;
       } else {
           if (entidad->getObject() == NULL) {
               entidad->setObject(malla);
           }
       }
       renderable::Object::MODE_COLOR modoColor = malla->getTypeColor();

       //auto [xS, yS, zS] = entity->transformada->getScale();
       bool cambio = malla->hasChange();
       if (cambio) {//|| 1==1
            clearEntity(entidad);//Eliminamos los buffer. //TODO: Ver si podemos optimizar esto
           //DBG("Cambia la malla con % vertices", tamañoVertices);
           float* vertices = new float[tamañoVertices];
           float* vectorMalla = malla->getMesh();
           int numeroVertices = malla->getVertexNumber();

#ifdef EDITOR
           float* vertices_id = new float[numeroVertices * 4];
           int j_id = 0;
           float* vertices_outline = new float[numeroVertices * 6];
           int j_outline = 0;
#endif

           float* vectorNormales = malla->getNormals();
           float* vectorColores = malla->getColors();
           float* vectorUVs = malla->getUVs();
           float* vectorIdMateriales = malla->getIdMaterials();

           int j = 0;
           int k = 0;
           int kColor = 0;
           int kUV = 0;
           int kIdMat = 0;
           for (int i = 0; i < numeroVertices; i++) {

               //resultX = (posX - centerX) * cosY * cosZ + (posY - centerY) * (-cosX * sinZ + sinX * sinY * cosZ) + (posZ - centerZ) * (sinX * sinZ + cosX * sinY * cosZ);
               //resultY = (posX - centerX) * cosY * sinZ + (posY - centerY) * (cosX * cosZ + sinX * sinY * sinZ) + (posZ - centerZ) * (-sinX * cosZ + cosX * sinY * sinZ);
               //resultZ = (posX - centerX) * (-cosY * sinX) + (posY - centerY) * (cosX * cosY) + (posZ - centerZ) * (sinX * sinY);
               vertices[j++] = vectorMalla[k];
               vertices[j++] = vectorMalla[k + 1];
               vertices[j++] = vectorMalla[k + 2];
               if (vectorNormales) {
                   vertices[j++] = vectorNormales[k];
                   vertices[j++] = vectorNormales[k + 1];
                   vertices[j++] = vectorNormales[k + 2];
               } else {
                   vertices[j++] = 0.0f;
                   vertices[j++] = 0.0f;
                   vertices[j++] = 1.f;
               }
               if (vectorColores) {
                   vertices[j++] = vectorColores[kColor++];
                   vertices[j++] = vectorColores[kColor++];
                   vertices[j++] = vectorColores[kColor++];
                   vertices[j++] = vectorColores[kColor++];
               } else {
                   vertices[j++] = 1.0f;
                   vertices[j++] = 1.0f;
                   vertices[j++] = 1.0f;
                   vertices[j++] = 1.0f;
               }
               if (vectorUVs) {
                   vertices[j++] = vectorUVs[kUV++];
                   vertices[j++] = vectorUVs[kUV++];
               } else {
                   vertices[j++] = 0.0f;
                   vertices[j++] = 0.0f;
               }
               if (vectorIdMateriales) {
                   vertices[j++] = vectorIdMateriales[kIdMat++];
               } else {
                   vertices[j++] = 0;
               }
#ifdef EDITOR
               vertices_id[j_id++] = vectorMalla[k];
               vertices_id[j_id++] = vectorMalla[k + 1];
               vertices_id[j_id++] = vectorMalla[k + 2];
               vertices_id[j_id++] = entity->id;

               vertices_outline[j_outline++] = vectorMalla[k];
               vertices_outline[j_outline++] = vectorMalla[k + 1];
               vertices_outline[j_outline++] = vectorMalla[k + 2];
               vertices_outline[j_outline++] = vectorNormales[k];
               vertices_outline[j_outline++] = vectorNormales[k + 1];
               vertices_outline[j_outline++] = vectorNormales[k + 2];
#endif

               k += 3;
           }/**/

           /*utiles::Log::debug("MESH");
           for (int i = 0; i < tamañoVertices; i++) {
              utiles::Log::debug(vertices[i]);
           }/**/
           entidad->setVertextCount(numeroVertices); //TODO: El número de vertices se obtendrá de la propia maya del objeto.
           unsigned int* indices = new unsigned int[numeroVertices];
           for (int i = 0; i < numeroVertices; i++) {
               indices[i] = 0;
           } /**/

           GLuint* vao = entidad->getVAO();
           GLuint* vbo = entidad->getVBO();

           //GLuint* ebo = entidad->getEBO();

           glGenVertexArrays(1, vao);
           glGenBuffers(1, vbo);
           //glGenBuffers(1, ebo);

           glBindVertexArray(*vao);

           glBindBuffer(GL_ARRAY_BUFFER, *vbo);
           glBufferData(GL_ARRAY_BUFFER, tamañoVertices * sizeof(float), vertices, GL_STATIC_DRAW);
           //glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(float), vertices, GL_STATIC_DRAW);

           //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
           //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

           //TODO: Modificar para que se adapte al shader que toque
           int parametros = 13;
           glEnableVertexAttribArray(0);
           glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)0);
           glEnableVertexAttribArray(1);
           glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(3 * sizeof(float)));
           glEnableVertexAttribArray(2);
           glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(6 * sizeof(float)));
           glEnableVertexAttribArray(3);
           glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(10 * sizeof(float)));
           glEnableVertexAttribArray(4);
           glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(12 * sizeof(float)));/**/

#ifdef EDITOR
           //SELECTOR
           GLuint* vao_id = entidad->getVAO_id();
           GLuint* vbo_id = entidad->getVBO_id();
           glGenVertexArrays(1, vao_id);
           glGenBuffers(1, vbo_id);

           glBindVertexArray(*vao_id);

           glBindBuffer(GL_ARRAY_BUFFER, *vbo_id);
           glBufferData(GL_ARRAY_BUFFER, numeroVertices * 4 * sizeof(float), vertices_id, GL_STATIC_DRAW);
           parametros = 4;
           glEnableVertexAttribArray(0);
           glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)0);
           glEnableVertexAttribArray(1);
           glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(3 * sizeof(float)));

           //MARCADO
           GLuint* vao_outline = entidad->getVAO_outline();
           GLuint* vbo_outline = entidad->getVBO_outline();
           glGenVertexArrays(1, vao_outline);
           glGenBuffers(1, vbo_outline);

           glBindVertexArray(*vao_outline);

           glBindBuffer(GL_ARRAY_BUFFER, *vbo_outline);
           glBufferData(GL_ARRAY_BUFFER, numeroVertices * 6 * sizeof(float), vertices_outline, GL_STATIC_DRAW);
           parametros = 6;
           glEnableVertexAttribArray(0);
           glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)0);
           glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(3 * sizeof(float)));

#endif


           /*if (modoColor == renderable::Object::TEXTURE && malla->isUpdatingTexture()) {
              entidad->clearText();
              std::vector<Material*> materiales = malla->getMaterials();
              for (int i = 0; i < materiales.size(); i++) {
                 if (materiales[i]->haveTextures()) {
                    std::vector<Texture*>* texturas = materiales[i]->getTextures();
                    for (int j = 0; j < texturas->size(); j++) {
                       entidad->addText(texturas->operator[](i)->getIdTexture());
                    }
                 }
              }

           }/**/


           //glBindVertexArray(0);
           delete[] vertices;
           delete[] indices;
#ifdef EDITOR
           delete[] vertices_id;
           delete[] vertices_outline;
#endif

           graphics::ShaderComponent* shaderComponent = entity->getComponent<graphics::ShaderComponent>();
           if (shaderComponent) {
              std::vector<unsigned int> idPrograms;
              idPrograms.push_back(shaderComponent->getMaterial());
#ifdef EDITOR
              auto idOutline = shaderComponent->getOutline();
              idPrograms.push_back(idOutline);
              idPrograms.push_back(shaderComponent->getClicking());
              idPrograms.push_back(shaderComponent->getShadow());
              //idPrograms.push_back(shaderComponent->getMaterial());
#endif // EDITOR

              for (auto idProgram : idPrograms) {
                 if (idProgram != 0) {

                    glUseProgram(idProgram);

                    auto modelLoc = glGetUniformLocation(idProgram, "ligths_numbers");
                    if (modelLoc != -1) {
                       auto modosMaterial = malla->getColorModes();
                       auto numeroMateriales = malla->getMaterialsNumber();
                       if (numeroMateriales > 0) {
                          GLuint block = glGetUniformLocation(idProgram, "conTextura");
                          if (block != GL_INVALID_INDEX) {
                             glUniform1i(block, modosMaterial[0] == renderable::Object::TEXTURE ? true : false);
                          }
                       } else {
                          GLuint block = glGetUniformLocation(idProgram, "conTextura");
                          if (block != GL_INVALID_INDEX) {
                             glUniform1i(block, false);
                          }
                       }
                       /*for (int i = 0; i < numeroMateriales; i++) {
                           GLuint block = glGetUniformBlockIndex(idProgram, "conTextura");
                           if (block != GL_INVALID_INDEX) {
                              GLuint bufferTexturas;
                              glGenBuffers(1, &bufferTexturas);
                              glBindBuffer(GL_UNIFORM_BUFFER, bufferTexturas);
                              bool* modosColor = new bool[20];// 20 es el número máximo de colores

                              for (int iColor = 0; iColor < 20; iColor++) {
                                 if (iColor < numeroMateriales) {
                                    modosColor[iColor] = modosMaterial[i] == renderable::Object::TEXTURE;
                                 } else {
                                    modosColor[iColor] = false;
                                 }
                              }
                              glBufferData(GL_UNIFORM_BUFFER, sizeof(bool) * 20, modosColor, GL_DYNAMIC_DRAW); //GL_DYNAMIC_DRAW //GL_STATIC_DRAW
                              GLuint idBloque = 2;
                              glUniformBlockBinding(idProgram, block, idBloque);
                              glBindBufferRange(GL_UNIFORM_BUFFER, idBloque, bufferTexturas, 0, sizeof(bool));
                              //glBindBufferBase(GL_UNIFORM_BUFFER, idBloque, bufferTexturas);
                              glBindBuffer(GL_UNIFORM_BUFFER, 0);
                              delete[] modosColor;
                              // bind light buffer to location 1
                           }
                       }/**/
                       //modelLoc = glGetUniformLocation(idProgram, "numero_texturas");
                       //glUniform1i(modelLoc, numeroMateriales);
                    }
                 }
              }

           }



       } /*else {
       GLuint* vao = entidad->getVAO();
       GLuint* vbo = entidad->getVBO();
       GLuint* ebo = entidad->getEBO();
       glGenVertexArrays(1, vao);
       glGenBuffers(1, vbo);
       //glGenBuffers(1, ebo);

       glBindVertexArray(*vao);
       glBindBuffer(GL_ARRAY_BUFFER, *vbo);

       glEnableVertexAttribArray(0);
       glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0);
       glEnableVertexAttribArray(1);
       glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3 * sizeof(float)));
       glEnableVertexAttribArray(2);
       glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));
       }/**/

       /*if (entity->has<graphics::ShaderComponent>()) {
           graphics::ShaderComponent* shaderComponent = entity->getComponent<graphics::ShaderComponent>();
           if (!shaderComponent->isCompiled()) {
               auto idsComp = shaderComponent->compileShaders();
               for (auto idComp : idsComp) {
                  entidad->addShaderProgram(idComp);
               }
           }
       }/**/



       
       if (camaraActual != NULL ) {
          graphics::ShaderComponent* shaderComponent = entity->getComponent<graphics::ShaderComponent>();
          if (shaderComponent) {
             std::vector<unsigned int> idPrograms;
             idPrograms.push_back(shaderComponent->getMaterial());
#ifdef EDITOR
             auto idOutline = shaderComponent->getOutline();
             idPrograms.push_back(idOutline);
             idPrograms.push_back(shaderComponent->getClicking());
             idPrograms.push_back(shaderComponent->getShadow());
             //idPrograms.push_back(shaderComponent->getMaterial());
#endif // EDITOR

             for (auto idProgram : idPrograms) {
                if (idProgram != 0) {
                   glUseProgram(idProgram);

#ifdef EDITOR
                   if (idProgram == idOutline) {
                      //Tenemos que agrandar un poco el objeto para poder seleccionarlo
                      //float escalaSeleccion = global->outlineThink;
                      //auto matrizTrans = entity->transformada->matrixCompleteScale(escalaSeleccion);
                      auto matrizTrans = entity->transformada->matrix();
                      processViewProjectionShader(idProgram, camaraActual->getViewMatrix(), camaraActual->getProjectionMatrix(), matrizTrans);//, render->matrixTrans());
                      //delete[] matrizTrans;
                      GLuint block = glGetUniformLocation(idProgram, "outlining");
                      if (block != GL_INVALID_INDEX) {
                         glUniform1f(block, global->outlineThink);
                      }
                   } else {
                      processViewProjectionShader(idProgram, camaraActual->getViewMatrix(), camaraActual->getProjectionMatrix(), entity->transformada->matrix());//, render->matrixTrans());
                   }
#else
                   processViewProjectionShader(idProgram, camaraActual->getViewMatrix(), camaraActual->getProjectionMatrix(), entity->transformada->matrix());//, render->matrixTrans());
#endif //EDITOR
                   processLightShader(idProgram);



                }

             }
          }
          {
             //Procesamos los Colliders
             auto colliders = entity->getComponents<Collider>();
             for (auto collider : *colliders) {
                glUseProgram(collider->getShaderProgram());
                processViewProjectionShader(collider->getShaderProgram(), camaraActual->getViewMatrix(), camaraActual->getProjectionMatrix(), render->matrixTrans());
             }
          }


          //glDisableVertexAttribArray(0);

          //Ahora le añadimos una textura

       }
   }
      

}

void MotorGL::updateEntityTEXT(RenderableComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type) {
   renderable::Text* texto = (renderable::Text*)render->getRenderable();
   int tamañoVertices = texto->getAllSize();
   if (tamañoVertices == 0) {
      return;
   }
   if (entidad == 0) {
      entidad = new EntityGL4(GL_TRIANGLES, texto);
      misEntidades[(Entity*)entity] = entidad;
   } else {
      if (entidad->getObject() == NULL) {
         entidad->setObject(texto);
      }
   }
   renderable::Object::MODE_COLOR modoColor = texto->getTypeColor();
   if (texto->hasChange()) {
      float* vertices = new float[tamañoVertices];

      float* vectorMalla = texto->getMesh();
      int numeroVertices = texto->getVertexNumber();
      float* vectorNormales = texto->getNormals();
      float* vectorColores = texto->getColors();
      float* vectorUVs = texto->getUVs();

      int j = 0;
      int k = 0;
      int kColor = 0;
      int kUV = 0;
      for (int i = 0; i < numeroVertices; i++) {
         vertices[j++] = vectorMalla[k];
         vertices[j++] = vectorMalla[k + 1];
         vertices[j++] = vectorMalla[k + 2];
         if (vectorNormales) {
            vertices[j++] = vectorNormales[k];
            vertices[j++] = vectorNormales[k + 1];
            vertices[j++] = vectorNormales[k + 2];
         } else {
            vertices[j++] = 0.0f;
            vertices[j++] = 0.0f;
            vertices[j++] = 1.f;
         }
         if (vectorColores) {
            vertices[j++] = vectorColores[kColor++];
            vertices[j++] = vectorColores[kColor++];
            vertices[j++] = vectorColores[kColor++];
            vertices[j++] = vectorColores[kColor++];
         } else {
            vertices[j++] = 1.f;
            vertices[j++] = 1.0f;
            vertices[j++] = 1.0f;
            vertices[j++] = 1.0f;
         }
         if (vectorUVs) {
            vertices[j++] = vectorUVs[kUV++];
            vertices[j++] = vectorUVs[kUV++];
         } else {
            vertices[j++] = 0.0f;
            vertices[j++] = 0.0f;
         }

         k += 3;
      }/**/

      /*utiles::Log::debug("MESH");
      for (int i = 0; i < tamañoVertices; i++) {
         utiles::Log::debug(vertices[i]);
      }/**/
      entidad->setVertextCount(numeroVertices); //TODO: El número de vertices se obtendrá de la propia maya del objeto.
      unsigned int* indices = new unsigned int[numeroVertices];
      for (int i = 0; i < numeroVertices; i++) {
         indices[i] = i; 
      } /**/

      GLuint* vao = entidad->getVAO();
      GLuint* vbo = entidad->getVBO();
      GLuint* ebo = entidad->getEBO();
      glGenVertexArrays(1, vao);
      glGenBuffers(1, vbo);
      //glGenBuffers(1, ebo);

      glBindVertexArray(*vao);

      glBindBuffer(GL_ARRAY_BUFFER, *vbo);
      glBufferData(GL_ARRAY_BUFFER, tamañoVertices * sizeof(float), vertices, GL_STATIC_DRAW);
      //glBufferData(GL_ARRAY_BUFFER, 27 * sizeof(float), vertices, GL_STATIC_DRAW);

      //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
      //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      //TODO: Modificar para que se adapte al shader que toque
      int parametros = 12;
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(3 * sizeof(float)));
      glEnableVertexAttribArray(2);
      glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(6 * sizeof(float)));
      glEnableVertexAttribArray(3);
      glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(10 * sizeof(float)));
      if (modoColor == renderable::Object::TEXTURE && texto->isUpdatingTexture()) {
         entidad->clearText();
         std::vector<Material*> materiales = texto->getMaterials();
         for (int i = 0; i < materiales.size(); i++) {
            if (materiales[i]->haveTextures()) {
               std::vector<Texture*>* texturas = materiales[i]->getTextures();
               for (int j = 0; j < texturas->size(); j++) {
                  entidad->addText(texturas->operator[](i)->getIdTexture());
               }
            }
         }

      }
      if (entity->has<graphics::ShaderComponent>()) {
         graphics::ShaderComponent* shader = entity->getComponent<graphics::ShaderComponent>();
         if (!shader->isCompiled()) {
            int idComp = shader->compileShader();
            entidad->addShaderProgram(idComp);
         }
      }


      //glBindVertexArray(0);
      delete[] vertices;
      delete[] indices;
   }


   if (camaraActual != NULL) {
      auto comp = entidad->getShadersPrograms();

      auto itrC = comp->begin();
      //glMatrixMode(GL_PROJECTION);
      if (itrC != comp->end()) {
         glUseProgram(*itrC);
         int modelLoc = glGetUniformLocation(*itrC, "model");
         if (modelLoc != -1) {
            glUniformMatrix4fv(modelLoc, 1, GL_TRUE, render->matrixTrans());
         }

         modelLoc = glGetUniformLocation(*itrC, "view");
         if (modelLoc != -1) {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, camaraActual->getViewMatrix());
         }

         //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, vista);
         modelLoc = glGetUniformLocation(*itrC, "projection");
         if (modelLoc != -1) {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, camaraActual->getProjectionMatrix());
         }
         //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, proyeccionOrto);

         if (modoColor == renderable::Object::TEXTURE) {
            modelLoc = glGetUniformLocation(*itrC, "con_textura");
            if (modelLoc != -1) {
               glUniform1i(modelLoc, 1);
            }
         }
         processLightShader(*itrC);
         /**/
      }
   }
}
void MotorGL::updateEntityGIZMOLIGTH(LightComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type){
   if (entidad == 0) {
      entidad = new EntityGL4(GL_TRIANGLE_FAN, 4); //GL_TRIANGLE_FAN
      misEntidades[(Entity*)entity] = entidad;
   } else {
      if (entidad->getObject() == NULL) {
         entidad->setObject(NULL);
      }
   }

   if (entity->has<graphics::ShaderComponent>()) { 
      graphics::ShaderComponent* shader = entity->getComponent<graphics::ShaderComponent>();
      if (!shader->isCompiled()) {
         auto idsComp = shader->compileShaders();
         for (auto idComp : idsComp) {
            entidad->addShaderProgram(idComp);
         }
      }
   }
   float u0 = 0;
   float u1 = 1;
   float v0 = 0;
   float v1 = 1;
   if (render->loadTexture()) {
      entidad->clearText();
      //Cargamos la textura a mano
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

      u0 = 0;
      u1 = 45.0f / (float)ancho;
      v0 = (float)(alto - 91) / (float)alto;
      v1 = (float)(alto - 46) / (float)alto;

      entidad->addText(texturaId);
        
      int tamañoVertices = 4;
      float* vertices = new float[tamañoVertices * 5] {
         0.1f, 0.1f, 0.0f, u1, v1, //x,y,z, u,v -->Arriba-Derecha
         0.1f, -0.1f, 0.0f, u1, v0, //x,y,z, u,v -->Abajo-Derecha
         -0.1f, -0.1f, 0.0f, u0, v0, //x,y,z, u,v -->Abajo-Izquierda
         -0.1f, 0.1f, 0.0f, u0, v1, //x,y,z, u,v -->Arriba-Izquierda
      };/**/

#ifdef EDITOR
      float* vertices_id = new float[tamañoVertices * 4] {
         0.1f, 0.1f, 0.0f, (float)entity->id, //x,y,z, id -->Arriba-Derecha
         0.1f, -0.1f, 0.0f, (float)entity->id, //x,y,z, id -->Abajo-Derecha
         -0.1f, -0.1f, 0.0f, (float)entity->id, //x,y,z, id -->Abajo-Izquierda
         -0.1f, 0.1f, 0.0f, (float)entity->id, //x,y,z, id -->Arriba-Izquierda
      };
     
#endif
      GLuint* vao = entidad->getVAO();
      GLuint* vbo = entidad->getVBO();
      GLuint* ebo = entidad->getEBO();
      glGenVertexArrays(1, vao);
      glGenBuffers(1, vbo);
      glGenBuffers(1, ebo);


      glBindVertexArray(*vao);

      glBindBuffer(GL_ARRAY_BUFFER, *vbo);
      glBufferData(GL_ARRAY_BUFFER, tamañoVertices * 5 * sizeof(float), vertices, GL_STATIC_DRAW);

      unsigned int indices[] = {1, 0, 3, 2};//{ 0, 3, 1, 1, 3, 2 };
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

      int parametros = 5;
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(3 * sizeof(float)));

#ifdef EDITOR
      GLuint* vao_id = entidad->getVAO_id();
      GLuint* vbo_id = entidad->getVBO_id();
      GLuint* ebo_id = entidad->getEBO_id();
      glGenVertexArrays(1, vao_id);
      glGenBuffers(1, vbo_id);
      glGenBuffers(1, ebo_id);

      glBindVertexArray(*vao_id);

      glBindBuffer(GL_ARRAY_BUFFER, *vbo_id);
      glBufferData(GL_ARRAY_BUFFER, tamañoVertices * 4 * sizeof(float), vertices_id, GL_STATIC_DRAW);

      //unsigned int indices[] = { 0, 3, 1, 1, 3, 2 };
      glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo_id);
      glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
      parametros = 4;
      glEnableVertexAttribArray(0);
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)0);
      glEnableVertexAttribArray(1);
      glVertexAttribPointer(1, 1, GL_FLOAT, GL_FALSE, parametros * sizeof(float), (void*)(3 * sizeof(float)));
      delete[] vertices_id;
#endif


      delete[]vertices;
   }

   
   
   

   if (camaraActual != NULL) {
      auto comp = entidad->getShadersPrograms();

      auto itrC = comp->begin();
      if (itrC != comp->end()) {
         glUseProgram(*itrC);
         int modelLoc;
         modelLoc = glGetUniformLocation(*itrC, "model");
         if (modelLoc != -1) {
            float* m = render->getMatrixGizmo();
            /*for (int i = 0; i < 16; i++) {
               DBG("[% %]", i, m[i]);
            }/**/
            glUniformMatrix4fv(modelLoc, 1, GL_TRUE, m);
         }

         modelLoc = glGetUniformLocation(*itrC, "view");
         if (modelLoc != -1) {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, camaraActual->getViewMatrix());
         }

         //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, vista);
         modelLoc = glGetUniformLocation(*itrC, "projection");
         if (modelLoc != -1) {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, camaraActual->getProjectionMatrix());
         }


      }
   }
}
void MotorGL::updateEntityInterface(RenderableComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type){
}
void MotorGL::processViewProjectionShader(unsigned int id, const float* view, const float* projection, float* model) {
   int modelLoc = glGetUniformLocation(id, "model");
   if (modelLoc != -1) {
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
   }

   modelLoc = glGetUniformLocation(id, "view");
   if (modelLoc != -1) {
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, view);
   }

   //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, vista);
   modelLoc = glGetUniformLocation(id, "projection");
   if (modelLoc != -1) {
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, projection);
   }
   modelLoc = glGetUniformLocation(id, "viewPos");
   if (modelLoc != -1) {
      float posCamara[3];
      std::tie(posCamara[0], posCamara[1], posCamara[2]) = camaraActual->getPosition();

      glUniform3fv(modelLoc, 3, posCamara);
   }
}
void MotorGL::processLightShader(unsigned int id) {
   //glUseProgram(id);
   int modelLoc;
  

   modelLoc = glGetUniformLocation(id, "intensidadLuz");
   if (modelLoc != -1) {
      glUniform1f(modelLoc, global->iLA);
   }
   modelLoc = glGetUniformLocation(id, "colorLuzAmbiente");
   if (modelLoc != -1) {
      glUniform3f(modelLoc, global->rLA, global->gLA, global->bLA);
   }

   LightGL4 lucesGL4[NUM_LIGHTS*6];
   int idLuz = 0;
   auto luces=Entity::getAllGlobalComponents<LightComponent>();
   for (auto luz : luces) {
      if (idLuz < NUM_LIGHTS && luz->isActive()) {
         auto [px, py, pz] = luz->getEntity()->transform()->getPosition();
         auto [r, g, b, a] = luz->getColor();
         lucesGL4[idLuz].setPosition(px, py, pz);
         lucesGL4[idLuz].setColor(r, g, b);
         lucesGL4[idLuz].constantAttenuation = 1.0f;
         lucesGL4[idLuz].linearAttenuation = 0.09f;
         lucesGL4[idLuz].quadraticAttenuation = 0.032f;
         //lucesGL4[idLuz].castsShadows = 5;

         lucesGL4[idLuz].castsShadows=1;
         const float* shadowMatrix = luz->getViewProjectMatrix();
         //for (int i = 0; i < 16; i++) {
         {
            int i = 0;
            lucesGL4[idLuz].shadowMatrix[1] =  shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[5] =  shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[9] = shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[13] = shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[2] = shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[6] =  shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[10] = shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[14] = shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[3] = shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[7] = shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[11] =  shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[15] =  shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[4] =  shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[8] =  shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[12] = shadowMatrix[i++];
            lucesGL4[idLuz].shadowMatrix[16] = shadowMatrix[i++];
            
         }
         //}
         //lucesGL4[idLuz].shadowMatrix[8] = 0.5f;
         idLuz++;
      }
   }
   //DBG("Structura %, Vector %, Total %", sizeof(LightGL4), sizeof(float) * 6, sizeof(lucesGL4));
   //auto [mylightbuffer, mylightbind]=myLight[id];
   if (myLight.find(id)==myLight.end()){
       //mylightbuffer == 0) {
      GLuint mylightbuffer = 0;
      GLuint mylightbind = 1;

      glGenBuffers(1, &mylightbuffer);
      glBindBuffer(GL_UNIFORM_BUFFER, mylightbuffer);
      glBufferData(GL_UNIFORM_BUFFER, sizeof(lucesGL4), lucesGL4, GL_DYNAMIC_DRAW);

      // bind light buffer to location 1
      GLuint block = glGetUniformBlockIndex(id, "LightBlock");
      
      glUniformBlockBinding(id, block, mylightbind);
      glBindBufferRange(GL_UNIFORM_BUFFER, mylightbind, mylightbuffer, 0, sizeof(lucesGL4));
      //glBindBufferBase(GL_UNIFORM_BUFFER, 1, mylightbuffer);
      
      glBindBuffer(GL_UNIFORM_BUFFER, 0);
      ///glBindBuffer(GL_UNIFORM_BUFFER, mylightbuffer);
           //glBindBufferBase(GL_UNIFORM_BUFFER, 1, mylightbuffer);
      //glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lucesGL4), lucesGL4);
      //glBindBuffer(GL_UNIFORM_BUFFER, 0); // Desvinculamos el búfer de datos
      myLight[id] = { mylightbuffer, mylightbind };
   } else {
       auto [mylightbuffer, mylightbind] = myLight[id];
      glBindBuffer(GL_UNIFORM_BUFFER, mylightbuffer);
      //glBindBufferBase(GL_UNIFORM_BUFFER, 1, mylightbuffer);
      glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(lucesGL4), lucesGL4);
      glBindBufferRange(GL_UNIFORM_BUFFER, mylightbind, mylightbuffer, 0, sizeof(lucesGL4));
      glBindBuffer(GL_UNIFORM_BUFFER, 0); // Desvinculamos el búfer de datos
   }
   modelLoc = glGetUniformLocation(id, "ligths_numbers"); 
   if (modelLoc != -1) {
      glUniform1i(modelLoc, idLuz);
   }
   /*modelLoc = glGetUniformLocation(id, "lights");
   if (modelLoc != -1) {
      glUniform1fv(modelLoc, idLuz * sizeof(LightGL4), (GLfloat*)&lucesGL4[0]);
   }/**/
   /*modelLoc = glGetUniformLocation(id, "posicionLuz");
   if (modelLoc != -1) {
      glUniform3f(modelLoc, global->xL, global->yL, global->zL);
   }
   modelLoc = glGetUniformLocation(id, "colorLuz");
   if (modelLoc != -1) {
      glUniform3f(modelLoc, global->rL, global->gL, global->bL);
   }
   modelLoc = glGetUniformLocation(id, "watiosLuz");
   if (modelLoc != -1) {
      glUniform1f(modelLoc, global->iL);
   }/**/
}
void MotorGL::processShader(){
   for (auto entidades: misEntidades) {
      auto comp = entidades.second->getShadersPrograms();
      auto itrC = comp->begin();
      if (itrC != comp->end()) {
         glUseProgram(*itrC);
         processLightShader(*itrC);
      }

   }
}


void MotorGL::updateEntityCUBE(RenderableComponent * render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type) {
   renderable::Cube* cubo = (renderable::Cube * )render->getRenderable();
   if (entidad == 0) {
      entidad = new EntityGL4(GL_TRIANGLE_FAN, cubo);
      misEntidades[(Entity*)entity] = entidad;
   } else {
      if (entidad->getObject() == NULL) {
         entidad->setObject(cubo);
      }
   }
   float vertices[] = {
     //FRENTE
     //Superior izquierda
     0.5f,  0.5f, 0.5f, //derecha arriba frente 0
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.5f, //derecha abajo frente 1
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     -0.5f,  0.5f, 0.5f, //izquiera arriba frente 3
     0.0f, 0.0f, 1.0f,
     1.0f, 0.0f, 0.0f,
     //Superior derecho
     -0.5f,  0.5f, 0.5f, //izquiera arriba frente 3
     0.0f, 0.0f, 1.0f,
     0.8f, 0.0f, 0.0f,
     -0.5f, -0.5f, 0.5f, //izquierda abajo frente 2
     0.0f, 0.0f, 1.0f,
     0.8f, 0.0f, 0.0f,
     0.5f, -0.5f, 0.5f, //derecha abajo frente 1
     0.0f, 0.0f, 1.0f,
     0.8f, 0.0f, 0.0f,

     //DERECHA
     0.5f,  0.5f,  0.5f, //derecha arriba frente 0
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.5f, -0.5f,  0.5f, //derecha abajo frente 1
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,
     0.5f,  0.5f,  -0.5f, //derecha arriba trasara 4
     1.0f, 0.0f, 0.0f,
     0.0f, 1.0f, 0.0f,

     0.5f,  0.5f,  -0.5f, //derecha arriba trasara 4
     1.0f, 0.0f, 0.0f,
     0.0f, 0.8f, 0.0f,
     0.5f, -0.5f,  -0.5f, //derecha abajo trasara 5
     1.0f, 0.0f, 0.0f,
     0.0f, 0.8f, 0.0f,
     0.5f, -0.5f,  0.5f, //derecha abajo frente 1
     1.0f, 0.0f, 0.0f,
     0.0f, 0.8f, 0.0f,

     //ARRIBA
     0.5f,  0.5f,  0.5f, //derecha arriba frente 0
     0.0f, -1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  -0.5f, //derecha arriba trasara 4
     0.0f, -1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     -0.5f,  0.5f,  -0.5f, //izquiera arriba trasera 7
     0.0f, -1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,

     -0.5f,  0.5f,  -0.5f, //izquiera arriba trasera 7
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     -0.5f,  0.5f,  0.5f, //izquierda arriba frente 0
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  0.5f, //derecha arriba frente 0
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,

     //IZQUIERDA
     -0.5f,  0.5f,  0.5f, //izquiera arriba frente 3
     -1.f,  0.f, 0.f,
     0.0f, 0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f, //izquierda abajo frente 2
     -1.f,  0.f, 0.f,
     0.0f, 0.0f, 1.0f,
     -0.5f,  -0.5f,  -0.5f, //izquiera abajo trasera 7
     -1.f,  0.f, 0.f,
     0.0f, 0.0f, 1.0f,

     -0.5f,  -0.5f,  -0.5f, //izquiera abajo trasera 7
     -1.f,  0.f, 0.f,
     0.0f, 0.0f, 1.0f,
     -0.5f, 0.5f,  -0.5f, //izquierda arriba trasera 6
     -1.f,  0.f, 0.f,
     0.0f, 0.0f, 1.0f,
     -0.5f, 0.5f,  0.5f, //izquierda arriba frente 2
     -1.f,  0.f, 0.f,
     0.0f, 0.0f, 1.0f,

     //ABAJO
     0.5f, -0.5f,  0.5f, //derecha abajo frente 1
     0.f, -1.f, 0.f,
     0.0f, 0.0f, 1.0f,
     -0.5f, -0.5f,  0.5f, //izquierda abajo frente 2
     0.f, -1.f, 0.f,
     0.0f, 0.0f, 1.0f,
     -0.5f, -0.5f,  -0.5f, //izquierda abajo trasera 6
     0.f, -1.f, 0.f,
     0.0f, 0.0f, 1.0f,

     -0.5f, -0.5f,  -0.5f, //izquierda abajo trasera 6
     0.f, -1.f, 0.f,
     0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  -0.5f, //derecha abajo trasera 6
     0.f, -1.f, 0.f,
     0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  0.5f, //derecha abajo frente 1
     0.f, -1.f, 0.f,
     0.0f, 0.0f, 1.0f,

     //TRASERA
     -0.5f, -0.5f,  -0.5f, //izquierda abajo trasera 6
     0.f, 0.f, -1.f,
     0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  -0.5f, //derecha abajo trasera 6
     0.f, 0.f, -1.f,
     0.0f, 0.0f, 1.0f,
     -0.5f,  0.5f,  -0.5f, //izquiera arriba trasera 7
     0.f, 0.f, -1.f,
        0.0f, 0.0f, 1.0f,

     -0.5f,  0.5f,  -0.5f, //izquiera arriba trasera 7
     0.f, 0.f, -1.f,
        0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  -0.5f, //derecha arriba trasara 4
     0.f, 0.f, -1.f,
        0.0f, 0.0f, 1.0f,
     0.5f, -0.5f,  -0.5f, //derecha abajo trasara 5
     0.f, 0.f, -1.f,
        0.0f, 0.0f, 1.0f
   };
   entidad->setVertextCount(3*(2*6)); //TODO: El número de vertices se obtendrá de la propia maya del objeto./**/
   /*utiles::Log::debug("\r\n\r\nCUBE");
   for (int i = 0; i < 324; i++) {
      utiles::Log::debug(vertices[i]);
   }/**/
   /*float vertices[] = {
     0.5f,  0.5f,  0.5f, //derecha arriba frente 0
     0.0f, -1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  -0.5f, //derecha arriba trasara 4
     0.0f, -1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     -0.5f,  0.5f,  -0.5f, //izquiera arriba trasera 7
     0.0f, -1.0f, 0.0f,
     0.0f, 0.0f, 1.0f
   };
   entidad->setVertextCount(3 * (1 * 1)); //TODO: El número de vertices se obtendrá de la propia maya del objeto./**/
   /*float vertices[] = {
     0.5f,  0.5f,  0.5f, //derecha arriba frente 0
     0.5f, -0.5f,  0.5f, //derecha abajo frente 1
    -0.5f, -0.5f,  0.5f, //izquierda abajo frente 2
    -0.5f,  0.5f,  0.5f, //izquiera arriba frente 3
     0.5f,  0.5f,  -0.5f, //derecha arriba trasara 4
     0.5f, -0.5f,  -0.5f, //derecha abajo trasara 5
    -0.5f, -0.5f,  -0.5f, //izquierda abajo frente 6
    -0.5f,  0.5f,  -0.5f, //izquiera arriba trasera 7
   /*0.0f, 0.0f, 1.0f, //Normal frente 8
   1.0f, 0.0f, 0.0f, //Normal derecha 9
   0.0f, 1.0f, 0.0f, //Normal superior 10
   -1.0f, 0.0f, 0.0f, //Normal izquierda 11
   0.0f, -1.0f, 0.0f, //Normal inferior 12
   0.0f, 0.0f, -1.0f, //Normal trasera 13/**/
   //};//(front)(right)(top)(left)(bottom)(back)/**/
   /*float normales[] = {
      0.0f, 0.0f, 1.0f,
      0.0f, 0.0f, 1.0f,

      1.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      
      0.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,

      -1.0f, 0.0f, 0.0f,
      -1.0f, 0.0f, 0.0f,

      0.0f, -1.0f, 0.0f,
      0.0f, -1.0f, 0.0f,

      0.0f, 0.0f, -1.0f,
      0.0f, 0.0f, -1.0f,
   };/**/
   unsigned int indices[] = {
     /* 0,1,3/*,1,3,2,
     /* 0,4,3,3,4,7/**/
     0, 1, 3, 1, 2, 3, //Triangulos de frente
     4, 5, 0, 5, 1, 0, //Triangulos de derecha
     7, 4, 3, 4, 0, 3, //Triangulos de arriba
     3, 2, 7, 2, 6, 7, //Triangulos de izquierda
     5, 6, 1, 6, 2, 1, //Triangulos de arriba abajo
     7, 6, 4, 6, 5, 4,  //Triangulos de arriba trasera
     /*8,8,
     9,9,
     10,10,
     11,11,
     12,12,
     13,13
     /**/
   };


   GLuint* vao = entidad->getVAO();
   GLuint* vbo = entidad->getVBO();
   GLuint* ebo = entidad->getEBO();
   glGenVertexArrays(1, vao);
   glGenBuffers(1, vbo);
   //glGenBuffers(1, ebo);

   glBindVertexArray(*vao);

   glBindBuffer(GL_ARRAY_BUFFER, *vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)0); 
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(3*sizeof(float)));
   glEnableVertexAttribArray(2);
   glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void*)(6 * sizeof(float)));

   
   

   
   if (camaraActual != NULL) {
      auto comp = entidad->getShadersPrograms();

      auto itrC = comp->begin();
      //glMatrixMode(GL_PROJECTION);
      if (itrC != comp->end()) {
         glUseProgram(*itrC);
         int modelLoc = glGetUniformLocation(*itrC, "model");
         glUniformMatrix4fv(modelLoc, 1, GL_TRUE, render->matrixTrans());
         modelLoc = glGetUniformLocation(*itrC, "view");

         glUniformMatrix4fv(modelLoc, 1, GL_FALSE, camaraActual->getViewMatrix());
         //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, vista);
         modelLoc = glGetUniformLocation(*itrC, "projection");
         glUniformMatrix4fv(modelLoc, 1, GL_FALSE, camaraActual->getProjectionMatrix());
         //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, proyeccionOrto);
         processLightShader(*itrC);
      }
   }

   //glDisableVertexAttribArray(0);

   //Ahora le añadimos una textura


   
}

void MotorGL::updateEntityLINE(RenderableComponent* render, EntityGL4* entidad, Entity* entity, TYPE_OPERATION type) {
   renderable::Line* linea = (renderable::Line*)render->getRenderable(); //Obtenemos los datos de la línea
   if (entidad == 0) {
      GLenum tipo = GL_LINES;
      switch (linea->getStyle()) {
         case 1:
            tipo = GL_LINE_STRIP;
            break;
         case 2:
            tipo = GL_LINE_LOOP;
            break;
         default:
            break;
      }

      entidad = new EntityGL4(tipo, linea);
      misEntidades[(Entity*)entity] = entidad;
      glGenVertexArrays(1, entidad->getVAO());
      glGenBuffers(1, entidad->getVBO());
   } else {
      if (entidad->getObject() == NULL) {
         entidad->setObject(linea);
      }
   }

   //Obtenemos los puntos
   int numeroPuntos = linea->getNumberPoints();
   float* vecPuntos = linea->getMesh();
   float* vecColores = linea->getColors();
   int length = numeroPuntos * (3+4);
   float* datos = new float [length];

   int jPunto1 = 0;
   int jPunto2 = 0;
   for (int i = 0; i < numeroPuntos; i++) {
      datos[jPunto1++] = vecPuntos[jPunto2++];
      datos[jPunto1++] = vecPuntos[jPunto2++];
      datos[jPunto1++] = vecPuntos[jPunto2++];
      datos[jPunto1++] = vecColores[0];
      datos[jPunto1++] = vecColores[1];
      datos[jPunto1++] = vecColores[2];
      datos[jPunto1++] = vecColores[3];
   }

   GLuint* vao = entidad->getVAO();
   GLuint* vbo = entidad->getVBO();
   GLuint* ebo = entidad->getEBO();
   
   
   glBindVertexArray(*vao);

   unsigned longitud = length * sizeof(float);
   glBindBuffer(GL_ARRAY_BUFFER, *vbo);
   glBufferData(GL_ARRAY_BUFFER, longitud, datos, GL_STATIC_DRAW);

   //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
   //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   int parametros = 7;
   int longitudParametros = parametros * sizeof(float);
   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, longitudParametros, (void*)0);
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, longitudParametros, (void*)(3*sizeof(float)));
    
   
   if (entity->has<graphics::ShaderComponent>()) {
       graphics::ShaderComponent* shader = entity->getComponent<graphics::ShaderComponent>();
      if (!shader->isCompiled()) {
         int idComp = shader->compileShader();
         entidad->addShaderProgram(idComp);
      }
   }

   if (camaraActual != NULL) {
      auto comp = entidad->getShadersPrograms();

      auto itrC = comp->begin();
      //glMatrixMode(GL_PROJECTION);
      if (itrC != comp->end()) {
         glUseProgram(*itrC);
         int modelLoc = glGetUniformLocation(*itrC, "model");
         if (modelLoc > -1) {
            glUniformMatrix4fv(modelLoc, 1, GL_TRUE, render->matrixTrans());
         } 

         modelLoc = glGetUniformLocation(*itrC, "view");
         if (modelLoc > -1) {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, camaraActual->getViewMatrix());
         }

         modelLoc = glGetUniformLocation(*itrC, "projection");
         if (modelLoc > -1) {
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, camaraActual->getProjectionMatrix());
         }
         processLightShader(*itrC);
      }
      
   }/**/
   

   delete[]datos;

}

void MotorGL::updateEntityIMG(RenderableComponent* render,EntityGL4 *entidad, Entity * entity, TYPE_OPERATION type) {
   renderable::Img* img = (renderable::Img*)render->getRenderable();
   if (entidad == 0) {
      entidad = new EntityGL4(GL_TRIANGLE_FAN, img);
      misEntidades[(Entity*)entity] = entidad;
   } else {
      if (entidad->getObject() == NULL) {
         entidad->setObject(img);
      }
   }


   float z = render->getZ();
   float vertices[] = {
      // posicion                                                                               // uv
      render->getX() + (img->getWidth() * 0.5f),  render->getY() + (img->getHeight() * 0.5f), z,   0.0f, 0.0f, // arriba derecha
      render->getX() + (img->getWidth() * 0.5f),  render->getY() - (img->getHeight() * 0.5f), z,   0.0f, 1.0f, // abajo derecha
      render->getX() - (img->getWidth() * 0.5f),  render->getY() - (img->getHeight() * 0.5f), z,   1.0f, 1.0f, // abajo izquierda
      render->getX() - (img->getWidth() * 0.5f),  render->getY() + (img->getHeight() * 0.5f), z,   1.0f, 0.0f  // arriba izquierda 
   };/**/
   /*float vertices[] = {
      // posicion                                                                               // uv
      0.5f,  0.5f, 0.0f,   0.0f, 0.0f, // arriba derecha
      0.5f,  0.0f, 0.0f,   0.0f, 1.0f, // abajo derecha
      0.0f,  0.0f, 0.0f,   1.0f, 1.0f, // abajo izquierda
      0.f, 0.5f, 0.0f,   1.0f, 0.0f  // arriba izquierda 
   };/**/
   unsigned int indices[] = {
       0, 1, 3, // primer triangulo
       1, 2, 3  // segundo triangulo
   };

   GLuint* vao = entidad->getVAO();
   GLuint* vbo = entidad->getVBO();
   GLuint* ebo = entidad->getEBO();
   glGenVertexArrays(1, vao);
   glGenBuffers(1, vbo);
   glGenBuffers(1, ebo);

   glBindVertexArray(*vao);

   glBindBuffer(GL_ARRAY_BUFFER, *vbo);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0); //Cojemos los 3 puntos del vertice
   glEnableVertexAttribArray(1);
   glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float))); //Cojemos los 2 valores de la textura a partir del 3 valor

   //entidad->setVertextCount(4); //TODO: El número de vertices se obtendrá de la propia maya del objeto.
   entidad->setVertextCount(6); //TODO: El número de vertices se obtendrá de la propia maya del objeto.


   //glDisableVertexAttribArray(0);

   //Ahora le añadimos una textura


   if (img->getData()) {
      //TODO: Hay que reconstruir este código para que la gestión de la textura se haga desde SetTexture
      /*GLuint* text = entidad->addText();
      glGenTextures(1, text);

      glBindTexture(GL_TEXTURE_2D, *text);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, img->isNearest() ? GL_NEAREST : GL_LINEAR); //GL_NEAREST
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, img->isNearest() ? GL_NEAREST : GL_LINEAR);
      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getData());

      if (img->isEditable()) {
         //Generamos el FBO
         GLuint* fbo = entidad->addFBO(img->getWidth(), img->getHeight(), img->getData(), img->isNearest() ? GL_NEAREST : GL_LINEAR);
         glGenFramebuffers(1, fbo);
         glBindFramebuffer(GL_FRAMEBUFFER, *fbo);
         glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, *text, 0);
         glBindFramebuffer(GL_FRAMEBUFFER, 0);
      }


      if (img->isMinMap()) {
         glGenerateMipmap(GL_TEXTURE_2D);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, img->isNearest() ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR);
         glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, img->isNearest() ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR);
      }

      //Activamos el Shader
      auto comp = entidad->getShadersPrograms();
      for (auto itrC = comp->begin(); itrC != comp->end(); itrC++) {
         //glUseProgram(*itrC);
         glUniform1i(glGetUniformLocation(*itrC, "textura"), 0);
         //glUniform1i(glGetUniformLocation(ID, name.c_str()), );
      }
      /**/
   }
}


/*std::vector<std::tuple<Key, std::function<void(Key)>, bool>> Input::controlTeclasPulsadas;
Input* Input::instancia;/**/
#ifndef SIN_REGISTRO_MOTOR
#define SIN_REGISTRO_MOTOR
REGISTRAR_MODULO(MotorGL); 

#endif // !SIN_REGISTRO_MOTOR
