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

typedef struct Octree Octree;
struct Octree
{
    Atome M;
    Octree* fils[8];
};
typedef Octree* L_affiche;

int position_octree(Point origine, Point M);
int egalite(Point A, Point B);

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
int fusionner_arbre(Octree* a_ajouter, Octree** resultat);
// vider
void vider_octree(Octree* l);

#endif // OCTREE_H_INCLUDED
