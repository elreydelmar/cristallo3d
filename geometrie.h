#ifndef GEOMETRIE_H_INCLUDED
#define GEOMETRIE_H_INCLUDED

#include <math.h>
#include <stdio.h>  // Utile a la fonction de test

/// Les types

typedef struct Point Point;
struct Point
{
    double x;
    double y;
    double z;
};

/*
    Matrice :
    (0,0) (0,1) (0,2) (0,3)
    (1,0)  ...
    (2,0)
    (3,0)
*/

typedef struct Matrice4 Matrice4;
struct Matrice4
{
    double m[4][4];
};
typedef Matrice4 Matrice; // Matrice est par defaut par 4

typedef struct Ligne Ligne;
struct Ligne
{
    Point P;
    Point Q;
};

/// Les fonctions

// Fonctions de test
void afficher_point(Point point);
void afficher_matrice(Matrice4 M);
void afficher_ligne (Ligne l);

// Fonctions Vectorielles
Point add_pts (Point P, Point Q); // Somme
Point sub_pts (Point P, Point Q); // Difference
Point mult_scal_pts (double k, Point P); // multiplication d'un point par un scalaire
double prod_scal (Point P, Point Q); // Produit scalaire
Point prod_vect (Point P, Point Q); // Produit vectoriel
double norme (Point P);
void normer (Point* P);

// Fonctions Matricielles
void set_null(Matrice4* M);
void set_id(Matrice4* M);
Matrice4 add_mat(Matrice4 M, Matrice4 N);   // Somme
Matrice4 sub_mat(Matrice4 M, Matrice4 N);   // Difference
Matrice4 mult_mat(Matrice4 M, Matrice4 N);  // Produit
double det(Matrice4 M); // determinant
double cofacteur(Matrice4 M, int i, int j); // donne la valeur dans la comatrice A FINIR
Point mult_mat_point (Matrice4 M, Point P); // Produit matrice point

#endif // GEOMETRIE_H_INCLUDED
