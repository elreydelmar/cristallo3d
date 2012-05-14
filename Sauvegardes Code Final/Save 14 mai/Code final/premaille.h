#ifndef PREMAILLE_H_INCLUDED
#define PREMAILLE_H_INCLUDED

#include <stdlib.h>
#include <string.h>
#include "type_ligne.h"
#include "arbre.h"

// Les types
struct _L_int
{
    int entier;
    struct _L_int* suivant;
};
typedef struct _L_int L_int;

struct _L_ligne
{
    Arbre* x;
    Arbre* y;
    Arbre* z;

    struct _L_ligne* queue;
};
typedef struct _L_ligne L_ligne;

struct _L_Pre_Atome
{
    char label[10];
    double x;
    double y;
    double z;

    struct _L_Pre_Atome* queue;
};
typedef struct _L_Pre_Atome L_Pre_Atome;

struct _Premaille
{
    double a;
    double b;
    double c;

    double alpha;
    double beta;
    double gamma;

    L_ligne* lignes;
    L_Pre_Atome* atomes;
};
typedef struct _Premaille Premaille;

// Les fonctions
void add_l_int(L_int** l, int entier); // ajoute en fin
void vider_l_int(L_int** liste);

void add_to_l_ligne(L_ligne** liste, Arbre* x, Arbre* y, Arbre* z);
void concat(L_ligne** liste, L_ligne* a_ajouter);
void vider_l_ligne(L_ligne* liste);

void add_to_l_pre_atome(L_Pre_Atome** liste, char label[], double x, double y, double z);
void vider_l_pre_atome(L_Pre_Atome* liste);

int type_loop(L_int* l); // 0 pour inutile, 1 pour symmetry, 2 pour le reste

L_ligne* symetries_translation();

#endif // PREMAILLE_H_INCLUDED
