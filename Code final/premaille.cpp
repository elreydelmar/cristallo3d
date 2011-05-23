#include "premaille.h"

void add_l_int(L_int** l, int entier)
{
    if(*l == NULL)
    {
        L_int* nouv = (L_int*) malloc(sizeof(L_int));
        nouv->entier = entier;
        nouv->suivant = NULL;
        *l = nouv;
    }
    else
        add_l_int(&((*l)->suivant), entier);
}

void concat(L_ligne** liste, L_ligne* a_ajouter)
{
    if(*liste == NULL)
    {
        *liste = a_ajouter;
    }
    else
    {
        concat(&((*liste)->queue), a_ajouter);
    }
}

void vider_l_int(L_int** liste)
{
    L_int* buff = NULL;
    while(*liste != NULL)
    {
        buff = (*liste)->suivant;
        free(*liste);
        *liste = buff;
    }
}

void add_to_l_ligne(L_ligne** liste, Arbre* x, Arbre* y, Arbre* z)
{
    if(x == NULL || y == NULL || z == NULL)
    {
        vider_arbre(x);
        vider_arbre(y);
        vider_arbre(z);
    }

    L_ligne* nouveau = (L_ligne*) malloc(sizeof(L_ligne));
        nouveau->x = x;
        nouveau->y = y;
        nouveau->z = z;
        nouveau->queue = *liste;

    *liste = nouveau;
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

void add_to_l_pre_atome(L_Pre_Atome** liste, char label[], double x, double y, double z)
{
    L_Pre_Atome* nouveau = (L_Pre_Atome*) malloc(sizeof(L_Pre_Atome));
        nouveau->x = x;
        nouveau->y = y;
        nouveau->z = z;
        strcpy(nouveau->label, label);
        nouveau->queue = *liste;
    *liste = nouveau;
}

void vider_l_pre_atome(L_Pre_Atome* liste)
{
    L_Pre_Atome* buff1 = liste;
    L_Pre_Atome* buff2;
    while(buff1 != NULL)
    {
        buff2 = buff1->queue;
        free(buff1);
        buff1 = buff2;
    }
}

int type_loop(L_int* l)
{
    L_int* buff = l;
    int trouve = 0;
    while(buff != NULL)
    {
        if(buff->entier == SYMMETRY)
            return 1;
        if(buff->entier == LABEL)
            trouve++;
        if(buff->entier == FX)
            trouve++;
        if(buff->entier == FY)
            trouve++;
        if(buff->entier == FZ)
        {
            if(trouve == 3)
                return 2;
        }

        buff = buff->suivant;
    }
    return 0;
}

L_ligne* symetries_translation()
{
    L_ligne* retour = NULL;
    Token t;
    Valeur v;
    Arbre* x;
    Arbre* y;
    Arbre* z;
        x = NULL;
            t = VAR;
            v.variable = X;
            x = ajouter_element(x, creer_element(t,v));
            t = OP;
            v.operateur = PLUS;
            x = ajouter_element(x, creer_element(t,v));
            t = REEL;
            v.reel = 1.;
            x = ajouter_element(x, creer_element(t,v));
        y = NULL;
            t = VAR;
            v.variable = Y;
            y = ajouter_element(y, creer_element(t,v));
        z = NULL;
            t = VAR;
            v.variable = Z;
            z = ajouter_element(z, creer_element(t,v));
    add_to_l_ligne(&retour, x, y, z);

        x = NULL;
            t = VAR;
            v.variable = X;
            x = ajouter_element(x, creer_element(t,v));
        y = NULL;
            t = VAR;
            v.variable = Y;
            y = ajouter_element(y, creer_element(t,v));
            t = OP;
            v.operateur = PLUS;
            y = ajouter_element(y, creer_element(t,v));
            t = REEL;
            v.reel = 1.;
            y = ajouter_element(y, creer_element(t,v));
        z = NULL;
            t = VAR;
            v.variable = Z;
            z = ajouter_element(z, creer_element(t,v));
    add_to_l_ligne(&retour, x, y, z);

        x = NULL;
            t = VAR;
            v.variable = X;
            x = ajouter_element(x, creer_element(t,v));
        y = NULL;
            t = VAR;
            v.variable = Y;
            y = ajouter_element(y, creer_element(t,v));
        z = NULL;
            t = VAR;
            v.variable = Z;
            z = ajouter_element(z, creer_element(t,v));
            t = OP;
            v.operateur = PLUS;
            z = ajouter_element(z, creer_element(t,v));
            t = REEL;
            v.reel = 1.;
            z = ajouter_element(z, creer_element(t,v));
    add_to_l_ligne(&retour, x, y, z);


    return retour;
}
