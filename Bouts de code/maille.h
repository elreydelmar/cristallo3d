#ifndef MAILLE_H_INCLUDED
#define MAILLE_H_INCLUDED

#include "geometrie.h"

typedef struct Atome Atome;
struct Atome
{
    char element[6];
    Point position; // attention , a adapter en fonction a,b,c alpha,beta,gamma
};

typedef struct Maille Maille;
struct Maille
{
    double alpha;
    double beta;
    double gamma;
    double a;
    double b;
    double c;
    int nbatomes;
    Atome* atomes; /*C est un tableau de taille nbatomes de type Point que Arnaud a défini*/
};


#endif // MAILLE_H_INCLUDED
