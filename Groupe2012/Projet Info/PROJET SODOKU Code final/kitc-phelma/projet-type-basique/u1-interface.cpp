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
    gInterface.Fenetre->label("Sudoku qui tue ! ") ;
    gInterface.Fenetre->begin() ;

    // Creation de la zone de dessin
    gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL ) ;
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL ) ;

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(580, 460, 100, 20, "Quitter") ;
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL ) ;

    //Création du bouton solution ou non :
    Fl_Check_Button* Solution ;

    gInterface.Solution = new Fl_Check_Button(80, 500, 100, 20, "Solution ?") ;
    gInterface.Solution->callback( SolutionCB, NULL ) ;

    //Konami code :)

    Fl_Button* BoutonKonami ;

    gInterface.BoutonKonami = new Fl_Button( 600, 500, 100, 20, "bouton Konami !" ) ;
    gInterface.BoutonKonami->callback( BoutonKonamiCB, NULL ) ;




    // Creation du bouton Aide
    gInterface.BoutonAide = new Fl_Button(580, 50, 100, 20, "Aide") ;
    gInterface.BoutonAide->callback( BoutonAideCB, NULL ) ;

    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}

void ActualiserInterface()
{

}
// Pour le menu du programme !

/*Fl_Menu_Item menuitems[] = {
{ "&Fichier", 0, 0, 0, FL_SUBMENU },
{ "&Nouvelle grille", FL_CTRL + 'n', (Fl_Callback *)NouvelleGrille},
{ "&Konamicode", FL_Up + FL_Down + FL_Left + FL_Right + 'a' + 'b', (Fl_Callback *)BoutonKonamiCB },

{ 0 },
};

//Menu au dessus :

    Fl_Menu_Bar *m = new Fl_Menu_Bar(0, 0, 640, 30);
    m->copy(menuitems);*/



 /* static Fl_Menu_Item	items[] =
   {
    { "&Jeu", 0, 0, 0, FL_SUBMENU },
    { "&Nouvele grille", FL_COMMAND | 'n', NouvelleGrille, 0, FL_MENU_DIVIDER },
    { "&Vérifier solution", FL_COMMAND | 'c', VerifSolution, 0, 0 },
    { "&Résoudre la grille", FL_COMMAND | 's', SolutionCB, 0, FL_MENU_DIVIDER },
    { "&Quitter", FL_COMMAND | 'q', BoutonQuitterCB, 0, 0 },
    { 0 },

    { 0 },
    { "&Help ! ", 0, 0, 0, FL_SUBMENU },
    { "&About Sudoku", FL_F + 1, BoutonAideCB, 0, 0 },
    { 0 },
    { 0 }
  };



  menubar_ = new Fl_Sys_Menu_Bar(0, 0, 640, 25);
  menubar_->menu(items);*/
