#ifndef MAILLE_H_INCLUDED
#define MAILLE_H_INCLUDED

#include "geometrie.h"
//#include "GLbasic.h"

#define EPSILON 0.00001

/*
    Les paramètres de la fonction afficher_maille :
    Maille maille, int nb_x (nombre de fois qu on représente la maile selon x), int nb_y, int nb_z, double espace // entre atomes

*/
/*
const Couleur couleurs[13] =
{
    {150,190,250}, // Bleu clair
    {50,50,200},   // Bleu foncé
    {100,250,140}, // Vert clair
    {20,150,50},   // Vert foncé
    {200,200,20},  // Jaune
    {250,150,20},  // Orange
    {250,150,150}, // Rose
    {250, 50, 50}, // Rouge
    {180, 50, 220}, // Violet
    {150, 100, 50}, // Marron
    {220,220,220}, // Blanc
    {120,120,120}, // Gris
    {20,20,20} // Noir
};
*/
typedef struct Atome_Type Atome_Type;
struct Atome_Type
{
    char symbole[6];
    int numero_atomique;
    double rayon_ionique;
    int index_couleur; // donne la couleur grace au tableau de passage
};

typedef struct Atome Atome;
struct Atome
{
    Point position;
    int type;
};

typedef struct Maille Maille;
struct Maille
{
    int nb_atomes;
    int nb_type_atomes;
    Atome_Type* types;
    Atome* atomes;

    double alpha;
    double beta;
    double gamma;
    double a;
    double b;
    double c;

//    Couleur couleur_trait;
};

int egalite(Point A, Point B);

#endif // MAILLE_H_INCLUDED
