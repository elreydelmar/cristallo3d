#include<stdio.h>
#include<stdlib.h>
#include "arbre.h"

typedef struct L_calcul L_calcul;
struct L_calcul
{
    Arbre *x;
    Arbre *y;
    Arbre *z;
L_calcul* suivant;}; //structure contenant 3 arbres

L_calcul* creer_liste(void)
{
     return NULL;
}

int est_vide(L_calcul* liste) //teste si la liste est vide
{
    if(liste==NULL)
    {return 1;
    }
    else
    {return 0;
    }
}

L_calcul* effacerliste(L_calcul* liste)
{
    L_calcul* var = liste;
    L_calcul* varsuivant;
    while(var != NULL);
    {
        /* On stocke l'élément suivant pour pouvoir ensuite avancer */
        varsuivant = var->suivant;
        /* On efface l'élément courant */
        free(var);
        /* On avance d'une case */
        var = varsuivant;
         return NULL;

    }
}

L_calcul* ajouterEnTete(L_calcul* liste, Arbre *x, Arbre *y, Arbre *z)
{
    /* On crée un nouvel élément */
    L_calcul* nouvelElement = malloc(sizeof(L_calcul));

    /* On assigne la valeur au nouvel élément */
    nouvelElement->x = x;
    nouvelElement->y = y;
    nouvelElement->z = z;

    /* On assigne l'adresse de l'élément suivant au nouvel élément */
    nouvelElement->suivant = liste;

    /* On retourne la nouvelle liste, i.e. le pointeur sur le premier élément */
    return nouvelElement;
}

int main()
{
    return 0;
}
