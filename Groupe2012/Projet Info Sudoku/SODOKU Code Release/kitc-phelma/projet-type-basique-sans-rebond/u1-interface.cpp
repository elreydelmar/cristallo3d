// u1-interface.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>         // cin, cout, ...
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// Definition des donnees de l'interface - structure globale de variables
struct Interface gInterface ;

// CreerInterface
void CreerInterface()
{
    // Creation de la fenetre principale
    gInterface.Fenetre = new Fl_Double_Window(800,600);
    gInterface.Fenetre->label("Projet Type") ;
    gInterface.Fenetre->begin() ;

    // Creation de la zone de dessin
    gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL ) ;
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL ) ;

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(20, 460, 100, 20, "Quitter") ;
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL ) ;

    // Creation du bouton Action
    gInterface.BoutonAction = new Fl_Button(580, 50, 100, 20, "Action") ;
    gInterface.BoutonAction->callback( BoutonActionCB, NULL ) ;

    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}

void ActualiserInterface()
{

}
