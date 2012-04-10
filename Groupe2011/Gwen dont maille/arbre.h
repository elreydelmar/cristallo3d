#ifndef ARBRE_H_INCLUDED
#define ARBRE_H_INCLUDED

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

#endif // ARBRE_H_INCLUDED
