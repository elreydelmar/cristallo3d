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
    int i;
    if(a.type == 1)
    {
        i=0;
    }
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

int fusionner_arbre(Octree* a_ajouter, Octree** resultat)
{
    if(a_ajouter == NULL)
        return 0;
    int r = ajouter_a_l_affichage(resultat, a_ajouter->M);
    int i;
    for(i=0; i<8; i++)
        r |= fusionner_arbre(a_ajouter->fils[i], resultat);
    free(a_ajouter);

    return r;
}

Octree* supp_octree(Octree* o, double min_x, double min_y, double min_z, double max_x, double max_y, double max_z)
{
    if(o != NULL)
    {
        int suppression[9] = {0};
        int i;
        if(o->M.position.x < min_x)
        {
            suppression[8] = 1;
            for(i=0; i<4; i++)
                suppression[i] = 1;
        }
        else if(o->M.position.x > max_x)
        {
            suppression[8] = 1;
            for(i=4; i<8; i++)
                suppression[i] = 1;
        }

        if(o->M.position.y < min_y)
        {
            suppression[8] = 1;
                suppression[0] = 1;
                suppression[1] = 1;
                suppression[4] = 1;
                suppression[5] = 1;
        }
        else if(o->M.position.y > max_y)
        {
            suppression[8] = 1;
                suppression[2] = 1;
                suppression[3] = 1;
                suppression[6] = 1;
                suppression[7] = 1;
        }

        if(o->M.position.z< min_z)
        {
            suppression[8] = 1;
            for(i=0; i<8; i+=2)
                suppression[i] = 1;
        }
        else if(o->M.position.z > max_z)
        {
            suppression[8] = 1;
            for(i=1; i<8; i+=2)
                suppression[i] = 1;
        }

        Octree* fils[8];
        for(i=0; i<8; i++)
        {
            if(suppression[i])
            {
                vider_octree(o->fils[i]);
                fils[i] = NULL;
            }
            else
                fils[i] = supp_octree(o->fils[i], min_x, min_y, min_z, max_x, max_y, max_z);
        }

        if(suppression[8])
        {
            o->fils[0] = NULL;
            for(i=1;i<8;i++)
            {
                fusionner_arbre(fils[i], &fils[0]);
                o->fils[i] = NULL;
            }
            vider_octree(o);
            return fils[0];
        }
        else
        {
            for(i=0; i<8; i++)
                o->fils[i] = fils[i];
            return o;
        }

    }
    return NULL;
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
