#ifndef GEOMETRIE_H_INCLUDED
#define GEOMETRIE_H_INCLUDED
#include<math.h>
#include<stdio.h>

typedef struct Point Point;
struct Point
{
    double x;
    double y;
    double z;
};

typedef struct Matrice4 Matrice4;
struct Matrice4
{
    double m[4][4];
};

typedef struct Ligne Ligne;
struct Ligne
{
    Point P;
    Point Q;
};


void afficher_point(Point point);

#endif // GEOMETRIE_H_INCLUDED
