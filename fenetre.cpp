#include "fenetre.h"

int init_fenetre(Fenetre* fenetre, HINSTANCE instance, Contexte_GL** contexte_gl)
{
    *fenetre = ouvrir_fenetre(instance);

    // Chargement de OpenGL
    *contexte_gl = (Contexte_GL*) malloc(sizeof(Contexte_GL));

    Rect position;
        position.x = 0;
        position.y = 0;
        position.w = WIDTH - WIDTH_COLONNE;
        position.h = HEIGHT;
    init_gl(fenetre, *contexte_gl, position);

    return 0;
}

Fenetre ouvrir_fenetre(HINSTANCE instance)
{
    Fenetre fenetre;

    fenetre.classe.style = 0;
    fenetre.classe.lpfnWndProc = evenement;
    fenetre.classe.cbClsExtra = 0;
    fenetre.classe.cbWndExtra = 0;
    fenetre.classe.hInstance = NULL;
    fenetre.classe.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    fenetre.classe.hCursor = LoadCursor(NULL, IDC_ARROW);
    fenetre.classe.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    fenetre.classe.lpszMenuName =  NULL;
    fenetre.classe.lpszClassName = "classeF";

    fenetre.instance = instance;


    // On prévoit quand même le cas où ça échoue
    RegisterClass(&(fenetre.classe));

    fenetre.handle = CreateWindow("classeF", "OpenGL", WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
                                                   NULL, NULL, fenetre.instance, NULL);
    return fenetre;
}

void afficher_fenetre(Fenetre* fenetre, int mode)
{
    ShowWindow(fenetre->handle, mode);
}

void update_fenetre(Fenetre* fenetre)
{
    UpdateWindow(fenetre->handle);
}

int fermer_fenetre(Fenetre* fenetre)
{
    DestroyWindow(fenetre->handle);
    UnregisterClass("classF",fenetre->instance);

    return 0;
}

int end_fenetre(Fenetre* fenetre, Contexte_GL* contexte_gl)
{
    delete_gl(contexte_gl);
    fermer_fenetre(fenetre);
    return 0;
}

int  init_gl(Fenetre* fenetre, Contexte_GL* contexte, Rect position)
{
    contexte->hWnd = CreateWindow("STATIC", "contexte_gl", WS_CHILD | WS_VISIBLE, position.x, position.y, position.w, position.h, fenetre->handle, NULL, fenetre->instance, NULL);

    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    // get the device context (DC)
    contexte->dc = GetDC( contexte->hWnd);

    // set the pixel format for the DC
    ZeroMemory( &pfd, sizeof( pfd ) );
    pfd.nSize = sizeof( pfd );
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
                  PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat( contexte->dc, &pfd );
    SetPixelFormat( contexte->dc, iFormat, &pfd );

    // create and enable the render context (RC)
    contexte->rc = wglCreateContext(contexte->dc);
    wglMakeCurrent(contexte->dc, contexte->rc);

    return 0;
}

void update_gl(Contexte_GL* contexte)
{
    SwapBuffers(contexte->dc);
}

int  delete_gl(Contexte_GL* contexte)
{
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext(contexte->rc );
    ReleaseDC(contexte->hWnd, contexte->dc);
    DestroyWindow(contexte->hWnd);

    return 0;
}

void sample_dessin_2d()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3ub(255,0,0);    glVertex2d(-0.75,-0.75);
        glColor3ub(0,255,0);    glVertex2d(0,0.75);
        glColor3ub(0,0,255);    glVertex2d(0.75,-0.75);
    glEnd();

    glFlush();
}

void sample_dessin_3d()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3ub(255,0,0);    glVertex3d(-0.75,-0.75,-10.);
        glColor3ub(0,255,0);    glVertex3d(0,0.75,-10.);
        glColor3ub(0,0,255);    glVertex3d(0.75,-0.75,-10.);
    glEnd();

    glFlush();
}
