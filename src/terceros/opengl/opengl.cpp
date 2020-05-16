#ifndef __MOTORGL
#define __MOTORGL


#include "opengl.h"


MotorGL::~MotorGL() {

}


void MotorGL::renderizar() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glColor3f(0.0f, 0.0f, 1.0f);
    glRectf(100.f, 150.0f, 150.0f, 100.0f);
    
    //glFlush();
    SwapBuffers(ghDC);
}

void MotorGL::inicializar(HWND hwnd, double ancho, double alto) {
    ghDC = GetDC(hwnd);
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
    glMatrixMode(GL_PROJECTION);
    //aspect = (GLfloat)width / height;
    //gluPerspective(45.0, aspect, 3.0, 7.0);
    //glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, ancho, alto, 0);
    glMatrixMode(GL_MODELVIEW);
    //glEnable(GL_TEXTURE_2D);
    //glEnable(GL_BLEND)
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA)
}
BOOL MotorGL::bSetupPixelFormat(HDC hdc) {
    PIXELFORMATDESCRIPTOR pfd, * ppfd;
    int pixelformat;

    ppfd = &pfd;

    ppfd->nSize = sizeof(PIXELFORMATDESCRIPTOR);
    ppfd->nVersion = 1;
    ppfd->dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
        PFD_DOUBLEBUFFER;
    ppfd->dwLayerMask = PFD_MAIN_PLANE;
    ppfd->iPixelType = PFD_TYPE_COLORINDEX;
    ppfd->cColorBits = 8;
    ppfd->cDepthBits = 16;
    ppfd->cAccumBits = 0;
    ppfd->cStencilBits = 0;

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
#endif // !__MOTORGL