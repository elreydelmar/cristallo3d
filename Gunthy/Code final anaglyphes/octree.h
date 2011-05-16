#ifndef OCTREE_H_INCLUDED
#define OCTREE_H_INCLUDED

#include "geometrie.h"
#include "maille.h"
#include <stdlib.h>

/*
          -z            +z
  -y   0   |   4     2   |   6

  +y   1   |   5     3   |   7
      -x      +x    -x      +x

*/

typedef struct Octree Octree;
struct Octree
{
    Atome M;
    Octree* fils[8];
};
typedef Octree* L_affiche;

int position_octree(Point origine, Point M);

// Nouvelle liste d affichage
L_affiche new_l_affiche();

// Ajout (retourne booleen pour ajoute ou non)
Octree* nouv_element(Atome M);
int ajouter_a_l_affichage(L_affiche* l, Atome a);
/*
    Si NULL, on le cree, on renvoie 1
    si == , on renvoie 0,
    sinon, on prend les parametres de la zone
*/

// vider
void vider_l_affichage(L_affiche l);

// Suppression
// TODO
L_affiche supp_inf_x(L_affiche l, double x); // Inférieur strict
L_affiche supp_sup_x(L_affiche l, double x); // Supérieur strict
L_affiche supp_sup_y(L_affiche l, double y);
L_affiche supp_inf_z(L_affiche l, double z);
L_affiche supp_sup_z(L_affiche l, double z);

// Camera
// TODO 2
//void affiche(L_affiche l, Camera c, int reponse[]); // reponse de taille 9, le 8 est l atome present

#endif // OCTREE_H_INCLUDED
