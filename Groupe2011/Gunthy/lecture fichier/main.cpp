#include "automate.h"

int main ()
{
    Maille m;
    int retour = charger_maille("1000001.cif",&m);
    if(retour == ERR_OUVERTURE_FICHIER)
        printf("Erreur a l ouverture du fichier\n");
    printf ("Parametre a : %lf\n",m.a);
    printf ("Parametre b : %lf\n",m.b);
    printf ("Parametre c : %lf\n",m.c);

    return 0;
}
