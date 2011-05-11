#ifndef OCTREE_H_INCLUDED
#define OCTREE_H_INCLUDED

#include "geometrie.h"
#include <stdlib.h>

#define EPSILON 0.00001

/*
          -z            +z
  -y   0   |   4     2   |   6

  +y   1   |   5     3   |   7
      -x      +x    -x      +x

*/

typedef struct Atome Atome;
struct Atome
{
    Point position;
    int type;
};

struct _Octree
{
    Atome M;
    struct _Octree* fils[8];
};
typedef struct _Octree Octree;

int position_octree(Point origine, Point M);

// Nouvelle liste d affichage
Octree* new_octree();

// Ajout (retourne booleen pour ajoute ou non)
Octree* nouv_element(Atome M);
int ajouter_a_l_affichage(Octree** l, Atome a);
/*
    Si NULL, on le cree, on renvoie 1
    si == , on renvoie 0,
    sinon, on prend les parametres de la zone
*/
int egalite(Point A, Point B);
// vider
void vider_l_affichage(Octree* l);

// Suppression
// TODO
Octree* supp_inf_x(Octree* l, double x); // Inférieur strict
Octree* supp_sup_x(Octree* l, double x); // Supérieur strict
Octree* supp_sup_y(Octree* l, double y);
Octree* supp_inf_z(Octree* l, double z);
Octree* supp_sup_z(Octree* l, double z);

// Camera
// TODO 2
//void affiche(Octree* l, Camera c, int reponse[]); // reponse de taille 9, le 8 est l atome present

#endif // OCTREE_H_INCLUDED
