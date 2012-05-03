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

    //Image de fond pour le sudoku :)
    if (gDonnees.Dark==0)
    {
        Fl_JPEG_Image Hello("C:\\Users\\Antoine\\Desktop\\Cristallo3D\\Groupe2012\\Projet Info\\PROJET SODOKU Code final\\kitc-phelma\\Hello.jpg");

        Hello.draw(X_ZONE+420, Y_ZONE-10 );

    }
    else if (gDonnees.Dark==1)
    {
        Fl_JPEG_Image Dark("C:\\Users\\Antoine\\Desktop\\Cristallo3D\\Groupe2012\\Projet Info\\PROJET SODOKU Code final\\kitc-phelma\\Dark.jpg");

        Dark.draw(X_ZONE+420, Y_ZONE-10 );
    }


    Fl_JPEG_Image GrilleSudoku("C:\\Users\\Antoine\\Desktop\\Cristallo3D\\Groupe2012\\Projet Info\\PROJET SODOKU Code final\\kitc-phelma\\GrilleSudokuVide.jpg");

    GrilleSudoku.draw(X_ZONE, Y_ZONE );



    int i=0;
    int j=0;

    fl_message_font(FL_HELVETICA, 15);
    fl_font(FL_HELVETICA, 30);

    for (i=0;i<9;i++)
    {
        for (j=0;j<9;j++)
        {
            if (grillin.table[j+9*i]==0)
            {
                fl_draw(" ",X_ZONE+15 +j*50, Y_ZONE+35 +i*50);
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

