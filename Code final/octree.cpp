#include "octree.h"

int position_octree(Point origine, Point M) // preferentiel dans l inferieur
{
    int retour = 0;
    if(origine.x < M.x)
        retour += 4;
    if(origine.y < M.y)
        retour += 2;
    if(origine.z < M.z)
        retour += 1;

    return retour;
}

Octree* nouv_element(Atome M)
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

int egalite(Point A, Point B)
{
    Point diff = sub_pts(A,B);
    if(norme(diff) < EPSILON)
        return 1;
    else
        return 0;
}

int ajouter_a_l_affichage(L_affiche* l, Atome a)
{
    if(*l == NULL)
    {
        *l = nouv_element(a);
        return 1;
    }
    else if(egalite(a.position, (*l)->M.position))
        return 0;
    else
    {
        int fils = position_octree((*l)->M.position, a.position);
        return ajouter_a_l_affichage(&((*l)->fils[fils]), a);
    }
}

void vider_octree(Octree* l)
{
    if(l != NULL)
    {
        int i;
        for(i=0; i<8; i++)
            vider_octree(l->fils[i]);
        free(l);
    }
}
