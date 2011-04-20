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
    Point M;
    Octree* fils[8];
};
typedef Octree* L_affiche;

int position_octree(Point origine, Point M);

// Nouvelle liste d affichage
L_affiche new_l_affiche();

// Ajout (retourne booleen pour ajoute ou non)
int ajouter_a_l_affichage(L_affiche* l, Atome a);
/*
    Si NULL, on le cree, on renvoie 1
    si == , on renvoie 0,
    sinon, on prend les parametres de la zone
*/

// vider
void vider_l_affichage(L_affiche l);

#endif // OCTREE_H_INCLUDED
