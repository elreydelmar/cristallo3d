#include "fenetre.h"

// Globales
Fenetre* g_fenetre;

int create_fenetre(HINSTANCE instance)
{
    static int appel = 0;
    if(appel == 1)
        return 1;
    else
        appel = 1;

    g_fenetre = (Fenetre*) malloc(sizeof(Fenetre));
    register_classe_fenetre(&(g_fenetre->fenetre), instance);
    g_fenetre->instance = instance;

    // Chargement de OpenGL
    Rect position;
        position.x = 0;
        position.y = 0;
        position.w = WIDTH - WIDTH_COLONNE;
        position.h = HEIGHT;
    init_gl(g_fenetre, position, instance);

    // Chargement du menu
    g_fenetre->menu = CreateWindow("classeF", "menu", WS_CHILD | WS_VISIBLE, position.w, 0, WIDTH_COLONNE, HEIGHT, g_fenetre->fenetre, NULL, instance, NULL);
    afficher_boutons(g_fenetre);

    // Chargement des events
    init_event();

    // Pour le process
    SetWindowLong(g_fenetre->fenetre, GWL_USERDATA, 1);
    SetWindowLong(g_fenetre->menu, GWL_USERDATA, 2);

    // Affichages
    ShowWindow(g_fenetre->fenetre, SW_SHOW);
    UpdateWindow(g_fenetre->fenetre);

    return 0;
}

int register_classe_fenetre(HWND *hFenetre, HINSTANCE instance)
{
    WNDCLASS classe;

    classe.style = CS_HREDRAW | CS_VREDRAW;
    classe.lpfnWndProc = evenement;
    classe.cbClsExtra = 0;
    classe.cbWndExtra = 0;
    classe.hInstance = NULL;
    classe.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    classe.hCursor = LoadCursor(NULL, IDC_ARROW);
    classe.hbrBackground = (HBRUSH)(1 + COLOR_BTNFACE);
    classe.lpszMenuName =  NULL;
    classe.lpszClassName = "classeF";

    // On prévoit quand même le cas où ça échoue
    RegisterClass(&(classe));

    *hFenetre = CreateWindow("classeF", "Cristallographie en 3d", WS_OVERLAPPEDWINDOW,
                                   CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT,
                                                   NULL, NULL, instance, NULL);
    return 0;
}

int init_gl(Fenetre* fenetre, Rect position, HINSTANCE instance)
{
    fenetre->gl = CreateWindow("STATIC", "Calcul de l'affichage en cours...", WS_CHILD | WS_VISIBLE, position.x, position.y, position.w, position.h, fenetre->fenetre, NULL, instance, NULL);

    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    // get the device context (DC)
    fenetre->dc = GetDC(fenetre->gl);

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
    iFormat = ChoosePixelFormat( fenetre->dc, &pfd );
    SetPixelFormat( fenetre->dc, iFormat, &pfd );

    // create and enable the render context (RC)
    fenetre->rc = wglCreateContext(fenetre->dc);
    wglMakeCurrent(fenetre->dc, fenetre->rc);

    return 0;
}

void delete_fenetre()
{
    static int appel = 0;
    if(appel == 1)
        return;
    else
        appel = 1;

    // Destruction d'OpenGL
    wglMakeCurrent( NULL, NULL );
    wglDeleteContext(g_fenetre->rc );
    ReleaseDC(g_fenetre->gl, g_fenetre->dc);

    // Destruction de la fenetre
    DestroyWindow(g_fenetre->fenetre); // Detruit aussi les CHILD
    UnregisterClass("classF",g_fenetre->instance);

    free(g_fenetre);
}

void update_gl()
{
    SwapBuffers(g_fenetre->dc);
}

void redimensionner(HWND fenetre, int width, int height)
{
    // Erreur ? Pas cense arriver si je mets un height min
    if(height == 0)
        height = 1;


    // On recupére l'handle gl
    HWND handle_gl = GetWindow(fenetre, GW_CHILD);
    HWND handle_menu = g_fenetre->menu;

    // On regarde l'agrandissement
    int new_x = width - WIDTH_COLONNE;
    int x,y;
    int gl_width, gl_height;


    double new_ratio = (double)new_x/(double)height;
    if(new_ratio > ratio)   // width est trop grand
    {
        gl_height = height;
        gl_width = (int)(ratio*height);
        x = (new_x-gl_width)/2;  // on centre en x
        y = 0;
    }
    else                    // height est trop grand
    {
        gl_width = new_x;
        gl_height = (int)((double)gl_width/ratio);
        x = 0;
        y = (height-gl_height)/2;
    }

    // On redimensionne la fenetre opengl
    MoveWindow(handle_gl, 0, 0, new_x, height, TRUE);
    // On repositionne la fenetre static
    MoveWindow(handle_menu, new_x, 0, WIDTH_COLONNE, height, TRUE);

    glViewport(x,y,gl_width,gl_height);
}

// On le garde

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
