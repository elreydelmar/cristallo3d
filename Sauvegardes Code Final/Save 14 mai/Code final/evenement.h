#ifndef EVENEMENT_H_INCLUDED
#define EVENEMENT_H_INCLUDED

#include "fenetre.h"
#include "actions.h"

#include <time.h>
#include <windowsx.h>


extern Fenetre* g_fenetre;
extern EventStatus* event_status;

// Les fonctions

LRESULT CALLBACK evenement(HWND, UINT, WPARAM, LPARAM);
LRESULT evenement_principale(HWND, UINT, WPARAM, LPARAM);
LRESULT evenement_menu(HWND, UINT, WPARAM, LPARAM);

int recuperer_evenement();
void evenement_clavier();
void traiter_evenement();

void evenement_bouton(HWND, UINT, WPARAM, LPARAM);

// Predicats
int is_in(POINT p, RECT r);

#endif // EVENEMENT_H_INCLUDED
