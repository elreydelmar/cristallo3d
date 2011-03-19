#ifndef EVENEMENT_H_INCLUDED
#define EVENEMENT_H_INCLUDED

#include "fenetre.h"

extern Fenetre* g_fenetre;

LRESULT CALLBACK evenement(HWND, UINT, WPARAM, LPARAM);

int recuperer_evenement();
void traiter_evenement();


#endif // EVENEMENT_H_INCLUDED
