#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include "evenement.h"
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

/* Les constantes */
#include "const_fenetre.h"

/* Les types */
typedef struct Rect Rect;
struct Rect
{
    int x;
    int y;
    int w;
    int h;
};

typedef struct Contexte_GL Contexte_GL;
struct Contexte_GL
{
    HWND hWnd;
    HDC dc;
    HGLRC rc;
};

// Fonctions Windows
int init_fenetre(Fenetre* fenetre, HINSTANCE instance, Contexte_GL** contexte_gl);
Fenetre ouvrir_fenetre(HINSTANCE instance);
void afficher_fenetre(Fenetre* fenetre, int mode);
void update_fenetre(Fenetre* fenetre);
int fermer_fenetre(Fenetre* fenetre);
int end_fenetre(Fenetre* fenetre, Contexte_GL* contexte_gl);

// Fonctions OpenGL
int  init_gl(Fenetre* fenetre, Contexte_GL* contexte, Rect position);
int  delete_gl(Contexte_GL* contexte);
void update_gl(Contexte_GL* contexte);

void sample_dessin_2d();
void sample_dessin_3d();


#endif // FENETRE_H_INCLUDED
