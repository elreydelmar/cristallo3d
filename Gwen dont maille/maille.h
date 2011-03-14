#ifndef MAILLE_H_INCLUDED
#define MAILLE_H_INCLUDED

#include "geometrie.h"

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
    Point* atomes; /*C est un tableau de  taille nbatones que arnaud a défini*/


};


#endif // MAILLE_H_INCLUDED
