#ifndef EVENEMENT_H_INCLUDED
#define EVENEMENT_H_INCLUDED

#include "fenetre.h"

// Le type de notification d'evenement
typedef struct EventStatus EventStatus;
struct EventStatus
{

};

extern Fenetre* g_fenetre;
extern EventStatus* event_status;

// Les fonctions

LRESULT CALLBACK evenement(HWND, UINT, WPARAM, LPARAM);

int recuperer_evenement();
void traiter_evenement();


// Controle de event_status
void init_event_status();
void delete_event_status();
void evenement_bouton(HWND, UINT, WPARAM, LPARAM);


#endif // EVENEMENT_H_INCLUDED
