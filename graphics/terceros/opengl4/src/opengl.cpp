#include "opengl.h"


MotorGL::MotorGL() { 
    //imagen = imagenes::PNG::cargar("h:/desarrollo/motor_videojuegos_2D/recursos/prueba.png");
    
}  

MotorGL::~MotorGL() {

    delete[]points;
    
    glfwTerminate();
     
}

/**
* Se encarga de renderizar cada escena
* 
* @param renderizable elemento a renderizar
*/
void MotorGL::renderizar(void* rederizables) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glEnable(GL_DEPTH_TEST);
    //glDepthFunc(GL_LESS);

    //glDepthMask(GL_FALSE);
    for (auto itr = misEntidades.begin(); itr != misEntidades.end();itr++) {
       std::vector<GLuint>* texts = itr->second->getTexts();
       int numText = GL_TEXTURE0;
       for (auto itrT = texts->begin(); itrT != texts->end(); itrT++) {
          glActiveTexture(numText++);
          glBindTexture(GL_TEXTURE_2D, *itrT);
       }

       auto comp = itr->second->getShadersPrograms();
       auto itrC = comp->begin();
       //glMatrixMode(GL_PROJECTION);
       /*if (itrC != comp->end()) {
          glUseProgram(*itrC);
          int modelLoc;
          //int modelLoc = glGetUniformLocation(*itrC, "model");
          //glUniformMatrix4fv(modelLoc, 1, GL_TRUE,itr->second-> >matrixTrans());
          modelLoc = glGetUniformLocation(*itrC, "view");
          glUniformMatrix4fv(modelLoc, 1, GL_FALSE, vista);
          modelLoc = glGetUniformLocation(*itrC, "projection");
          glUniformMatrix4fv(modelLoc, 1, GL_FALSE, proyeccion);

       }/**/
       auto fbos = itr->second->getFBOs();
       for (auto itrFBO = fbos->begin(); itrFBO != fbos->end(); itrFBO++) {
          //glViewport(0, 0, std::get<1>(*itrFBO), std::get<2>(*itrFBO));
          glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, std::get<1>(*itrFBO), std::get<2>(*itrFBO), 0, GL_RGBA, GL_FLOAT, std::get<3>(*itrFBO));
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, std::get<4>(*itrFBO)); //GL_NEAREST
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, std::get<4>(*itrFBO));
          glBindFramebuffer(GL_FRAMEBUFFER, 0);
          //auto entidadImagen = itr->first;
          //if (entidadImagen->)
       }
        //int shadersCompiledCount = entidades[i].getObject()->getShadersCompiled()->size();
       int shadersCompiledCount = itr->second->getShadersPrograms()->size();
        for (int j = 0; j < shadersCompiledCount; j++) {
            short int ps = itr->second->getShadersPrograms()->operator[](j);
            glUseProgram(ps);
        }
        

        GLuint vao = *(itr->second->getVAO());
        glBindVertexArray(vao);
        //for (int iLado = 0; iLado < 6; iLado++) {
           //glBindBuffer(GL_ARRAY_BUFFER, *(itr->second->getVBO()));
           //glEnableVertexAttribArray(1);
           //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)((24+(3*iLado)) * sizeof(float)));
           //glVertexAttrib3f(1, 0.0, 1.0, 0.0);
           /*switch (iLado) {
            case 0:
               glVertexAttrib3f(1, 0.0, 0.0, 1.0);
               break;  
            case 1:
               glVertexAttrib3f(1, 1.0, 0.0, 0.0);
               break;
            case 2:
               glVertexAttrib3f(1, 0.0, 1.0, 0.0);
               break;
            case 3:
               glVertexAttrib3f(1, -1.0, 0.0, 0.0);
               break;
            case 4:
               glVertexAttrib3f(1, 0.0, -1.0, 0.0);
               break;
            case 5:
               glVertexAttrib3f(1, 0.0, 0.0, -1.0);
               break;

           }/**/
           /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(itr->second->getEBO()));
           glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)((6*iLado) * sizeof(GL_UNSIGNED_INT)));/**/
           glDrawArrays(GL_TRIANGLES, 0, itr->second->getVertextCount());
        //}
        /*glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        //glVertexAttrib3f(1, 0.0, 0.0, 1.0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *(itr->second->getEBO()));
        glDrawElements(GL_TRIANGLES, itr->second->getVertextCount(), GL_UNSIGNED_INT, 0);
        //glDrawArrays(itr->second->getMode(), 0, itr->second->getVertextCount());
        /**/

        //glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    // draw points 0-3 from the currently bound VAO with current in-use shader
    //glDrawArrays(GL_TRIANGLES, 0, 3);
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window);
    // update other events like input handling 
    glfwPollEvents();
    if (glfwWindowShouldClose(window)) {
        setEnd();
    }
    //glDepthMask(GL_TRUE);
    //glDisable(GL_DEPTH_TEST);

    /*float* vertices=new float[18];
    glBufferSubData(0, 0, 18, vertices);
    if (derecha) {
        if (vertices[0] < 1) {
            vertices[0] += 0.1;
        } else {
            derecha = false;
        }
    } else {
        if (vertices[0] > -1) {
            vertices[0] -= 0.1;
        } else {
            derecha = true;
        }
    }
    delete[]vertices;*/
}
void MotorGL::renderizarImagen(renderable::Img* img) {
    

}

void MotorGL::renderizarCubo(renderable::Cube * cubo) {
    
}
void MotorGL::renderizar() { 
   glViewport(0, 0, ancho, alto);
   renderizar(0);
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
void MotorGL::updateEntity(void* entity) {
   auto itr = misEntidades.find((Entity*)entity);
   EntityGL4* entidad = NULL;
   if (itr != misEntidades.end()) { //Si existe la borramos
      entidad = misEntidades[(Entity*)entity];
      clearEntity(entidad); 
   }
   
   auto renderables = ((Entity*)entity)->getComponent<RenderableComponent>();
   if (renderables != NULL) {
      for (auto itrR = renderables->begin(); itrR != renderables->end(); itrR++) {
         RenderableComponent* r = (RenderableComponent*)(*itrR);
         if (r && r->getRenderable()) {
            switch (r->getRenderable()->getType()) {
            case renderable::Object::TYPE::IMG: //Es una IMAGEN
               updateEntityIMG(r, entidad, (Entity*)entity);
               break;
            case renderable::Object::TYPE::CUBE:
               updateEntityCUBE(r, entidad, (Entity*)entity);
               break;
            }
         }

      }
   }
}
/**
* Borra una entidad del sistema
* 
*/
void MotorGL::removeEntity(void* entity) {
   for (auto itr = entities.begin(); itr != entities.end(); itr++) {
      if (entity == (*itr)) {
         clearEntity(misEntidades[(Entity*)entity]);
         delete misEntidades[(Entity*)*itr];
         misEntidades.erase((Entity *)*itr);
         delete ((Entity*)*itr);
         entities.erase(itr);
         return;
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

   auto itr = entities.begin();
   while(itr != entities.end()) {
         //GLuint* vao = ((Entity*)(*itr))->getVAO();
         //TODO: REVISAR ESTO QUE SEGURAMENTE ESTÁ MAL Y ADEMÁS FALTARÍAN EL EBO, Texts, Frames...
      EntityGL4* egl4 = misEntidades[((Entity*)(*itr))];
      if (egl4) {
         GLuint* vbo = egl4->getVBO();
         if (vbo > 0) {
            glDeleteBuffers(1, vbo);
         }
         GLuint* vao = egl4->getVAO();
         if (vbo > 0) {
            glDeleteVertexArrays(1, vao);
         }
         delete egl4;
      }
      misEntidades.erase((Entity*)(*itr));
      delete ((Entity*)*itr);
      //itr = entities.begin();
      itr++;
   }
   entities.clear();
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
    this->ancho = ancho;
    this->alto = alto;
    if (!glfwInit()) {
        //fprintf(stderr, "Error al inicializar GLFW\n");
        return false;
    }
    /*glfwWindowHint(GLFW_SAMPLES, 4);   
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); */

    window = glfwCreateWindow(ancho, alto, "Prueba", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return false;
    }
    open = true;
    glfwSetWindowCloseCallback(window, closeWindow);
    glfwSetKeyCallback(window, key_callback);
    glfwSetWindowFocusCallback(window, focus);
    //glfwSetWindowAspectRatio(window, 1, 1); //Podemos indicarle la relación de tamaño de ventana por ejempo 4:3 o 16:9
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
    const GLubyte* version = glGetString(GL_VERSION); // version as a string

    
    // tell GL to only draw onto a pixel if the shape is closer to the viewer
    //glEnable(GL_DEPTH_TEST); // enable depth-testing
    //glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glfwWindowHint(GLFW_SAMPLES, 4);

    glEnable(GL_MULTISAMPLE);
      

    return true;
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

int MotorGL::loadShader(const char* path, Graphics::Shader::TYPE_SHADER type) {
    const char* data = (const char*)loadShader(path);
    GLuint s = 0;
    if (data != 0) {
      switch (type) { 
      case Graphics::Shader::TYPE_SHADER::VERTEX:
         s = glCreateShader(GL_VERTEX_SHADER);
         break;
      case Graphics::Shader::TYPE_SHADER::FRAGMENT:
         s = glCreateShader(GL_FRAGMENT_SHADER);
         break;
      }
      glShaderSource(s, 1, &data, NULL);
      glCompileShader(s);
      //object->addShader(s, type, data, strlen(data) + 1);
    }
    if (data) {
        delete[] data;
    }
    
    return (int)s;
}
void MotorGL::reloadShader(const char* path, Graphics::Shader::TYPE_SHADER type, int id, int idProgram) {
   const char* data = (const char*)loadShader(path);
   
   //GLuint s = 0;
   if (data != 0) {
      glShaderSource(id, 1, &data, NULL);
      glCompileShader(id);

      //glDetachShader(idProgram,id);
      //glAttachShader(idProgram, id);
      glLinkProgram(idProgram);
      //object->addShader(s, type, data, strlen(data) + 1);
   }
   if (data) {
      delete[] data;
   }
}
int MotorGL::compileShader(std::vector<short>* ids) {
    
    GLuint ps = glCreateProgram();
    GLuint temporal = 0;
    for (auto itr = ids->begin(); itr != ids->end(); itr++) {
       glAttachShader(ps, *itr);
    }
    glLinkProgram(ps);

    return ps;
}

int MotorGL::compileShader(int ps) {
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
int MotorGL::compileShader(std::vector<short>* shadersId, void* entity) {
   int id= compileShader(shadersId);
   bool noEncontre = true;
   for (auto itr = misEntidades.begin(); itr != misEntidades.end() && noEncontre; itr++) {
      if (itr->first == entity) {
         itr->second->addShaderProgram(id);
         noEncontre = false;
      }
   }
   if (noEncontre) {
      EntityGL4* egl4 = new EntityGL4();
      egl4->addShaderProgram(id);
      misEntidades[(Entity*)entity] = egl4;
   }
   return id;
}
int MotorGL::compileShader(int ps, void* entity) {
   int id = compileShader(ps);
   return id;
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
      float centroAnchoVentana=((float)Screen::getWidth()) * 0.5f;
      float centroAltoVentana = ((float)Screen::getHeight()) * 0.5f;

      float centroAnchoCamara = ((float)camaraActual->getWidth()) * 0.5f;
      float centroAltoCamara = ((float)camaraActual->getHeight()) * 0.5f;
      glViewport(centroAnchoVentana-centroAnchoCamara, centroAltoVentana-centroAltoCamara, centroAnchoVentana + centroAnchoCamara, centroAltoVentana + centroAltoCamara);
   }
}

void MotorGL::closeWindow(GLFWwindow* window) {
   open = false;
}
/**/

void MotorGL::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (action) {
    case GLFW_PRESS:
        input.setKeyDown(scancode, mods);
        break;
    case GLFW_RELEASE:
        input.setKeyUp(scancode, mods);
        break;
    }    
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
void MotorGL::updateEntityCUBE(RenderableComponent * render, EntityGL4* entidad, Entity* entity) {
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
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     0.5f,  0.5f,  -0.5f, //derecha arriba trasara 4
     0.0f, 1.0f, 0.0f,
     0.0f, 0.0f, 1.0f,
     -0.5f,  0.5f,  -0.5f, //izquiera arriba trasera 7
     0.0f, 1.0f, 0.0f,
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
   entidad->setVertextCount(3*(2*6)); //TODO: El número de vertices se obtendrá de la propia maya del objeto.
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

      }
   }

   //glDisableVertexAttribArray(0);

   //Ahora le añadimos una textura


   
}
void MotorGL::updateEntityIMG(RenderableComponent* render,EntityGL4 *entidad, Entity * entity) {
   renderable::Img* img = (renderable::Img*)render->getRenderable();
   if (entidad == 0) {
      entidad = new EntityGL4(GL_TRIANGLE_FAN, img);
      misEntidades[(Entity*)entity] = entidad;
   } else {
      if (entidad->getObject() == NULL) {
         entidad->setObject(img);
      }
   }


   /*float points[] = {
         -0.8f,  -0.8f,  0.0f,
         -0.8f,   0.8f,  0.0f,
         0.8f,   0.8f,  0.0f,
         0.8f,  -0.8f,  0.0f
   };/**/
   //renderable::Img* img = (renderable::Img*)r->getRenderable();
   /*float vertices[] = {
      // posicion           // uv
       0.5f,  0.5f, 0.0f,   0.0f, 0.0f, // arriba derecha
       0.5f, -0.5f, 0.0f,   0.0f, 1.0f, // abajo derecha
      -0.5f, -0.5f, 0.0f,   1.0f, 1.0f, // abajo izquierda
      -0.5f,  0.5f, 0.0f,   1.0f, 0.0f  // arriba izquierda 
   };/**/
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
      GLuint* text = entidad->addText();
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
   }
}

Input MotorGL::input;

REGISTRAR_MODULO(MotorGL); 