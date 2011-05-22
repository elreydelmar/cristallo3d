#ifndef FENETRE_H_INCLUDED
#define FENETRE_H_INCLUDED

#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

#include "boutons.h"

/* Les constantes */
#include "const_fenetre.h"
#include "type_fenetre.h"

/* Les types */

typedef struct Rect Rect;
struct Rect
{
    int x;
    int y;
    int w;
    int h;
};

// Les extern
extern LRESULT CALLBACK evenement(HWND, UINT, WPARAM, LPARAM);
extern void init_event();
extern Fenetre* g_fenetre;

// Fonctions refaites simplifiees
/// TODO : GESTION DES ERREURS
int create_fenetre(HINSTANCE instance);  // Contient une structure de controle pour qu'il n'y ait qu'un seul appel
    int register_classe_fenetre(HWND *hFenetre, HINSTANCE instance);
    int init_gl(Fenetre* fenetre);   // Contient une structure de controle pour qu'il n'y ait qu'un seul appel
void delete_fenetre();


// Les evenements
void update_gl();

void redimensionner(HWND fenetre, int width, int height);

void afficher_image();



#endif // FENETRE_H_INCLUDED
