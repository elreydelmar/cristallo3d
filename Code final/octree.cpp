#include "Octree.h"

int position_octree(Point origine, Point M)
{
    int retour = 0;
    if(origine.x < M.x)
        retour += 4;
    if(origine.y < M.y)
        retour += 1;
    if(origine.z < M.z)
        retour += 2;

    return retour;
}

Octree* nouv_element(Point M)
{
    Octree* retour = (Octree*) malloc(sizeof(Octree));
        retour->M = M;
    int i;
    for(i=0; i<8; i++)
        retour->fils[i] = NULL;

    return retour;
}

L_affiche new_l_affiche()
{
    return NULL;
}
int ajouter_a_l_affichage(L_affiche* l, Atome a)
{
    if(*l == NULL)
    {
        *l = nouv_element(a.position);
        return 1;
    }
    else if(egalite(a.position, (*l)->M))
        return 0;
    else
    {
        int fils = position_octree((*l)->M, a.position);
        return ajouter_a_l_affichage(&((*l)->fils[fils]), a);
    }
}

void vider_l_affichage(L_affiche l)
{
    if(l != NULL)
    {
        int i;
        for(i=0; i<8; i++)
            vider_l_affichage(l->fils[i]);
        free(l);
    }
}
