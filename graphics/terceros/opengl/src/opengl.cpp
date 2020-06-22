#include "opengl.h"


MotorGL::MotorGL() { 
    ghDC = NULL;
    ghRC = NULL;
    imagen = imagenes::PNG::cargar("h:/desarrollo/motor_videojuegos_2D/recursos/prueba.png");
    
}

MotorGL::~MotorGL() {
    if (imagen != NULL) {
        delete imagen;
    }
}

void MotorGL::renderizar(void* rederizables) {
    std::vector<renderable::Object*> objetos = (std::vector<renderable::Object*>) (*(std::vector<renderable::Object*>*)rederizables);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    renderable::Img* img;
    for (int i = 0; i < objetos.size(); i++) {
        switch (objetos[i]->getType()) {
        case renderable::Object::TYPE::IMG:
            img = (renderable::Img*)objetos[i];
            glEnable(GL_TEXTURE_2D);
            //glDrawPixels(img->getWidth(), img->getHeight(), GL_RGBA, GL_FLOAT, img->getData());
            GLuint imgTextura;
            glGenTextures(1, &imgTextura);
            glBindTexture(GL_TEXTURE_2D, imgTextura);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//Probar con GL_LINEAR
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//Probar con GL_LINEAR
            /*if (repetir) {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            }/**/
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getData());
            glBegin(GL_QUADS);
            glTexCoord2f(0, 1);//Arriba - Izquierda
            glVertex2f(0, alto);
            glTexCoord2f(1, 1);//Arriba - Derecha
            glVertex2f(img->getWidth(), img->getHeight());
            glTexCoord2f(1, 0);//Abajo - Derecha
            glVertex2f(img->getWidth(), 0);
            glTexCoord2f(0, 0);//Abajo - Izquierda
            glVertex2f(0, 0);

            glEnd();
            glDisable(GL_TEXTURE_2D);
            break;
        case renderable::Object::TYPE::CUBE:
            renderizarCubo((renderable::Cube *)objetos[i]);
            
            break;
        default:
            break;
        }
    }
    SwapBuffers(ghDC);
}
void MotorGL::renderizarCubo(renderable::Cube * cubo) {
    float mitadLado = cubo->l * 0.5;
    float cX = cubo->pX * 0.5;
    float cY = cubo->pY * 0.5;
    float cZ = cubo->pZ;

    glPushMatrix();
    glTranslatef(cX, cY, 0.0f);
    glRotatef(cubo->rX, 1, 0, 0);
    glTranslatef(-cX , -cY, 0.0f);
    glTranslatef(cX, cY, 0.0f);
    glRotatef(cubo->rY, 0, 1, 0);
    glTranslatef(-cX, -cY, 0.0f);
    glTranslatef(cX, cY, 0.0f);
    glRotatef(cubo->rZ, 0, 0, 1);
    glTranslatef(-cX, -cY, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    //float ancho = 200;
    static const GLfloat vertices[] = {
        //Frente
        cX - mitadLado,cY + mitadLado,cZ + mitadLado,
        cX + mitadLado,cY + mitadLado,cZ + mitadLado,
        cX + mitadLado,cY - mitadLado,cZ + mitadLado,
        cX - mitadLado,cY - mitadLado,cZ + mitadLado,
        //Trasera
        cX - mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ - mitadLado,
        //Izquierda
        cX - mitadLado,cY + mitadLado,cZ + mitadLado,
        cX - mitadLado,cY + mitadLado,cZ - mitadLado,
        cX - mitadLado,cY - mitadLado,cZ - mitadLado,
        cX - mitadLado,cY - mitadLado,cZ + mitadLado,
        //Derecha
        cX + mitadLado,cY + mitadLado,cZ + mitadLado,
        cX + mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ + mitadLado,
        //Arriba
        cX - mitadLado,cY + mitadLado,cZ + mitadLado,
        cX - mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY + mitadLado,cZ + mitadLado,
        //Abajo
        cX - mitadLado,cY - mitadLado,cZ + mitadLado,
        cX - mitadLado,cY - mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ + mitadLado,

    };
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();
}
void MotorGL::renderizar() { 
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glColor3f(0.0f, 1.0f, 0.0f);
    double ancho = 800;
    double alto = 600;
    float* completo = new float[ancho * alto * 4];
    float velocidadIncremento = 0.05;
    int pixel = 0;
    for (int y = 0; y < alto; y++) {
        for (int x = 0; x < ancho; x++) {
            completo[pixel++] = 0;
            completo[pixel++] = color;
            completo[pixel++] = 0;
            completo[pixel++] = 1;
        }
    }
    pixel = 0;
    for (int y = 0; y < alto; y++) { 
        for (int x = 0; x < ancho; x++) {
            if (completo[pixel] == 0 && completo[pixel+1] > 0.5 && completo[pixel+2] == 0 && completo[pixel+3] == 1) {
                completo[pixel] = 1;
                completo[pixel + 2] = 1;
            }
            pixel += 4;
        }
    }
    pixel = 0;
    for (int y = 0; y < 50; y++) {
        for (int x = 0; x < 50; x++) {
            completo[pixel++] = x/50;
            completo[pixel++] = x/50;
            completo[pixel++] = x/50;
            completo[pixel++] = 1;
        }
    }
    if (subiendo) {
        if (color >= 1) {
            subiendo = false;
        }else {
            color += velocidadIncremento;
        }
    }else {
        if (color <= 0) {
            subiendo = true;
        }
        else {
            color -= velocidadIncremento;
        }
    }
    ////glRasterPos2d(0, 0);
    //glRasterPos3d(0, alto*.5, 0);
    //glDrawPixels(ancho, alto, GL_RGBA, GL_FLOAT, completo);
    delete []completo;
    glPushMatrix();
    glTranslatef(ancho*0.5, alto*0.5, 0.0f);
    glRotatef(-20, 1, 0, 0);
    glTranslatef(-ancho * 0.5, -alto * 0.5, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3d(180.f, 100.f, 0.f);
    glVertex3d(230.f, 100.f, 0.f);
    glVertex3d(230.f, 150.f, 0.f);
    glEnd();
    glTranslatef(100.0f, alto * .5, 0.0f);

    glColor3f(0.0f, 0.0f, 1.0f);
    glBegin(GL_TRIANGLES);
    glVertex3d(180.f, 100.f, 0.f);
    glVertex3d(230.f, 100.f, 0.f);
    glVertex3d(230.f, 150.f, 0.f);
    glEnd();
    glTranslatef(-100.0f, -alto * .5, 0.0f);
    
    glPopMatrix();
    glColor3f(0.0f, 0.0f, 1.0f);
    //float ancho = 200;
    float mitadLado = ancho*0.5;
    float cX = ancho*0.5;
    float cY = alto*0.5;
    float cZ = -500;
    static const GLfloat vertices[] = {
        //Frente
        cX - mitadLado,cY + mitadLado,cZ + mitadLado,
        cX + mitadLado,cY + mitadLado,cZ + mitadLado,
        cX + mitadLado,cY - mitadLado,cZ + mitadLado,
        cX - mitadLado,cY - mitadLado,cZ + mitadLado,
        //Trasera
        cX - mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ - mitadLado,
        //Izquierda
        cX - mitadLado,cY + mitadLado,cZ + mitadLado,
        cX - mitadLado,cY + mitadLado,cZ - mitadLado,
        cX - mitadLado,cY - mitadLado,cZ - mitadLado,
        cX - mitadLado,cY - mitadLado,cZ + mitadLado,
        //Derecha
        cX + mitadLado,cY + mitadLado,cZ + mitadLado,
        cX + mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ + mitadLado,
        //Arriba
        cX - mitadLado,cY + mitadLado,cZ + mitadLado,
        cX - mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY + mitadLado,cZ - mitadLado,
        cX + mitadLado,cY + mitadLado,cZ + mitadLado,
        //Abajo
        cX - mitadLado,cY - mitadLado,cZ + mitadLado,
        cX - mitadLado,cY - mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ - mitadLado,
        cX + mitadLado,cY - mitadLado,cZ + mitadLado,

    };
    /*glBegin(GL_TRIANGLE_STRIP);
    int pos = 0;
    for (int i = 0; i < 36; i++) {
        glVertex3f(g_vertex_buffer_data[pos++], g_vertex_buffer_data[pos++], g_vertex_buffer_data[pos++]);
    }
    glEnd();*/

    
    /*glPushMatrix();
    glTranslatef(ancho*0.5, alto*.5, -500);
    glRotatef(-20, 1, 0, 0);
    glRotatef(-20, 0, 1, 0);
    glTranslatef(-ancho * 0.5, -alto * .5, 500);
    glPopMatrix();
    
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
    glPopMatrix();/**/
    SwapBuffers(ghDC);
    
    return;
    //glTranslatef(0.0f, 0.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex3d(180.f, 100.f, 0.f);
    glVertex3d(230.f, 100.f, 0.f);
    glVertex3d(230.f, 150.f, 0.f);
    glEnd();
    //glPushMatrix();
    float puntoLuz;
    //glLightfv(GL_LIGHT0,GL_POSITION,puntoLuz)
    //glTranslatef(0.0f, 0.0f, -100.0f);
    //glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRasterPos2d(100,150);
    //glPixelZoom(0.25f, 0.25f);
    //glPixelTransferi(GL_UNPACK_ALIGNMENT, 4);
    /*int ancho = 10;
    int alto = 10;
    float * buffer = ( float*)malloc(sizeof( float)*ancho * alto * 4);
    for (int i = 0; i < (ancho * alto * 4); ) {
        buffer[i++] = 1.0f;
        buffer[i++] = 0.0f;
        buffer[i++] = 0.0f;
        buffer[i++] = 1.0f;
    }
    glDrawPixels(ancho, alto, GL_RGBA, GL_FLOAT, buffer);
    free(buffer);/**/
    if (imagen!=NULL) {
        //glRasterPos2d(0, 0+(imagen->cogerAlto()));
        glDrawPixels(imagen->cogerAncho(), imagen->cogerAlto(), GL_RGBA, GL_FLOAT,imagen->cogerDatos());
    }/**/
    glRectf(100.f, 150.0f, -500.0f, 500.0f);

    glColor3f(0.0f, 1.0f, 0.0f);
    /*glBegin(GL_TRIANGLE_STRIP);
    glVertex3d(180.f, 100.f,0.f);
    glVertex3d(230.f, 100.f, 0.f);
    glVertex3d(230.f, 150.f, 0.f);
    glVertex3d(180.f, 150.f, -50.f);
    glVertex3d(180.f, 100.f, 0.f);/**/
    /*glVertex3d(-1.f, 1.f, 0.f);
    glVertex3d(1.f, 1.f, 0.f);
    glVertex3d(1.f, -1.f, 0.f);
    glVertex3d(-0.5f, -0.5f, 0.f);
    glVertex3d(-1.f, 1.f, 0.f);/**/
    //glEnd();



    /*static const GLfloat g_vertex_buffer_data[] = {
    -1.0f,-1.0f,-1.0f, // triángulo 1 : comienza
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triángulo 1 : termina
    1.0f, 1.0f,-1.0f, // triángulo 2 : comienza
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triángulo 2 : termina
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    };
    glDrawArrays(GL_TRIANGLES, 0, 12 * 3);*/

    //glFlush();
    SwapBuffers(ghDC);
}

void MotorGL::inicializar(void * hwnd, double ancho, double alto) {
    this->ancho = ancho;
    this->alto = alto;
    ghDC = GetDC((HWND)hwnd);
    if (!bSetupPixelFormat(ghDC))
        PostQuitMessage(0);

    ghRC = wglCreateContext(ghDC);
    wglMakeCurrent(ghDC, ghRC);

   

    //GLfloat     maxObjectSize, aspect;
    //GLdouble    near_plane, far_plane;

    glClearIndex((GLfloat)0);
    glClearDepth(1.0);

    glEnable(GL_DEPTH_TEST);


    glClearColor(0, 0, 0, 0);
    //glMatrixMode(GL_PROJECTION);
    //aspect = (GLfloat)width / height;
    //gluPerspective(45.0, aspect, 3.0, 7.0); 
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity(); 
    
    float fAspecto = (float)ancho / (float)alto;
    glViewport(0, 0, ancho, alto);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //gluOrtho2D(0, ancho, alto, 0);
    //glMatrixMode(GL_PROJECTION);
    //glLoadIdentity(); 
    glOrtho(0, ancho, alto,0, -1000,1000);
    //gluPerspective(60.f, fAspecto, 0, 1000);
    //glFrustum(0, ancho, alto, 0, 0, 1000);
    //gluLookAt(ancho*0.5f, alto*.5f, 0, ancho * 0.5f, alto * .5f, 0, 0, 0,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();/**/
    //
    //glTranslatef(0.0f, 0.0f, 0.0f);
    //glEnable(GL_TEXTURE_2D);
    /*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
    
}
BOOL MotorGL::bSetupPixelFormat(HDC hdc) {
    PIXELFORMATDESCRIPTOR pfd, * ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER | PFD_GENERIC_ACCELERATED;
    //ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_RGBA;
    ppfd->cColorBits = 24;
    ppfd->cDepthBits = 16; 
    //ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 8;
    
    pixelformat = ChoosePixelFormat(hdc, ppfd);

    if ((pixelformat = ChoosePixelFormat(hdc, ppfd)) == 0) {
        MessageBox(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    if (SetPixelFormat(hdc, pixelformat, ppfd) == FALSE) {
        MessageBox(NULL, "SetPixelFormat failed", "Error", MB_OK);
        return FALSE;
    }

    return TRUE;
}
//template inline void EXPORTAR_MOTOR MotorGL::inicializar(HWND, double, double);
REGISTRAR_MODULO(MotorGL); 