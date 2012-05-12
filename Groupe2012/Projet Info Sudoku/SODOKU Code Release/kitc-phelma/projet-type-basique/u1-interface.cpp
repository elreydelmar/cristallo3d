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
    gInterface.Fenetre->color(FL_DARK1) ;

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
    gInterface.BoutonFacile ->labelcolor( FL_DARK_RED ) ;
    gInterface.BoutonFacile->color( FL_WHITE ) ;
    gInterface.BoutonFacile->callback( BoutonFacileCB, NULL ) ;

        // Creation du bouton Difficulte 2
    gInterface.BoutonMoyen = new Fl_Button(600, 180, 80, 30, "Moyen") ;
    gInterface.BoutonMoyen ->labelcolor( FL_DARK_RED ) ;
    gInterface.BoutonMoyen->color( FL_WHITE ) ;
    gInterface.BoutonMoyen->callback( BoutonMoyenCB, NULL ) ;

        // Creation du bouton Difficulte 3
    gInterface.BoutonExpert = new Fl_Button(700, 180, 80, 30, "Expert") ;
    gInterface.BoutonExpert ->labelcolor( FL_DARK_RED ) ;
    gInterface.BoutonExpert->color( FL_WHITE ) ;
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



    gDonnees.Dark=0;
    gDonnees.Done=0;
    // Creation du bouton Vador
    gInterface.BoutonVador = new Fl_Button(680, 260, 100, 35, "Dark Side") ;
    gInterface.BoutonVador ->labelcolor( FL_RED ) ;
    gInterface.BoutonVador->color( FL_BLACK ) ;
    gInterface.BoutonVador->callback( BoutonVadorCB, NULL ) ;


        // Creation du bouton Chercher Sol Vador
    gInterface.BoutonChercherSolutions = new Fl_Button(650, 310, 140, 35, "Chercher Solutions") ;
    gInterface.BoutonChercherSolutions ->labelcolor( FL_WHITE ) ;
    gInterface.BoutonChercherSolutions->color( FL_DARK1 ) ;
    gInterface.BoutonChercherSolutions->callback( BoutonChercherSolutionsCB, NULL ) ;
    gInterface.BoutonChercherSolutions->hide();



    // Creation du bouton Aide
    gInterface.BoutonAide = new Fl_Button(700, 380, 60, 25, "Aide") ;
    gInterface.BoutonAide->callback( BoutonAideCB, NULL ) ;


    // Creation recommencer jeu
    gInterface.BoutonRecommencer = new Fl_Button(690, 424, 80, 25, "Reload") ;
    gInterface.BoutonRecommencer->callback( BoutonRecommencerCB, NULL ) ;

    // Creation du machin de selection

    gInterface.ChampSaisieNum = new Fl_Value_Input(30,30, 38, 50, "" ) ;
    gInterface.ChampSaisieNum->when( FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED ) ;
    gInterface.ChampSaisieNum->callback( ChampSaisieNumCB, NULL ) ;
    gInterface.ChampSaisieNum->hide();


   // CHRONO

    gInterface.Secondes = new Fl_Value_Output( 644, 140, 22, 22, "" ) ;
    gInterface.Secondes->value( gDonnees.Seconds );
    gInterface.Secondes->hide();



    gInterface.Minutes = new Fl_Value_Output( 622,140, 22, 22, "" ) ;
    gInterface.Minutes->value( gDonnees.Min ); // Minutes
    gInterface.Minutes->hide();


    gInterface.Heures = new Fl_Value_Output( 600, 140, 22, 22, "" ) ;
    gInterface.Heures->value( gDonnees.Heu ); // Heures
    gInterface.Heures->hide();



    // Affichage d'une erreur
    gInterface.NotificationErreur = new Fl_Output( 500, 380, 180, 25, "" ) ;

    // Affichage de la fenetre
    gInterface.Fenetre->end();
    gInterface.Fenetre->show();






}

void ActualiserInterface() // Cette fonction actualise l'interface
{
    gInterface.Fenetre->begin(); // On commence à modifier la fenêtre
    if (gDonnees.ActuON == 1 && gDonnees.DejaOccupe ==0) // Si on est en mode Actualiser l'interface ON et que la case n'est pas occupée
    {
        gInterface.ChampSaisieNum ->hide(); // On cache le champ de saisie

        gInterface.ChampSaisieNum = new Fl_Value_Input(gDonnees.CaseSaisieX+12,gDonnees.CaseSaisieY, 38, 50, "" ) ; // On cré le champ de saisie dans la case ou on a cliqué
        gInterface.ChampSaisieNum->textcolor(FL_RED);
        gInterface.ChampSaisieNum->textsize(30);
        gInterface.ChampSaisieNum->when( FL_WHEN_ENTER_KEY | FL_WHEN_NOT_CHANGED ) ;// Mode de déclenchement de la CB
        gInterface.ChampSaisieNum->callback( ChampSaisieNumCB, NULL ) ; //Callback du champ de saisie des chiffres
        gInterface.ChampSaisieNum->show(); //On l'affiche
    }
    if (gDonnees.Incorrect==1) // Affichage dans la barre de notification de l'état du programme (Erreurs, ou grille résolue)
    {
        gInterface.NotificationErreur->value( "Reponse incorrecte" ) ;
    }
    else if (gDonnees.Incorrect==2)
    {
        gInterface.NotificationErreur->value( "Valeur incorrecte" ) ;
    }
    else if (gDonnees.Incorrect==3)
    {
        gInterface.NotificationErreur->value( "" ) ;
    }
    else if (gDonnees.Incorrect==4)
    {
        gInterface.NotificationErreur->value( "Grille Resolue" ) ;
    }
    gInterface.Secondes->value( gDonnees.Seconds ); // On modifie le Timer.. On le modifie en temps réel dans Actualiser interface
    gInterface.Minutes->value( gDonnees.Min );
    gInterface.Heures->value( gDonnees.Heu );
    gInterface.Fenetre->end(); //On termine l'edition de la fenêtre
    gInterface.Fenetre->show(); //On affiche la fenêtre
    gDonnees.ActuON=0; // Actualiser OFF

    if (gDonnees.Recommencer==1) //Prise en charge de la fonction Reload : si Recommencer est à 1
    {
        int j=0;
        gInterface.Fenetre->hide(); //On cache la fenêtre
        //gInterface.Fenetre->end() ;
        CreerInterface() ; // On cré de nouveau l'interface

        // Initialisation du logiciel
        InitialiserDonnees() ; // On initialise les donnees
        gInterface.ZoneDessin->redraw() ; // On redessine la zone de dessin

        for (j=0; j<81 ; j++) //On pense aussi à réinitialiser la grille à 0
        {
            grillin.table [j]=0;
        }
        gDonnees.Time=0; //Timer à 0
        gDonnees.Recommencer=0; // On quitte recommencer
    }

}
