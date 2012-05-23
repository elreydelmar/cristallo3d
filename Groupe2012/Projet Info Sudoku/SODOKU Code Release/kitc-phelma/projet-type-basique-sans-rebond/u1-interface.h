// u1-interface.h
// Sentinelle d'inclusion
#ifndef _u1_interface_h
#define _u1_interface_h

// Declarations externes - inclusion des fichiers d'entete
#include "main.h"
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Button.H>

// Definition des constantes
#define X_ZONE  20      // X de la zone
#define Y_ZONE  40      // Y de la zone
#define L_ZONE  400     // Largeur de la zone
#define H_ZONE  400     // Hauteur de la zone

// Declaration des objets de l'interface
struct Interface
{
    Fl_Double_Window*   Fenetre ;
    DrawingArea*        ZoneDessin ;
    Fl_Button*          BoutonQuitter ;
    Fl_Button*          BoutonAction ;
} ;

// Declaration des objets de l'interface generale - ne pas supprimer
extern struct Interface gInterface ;


// Declaration des sous-programmes
void CreerInterface();
void ActualiserInterface();

#endif // _u1_interface_h
