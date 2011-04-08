#include "arbre.h"

int poids(Arbre* element)
{
    if(element == NULL)
        return 0;
    if(element->type == VAR || element->type == REEL)
        return 4;
    else    // Operateur
    {
        if(element->valeur.operateur == FOIS || element->valeur.operateur == DIVISE)
            return 2;
        else
            return 1;
    }
}

Arbre* creer_element(Token type, Valeur val)
{
    Arbre* retour = (Arbre*) malloc(sizeof(Arbre));
        retour->type = type;
        retour->valeur = val;
        retour->fils_g = NULL;
        retour->fils_d = NULL;
    return retour;
}

Arbre* ajouter_element(Arbre* arbre, Arbre* element)
{
    if(arbre == NULL)
        return element;

    // On n est pas a la branche la plus basse
    int poids_courant = poids(arbre);
    int poids_element = poids(element);
    if(poids_courant >= poids_element)  // le cas egal etant possible qu avec des operateurs
    {
        element->fils_g = arbre; // la droite est forcement NULL
        return element;
    }
    else    // On descend d'un etage => forcement a droite ?
    {
        arbre->fils_d = ajouter_element(arbre->fils_d, element);
        return arbre;
    }
}

void vider_arbre(Arbre* arbre)
{
    if(arbre != NULL)
    {
        vider_arbre(arbre->fils_g);
        vider_arbre(arbre->fils_d);

        free(arbre);
    }
}

double calcul_arbre(Arbre* arbre, double val_x, double val_y, double val_z, int* erreur)
{
    if(arbre == NULL)
    {
        *erreur = 1;
        return 0;
    }
    if(*erreur)
        return 0;

    switch(arbre->type)
    {
        case REEL :
            return arbre->valeur.reel;
        case VAR :
            switch(arbre->valeur.variable)
            {
                case X :
                    return val_x;
                case Y :
                    return val_y;
                case Z :
                    return val_z;
            }
        case OP :
            double gauche = calcul_arbre(arbre->fils_g, val_x, val_y, val_z, erreur);
            double droite = calcul_arbre(arbre->fils_d, val_x, val_y, val_z, erreur);
            if(erreur)
                return 0;
            switch(arbre->valeur.operateur)
            {
                case PLUS :
                    return gauche + droite;
                case MOINS :
                    return gauche - droite;
                case FOIS :
                    return gauche * droite;
                case DIVISE :
                    if(droite == 0)
                    {
                        *erreur = 1;
                        return 0;
                    }
                    else
                        return gauche / droite;
            }
    }
}
