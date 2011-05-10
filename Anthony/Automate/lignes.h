#ifndef LIGNES_H_INCLUDED
#define LIGNES_H_INCLUDED

#include "arbre.h"
#include "maille.h"

typedef struct L_ligne L_ligne;
struct L_ligne
{
    Arbre* x;
    Arbre* y;
    Arbre* z;

    L_ligne* queue;
};

enum Label
{
    LABEL, SYMBOL, FRACT_X, FRACT_Y, FRACT_Z, NONE
};
typedef enum Label Label;

typedef struct L_label L_label;
struct L_label
{
    Label label;
    L_label* queue;
};

typedef struct L_Atome L_Atome;
struct L_Atome
{
    Atome atome;
    L_Atome* queue;
};

typedef struct L_Atome_Type L_Atome_Type;
struct L_Atome_Type
{
    Atome_Type atome_type;
    L_Atome_Type* queue;
};

L_ligne* add_to_l_ligne(L_ligne* liste, Arbre* x, Arbre* y, Arbre* z);
void vider_l_ligne(L_ligne* liste);

L_label* add_label(L_label* liste, Label l);
void vider_l_label(L_label* liste);

L_Atome* add_atome(L_Atome* liste, Atome a);
void vider_l_atome(L_Atome* liste);

L_Atome_Type* add_atome(L_Atome_Type* liste, Atome_Type t);
void vider_l_atome_type(L_Atome_Type* liste);

// Faire une fonction creer liste d atomes
// et une fonction de transposition au tableau avec suppression des doublons

#endif // LIGNES_H_INCLUDED
