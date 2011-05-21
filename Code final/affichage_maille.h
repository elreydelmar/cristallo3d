#ifndef AFF_MAILLE_H
#define AFF_MAILLE_H

#include "maille.h"
#include "octree.h"

void test_affichage(int affiche[9], Camera* C, Octree* O);

void afficher_atome(Atome A, Atome_Type T);

Matrice passage(double a,double b,double c,double alpha,double beta,double gamma);

void afficher_contour(Maille* M, Matrice P);

void afficher_les_atomes (Maille* M, Matrice P);
void _afficher_les_atomes(Maille* M, Octree* O, Matrice P);

void afficher_maille (Maille* M);

#endif
