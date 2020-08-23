#include "opengl.h"


MotorGL::MotorGL() { 
    //imagen = imagenes::PNG::cargar("h:/desarrollo/motor_videojuegos_2D/recursos/prueba.png");
    
}  

MotorGL::~MotorGL() {

    delete[]points;
    
    glfwTerminate();
}

void MotorGL::renderizar(void* rederizables) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for (auto itr = misEntidades.begin(); itr != misEntidades.end();itr++) {
        //int shadersCompiledCount = entidades[i].getObject()->getShadersCompiled()->size();
       int shadersCompiledCount = itr->second->getShadersPrograms()->size();
        for (int j = 0; j < shadersCompiledCount; j++) {
            short int ps = itr->second->getShadersPrograms()->operator[](j);
            glUseProgram(ps);
        }
        GLuint vao = *(itr->second->getVAO());
        glBindVertexArray(vao);
        glDrawArrays(itr->second->getMode(), 0, itr->second->getVertextCount());
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
    float* vertices=new float[18];
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
    delete[]vertices;
}
void MotorGL::renderizarImagen(renderable::Img* img) {
    

}

void MotorGL::renderizarCubo(renderable::Cube * cubo) {
    
}
void MotorGL::renderizar() { 
    renderizar(0);
}


void MotorGL::inicializarLuz() {
    
}
void MotorGL::ponerCamara(float posX, float posY, float posZ, float targetX, float targetY, float targetZ) {
   
}
/*Método para acutalizar los VAO (Array de Vertices),.....*/
void MotorGL::updateEntity(void* entity) {
   auto itr = misEntidades.find((Entity*)entity);
   EntityGL4* entidad = NULL;
   if (itr == misEntidades.end()) { //Si no existe
      auto renderables = ((Entity*)entity)->getComponent<RenderableComponent>();
      if (renderables != NULL) {
         for (auto itrR = renderables->begin(); itrR != renderables->end(); itrR++) {
            RenderableComponent* r = (RenderableComponent*)(*itrR);
            switch (r->getRenderable()->getType()) {
            case renderable::Object::TYPE::IMG:
               misEntidades[(Entity*)entity] = new EntityGL4(GL_TRIANGLE_FAN, r->getRenderable());
               GLuint* vao = misEntidades[(Entity*)entity]->getVAO();

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

               misEntidades[(Entity*)entity]->setVertextCount(4); //TODO: El número de vertices se obtendrá de la propia maya del objeto.
               glBindVertexArray(*vao);
               glEnableVertexAttribArray(0);
               glBindBuffer(GL_ARRAY_BUFFER, vbo);
               glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
               //glDisableVertexAttribArray(0);
            }

         }
      }

      
      //entidad=new EntityGL4()
   }

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
    glEnable(GL_DEPTH_TEST); // enable depth-testing
    glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"


    /*

    float pointsT[] = {
       0.0f,  0.5f,  0.0f,
       0.5f, -0.5f,  0.0f,
      -0.5f, -0.5f,  0.0f,
      1.0f,  1.0f,  0.0f,
       1.0f,  0.f,  0.0f,
       0.f, 0.5f,  0.0f
    };
    points = new float[18];
    for (int i = 0; i < 18; i++) {
        points[i] = pointsT[i];
    }
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

    //glBufferData()
     
    float points2[] = {
       1.0f,  1.0f,  0.0f,
       1.0f,  0.f,  0.0f,
       0.f, 0.5f,  0.0f
    };
    GLuint vbo2;
    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), points2, GL_STATIC_DRAW);

    vaos.push_back(GLuint(0));
    glGenVertexArrays(1, &(vaos[0]));
    glBindVertexArray(vaos[0]);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    /**/




    

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
      }
   }
   return id;
}
int MotorGL::compileShader(int ps, void* entity) {
   int id = compileShader(ps);
   return id;
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


Input MotorGL::input;

REGISTRAR_MODULO(MotorGL); 