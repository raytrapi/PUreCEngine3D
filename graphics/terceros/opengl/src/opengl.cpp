#include "opengl.h"


MotorGL::MotorGL() { 
    ghDC = NULL;
    ghRC = NULL;
    //imagen = imagenes::PNG::cargar("h:/desarrollo/motor_videojuegos_2D/recursos/prueba.png");
    
}

MotorGL::~MotorGL() {
    if (imagen != NULL) {
        delete imagen;
    }
}

void MotorGL::render(void* rederizables) {
    std::vector<renderable::Object*> objetos = (std::vector<renderable::Object*>) (*(std::vector<renderable::Object*>*)rederizables);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

    // save the initial ModelView matrix before modifying ModelView matrix
    glPushMatrix();

    // tramsform camera
    //glTranslatef(0, 0, -1.5f);
    /*float xRaton = 0;
    float yRaton = 0;
    Mouse::getPosition(xRaton, yRaton);
    anguloX += (xMouse-xRaton);
    anguloY += (yMouse - yRaton);
    glRotatef(anguloX, 0, 1, 0);   // heading
    glRotatef(anguloY, 1, 0, 0);   // pitch
    //xMouse = xRaton;
    //yMouse = yRaton;
    /**/


    renderable::Img* img;
    for (int i = 0; i < objetos.size(); i++) {
        switch (objetos[i]->getType()) {
        case renderable::Object::TYPE::IMG:
            renderizarImagen((renderable::Img*)objetos[i]);
            
            //glPopMatrix();
            break;
        case renderable::Object::TYPE::CUBE:
            renderizarCubo((renderable::Cube *)objetos[i]);
            
            break;
        default:
            break;
        }
    }
    glPopMatrix();
    SwapBuffers(ghDC);
}
void MotorGL::renderizarImagen(renderable::Img* img) {
    /*glEnable(GL_TEXTURE_2D);
    //glDrawPixels(img->getWidth(), img->getHeight(), GL_RGBA, GL_FLOAT, img->getData());
    GLuint imgTextura;
    imgTextura = img->getId();
    if (imgTextura == 0) {
        glGenTextures(1, &imgTextura);
        img->setId(imgTextura);
    }
    glBindTexture(GL_TEXTURE_2D, imgTextura);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);//Probar con GL_LINEAR
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);//Probar con GL_LINEAR
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->getWidth(), img->getHeight(), 0, GL_RGBA, GL_FLOAT, img->getData());
    glPushMatrix();
    glTranslatef(img->getX(), img->getY(), img->getZ());
    glRotatef(img->getRX(), 1.f, 0, 0);
    glRotatef(img->getRY(), 0, 1.f, 0);
    glRotatef(img->getRZ(), 0, 0, 1.f);

    glBegin(GL_QUADS);

    glVertex2f(0, 0);//coordenada u-v 
    glTexCoord2f(0,0);//Abajo - Izquierda

    glVertex2f(img->getWidth(), 0);//coordenada u-v
    glTexCoord2f(1,0);//Abajo - Derecha

    glVertex2f(img->getWidth(), img->getHeight());//coordenada u-v
    glTexCoord2f(1, 1);//Arriba - Derecha

    glVertex2f(0, img->getHeight());//coordenada u-v
    glTexCoord2f(0, 1); //Arriba - Izquierda //Representa la posición en pantalla

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);/**/

}

void MotorGL::renderizarCubo(renderable::Cube* cube) {

   /*renderable::Cube * cubo=render->ob
    float mitadLado = cubo->getSize();
    float cX = cubo->getX();
    float cX_2 = cX * 0.5f;
    float cY = cubo->getY();
    float cY_2 = cY * 0.5f;
    float cZ = cubo->getZ();
    float cZ_2 = cZ * 0.5f;

    
    

    glColor3f(cubo->r, cubo->g,  cubo->b);
    //float ancho = 200;
    GLfloat vertices[] = {
        //Frente
        + mitadLado,+ mitadLado,+ mitadLado,
        - mitadLado,+ mitadLado,+ mitadLado,
        - mitadLado,- mitadLado,+ mitadLado,
        + mitadLado,- mitadLado,+ mitadLado,
        //Derecha
        + mitadLado,+ mitadLado,+ mitadLado,
        + mitadLado,- mitadLado,+ mitadLado,
        + mitadLado,- mitadLado,- mitadLado,
        + mitadLado,+ mitadLado,- mitadLado,
        //Arriba
        + mitadLado,+ mitadLado,+ mitadLado,
        + mitadLado,+ mitadLado,- mitadLado,
        - mitadLado,+ mitadLado,- mitadLado,
        - mitadLado,+ mitadLado,+ mitadLado,
        //Izquierda
        - mitadLado,+ mitadLado,+ mitadLado,
        - mitadLado,+ mitadLado,- mitadLado,
        - mitadLado,- mitadLado,- mitadLado,
        - mitadLado,- mitadLado,+ mitadLado,
        //Abajo
        - mitadLado,- mitadLado,- mitadLado,
        + mitadLado,- mitadLado,- mitadLado,
        + mitadLado,- mitadLado,+ mitadLado,
        - mitadLado,- mitadLado,+ mitadLado,
        //Trasera
        + mitadLado,- mitadLado,- mitadLado,
        - mitadLado,- mitadLado,- mitadLado,
        - mitadLado,+ mitadLado,- mitadLado,
        + mitadLado,+ mitadLado,- mitadLado,
        

    };
    GLfloat normales[] = { 
        0, 0, 1,   0, 0, 1,   0, 0, 1,   0, 0, 1,   // v0,v1,v2,v3 (front)
        1, 0, 0,   1, 0, 0,   1, 0, 0,   1, 0, 0,   // v0,v3,v4,v5 (right)
        0, 1, 0,   0, 1, 0,   0, 1, 0,   0, 1, 0,   // v0,v5,v6,v1 (top)
        -1, 0, 0,  -1, 0, 0,  -1, 0, 0,  -1, 0, 0,   // v1,v6,v7,v2 (left)
        0,-1, 0,   0,-1, 0,   0,-1, 0,   0,-1, 0,   // v7,v4,v3,v2 (bottom)
        0, 0,-1,   0, 0,-1,   0, 0,-1,   0, 0,-1 }; // v4,v7,v6,v5 (back)
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glNormalPointer(GL_FLOAT, 0, normales);
    glVertexPointer(3, GL_FLOAT, 0, vertices);

    glPushMatrix();
    glTranslatef(cX, cY, cZ);
    glRotatef(cubo->getRX(), 0,1.f, 0);
    glRotatef(cubo->getRY(), 1.f, 0, 0);
    glRotatef(cubo->getRZ(), 0, 0, 1.f);
    //glTranslatef(-cX, -cY, -cZ );
    //glTranslatef(-cX, -cY, 0);
    //glTranslatef(cX, cY, cZ);
    
    //
    
    //glTranslatef(-cX_2, -cY_2, 0.0f);

    glDrawArrays(GL_QUADS, 0, 24);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glPopMatrix();
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);/**/
}
void MotorGL::render() { 
    
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

bool MotorGL::inicializar(void * hwnd, double ancho, double alto) {
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

    glShadeModel(GL_SMOOTH);                    // shading mathod: GL_SMOOTH or GL_FLAT
    glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

    // enable /disable features
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    ////glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    ////glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_DEPTH_TEST);
    //glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    //glEnable(GL_CULL_FACE);

    // track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
    //glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
    //glEnable(GL_COLOR_MATERIAL);

    glClearColor(0, 0, 0, 0);                   // background color
    glClearStencil(0);                          // clear stencil buffer
    glClearDepth(1.0f);                         // 0 is near, 1 is far
    glDepthFunc(GL_LEQUAL);
    inicializarLuz();/**/

    //glEnable(GL_DEPTH_TEST);


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
    //glOrtho(0, ancho, alto,0, 0,1000);
    gluPerspective(60.f, fAspecto, 0.f, 1000.f);
    //glFrustum(0, ancho, alto, 0, -1000, 1000);
    //gluLookAt(ancho*0.5f, alto*.5f, 0, ancho * 0.5f, alto * .5f, 0, 0, 0,1.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();/**/


    //Mouse::getPosition(xMouse, yMouse);

    //
    //glTranslatef(0.0f, 0.0f, 0.0f);
    //glEnable(GL_TEXTURE_2D);
    /*glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
    return true; 
}
void MotorGL::inicializarLuz() {
    float ambiente = 0.2f;
    float difusa = 0.7f;
    float especular = 1.f;
    GLfloat luzAmbiente[] = { ambiente, ambiente, ambiente, 1.0f };
    GLfloat luzDifusa[] = { difusa, difusa, difusa, 1.0f };
    GLfloat luzEspecular[] = { especular, especular, especular, 1 };
    glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
    glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);

    
    float puntoLuz[4] = { 0, 0, 20, 1 }; 
    glLightfv(GL_LIGHT0, GL_POSITION, puntoLuz);
    glEnable(GL_LIGHT0);/**/
}
void MotorGL::ponerCamara(float posX, float posY, float posZ, float targetX, float targetY, float targetZ) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(posX, posY, posZ, targetX, targetY, targetZ, 0, 1, 0); // eye(x,y,z), focal(x,y,z), up(x,y,z)
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
Entity* MotorGL::drawLine(float* vertex, unsigned countVertex, float r, float g, float b, float a, unsigned width) {
   return NULL;
};
//template inline void EXPORTAR_MOTOR MotorGL::inicializar(HWND, double, double);
REGISTRAR_MODULO(MotorGL); 