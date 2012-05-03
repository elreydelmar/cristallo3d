// u2-dessin.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>         // cin, cout, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_draw.H>     // fonctions de dessin
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

    Fl_JPEG_Image GrilleSudoku("C:\\Users\\Antoine\\Documents\\PHELMA\\Projet info\\kitc-phelma\\GrilleSudokuVide.jpg");

    GrilleSudoku.draw(X_ZONE, Y_ZONE );
}
