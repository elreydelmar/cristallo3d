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

}

// ZoneDessinSourisCB
void ZoneDessinSourisCB( Fl_Widget* widget, void* data )
{
    // ATTENTION : X et Y ne sont pas relatifs a la zone mais a la fenetre qui la contient !!!!
    // Définition des variables
    int X, Y ;          // X et Y du clic
    int IClic, JClic;

    if ( Fl::event() == FL_PUSH )
    {
        // Gestion des clics souris du jeu mastermind

        // Recuperation des coordonnees X,Y du clic souris
        // ATTENTION : X et Y ne sont pas relatifs à la zone mais à la fenetre qui la contient !!!!"
        X =  Fl::event_x() ;
        Y = Fl::event_y() ;

        // Transformation des coordonnees du clic souris en coordonnes IClic/JClic du tableau de jeu
        JClic = ( X - X_ZONE ) / 40;
        IClic = ( Y - Y_ZONE ) / 40;

        if (IClic == 1 && JClic > 0 && JClic < 7) // Pion de couleur selectionne
            gDonnees.PionCourant = JClic -1;

        if (IClic-3 == gDonnees.LigneCourante && JClic > 1 && JClic < 6)
            gDonnees.TableauJeu[IClic-3][JClic-2]=gDonnees.PionCourant;

        // On redessine la zone
        gInterface.ZoneDessin->redraw() ;
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
        // Touches speciales
        case FL_Left :
            printf("Appui sur la touche Gauche\n");
            break;
        case FL_Right :
            printf("Appui sur la touche Droite\n");
            break;
        case FL_Up :
            printf("Appui sur la touche Haut\n");
            break ;
        case FL_Down :
            printf("Appui sur la touche Bas\n");
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

void BoutonRejouerCB(Fl_Widget* w, void* data)
{
    printf("BoutonRejouerCB\n");
    InitialiserDonnees();
    gInterface.BoutonValider->position(10*40+20,(gDonnees.LigneCourante+3)*40+20); // Postionner le bouton Valider en face de la ligne de jeu courante
    gInterface.Fenetre->redraw();
    // Solution alternative plus localisee pour redessiner le bouton valider
    //gInterface.BoutonValider->hide();
    //gInterface.BoutonValider->redraw();
    //gInterface.BoutonValider->show();
}

void BoutonValiderCB(Fl_Widget* w, void* data)
{
    printf("BoutonValiderCB\n");
    int j;
    int CompteurPionsJoues = 0;

    for(j=0;j<=3;j++)
       if (gDonnees.TableauJeu[gDonnees.LigneCourante][j] != -1) CompteurPionsJoues++;

    if (CompteurPionsJoues == 4)
    {
        compteBPMP();
        if (gDonnees.BienPlaces[gDonnees.LigneCourante] == 4)
        {
            if(gDonnees.SentinelleSolution == 0)
                gDonnees.GameOver = 2;
        }
        else if(gDonnees.LigneCourante < NB_MAX_COUPS-1)
        {
            gDonnees.LigneCourante++;
            gInterface.BoutonValider->position(10*40+20,(gDonnees.LigneCourante+3)*40+20);
            gInterface.Fenetre->redraw();
            // Solution alternative plus localisee pour redessiner le bouton valider
            //gInterface.BoutonValider->hide();
            //gInterface.BoutonValider->redraw();
            //gInterface.BoutonValider->show();
        }
        else gDonnees.GameOver = 1;

        // On redessine la zone
        gInterface.ZoneDessin->redraw() ;
    }
}

void BoutonSolutionCB(Fl_Widget* w, void* data)
{
    printf("BoutonSolutionCB\n");
    gDonnees.SentinelleSolution = 1;
    if (gDonnees.GameOver == 0)
        gDonnees.GameOver = 1;

    // On redessine la zone
    gInterface.ZoneDessin->redraw();
}
