#ifndef LIGNES_H_INCLUDED
#define LIGNES_H_INCLUDED

#include "arbre.h"

typedef struct L_ligne L_ligne;
struct L_ligne
{
    Arbre* x;
    Arbre* y;
    Arbre* z;

    L_ligne* queue;
};

L_ligne* add_to_l_ligne(L_ligne* liste, Arbre* x, Arbre* y, Arbre* z);
void vider_l_ligne(L_ligne* liste);

// Faire une fonction creer liste d atomes
// et une fonction de transposition au tableau avec suppression des doublons

#endif // LIGNES_H_INCLUDED
