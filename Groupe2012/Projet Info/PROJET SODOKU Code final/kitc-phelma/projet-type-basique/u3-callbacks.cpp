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

// TraiterCycle
void TraiterCycleCB()
{
    // Trace pour bien montrer que la fonction est appelee cycliquement
    // printf(""Appel de TraiterCycleCB");



    // On redessine la zone
    gInterface.ZoneDessin->redraw() ;
    gInterface.BoutonKonami ->hide() ;

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
        printf("Mouse push = %i x = %i y = %i\n", Fl::event_button(), Fl::event_x(), Fl::event_y());
    }
}

// ZoneDessinClavierCB
void ZoneDessinClavierCB( Fl_Widget* widget, void* data )
{
    // Definition des variables
    int Touche ;
    int a,b,c,d,e,f,g,h,i = 0; // Pour le Konami code;)

    // Recuperation de la touche clavier activee
    Touche = Fl::event_key() ;

    // Traitement de la touche
    switch ( Touche )
    {
        // Touches speciales
        case FL_Left :
            printf("Appui sur la touche Gauche\n");
            a = 1;
            break;
        case FL_Right :
            printf("Appui sur la touche Droite\n");
            b = 1;
            break;
        case FL_Up :
            printf("Appui sur la touche Haut\n");
            c = 1;
            break ;
        case FL_Down :
            printf("Appui sur la touche Bas\n");
            d = 1;
            break ;
        // Caracteres
        case ' ' :
            printf("Appui sur la touche Espace\n");
            break ;
        case 'a' :
            printf("Appui sur le caractere a\n");
            e = 1;
            break ;
        case 'b' :
            printf("Appui sur le caractere b\n");
            f = 1;
            break ;
        case '1' :
            printf("Appui sur le caractere 1\n");
            break ;
        case '2' :
            printf("Appui sur le chiffre 2\n");
            break ;
        if ((a && b && c && d && e && f) == 1)
            {
                gInterface.BoutonKonami ->show() ;
            }
        else{};
    }
}

//Fin du programme :

void BoutonQuitterCB(Fl_Widget* w, void* data)
{
  int Reponse ;

    Reponse = fl_ask("Voulez vous réellement quitter ce jeu merveilleux ?");
    if (Reponse == 1) {exit(0) ;}
    else {};
}

//Bouton qui permet d'afficher l'aide...

void BoutonAideCB(Fl_Widget* w, void* data)
{
    fl_alert("Tu dois bien être capable de te débrouiller tout seul nan ? :)" );
}

//Bouton d'affichage de la solution du sudoku...

void SolutionCB (Fl_Widget* w, void* data)
{
    fl_alert("Cette fonction est inutile :)" );
}

void BoutonKonamiCB(Fl_Widget* w, void* data)
{
     fl_alert("Bravo tu as réussi à trouver le konami code ! ! ! " );
}

