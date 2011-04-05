#include "fichier.h"

int main ()
{
    Maille m;
    int retour = charger_maille("1000001.cif",&m);
    if(retour == ERR_OUVERTURE_FICHIER)
        printf("Erreur a l ouverture du fichier\n");
    printf ("Parametre a : %lf\n",m.a);

    return 0;
}
