#ifndef EVENEMENT_H_INCLUDED
#define EVENEMENT_H_INCLUDED

#include <windows.h>


typedef struct Fenetre Fenetre;
struct Fenetre
{
    HWND handle;
    MSG message;
    WNDCLASS classe;
    HINSTANCE instance;
};

LRESULT CALLBACK evenement(HWND, UINT, WPARAM, LPARAM);

int recuperer_evenement(Fenetre* fenetre);
void traiter_evenement(Fenetre* fenetre);


#endif // EVENEMENT_H_INCLUDED
