// u2-dessin.cpp
// Declarations externes - inclusion des fichiers d'entete
// Librairies standards
#include <iostream>         // cin, cout, ...
// Librairies fltk
#include <FL/Fl.H>
#include <FL/fl_draw.H>     // fonctions de dessin
// Ajouts pour mastermind
#include <string.h>                 // ajoute pour le mastermind pour les fonctions strcpy ...
#include <FL/Fl_BMP_Image.H>        // ajoute la gestion des images externes de format bmp
//#include <FL/Fl_JPEG_Image.H>       // ajoute la gestion des images externes de format jpeg
//#include <FL/Fl_PNG_Image.H>       // ajoute la gestion des images externes de format png
// Programmes locaux
#include "u1-interface.h"
#include "u2-dessin.h"
#include "u4-fonctions.h"

// Declaration pour utiliser iostream
using namespace std;

// DessinerZone
void ZoneDessinDessinerCB( Fl_Widget* widget, void* data )
{
    int i, j, k;
    // On efface toute la zone ( en dessinant dessus un rectangle plein, noir )
    fl_color(FL_BLACK);
    fl_rectf(X_ZONE, Y_ZONE, L_ZONE, H_ZONE);

    // On dessine la liste des 6 pions disponibles en haut de la zone
    ChoisirCouleurPion(0) ;
    fl_pie( X_ZONE + 40, Y_ZONE + 40,  2*RAYON_PION,  2*RAYON_PION,  0, 360 );
    ChoisirCouleurPion(1) ;
    fl_pie( X_ZONE + 2*40, Y_ZONE + 40,  2*RAYON_PION,  2*RAYON_PION,  0, 360 );
    ChoisirCouleurPion(2) ;
    fl_pie( X_ZONE + 3*40, Y_ZONE + 40,  2*RAYON_PION,  2*RAYON_PION,  0, 360 );
    ChoisirCouleurPion(3) ;
    fl_pie( X_ZONE + 4*40, Y_ZONE + 40,  2*RAYON_PION,  2*RAYON_PION,  0, 360 );
    ChoisirCouleurPion(4) ;
    fl_pie( X_ZONE + 5*40, Y_ZONE + 40,  2*RAYON_PION,  2*RAYON_PION,  0, 360 );
    ChoisirCouleurPion(5) ;
    fl_pie( X_ZONE + 6*40, Y_ZONE + 40,  2*RAYON_PION,  2*RAYON_PION,  0, 360 );

    // On dessine les cases de jeu et les cases de resultats/aides
    for (i=0; i <=9; i++)
    {
        for (j=0; j<=3; j++) // Dessin des cases de jeu
        {
            //Dessin des cases de jeu
            ChoisirCouleurPion(gDonnees.TableauJeu[i][j]);
            fl_pie( X_ZONE + 2*40 + j * 40, Y_ZONE + 3*40 + i * 40,  2*RAYON_PION,  2*RAYON_PION,  0, 360 );
        }

        k=0;
        while( k < gDonnees.BienPlaces[i] ) // Dessin des pions de bonne couleur bien places
        {
            ChoisirCouleurResultat(1);
            fl_pie( X_ZONE + 6*40 + RAYON_PION/2 + k * 40, Y_ZONE + 3*40 + RAYON_PION/2 + i * 40,  RAYON_PION,  RAYON_PION,  0, 360 );
            k++;
        }
        while( k < gDonnees.BienPlaces[i] + gDonnees.MalPlaces[i] ) // Dessin des pions de bonne couleur mal places
        {
            ChoisirCouleurResultat(0);
            fl_pie( X_ZONE + 6*40 + RAYON_PION/2 + k * 40, Y_ZONE + 3*40 + RAYON_PION/2 + i * 40,  RAYON_PION,  RAYON_PION,  0, 360 );
            k++;
        }
        while( k < NB_PIONS ) // Dessin des pions de mauvaise couleur
        {
            ChoisirCouleurResultat(-1);
            fl_pie( X_ZONE + 6*40 + RAYON_PION/2 + k * 40, Y_ZONE + 3*40 + RAYON_PION/2 + i * 40,  RAYON_PION,  RAYON_PION,  0, 360 );
            k++;
        }

    }

    if (gDonnees.GameOver != 0) // Dessin de la solution si jeu fini (perdu ou gagne)
    {
        for(i=0;i<=3;i++) // determination de la couleur de chaque pion de la solution et affichage
        {
            ChoisirCouleurPion(gDonnees.Solution[i]);
            fl_pie( X_ZONE + 2*40 + i * 40, Y_ZONE + 14 * 40,  2*RAYON_PION,  2*RAYON_PION,  0, 360 );
        }
    }

    // Tout le code ci-dessous est optionnel

    // Optionnel : Indicateur du pion selectionne
    if(gDonnees.PionCourant != -1)
    {
        fl_color(FL_WHITE);
        fl_pie( X_ZONE + 40 + 15 + gDonnees.PionCourant * 40, Y_ZONE + 2 * 40 + 5, 10, 10,  0, 360 );
    }

    // Optionnel : Marquage de la ligne de jeu en cours
    fl_color(FL_WHITE);
    fl_pie(X_ZONE + 40 + 25, Y_ZONE + 3*40+ 15 + gDonnees.LigneCourante*40, 10, 10,  0, 360 );

    // Optionnel : Message de GameOver
    char TexteGagnePerdu[30];

    if (gDonnees.GameOver != 0)
    {
        if (gDonnees.GameOver == 2)
            strcpy(TexteGagnePerdu,"Gagne !");
        else
            strcpy(TexteGagnePerdu,"Perdu !");
        fl_font(FL_HELVETICA_BOLD, 20);
        fl_color(FL_WHITE);
        fl_draw(TexteGagnePerdu, X_ZONE + 3 * 40 + 5, Y_ZONE + 16 * 40 - 15);
    }

    // Optionnel : Titre du jeu
    char TexteTitre[30];
    fl_font(FL_HELVETICA_BOLD, 28);
    fl_color(FL_RED);
    strcpy(TexteTitre,"PhelMasterMind");
    fl_draw(TexteTitre, X_ZONE + 40 + 22, Y_ZONE + 28);

    // Optionnel : lignes de separation des zones de jeu
    fl_color(FL_DARK3);
    fl_line(X_ZONE,Y_ZONE+2*40+20, X_ZONE+10*40-1, Y_ZONE+2*40+20);
    fl_line(X_ZONE,Y_ZONE+13*40+20, X_ZONE+10*40-1, Y_ZONE+13*40+20);

    // Optionnel : affichage du logo phelma
    Fl_BMP_Image ImageLogoPhelma("media/logophelma.bmp") ;
    //Fl_JPEG_Image ImageLogoPhelma("media/logophelma.jpg") ;
    ImageLogoPhelma.draw(X_ZONE+6*40+30, Y_ZONE + 13*40+32);
}

// 2 procedures deja faites fournies pour le projet Mastermind : ChoisirCouleurPion et ChoisirCouleurResultat

// Fixer la couleur des pions de jeu Mastermind
void ChoisirCouleurPion(int Pion) // Correspondance numero de pion avec couleur associee, sert au dessin des pions du jeu
{
    switch (Pion) {
        // -1 : case vide pour placer un pion de couleur
        case -1 : fl_color(FL_DARK2); break;
        case 0 : fl_color(FL_CYAN); break;
        case 1 : fl_color(FL_BLUE); break;
        case 2 : fl_color(FL_RED); break;
        case 3 : fl_color(FL_YELLOW); break;
        case 4 : fl_color(FL_GREEN); break;
        case 5 : fl_color(FL_MAGENTA); break;
    }
}

// Fixer la couleur des pions de resultats-aides Mastermind
void ChoisirCouleurResultat(int Resultat) // Couleurs pion place(1), mal place(0), pas place (-1), sert au dessin des pions resultats-aides
{
    switch (Resultat) {
        case -1 : fl_color(FL_DARK3); break;    // -1 : pas place : gris fonce
        case 0 : fl_color(FL_WHITE); break;     // 0 : bonne couleur, mal place : blanc
        case 1 : fl_color(FL_RED); break;       // 1 : bonne couleur, bien place : rouge
    }
}
