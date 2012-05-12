// u2-dessin.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>         // cin, cout, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_draw.H>     // fonctions de dessin
#include <FL/fl_ask.H>
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u4-fonctions.h"
#include <FL/Fl_JPEG_Image.H>
#include <string.h>

// Declaration pour utiliser iostream
using namespace std;


// DessinerZone
void ZoneDessinDessinerCB( Fl_Widget* widget, void* data )
{
    // On efface toute la zone ( en dessinant dessus un rectangle plein, noir )

    fl_color(FL_BLACK);


    if (gDonnees.EnSaisie==0) //Si on est pas en saisie d'un chiffre dans une case (PROBLEME DE RECOUVREMENT DE LA FENETRE DE SAISIE)
    {
        // On dessine l'image
        Fl_JPEG_Image GrilleSudoku("images\\GrilleSudokuVide.jpg");

        GrilleSudoku.draw(X_ZONE, Y_ZONE );
    }


    //Image de fond pour le sudoku :)
    if (gDonnees.Dark==0) //En fonction du mode ou on se trouve (jeu ou IA)
    {
        // Affichage de l'image SUDOKU
        Fl_JPEG_Image Hello("images\\Hello.jpg");

        Hello.draw(X_ZONE+476, Y_ZONE-10 );

    }
    else if (gDonnees.Dark==1)
    {
        Fl_JPEG_Image Dark("images\\Dark.jpg");

        Dark.draw(X_ZONE+470, Y_ZONE-10 );
    }


    /*
    Debut de l'écriture de la grille sur la fenêtre
    Cette ecriture se fait en temps reel
    Donc si on change le tableau  ( grillin -> table [] )
    ça change en live sur la fenêtre
    */

    int i=0;
    int j=0;

    fl_message_font(FL_HELVETICA, 15);
    fl_font(FL_HELVETICA, 30);

    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++) // On fait des CASE en fonction de chaque chiffre
        {
            if (grillin.table[j+9*i]==0)
            {
                fl_draw(" ",X_ZONE+15 +j*50, Y_ZONE+35 +i*50); //Si on  0 dans le tableau, on affiche rien du tout
            }
            if (grillin.table[j+9*i]==1)
            {
                fl_draw("1",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
            }
            if (grillin.table[j+9*i]==2)
            {
                fl_draw("2",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
            }
            if (grillin.table[j+9*i]==3)
            {
                fl_draw("3",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
            }
            if (grillin.table[j+9*i]==4)
            {
                fl_draw("4",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
            }
            if (grillin.table[j+9*i]==5)
            {
                fl_draw("5",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
            }
            if (grillin.table[j+9*i]==6)
            {
                fl_draw("6",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
            }
            if (grillin.table[j+9*i]==7)
            {
                fl_draw("7",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
            }
            if (grillin.table[j+9*i]==8)
            {
                fl_draw("8",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
            }
            if (grillin.table[j+9*i]==9)
            {
                fl_draw("9",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
            }
        }



    }





}

