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

L_affiche supp_inf_x(L_affiche l, double x)
{

}

L_affiche supp_sup_x(L_affiche l, double x)
{

}

L_affiche supp_sup_y(L_affiche l, double y)
{

}

L_affiche supp_inf_z(L_affiche l, double z)
{

}

L_affiche supp_sup_z(L_affiche l, double z)
{

}
