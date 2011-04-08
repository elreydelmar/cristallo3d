#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

#include <stdlib.h>

enum Token
{
    REEL, OP, VAR
};
typedef enum Token Token;

enum Op
{
    PLUS, MOINS, FOIS, DIVISE
};
typedef enum Op Op;

enum Var
{
    X,Y,Z
};
typedef enum Var Var;

typedef union Valeur Valeur;
union Valeur
{
    Var variable;
    Op operateur;
    double reel;
};

typedef struct Arbre Arbre;
struct Arbre
{
    Token type;
    Valeur valeur;
    Arbre* fils_g;
    Arbre* fils_d;
};

int poids(Arbre* element);
Arbre* creer_element(Token type, Valeur val);
Arbre* ajouter_element(Arbre* arbre, Arbre* element); // A tester
void vider_arbre(Arbre* arbre);

double calcul_arbre(Arbre* arbre, double val_x, double val_y, double val_z, int* erreur);

#endif // ARBRE_H_INCLUDED
