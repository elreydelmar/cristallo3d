#ifndef MAILLE_H_INCLUDED
#define MAILLE_H_INCLUDED

#include "geometrie.h"
#include "GLbasic.h"

#define EPSILON 0.00001

/*
    * Les paramètres de la fonction afficher_maille :
    Maille maille, int nb_x, /* nombre de fois qu on représente la maile selon x), int nb_y, int nb_z, double espace // entre atomes

*/
typedef struct Atome_Type Atome_Type;
struct Atome_Type
{
    char symbole[6];
    int numero_atomique;
    double rayon_ionique;
    Couleur couleur;
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
};

int egalite(Point A, Point B);

#endif // MAILLE_H_INCLUDED
