#include "lignes.h"

L_ligne* add_to_l_ligne(L_ligne* liste, Arbre* x, Arbre* y, Arbre* z)
{
    if(x == NULL || y == NULL || z == NULL)
    {
        vider_arbre(x);
        vider_arbre(y);
        vider_arbre(z);
        return liste;
    }

    L_ligne* nouveau = (L_ligne*) malloc(sizeof(L_ligne*));
        nouveau->x = x;
        nouveau->y = y;
        nouveau->z = z;
        nouveau->queue = liste;

    return nouveau;
}

void vider_l_ligne(L_ligne* liste)
{
    L_ligne* buff1 = liste;
    L_ligne* buff2;
    while(buff1 != NULL)
    {
        buff2 = buff1->queue;
        vider_arbre(buff1->x);
        vider_arbre(buff1->y);
        vider_arbre(buff1->z);
        free(buff1);
        buff1 = buff2;
    }
}
