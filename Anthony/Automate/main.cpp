#include "automate.h"

void afficher_arbre(Arbre* a);
void test_arbre();

int main ()
{
    Maille m;
    int retour = charger_maille("1000001.cif",&m);
    if(retour == ERR_OUVERTURE_FICHIER)
        printf("Erreur a l ouverture du fichier\n");
    printf ("Parametre a : %lf\n",m.a);
    printf ("Parametre b : %lf\n",m.b);
    printf ("Parametre c : %lf\n\n",m.c);

    printf ("Parametre alpha : %lf\n",m.alpha);
    printf ("Parametre beta : %lf\n",m.beta);
    printf ("Parametre gamma : %lf\n",m.gamma);

    return 0;
}

void test_arbre()
{
    Token objet;
    Valeur val;
    Arbre* a = NULL;


    objet = REEL;
    val.reel = 1.;
    a = ajouter_element(a, creer_element(objet, val));

    objet = OP;
    val.operateur = PLUS;
    a = ajouter_element(a, creer_element(objet, val));

    objet = REEL;
    val.reel = 2.;
    a = ajouter_element(a, creer_element(objet, val));

    afficher_arbre(a);

    int erreur = 0;
    printf("\n\n%lf", calcul_arbre(a,0.,0.,0., &erreur));

    vider_arbre(a);
}


void afficher_arbre(Arbre* a)
{
    if(a == NULL)
        return;

    switch(a->type)
    {
        case VAR :
            switch(a->valeur.variable)
            {
                case X : printf("x");  break;
                case Y : printf("y");  break;
                case Z : printf("z");  break;
            }
        break;

        case OP:
            printf("(");
            afficher_arbre(a->fils_g);
            switch(a->valeur.operateur)
            {
                case PLUS : printf("+");  break;
                case MOINS : printf("-");  break;
                case FOIS : printf("*");  break;
                case DIVISE : printf("/");  break;
            }
            afficher_arbre(a->fils_d);
            printf(")");
        break;

        case REEL :
            printf("%lf", a->valeur.reel);
        break;
    }
}
