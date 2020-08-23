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
    for (int i = 0; i < entities.size(); i++) {
        //int shadersCompiledCount = entidades[i].getObject()->getShadersCompiled()->size();
        //for (int j = 0; j < shadersCompiledCount; j++) {
        //    short int ps = entidades[i].getObject()->getShadersCompiled()->operator[](j);
        //    glUseProgram(ps);
        //}
        /*GLuint vao = *entities[i].getVAO();
        glBindVertexArray(vao);
        glDrawArrays(entidades[i].getMode(), 0, entidades[i].getVertextCount());*/

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

    glfwSetKeyCallback(window, key_callback);

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
/*const byte* MotorGL::loadShader(const char* path) {
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
}

int MotorGL::loadShader(const char* path, renderable::Shader::TYPE type, renderable::Object* object) {
    const char* data = (const char*)loadShader(path);
    GLuint s = 0;
    if (data != 0) {
        switch (type) {
        case renderable::Shader::TYPE::VERTEX:
            s = glCreateShader(GL_VERTEX_SHADER);
            break;
        case renderable::Shader::TYPE::FRAGMENT:
            s = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        }
        glShaderSource(s, 1, &data, NULL);
        glCompileShader(s);
        object->addShader(s, type, data, strlen(data) + 1);
    }
    if (data) {
        delete[] data;
    }
    
    return s;
}

int MotorGL::compileShader(renderable::Object* object) {
    
    GLuint ps = glCreateProgram();
    compileShader(object, ps);
    return ps;
}

int MotorGL::compileShader(renderable::Object* object, int ps) {
    int longitud = object->getShaders()->size();
    GLuint temporal = 0;
    if (longitud > 0) {
        for (int i = 0; i < longitud; i++) {
            glAttachShader(ps, object->getShaders()->operator[](i)->getId());
        }
        glLinkProgram(ps);
        object->addShader(ps, renderable::Shader::TYPE::COMPILE);
    }

    return ps;
}/**/

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


Input MotorGL::input;

REGISTRAR_MODULO(MotorGL); 