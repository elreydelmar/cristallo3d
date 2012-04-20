// u3-callbacks.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>     // cout, cin, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_ask.H>  // fl_message, fl_alert, fl_ask
#include <FL/Fl_File_Chooser.H> // fl_file_chooser
// Programmes locaux
#include "u1-interface.h"
#include "u3-callbacks.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

int avecousans = 0;


// TraiterCycle
void TraiterCycleCB()
{
    // Trace pour bien montrer que la fonction est appelee cycliquement
    // printf(""Appel de TraiterCycleCB");
        ActualiserInterface();


    // Deplacement de la boule
    if (avecousans == 0)
        DeplacerBouleSansRebond() ;
    else if (avecousans ==1)
        DeplacerBouleAvecRebond() ;

    else
     printf("Erreur\n");

    // On redessine la zone
    gInterface.ZoneDessin->redraw() ;

    // Code a activer en cas de probleme pour saisir les evenements du clavier
    // Probleme : si les evenements du clavier ne sont pas bien pris en compte pour agir sur la zone de dessin.
    // Solution : On ramene systematiquement le focus des evenements sur la zone de dessin
    // Attention, cela peut perturber certains elements d'interface comme des champs de saisie texte ou numerique

    // Fl::focus(gInterface.ZoneDessin);

    // Fin code a activer en cas de probleme
}

// ZoneDessinSourisCB
void ZoneDessinSourisCB( Fl_Widget* widget, void* data )
{
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!

    if ( Fl::event() == FL_PUSH )
    {
       //do
        //{
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());

        // On repositionne la boule a l'endroit du clic
        gDonnees.Boule.X = Fl::event_x() - X_ZONE ;
        gDonnees.Boule.Y = Fl::event_y() - Y_ZONE ;
        //}

        //while ( Fl::event() == FL_PUSH );
    }

}

// ZoneDessinClavierCB
void ZoneDessinClavierCB( Fl_Widget* widget, void* data )
{
    // Definition des variables
    int Touche ;

    // Recuperation de la touche clavier activee
    Touche = Fl::event_key() ;

    // Traitement de la touche
    switch ( Touche )
    {
        // Touches speciales
        case FL_Left :
            printf("Appui sur la touche Gauche\n");
            gDonnees.Boule.VX = gDonnees.Boule.VX - 1;
            break;
        case FL_Right :
            printf("Appui sur la touche Droite\n");
             gDonnees.Boule.VX = gDonnees.Boule.VX + 1;
            break;
        case FL_Up :
            printf("Appui sur la touche Haut\n");
            gDonnees.Boule.VY = gDonnees.Boule.VY - 1;
            break ;
        case FL_Down :
            printf("Appui sur la touche Bas\n");
            gDonnees.Boule.VY = gDonnees.Boule.VY +1;
            break ;
        // Caracteres
        case ' ' :
            printf("Appui sur la touche Espace\n");
            break ;
        case 'a' :
            printf("Appui sur le caractere a\n");
            break ;
        case 'b' :
            printf("Appui sur le caractere b\n");
            break ;
        case '1' :
            printf("Appui sur le caractere 1\n");
            break ;
        case '2' :
            printf("Appui sur le chiffre 2\n");
            break ;
    }
}

void BoutonQuitterCB(Fl_Widget* w, void* data)
{
    // Fin du programme
    exit(0) ;
}

void BoutonActionCB(Fl_Widget* w, void* data)
{
    gDonnees.Boule.X = L_ZONE / 2 ;
    gDonnees.Boule.Y = (L_ZONE / 2 )-20 ;
     printf("BoutonActionCB\n");
}


void BoutonAvecCB(Fl_Widget* w, void* data)
{
    avecousans = gInterface.BoutonAvec->value();
     printf("BoutonAvecCB\n");
}

