#ifndef CONST_FENETRE_H_INCLUDED
#define CONST_FENETRE_H_INCLUDED

#define WIDTH 1020
#define HEIGHT 700

#define WIDTH_COLONNE 320

#define HEIGHT_MIN 500 //prévision
#define WIDTH_MIN WIDTH_COLONNE+100 //prévision


#define Y_ESPACE 10

#define Y_CAMERA Y_ESPACE
#define HEIGHT_CAMERA 292

#define Y_MAILLE 2*Y_ESPACE+HEIGHT_CAMERA
#define HEIGHT_MAILLE 250

#define HEIGHT_RETRO 100
#define HEIGHT_DIST 110

#define Y_VALEUR 3*Y_ESPACE+HEIGHT_CAMERA+HEIGHT_MAILLE
#define HEIGHT_VALEUR 170

#define ALINEA_MENU 20
#define WIDTH_MENU WIDTH_COLONNE - 2*ALINEA_MENU

#define ALINEA_BLOC 20
#define WIDTH_BLOC WIDTH_MENU-2*ALINEA_BLOC

#define Y_CHAR 15
// Bas du menu
#define ECART_BOUTON 10
#define TAILLE_BOUTON 80
#define Y_OTHER 570

// Contexte OpenGL
const double ratio = (double)(WIDTH - WIDTH_COLONNE)/(double)HEIGHT;

#endif // CONST_FENETRE_H_INCLUDED
