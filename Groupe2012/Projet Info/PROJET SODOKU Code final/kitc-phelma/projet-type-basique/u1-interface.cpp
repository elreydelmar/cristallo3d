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
    gInterface.Fenetre = new Fl_Double_Window(800,515);
    gInterface.Fenetre->label("Jeu Sudoku") ;
    gInterface.Fenetre->begin() ;
    gInterface.Fenetre->color(FL_DARK_CYAN) ;

    // Creation de la zone de dessin
    gInterface.ZoneDessin = new DrawingArea(X_ZONE,Y_ZONE,L_ZONE,H_ZONE);
    gInterface.ZoneDessin->draw_callback( ZoneDessinDessinerCB, NULL ) ;
    gInterface.ZoneDessin->mouse_callback( ZoneDessinSourisCB, NULL ) ;
    gInterface.ZoneDessin->keyboard_callback( ZoneDessinClavierCB, NULL ) ;

    // Creation du bouton Quitter
    gInterface.BoutonQuitter = new Fl_Button(680, 460, 100, 35, "Quitter") ;
    gInterface.BoutonQuitter ->labelcolor( FL_WHITE ) ;
    gInterface.BoutonQuitter->color( FL_DARK_RED ) ;
    gInterface.BoutonQuitter->callback( BoutonQuitterCB, NULL ) ;

    // Creation du bouton Difficulte 1
    gInterface.BoutonFacile = new Fl_Button(500, 180, 80, 30, "Facile") ;
    gInterface.BoutonFacile ->labelcolor( FL_WHITE ) ;
    gInterface.BoutonFacile->color( FL_DARK_MAGENTA ) ;
    gInterface.BoutonFacile->callback( BoutonFacileCB, NULL ) ;

        // Creation du bouton Difficulte 2
    gInterface.BoutonMoyen = new Fl_Button(600, 180, 80, 30, "Moyen") ;
    gInterface.BoutonMoyen ->labelcolor( FL_WHITE ) ;
    gInterface.BoutonMoyen->color( FL_DARK_MAGENTA ) ;
    gInterface.BoutonMoyen->callback( BoutonMoyenCB, NULL ) ;

        // Creation du bouton Difficulte 3
    gInterface.BoutonExpert = new Fl_Button(700, 180, 80, 30, "Expert") ;
    gInterface.BoutonExpert ->labelcolor( FL_WHITE ) ;
    gInterface.BoutonExpert->color( FL_DARK_MAGENTA ) ;
    gInterface.BoutonExpert->callback( BoutonExpertCB, NULL ) ;

    //Création du bouton solution ou non :
    gInterface.GroupeBoutonsSolution = new Fl_Group( 520, 460, 100, 20, "" ) ;
    gInterface.GroupeBoutonsSolution->begin() ;

    gInterface.BoutonSolOui = new Fl_Round_Button( 520, 460, 100, 20, "Solution") ;
    gInterface.BoutonSolOui->type(FL_RADIO_BUTTON) ;
    gInterface.BoutonSolOui ->callback(BoutonSolutionCB, NULL ) ;


    gInterface.GroupeBoutonsSolution->end();
    gInterface.BoutonSolOui ->hide();

    // Creation du bouton Chuck Norris
    gInterface.BoutonChuck = new Fl_Button(510, 220, 100, 35, "Chuck Norris") ;
    gInterface.BoutonChuck ->labelcolor( FL_WHITE ) ;
    gInterface.BoutonChuck->color( FL_DARK_RED ) ;
    gInterface.BoutonChuck->callback( BoutonChuckCB, NULL ) ;
    gInterface.BoutonChuck -> hide();

   /* Fl_Check_Button* Solution ;

    gInterface.Solution = new Fl_Check_Button(520, 460, 100, 20, "Solution ?") ;
    gInterface.Solution->callback( SolutionCB, NULL ) ;
    */

    //Konami code :)
    Fl_Button* BoutonKonami ;

    gInterface.BoutonKonami = new Fl_Button( 600, 500, 100, 20, "bouton Konami !" ) ;
    gInterface.BoutonKonami->callback( BoutonKonamiCB, NULL ) ;



    //grille grillin;
    //CreationGrille(&grillin);

/*
    // Création bouton saisie num
    Fl_Value_Output * ChampNum;
    gInterface.ChampNum = new Fl_Value_Output( X_ZONE , Y_ZONE , 50, 50 , "");
    gInterface.ChampNum -> value (0);
*/




    // Creation du bouton Aide
    gInterface.BoutonAide = new Fl_Button(700, 400, 60, 25, "Aide") ;
    gInterface.BoutonAide->callback( BoutonAideCB, NULL ) ;


    // Creation du machin de selection
    Fl_Value_Input* ChampSaisieNum ;
    gInterface.ChampSaisieNum = new Fl_Value_Input(30,30, 50, 50, "" ) ;
    gInterface.ChampSaisieNum->when( FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED ) ;
    gInterface.ChampSaisieNum->callback( ChampSaisieNumCB, NULL ) ;
    gInterface.ChampSaisieNum->hide();



    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
}

void ActualiserInterface()
{
    gInterface.Fenetre->begin();
    if (gDonnees.ActuON == 1 && gDonnees.DejaOccupe ==0)
    {
        gInterface.ChampSaisieNum ->hide();

        gInterface.ChampSaisieNum = new Fl_Value_Input(gDonnees.CaseSaisieX,gDonnees.CaseSaisieY, 50, 50, "" ) ;

    }
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();
    gDonnees.ActuON=0;

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
