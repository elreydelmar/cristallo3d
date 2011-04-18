#include "automate.h"

void test_arbre();
void test_maille();

int main ()
{
    test_maille();

    return 0;
}

void test_maille()
{
    Maille m;
    int retour = charger_maille("1008006.cif",&m);
    if(retour == ERR_OUVERTURE_FICHIER)
        printf("Erreur a l ouverture du fichier\n");
    printf ("Parametre a : %lf\n",m.a);
    printf ("Parametre b : %lf\n",m.b);
    printf ("Parametre c : %lf\n\n",m.c);

    printf ("Parametre alpha : %lf\n",m.alpha);
    printf ("Parametre beta : %lf\n",m.beta);
    printf ("Parametre gamma : %lf\n",m.gamma);

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

